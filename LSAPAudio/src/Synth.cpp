#include "audiopch.h"
#include "Synth.h"

namespace LSAP {

	Synth* Synth::sSynthInstance = nullptr;
	double Synth::sSynthOctave = 0.0;

	Synth::Synth()
		: mSoundGenerator(new SoundGenerator())
	{
		sSynthInstance = this;
		mSoundGenerator->setSynthFunc(std::bind(&Synth::fillOutputBuffer, this, std::placeholders::_1));
		
		pushOscillator(new Oscillator(new SineWave(), "Oscillator 1"));
		pushOscillator(new Oscillator(new SquareWave(), "Oscillator 2"));
		pushOscillator(new Oscillator(new SineWave(), "Oscillator 3"));
		
		outputSound();
	}
	Synth::~Synth()
	{
		
	}
	
	void Synth::outputSound()
	{
		mSoundGenerator->generateSound();
	}

	void Synth::onSynthStop()
	{
		mSoundGenerator->stopSound();
	}

	void Synth::pushOscillator(Oscillator* osc)
	{
		mOscStack.pushOsc(osc);
	}

	void Synth::pushNote(Note n)
	{
		std::unique_lock<std::mutex> lm(notes);
		auto result = std::find_if(mOscStack.getNotes().begin(), mOscStack.getNotes().end(), [&n](Note& check)
			{ return check.noteFrequency == n.noteFrequency; });

		if (result == mOscStack.getNotes().end()) {
			mOscStack.onNotePush(n).noteEnv.setState(1);
		}

		// If note is found and is in release state (but pressed again),
		// reset the state to attack
		else if (result->noteEnv.getState() == 4) {
			result->noteEnv.setState(1);
		}
	}
	void Synth::popNote(Note note) {
		std::unique_lock<std::mutex> lm(notes);
		auto it = std::find_if(mOscStack.getNotes().begin(), mOscStack.getNotes().end(), [&note](Note& index)
			{ return note.noteFrequency == index.noteFrequency; });
		if (it != mOscStack.getNotes().end()) {
			it->noteEnv.setState(4);
		}
	}

	bool Synth::onKeyPressed(KeyPressedEvent& event)
	{
		switch (event.getKeyCode()) {
		case Key::A:
			pushNote(Note(Notes::C));
			break;
		case Key::W:
			pushNote(Note(Notes::Db));
			break;
		case Key::S:
			pushNote(Note(Notes::D));
			break;
		case Key::E:
			pushNote(Note(Notes::Eb));
			break;
		case Key::D:
			pushNote(Note(Notes::E));
			break;
		case Key::F:
			pushNote(Note(Notes::F));
			break;
		case Key::T:
			pushNote(Note(Notes::Gb));
			break;
		case Key::G:
			pushNote(Note(Notes::G));
			break;
		case Key::Y:
			pushNote(Note(Notes::Ab));
			break;
		case Key::H:
			pushNote(Note(Notes::A));
			break;
		case Key::U:
			pushNote(Note(Notes::Bb));
			break;
		case Key::J:
			pushNote(Note(Notes::B));
			break;

			// Octave higher
		case Key::K:
			pushNote(Note(Notes::C2));
			break;
		case Key::O:
			pushNote(Note(Notes::Db2));
			break;
		case Key::L:
			pushNote(Note(Notes::D2));
			break;
		case Key::P:
			pushNote(Note(Notes::Eb2));
			break;
		case Key::Semicolon:
			pushNote(Note(Notes::E2));
			break;
		case Key::Apostrophe:
			pushNote(Note(Notes::F2));
			break;

		// Octave control
		case Key::Z:
			if (!event.isRepeat()) {
				for (auto& i : mOscStack.getNotes())
				{
					i.noteEnv.setState(4);
				}
				sSynthOctave -= 12.0;
			}
			break;
		case Key::X:
			if (!event.isRepeat()) {
				for (auto& i : mOscStack.getNotes())
				{
					i.noteEnv.setState(4);
				}
				sSynthOctave += 12.0;
			}
			break;
		}


		return false;
	}

	bool Synth::onKeyReleased(KeyReleasedEvent& event)
	{
		switch (event.getKeyCode()) {
		case Key::A:
			popNote(Note(Notes::C));
			break;
		case Key::W:
			popNote(Note(Notes::Db));
			break;
		case Key::S:
			popNote(Note(Notes::D));
			break;
		case Key::E:
			popNote(Note(Notes::Eb));
			break;
		case Key::D:
			popNote(Note(Notes::E));
			break;
		case Key::F:
			popNote(Note(Notes::F));
			break;
		case Key::T:
			popNote(Note(Notes::Gb));
			break;
		case Key::G:
			popNote(Note(Notes::G));
			break;
		case Key::Y:
			popNote(Note(Notes::Ab));
			break;
		case Key::H:
			popNote(Note(Notes::A));
			break;
		case Key::U:
			popNote(Note(Notes::Bb));
			break;
		case Key::J:
			popNote(Note(Notes::B));
			break;

			// Octave higher
		case Key::K:
			popNote(Note(Notes::C2));
			break;
		case Key::O:
			popNote(Note(Notes::Db2));
			break;
		case Key::L:
			popNote(Note(Notes::D2));
			break;
		case Key::P:
			popNote(Note(Notes::Eb2));
			break;
		case Key::Semicolon:
			popNote(Note(Notes::E2));
			break;
		case Key::Apostrophe:
			popNote(Note(Notes::F2));
			break;
		}
		return false;
	}

	double Synth::fillOutputBuffer(double time)
	{
		std::unique_lock<std::mutex> lm(notes);
		double data = 0;
		for (auto& i : mOscStack.getNotes()) {
			data += mOscStack.onOscStackFill(i, time);
		}
		std::erase_if(mOscStack.getNotes(), [](Note& index) {
			return index.noteDone; });
		
		return data;
	}

}
