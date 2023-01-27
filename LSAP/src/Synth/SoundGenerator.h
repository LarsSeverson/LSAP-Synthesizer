#pragma once

namespace LSAP {

	class SoundGenerator
	{
		using EventFn = std::function<double(double T)>;
	public:
		SoundGenerator(std::wstring outputDevice, unsigned int sampleRate, unsigned int nChannels, unsigned int blockCount, unsigned int blockSamples);
		~SoundGenerator();

		// This function opens the given waveform-audio output device for playback.
		void openAudioDevice();
		void setBlockMemory();
		void playSound();

		void setSynthFunc(const EventFn& f);
		static std::wstring getActiveDevice();
	private:
		std::wstring mOutputDevice;

		EventFn mUserSynthFunction;

		double mGlobalTime;

		unsigned int mSampleRate;
		unsigned int mnChannels;
		unsigned int mBlockCount;
		unsigned int mBlockSamples;
		unsigned int mBlockCurrent;
		int* mBlockMemory;

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
