#pragma once
#include <mmdeviceapi.h>
#include <Audioclient.h>
#include <stdint.h>
#include <assert.h>

#include <LSAP/Log.h>
namespace LSAP {

#define REFTIMES_PER_SEC 10000000
#define EXIT_ON_ERROR(punk) if(punk != S_OK) { LS_CORE_ERROR("Failed to initialize audio."); }

	struct AudioData {

		AudioData(unsigned int nChannels = 2)
			: 
			nChannels(nChannels), 
			bitsPerSample(16)
		{}

		std::wstring outputDevice;
		unsigned int nChannels;
		unsigned int bitsPerSample;
	};

	class SynthBackend
	{
	public:
		SynthBackend(const AudioData& audioData = AudioData());
		virtual ~SynthBackend() = default;

		void startSoundThread();
		void run();
		void stopSound();

		// override it
		virtual void getNextAudioBlock(const SynthBackend& data) {}
	public:
		std::shared_ptr<short[]> outputBuffer;
		uint32_t frameCount;
		uint32_t bufferPadding;

		size_t numVoices;

		bool mIsRunning;
		double time;

		AudioData mAudioData;

		HRESULT hr;

		IMMDeviceEnumerator* deviceEnumerator;
		IMMDevice* audioDevice;
		IAudioClient2* audioClient;
		IAudioRenderClient* audioRenderClient;

		WAVEFORMATEX wfx;
		DWORD streamFlags;
		REFERENCE_TIME soundBufferDuration;

	private:
		std::thread mSynthBackendThread;
		std::mutex  mBackendMutex;
		uint32_t bufferSize;
	};
}
