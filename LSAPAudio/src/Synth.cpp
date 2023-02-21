#include "audiopch.h"
#include "Synth.h"


namespace LSAP {

	Synth* Synth::sSynthInstance = nullptr;
	double Synth::sOctave = 1.0;

	Synth::Synth()
		: mSoundGenerator(new SoundGenerator()), isRunning(true)
	{
		sSynthInstance = this;
		mSoundGenerator->setSynthFunc(std::bind(&Synth::fillOutputBuffer, this, std::placeholders::_1));
		outputSound();
	}
	Synth::~Synth()
	{
		
	}
	
	void Synth::outputSound()
	{
		mSoundGenerator->generateSound();
	}
	void Synth::onSynthUpdate()
	{

	}

	void Synth::onSynthStop()
	{
		isRunning = false;
	}

	void Synth::runSynth()
	{
		while (isRunning) {
			onSynthUpdate();
			mOscStack.onOscStackUpdate();
		}
	}

	void Synth::pushOscillator(Oscillator::Oscillator* osc)
	{
		mOscStack.pushOsc(osc);
	}

	void Synth::pushNote(Note n)
	{
		notes.lock();

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
		notes.unlock();
	}
	void Synth::popNote(Note note) {
		notes.lock();
		auto it = std::find_if(mOscStack.getNotes().begin(), mOscStack.getNotes().end(), [&note](Note& index)
			{ return note.noteFrequency == index.noteFrequency; });
		if (it != mOscStack.getNotes().end()) {
			it->noteEnv.setState(4);
		}
		notes.unlock();
	}

	void Synth::checkInput(Event& event, uint16_t octave)
	{
		switch (event.isInCategory(EventCategory::EventCategoryKeyboard)) {
		case Key::A:
		{
			pushNote(Note(Notes::C, octave));
			break;
		}
		}


		/*Note& newNote = note;
		if (Input::sIsKeyPressed(key)) {
			pushNote(newNote);
		}
		else {
			popNote(newNote);
		}*/
	}

	bool Synth::onKeyPressed(KeyPressedEvent& event)
	{
		switch (event.getKeyCode()) {
		case Key::A:
			pushNote(Note(Notes::C, sOctave));
			break;
		case Key::W:
			pushNote(Note(Notes::Db, sOctave));
			break;
		case Key::S:
			pushNote(Note(Notes::D, sOctave));
			break;
		case Key::E:
			pushNote(Note(Notes::Eb, sOctave));
			break;
		case Key::D:
			pushNote(Note(Notes::E, sOctave));
			break;
		case Key::F:
			pushNote(Note(Notes::F, sOctave));
			break;
		case Key::T:
			pushNote(Note(Notes::Gb, sOctave));
			break;
		case Key::G:
			pushNote(Note(Notes::G, sOctave));
			break;
		case Key::Y:
			pushNote(Note(Notes::Ab, sOctave));
			break;
		case Key::H:
			pushNote(Note(Notes::A, sOctave));
			break;
		case Key::U:
			pushNote(Note(Notes::Bb, sOctave));
			break;
		case Key::J:
			pushNote(Note(Notes::B, sOctave));
			break;

			// Octave higher
		case Key::K:
			pushNote(Note(Notes::C, sOctave + 1));
			break;
		case Key::O:
			pushNote(Note(Notes::Db, sOctave + 1));
			break;
		case Key::L:
			pushNote(Note(Notes::D, sOctave + 1));
			break;
		case Key::P:
			pushNote(Note(Notes::Eb, sOctave + 1));
			break;
		case Key::Semicolon:
			pushNote(Note(Notes::E, sOctave + 1));
			break;
		case Key::Apostrophe:
			pushNote(Note(Notes::F, sOctave + 1));
			break;

		/*case Key::Z:
			if (!event.isRepeat()) {
				sOctave /= 2;
			}
			break;
		case Key::X:
			if (!event.isRepeat()) {
				sOctave *= 2;
			}
			break;*/
		}


		return false;
	}

	bool Synth::onKeyReleased(KeyReleasedEvent& event)
	{
		switch (event.getKeyCode()) {
		case Key::A:
			popNote(Note(Notes::C, sOctave));
			break;
		case Key::W:
			popNote(Note(Notes::Db, sOctave));
			break;
		case Key::S:
			popNote(Note(Notes::D, sOctave));
			break;
		case Key::E:
			popNote(Note(Notes::Eb, sOctave));
			break;
		case Key::D:
			popNote(Note(Notes::E, sOctave));
			break;
		case Key::F:
			popNote(Note(Notes::F, sOctave));
			break;
		case Key::T:
			popNote(Note(Notes::Gb, sOctave));
			break;
		case Key::G:
			popNote(Note(Notes::G, sOctave));
			break;
		case Key::Y:
			popNote(Note(Notes::Ab, sOctave));
			break;
		case Key::H:
			popNote(Note(Notes::A, sOctave));
			break;
		case Key::U:
			popNote(Note(Notes::Bb, sOctave));
			break;
		case Key::J:
			popNote(Note(Notes::B, sOctave));
			break;

			// Octave higher
		case Key::K:
			popNote(Note(Notes::C, sOctave + 1));
			break;
		case Key::O:
			popNote(Note(Notes::Db, sOctave + 1));
			break;
		case Key::L:
			popNote(Note(Notes::D, sOctave + 1));
			break;
		case Key::P:
			popNote(Note(Notes::Eb, sOctave + 1));
			break;
		case Key::Semicolon:
			popNote(Note(Notes::E, sOctave + 1));
			break;
		case Key::Apostrophe:
			popNote(Note(Notes::F, sOctave + 1));
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
