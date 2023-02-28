#include "audiopch.h"
#include "SoundGenerator.h"

namespace LSAP {
	// public
	SoundGenerator::SoundGenerator(const AudioData& audioData)
		: mUserSynthFunction(nullptr), mGlobalTime(0.0), mBlockMemory(nullptr),
		  mWaveHeaders(nullptr), mDevice(nullptr), mBlockZero(8), isRunning(true)
	{
		openAudioDevice(audioData);
	}
	SoundGenerator::~SoundGenerator() {
		delete[] mBlockMemory;
	}

	void SoundGenerator::openAudioDevice(const AudioData& audioData) {
		WAVEFORMATEX waveFormat;
		waveFormat.wFormatTag = WAVE_FORMAT_PCM;
		waveFormat.nSamplesPerSec = audioData.sampleRate;
		waveFormat.wBitsPerSample = sizeof(int) * 8;
		waveFormat.nChannels = audioData.nChannels;
		waveFormat.nBlockAlign = (waveFormat.nChannels * waveFormat.wBitsPerSample) / 8;
		waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;
		waveFormat.cbSize = 0;

		if (waveOutOpen(&mDevice, 0, &waveFormat, (DWORD_PTR)waveOutProcWrap, (DWORD_PTR)this, CALLBACK_FUNCTION) != S_OK) {
			std::cout << "Could not open device";
			return;
		}

		setBlockMemory(audioData);
	}

	void SoundGenerator::setBlockMemory(const AudioData& audioData) {

		// 8 * 512 = 4096
		mBlockMemory = new int[audioData.blockCount * audioData.blockSamples];
		ZeroMemory(mBlockMemory, sizeof(int) * audioData.blockCount * audioData.blockSamples);

		mWaveHeaders = std::make_unique<WAVEHDR[]>(audioData.blockCount);

		for (unsigned int i = 0; i < audioData.blockCount; ++i) {

			// 512 * 4 = 2048
			mWaveHeaders[i].dwBufferLength = (DWORD)(audioData.blockSamples * sizeof(int));
			// 0 -> 512 -> 1024 - > 1536
			mWaveHeaders[i].lpData = (LPSTR)(mBlockMemory + (i * audioData.blockSamples));
		}
	}

	void SoundGenerator::generateSound() {
		double offset = 1.0 / double(44100);
		mThread = std::thread(&SoundGenerator::threadPlaySound, this, offset, mGlobalTime);
		mThread.detach();
	}

	void SoundGenerator::setSynthFunc(const EventFn& func) {
		mUserSynthFunction = func;
	}

	// private:
	void SoundGenerator::threadPlaySound(double offset, double mGlobalTime) {
		constexpr double maxSample = std::numeric_limits<int>::max();
		constexpr double minSample = std::numeric_limits<int>::min();
		int mBlockCurrent = 0;
		int mBlockSamples = 512;
		int mBlockCount = 8;
		while (isRunning) {
			if (mBlockZero == 0) {
				std::unique_lock<std::mutex> stop(mBlockFree);
				while (mBlockZero == 0) {
					mConditionNotZero.wait(stop);
				}
			}
			mBlockZero--;
			for (unsigned int i = 0; i < mBlockSamples; ++i) {
				int newSample = (int)(std::clamp((mUserSynthFunction(mGlobalTime) * maxSample), minSample, maxSample));
				mBlockMemory[i + (mBlockCurrent * mBlockSamples)] = newSample;
				mGlobalTime += offset;
			}

			// Now we write to the output device
			waveOutPrepareHeader(mDevice, &mWaveHeaders[mBlockCurrent], sizeof(WAVEHDR));
			waveOutWrite(mDevice, &mWaveHeaders[mBlockCurrent], sizeof(WAVEHDR));

			mBlockCurrent++;
			// So it doesn't go over threshold
			mBlockCurrent %= mBlockCount;
		}
	}
	void SoundGenerator::blockCount() {
		mBlockZero++;

		std::unique_lock<std::mutex> stop(mBlockFree);
		mConditionNotZero.notify_one();
	}

	void CALLBACK SoundGenerator::waveOutProcWrap(HWAVEOUT hWaveOut, UINT uMsg, unsigned long* dwInstance, DWORD dwParam1, DWORD dwParam2){
		if (uMsg != WOM_DONE) {
			return;
		}
		((SoundGenerator*)(dwInstance))->blockCount();
	}


}