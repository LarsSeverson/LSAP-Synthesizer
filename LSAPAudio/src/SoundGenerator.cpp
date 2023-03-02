#include "audiopch.h"
#include "SoundGenerator.h"
#include "LSAP/Log.h"

namespace LSAP {
	// public
	SoundGenerator::SoundGenerator(const AudioData& audioData)
		: mTime(0.0), mIsRunning(true), mAudioData(audioData)
	{
		mDeltaTime = 1.0 / (double)mAudioData.sampleRate;
		mCurrentBlock = 0;
		mBlockZero = mAudioData.blockCount;
		openAudioDevice();
	}
	SoundGenerator::~SoundGenerator() {
	}

	void SoundGenerator::openAudioDevice() {
		WAVEFORMATEX waveFormat;
		waveFormat.wFormatTag = WAVE_FORMAT_PCM;
		waveFormat.nSamplesPerSec = mAudioData.sampleRate;
		waveFormat.wBitsPerSample = sizeof(int) * 8;
		waveFormat.nChannels = mAudioData.nChannels;
		waveFormat.nBlockAlign = (waveFormat.nChannels * waveFormat.wBitsPerSample) / 8;
		waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;
		waveFormat.cbSize = 0;

		if (waveOutOpen(&mDevice, WAVE_MAPPER, &waveFormat, (DWORD_PTR)waveOutProcWrap, (DWORD_PTR)this, CALLBACK_FUNCTION) != S_OK) {
			LS_CORE_ERROR("Could not open device.");
			return;
		}
		setBlockMemory();
	}

	void SoundGenerator::setBlockMemory() {

		mOutputBuffer = std::make_unique<std::vector<int>[]>(mAudioData.blockCount);
		mWaveOutBuffer = std::make_unique<WAVEHDR[]>(mAudioData.blockCount);

		for (unsigned int i = 0; i < mAudioData.blockCount; ++i) {
			mOutputBuffer[i].resize(mAudioData.blockSamples * mAudioData.nChannels);
			mWaveOutBuffer[i].dwBufferLength = (DWORD)(mAudioData.blockSamples * sizeof(int));
			mWaveOutBuffer[i].lpData = (LPSTR)mOutputBuffer[i].data();
		}
	}

	void SoundGenerator::generateSound() {
		mThread = std::thread(&SoundGenerator::fillOutputBuffer, this);
	}

	void SoundGenerator::setSynthFunc(const std::function<double(double)>& func) {
		mUserSynthFunction = func;
	}

	void SoundGenerator::stopSound()
	{
		mIsRunning = false;
		if (mThread.joinable()) {
			mThread.join();
		}
	}

	void SoundGenerator::fillOutputBuffer() {
		constexpr double maxSample = std::numeric_limits<int>::max();
		constexpr double minSample = std::numeric_limits<int>::min();

		while (mIsRunning) {
			if (mTime >= std::numeric_limits<double>::max()) {
				std::unique_lock<std::mutex> timelock(mSoundGenMutex);
				mTime = 0.0;
			}
			if (mBlockZero == 0) {
				std::unique_lock<std::mutex> stop(mSoundGenMutex);
				while (mBlockZero == 0) {
					mSoundGenCondition.wait(stop);
				}
			}
			mBlockZero--;
			for (int i = 0; i < mOutputBuffer[mCurrentBlock].size(); ++i) {
				mOutputBuffer[mCurrentBlock][i] = (int)std::clamp((mUserSynthFunction(mTime) * maxSample), minSample, maxSample);
				mTime = mTime + mDeltaTime;
			}

			waveOutPrepareHeader(mDevice, &mWaveOutBuffer[mCurrentBlock], sizeof(WAVEHDR));
			waveOutWrite(mDevice, &mWaveOutBuffer[mCurrentBlock], sizeof(WAVEHDR));

			mCurrentBlock++;
			// So it doesn't go over threshold
			mCurrentBlock %= mAudioData.blockCount;
		}
	}

	// private:
	void SoundGenerator::countBlock() {
		mBlockZero++;

		std::unique_lock<std::mutex> stop(mSoundGenMutex);
		mSoundGenCondition.notify_one();
	}

	void CALLBACK SoundGenerator::waveOutProcWrap(HWAVEOUT hWaveOut, UINT uMsg, unsigned long* dwInstance, DWORD dwParam1, DWORD dwParam2) {
		if (uMsg != WOM_DONE) {
			return;
		}
		((SoundGenerator*)(dwInstance))->countBlock();
	}


}