#include "audiopch.h"
#include "Synth.h"


namespace LSAP {

	Synth* Synth::sSynthInstance = nullptr;

	Synth::Synth()
		: mSoundGenerator(new SoundGenerator())
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

	}

	void Synth::runSynth()
	{
		while (true) {
			onSynthUpdate();
			mOscStack.onOscStackUpdate();
		}
	}

	void Synth::pushOscillator(Oscillator::Oscillator* osc)
	{
		mOscStack.pushOsc(osc);
	}

	void Synth::pushNote(const Note& n)
	{
		// If found
		notes.lock();
		auto result = std::find_if(mNotes.begin(), mNotes.end(), [n](const Note& check) { return check.noteFrequency == n.noteFrequency; });
		if (result == mNotes.end()) {
			mNotes.emplace_back(n);
			mOscStack.onNotePressed(.1);
		}
		notes.unlock();
	}
	void Synth::popNote(Note& note) {
		notes.lock();
		auto it = std::find_if(mNotes.begin(), mNotes.end(), [note](Note& index) { return note.noteFrequency == index.noteFrequency; });
		if (it != mNotes.end()) {
			it->noteDone = true;
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
		std::erase_if(mNotes, [](const Note& index) { return index.noteDone; });
		return data;
	}

}
