namespace LSAP {

	struct AudioData {

		AudioData(std::wstring outputD = getActiveDevice(), unsigned int sampleRate = 44100, unsigned int nChannels = 1, unsigned int countBlock = 8, unsigned int blockSamples = 512)
			: outputDevice(outputD), sampleRate(sampleRate), nChannels(nChannels), blockCount(countBlock), blockSamples(blockSamples)
		{}

		std::wstring outputDevice;
		unsigned int sampleRate;
		unsigned int nChannels;
		unsigned int blockCount;
		unsigned int blockSamples;

		static std::wstring getActiveDevice() {
			int deviceCount = waveOutGetNumDevs();
			std::vector<std::wstring> devices;
			WAVEOUTCAPS woc;
			for (int i = 0; i < deviceCount; ++i) {
				if (waveOutGetDevCaps(i, &woc, sizeof(WAVEOUTCAPS)) == S_OK) {
					devices.push_back(woc.szPname);
				}
			}
			return devices[0];
		}
	};

	class SoundGenerator
	{
	public:
		SoundGenerator(const AudioData& audioData = AudioData());
		~SoundGenerator();

		void setSynthFunc(const std::function<double(double)>& func);
		void stopSound();
		void generateSound();

		double getTime() {
			return mDeltaTime;
		}

	private:
		void fillOutputBuffer();
		void openAudioDevice();
		void setBlockMemory();
		void countBlock();

		static void CALLBACK waveOutProcWrap(HWAVEOUT hWaveOut, UINT uMsg, unsigned long* dwInstance, DWORD dwParam1, DWORD dwParam2);

	private:
		std::function<double(double)> mUserSynthFunction;

		int mCurrentBlock;
		double mDeltaTime;
		bool mIsRunning;

		std::unique_ptr<WAVEHDR[]> mWaveOutBuffer;
		std::unique_ptr<std::vector<int>[]> mOutputBuffer;

		std::thread mThread;
		std::mutex mSoundGenMutex;
		std::condition_variable mSoundGenCondition;

		std::atomic<unsigned int> mBlockZero;
		std::atomic<double> mTime;


		HWAVEOUT mDevice;
		AudioData mAudioData;
	};
}
