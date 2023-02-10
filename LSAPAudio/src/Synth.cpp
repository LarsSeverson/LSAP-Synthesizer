#include "audiopch.h"
#include "Synth.h"


namespace LSAP {

	Synth* Synth::sSynthInstance = nullptr;
	uint16_t Synth::sOctave = 1;

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

	void Synth::pushNote(Note& n)
	{

		notes.lock();
		auto result = std::find_if(mNotes.begin(), mNotes.end(), [&n](Note& check) { return check.noteFrequency == n.noteFrequency; });
		if (result == mNotes.end()) {
			mNotes.emplace_back(n).noteEnv.setState(1);
		}
		// If note is found and is in release state (but pressed again),
		// reset the state to attack
		else if (result->noteEnv.getState() == 4) {
			result->noteEnv.setState(1);
		}
		notes.unlock();
	}
	void Synth::popNote(Note& note) {
		notes.lock();
		auto it = std::find_if(mNotes.begin(), mNotes.end(), [&note](Note& index) { return note.noteFrequency == index.noteFrequency; });
		if (it != mNotes.end()) {
			it->noteEnv.setState(4);
		}
		notes.unlock();
	}

	void Synth::checkInput(uint16_t key, Note note)
	{
		Note& newNote = note;
		if (Input::sIsKeyPressed(key)) {
			pushNote(newNote);
		}
		else {
			popNote(newNote);
		}
	}

	double Synth::fillOutputBuffer(double time)
	{
		std::unique_lock<std::mutex> lm(notes);
		double data = 0;
		for (auto& i : mNotes) {
			data += mOscStack.onOscStackFill(i, time);
		}
		std::erase_if(mNotes, [](Note& index) {
			return index.noteDone; });
		
		return data;
	}

}
