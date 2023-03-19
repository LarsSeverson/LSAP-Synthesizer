#include "audiopch.h"
#include "Synth.h"

namespace LSAP {

	Synth* Synth::sSynthInstance = nullptr;
	int Synth::sSynthOctave = 0;
	Synth::Synth()
		: mEnvelope(new EnvelopeData(0.0, 0.0, 1.0, 0.0))
	{
		sSynthInstance = this;
		
		pushOscillator(new Oscillator(new SineWave(),   "Oscillator 1"));
		pushOscillator(new Oscillator(new SquareWave(), "Oscillator 2"));
		pushOscillator(new Oscillator(new SineWave(),   "Oscillator 3"));
		startSoundThread();
	}
	Synth::~Synth()
	{
		
	}

	void Synth::onSynthUpdate()
	{
		std::lock_guard<std::mutex> lock(synthMutex);
		std::erase_if(notes, [](const auto& note) { return note.second.noteDone; });

	}

	void Synth::onSynthStop()
	{
		stopSound();
	}

	void Synth::pushOscillator(Oscillator* osc)
	{
		mOscStack.pushOsc(osc);
	}

	void Synth::setEnvelope(EnvelopeData& data)
	{
		mEnvelope.reset(&data);
	}

	void Synth::pushNote(const Notes& note)
	{
		double freq = Note::calcFrequency(note);
		auto it = notes.try_emplace(freq, Note(note, mOscStack.getOscillators()));

		if (!it.second) {
			if(notes.at(freq).noteEnv.getState() == 4)
				it.first->second.noteEnv.setState(1);
		}
	}
	void Synth::popNote(const Notes& note) {
		double freq = Note::calcFrequency(note);
		if (notes.contains(freq)) {
			notes.at(freq).noteEnv.setState(4);
		}
	}

	bool Synth::onKeyPressed(KeyPressedEvent& event)
	{
		std::lock_guard<std::mutex> lock(synthMutex);
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
			if (!event.isRepeat()) {
				for (auto& [key, value] : notes)
				{
					value.noteEnv.setState(4);
				}
				sSynthOctave -= 12;
			}
			break;
		case Key::X:
			if (!event.isRepeat()) {
				for (auto& [key, value] : notes)
				{
					value.noteEnv.setState(4);
				}
				sSynthOctave += 12;
			}
			break;
		}


		return false;
	}

	bool Synth::onKeyReleased(KeyReleasedEvent& event)
	{
		std::lock_guard<std::mutex> lock(synthMutex);
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

	void Synth::getNextAudioBlock(SynthBackend& data)
	{
		int bufferSize = data.frameCount;

		for (unsigned int i = 0; i < bufferSize; ++i) {
			double value = 0.0;
			for (auto& note : notes) {
				value += note.second.getSample(mOscStack.getOscillators()) * note.second.processEnv(*mEnvelope);
			}

			data.outputBuffer[i * data.wfx.nChannels] = static_cast<short>(value * 32767);
			data.outputBuffer[i * data.wfx.nChannels + 1] = static_cast<short>(value * 32767);
			data.time += 1.f / data.mAudioData.sampleRate;
		}
	}
}
