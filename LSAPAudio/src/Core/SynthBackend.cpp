#include "audiopch.h"
#include "SynthBackend.h"


namespace LSAP {
	SynthBackend::SynthBackend(const AudioData& audioData)
		:
		mIsRunning(true),
		mAudioData(audioData),
		bufferSize(0),
		time(0.0),
		outputBuffer(std::make_shared<short[]>(bufferSize)),
		soundBufferDuration(REFTIMES_PER_SEC * 2),
		bufferPadding(0),
		frameCount(0),
		numVoices(16)
	{
		hr = CoInitializeEx(nullptr, COINIT_SPEED_OVER_MEMORY);
		EXIT_ON_ERROR(hr);

		hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), nullptr, CLSCTX_ALL, __uuidof(IMMDeviceEnumerator), (LPVOID*)(&deviceEnumerator));
		EXIT_ON_ERROR(hr);

		hr = deviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &audioDevice);
		EXIT_ON_ERROR(hr);

		hr = audioDevice->Activate(__uuidof(IAudioClient2), CLSCTX_ALL, nullptr, (LPVOID*)(&audioClient));
		EXIT_ON_ERROR(hr);

		wfx = {};
		wfx.wFormatTag = WAVE_FORMAT_PCM;
		wfx.nChannels = audioData.nChannels;
		wfx.nSamplesPerSec = (DWORD)Backend::sampleRate;
		wfx.wBitsPerSample = audioData.bitsPerSample;
		wfx.nBlockAlign = (wfx.nChannels * wfx.wBitsPerSample) / 8;
		wfx.nAvgBytesPerSec = wfx.nSamplesPerSec * wfx.nBlockAlign;

		streamFlags = 
			(AUDCLNT_STREAMFLAGS_RATEADJUST | 
			 AUDCLNT_STREAMFLAGS_AUTOCONVERTPCM | 
			 AUDCLNT_STREAMFLAGS_SRC_DEFAULT_QUALITY);

		hr = audioClient->Initialize(AUDCLNT_SHAREMODE_SHARED, streamFlags, soundBufferDuration, 0, &wfx, nullptr);
		EXIT_ON_ERROR(hr);

		hr = audioClient->GetService(__uuidof(IAudioRenderClient), (LPVOID*)(&audioRenderClient));
		EXIT_ON_ERROR(hr);

		hr = audioClient->GetBufferSize(&bufferSize);
		bufferSize = 4029;
		EXIT_ON_ERROR(hr);

		hr = audioClient->Start();
		EXIT_ON_ERROR(hr);

	}

	void SynthBackend::startSoundThread()
	{
		mSynthBackendThread = std::thread(&SynthBackend::run, this);
	}
	void SynthBackend::run() 
	{
		while (mIsRunning) {
			hr = audioClient->GetCurrentPadding(&bufferPadding);
			EXIT_ON_ERROR(hr);

			frameCount = bufferSize - bufferPadding;

			hr = audioRenderClient->GetBuffer(frameCount, (BYTE**)(&outputBuffer));
			EXIT_ON_ERROR(hr);

			{
				std::lock_guard<std::mutex> lock(mBackendMutex);
				getNextAudioBlock(*this);
			}

			hr = audioRenderClient->ReleaseBuffer(frameCount, 0);
			EXIT_ON_ERROR(hr);
		}
	}
	void SynthBackend::stopSound()
	{
		mIsRunning = false;
		if (mSynthBackendThread.joinable()) {
			mSynthBackendThread.join();
		}

	}
}