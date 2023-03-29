#include "audiopch.h"
#include "Synth.h"

namespace LSAP {

	Synth* Synth::sSynthInstance = nullptr;
	int Synth::sSynthOctave = 0;
	Synth::Synth()
		:
		voicePool(std::make_unique<VoicePool>(16, 3)),
		envelopeGui(std::make_unique<EnvelopePanel>()),
		oscillatorGui(std::make_unique<OscillatorPanels>())
	{
		sSynthInstance = this;

		oscillatorGui->addOscillator(0, std::make_unique<OscillatorGui>(WaveformType::sine,	0,	"Oscillator 1"));
		oscillatorGui->addOscillator(1, std::make_unique<OscillatorGui>(WaveformType::square,	1,  "Oscillator 2"));
		oscillatorGui->addOscillator(2, std::make_unique<OscillatorGui>(WaveformType::sine,	2,	"Oscillator 3"));

		voicePool->syncOscillators(oscillatorGui->get(0));
		voicePool->syncOscillators(oscillatorGui->get(1));
		voicePool->syncOscillators(oscillatorGui->get(2));
		voicePool->syncEnvelope(*envelopeGui);
		
		LS_CORE_INFO("Synth Created");
		startSoundThread();
	}
	Synth::~Synth()
	{
		
	}

	void Synth::onSynthUpdate()
	{

	}

	void Synth::onSynthStop()
	{
		stopSound();
	}

	void Synth::onGuiRender()
	{
		oscillatorGui->onGuiRender();
		envelopeGui->onGuiRender();
	}

	void Synth::pushNote(Notes note)
	{
		Voice& freeVoice = voicePool->getFreeVoice();
		freeVoice.setNote(Note(note));
		freeVoice.getEnvelope().gate(true);
		freeVoice.voiceOn = true;
	}

	void Synth::popNote(Notes note) 
	{
		voicePool->freeVoice(note);
	}

	bool Synth::onKeyPressed(KeyPressedEvent& event)
	{
		std::unique_lock<std::mutex> lock(synthMutex);
		if (!event.isRepeat()) {
			switch (event.getKeyCode()) {
			case Key::A:
				pushNote(Notes::C);
				break;
			case Key::W:
				pushNote(Notes::Db);
				break;
			case Key::S:
				pushNote(Notes::D);
				break;
			case Key::E:
				pushNote(Notes::Eb);
				break;
			case Key::D:
				pushNote(Notes::E);
				break;
			case Key::F:
				pushNote(Notes::F);
				break;
			case Key::T:
				pushNote(Notes::Gb);
				break;
			case Key::G:
				pushNote(Notes::G);
				break;
			case Key::Y:
				pushNote(Notes::Ab);
				break;
			case Key::H:
				pushNote(Notes::A);
				break;
			case Key::U:
				pushNote(Notes::Bb);
				break;
			case Key::J:
				pushNote(Notes::B);
				break;

				// Octave higher
			case Key::K:
				pushNote(Notes::C2);
				break;
			case Key::O:
				pushNote(Notes::Db2);
				break;
			case Key::L:
				pushNote(Notes::D2);
				break;
			case Key::P:
				pushNote(Notes::Eb2);
				break;
			case Key::Semicolon:
				pushNote(Notes::E2);
				break;
			case Key::Apostrophe:
				pushNote(Notes::F2);
				break;

				// Octave control
			case Key::Z:
				for (auto& voice : voicePool->getVoices()) {
					voice->getEnvelope().gate(false);
				}
				sSynthOctave -= 12;
				break;
			case Key::X:
				for (auto& voice : voicePool->getVoices()) {
					voice->getEnvelope().gate(false);
				}
				sSynthOctave += 12;
				break;
			}
		}

		return false;
	}

	bool Synth::onKeyReleased(KeyReleasedEvent& event)
	{
		std::unique_lock<std::mutex> lock(synthMutex);
		switch (event.getKeyCode()) {
		case Key::A:
			popNote(Notes::C);
			break;
		case Key::W:
			popNote(Notes::Db);
			break;
		case Key::S:
			popNote(Notes::D);
			break;
		case Key::E:
			popNote(Notes::Eb);
			break;
		case Key::D:
			popNote(Notes::E);
			break;
		case Key::F:
			popNote(Notes::F);
			break;
		case Key::T:
			popNote(Notes::Gb);
			break;
		case Key::G:
			popNote(Notes::G);
			break;
		case Key::Y:
			popNote(Notes::Ab);
			break;
		case Key::H:
			popNote(Notes::A);
			break;
		case Key::U:
			popNote(Notes::Bb);
			break;
		case Key::J:
			popNote(Notes::B);
			break;

			// Octave higher
		case Key::K:
			popNote(Notes::C2);
			break;
		case Key::O:
			popNote(Notes::Db2);
			break;
		case Key::L:
			popNote(Notes::D2);
			break;
		case Key::P:
			popNote(Notes::Eb2);
			break;
		case Key::Semicolon:
			popNote(Notes::E2);
			break;
		case Key::Apostrophe:
			popNote(Notes::F2);
			break;
		}
		return false;
	}

	void Synth::getNextAudioBlock(const SynthBackend& data)
	{
		int bufferSize = data.frameCount;

		for (int i = 0; i < bufferSize; ++i) {
			double sample = 0.0;

			for (auto& voice : voicePool->getVoices()) {
				if (voice->voiceOn) {
					sample += voice->getSample();
				}
			}

			data.outputBuffer[i * data.wfx.nChannels] = static_cast<short>(sample * 32767);
			data.outputBuffer[i * data.wfx.nChannels + 1] = static_cast<short>(sample * 32767);
		}
	}
}
