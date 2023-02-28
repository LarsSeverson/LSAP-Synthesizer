#pragma once

namespace LSAP {

	struct AudioData {

		AudioData(std::wstring outputD = getActiveDevice(), unsigned int sampleRate = 44100, unsigned int nChannels = 1, unsigned int blockCount = 8, unsigned int blockSamples = 512)
			: outputDevice(outputD), sampleRate(sampleRate), nChannels(nChannels), blockCount(blockCount), blockSamples(blockSamples)
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
		using EventFn = std::function<double(double)>;
	public:
		SoundGenerator(const AudioData& audioData = AudioData());
		~SoundGenerator();

		void setSynthFunc(const EventFn& func);
		void stopSound() { isRunning = false; }
		void generateSound();
	
	private:
		void openAudioDevice(const AudioData& audioData);
		void setBlockMemory(const AudioData& audioData);
	private:

		EventFn mUserSynthFunction;

		double mGlobalTime;
		int* mBlockMemory;
		bool isRunning;

		std::unique_ptr<WAVEHDR[]> mWaveHeaders;
		HWAVEOUT mDevice;

		std::thread mThread;
		std::mutex mBlockFree;
		std::atomic<unsigned int> mBlockZero;
		std::condition_variable mConditionNotZero;

		void blockCount();
		// If dwInstance was a DWORD, it would be undefined behavior to cast to SoundGenerator* in 64 bit...
		// unsigned long ptr is compatible for both 64 bit and 32 bit
		static void CALLBACK waveOutProcWrap(HWAVEOUT hWaveOut, UINT uMsg, unsigned long* dwInstance, DWORD dwParam1, DWORD dwParam2);
		void threadPlaySound(double offset, double mGlobalTime);
	};
}
