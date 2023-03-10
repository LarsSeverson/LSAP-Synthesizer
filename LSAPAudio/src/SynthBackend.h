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

		AudioData(std::wstring outputD = getActiveDevice(), unsigned int sampleRate = 44100, unsigned int nChannels = 2)
			: outputDevice(outputD), sampleRate(sampleRate), nChannels(nChannels), bitsPerSample(16)
		{}

		std::wstring outputDevice;
		unsigned int sampleRate;
		unsigned int nChannels;
		unsigned int bitsPerSample;

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

	class SynthBackend
	{
	public:
		SynthBackend(const AudioData& audioData = AudioData());
		virtual ~SynthBackend() = default;

		void startSoundThread();
		void run();
		void stopSound();

		// override it
		virtual void getNextAudioBlock(SynthBackend& data) {}
	public:
		std::shared_ptr<short[]> outputBuffer;
		uint32_t frameCount;
		uint32_t bufferPadding;

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
