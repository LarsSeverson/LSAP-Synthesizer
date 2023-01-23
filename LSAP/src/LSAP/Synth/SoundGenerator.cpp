#include "lspch.h"
#include "SoundGenerator.h"

namespace LSAP {
	// public
	SoundGenerator::SoundGenerator(std::wstring outputDevice, unsigned int sampleRate, unsigned int nChannels,
		unsigned int blockCount, unsigned int blockSamples)
		: mOutputDevice(outputDevice), mSampleRate(sampleRate), mnChannels(nChannels),
		mBlockCount(blockCount), mBlockSamples(blockSamples), mDevice(nullptr), mBlockCurrent(0),
		mBlockMemory(nullptr), mBlockZero(mBlockCount), mGlobalTime(0.0), mWaveHeaders(nullptr)
	{

	}
	SoundGenerator::~SoundGenerator() {
		delete[] mBlockMemory;
	}

	void SoundGenerator::openAudioDevice() {
		WAVEFORMATEX waveFormat;
		waveFormat.wFormatTag = WAVE_FORMAT_PCM;
		waveFormat.nSamplesPerSec = mSampleRate;
		waveFormat.wBitsPerSample = sizeof(int) * 8;
		waveFormat.nChannels = mnChannels;
		waveFormat.nBlockAlign = (waveFormat.nChannels * waveFormat.wBitsPerSample) / 8;
		waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;
		waveFormat.cbSize = 0;

		if (waveOutOpen(&mDevice, 0, &waveFormat, (DWORD_PTR)waveOutProcWrap, (DWORD_PTR)this, CALLBACK_FUNCTION) != S_OK) {
			std::cout << "Could not open device";
			return;
		}
	}

	void SoundGenerator::setBlockMemory() {

		// 8 * 512 = 4096
		mBlockMemory = new int[mBlockCount * mBlockSamples];
		ZeroMemory(mBlockMemory, sizeof(int) * mBlockCount * mBlockSamples);

		mWaveHeaders = std::make_unique<WAVEHDR[]>(mBlockCount);

		for (int i = 0; i < mBlockCount; ++i) {

			// 512 * 4 = 2048
			mWaveHeaders[i].dwBufferLength = (DWORD)(mBlockSamples * sizeof(int));
			// 0 -> 512 -> 1024 - > 1536
			mWaveHeaders[i].lpData = (LPSTR)(mBlockMemory + (i * mBlockSamples));
		}
	}

	void SoundGenerator::playSound() {
		int previousSample;
		double offset = 1.0 / double(mSampleRate);
		mThread = std::thread(&SoundGenerator::threadPlaySound, this, offset, mGlobalTime);
		mThread.detach();
	}

	void SoundGenerator::setSynthFunc(const EventFn& func) {
		mUserSynthFunction = func;
	}

	std::wstring SoundGenerator::getActiveDevice() {
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

	// private:
	void SoundGenerator::threadPlaySound(double offset, double mGlobalTime) {
		constexpr double maxSample = std::numeric_limits<int>::max();
		constexpr double minSample = std::numeric_limits<int>::min();

		while (true) {

			if (mBlockZero == 0) {
				std::unique_lock<std::mutex> stop(mBlockFree);
				while (mBlockZero == 0) {
					mConditionNotZero.wait(stop);
				}
			}

			mBlockZero--;

			for (int i = 0; i < mBlockSamples; ++i) {
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

	void CALLBACK SoundGenerator::waveOutProcWrap(HWAVEOUT hWaveOut, UINT uMsg, unsigned long* dwInstance, DWORD dwParam1, DWORD dwParam2) {
		if (uMsg != WOM_DONE) {
			return;
		}
		((SoundGenerator*)(dwInstance))->blockCount();
	}
}