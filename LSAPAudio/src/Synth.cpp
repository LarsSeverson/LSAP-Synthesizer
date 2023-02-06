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
		mOscStack.onOscStackUpdate();
	}

	void Synth::onSynthStop()
	{

	}

	void Synth::runSynth()
	{
		while (true) {
			onSynthUpdate();
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
		auto result = std::find_if(mNotes.begin(), mNotes.end(), [n](const Note& check) { return check.mID == n.mID; });
		if (result == mNotes.end()) {
			mNotes.emplace_back(n);
		}
		notes.unlock();

	}
	void Synth::popNote(Note* n) {

		// In progress...
		auto it = std::find_if(mNotes.begin(), mNotes.end(), [&n](const Note& index) {
			return &index == n; 
		});
		if (it != mNotes.end()) {
			Note* p = n;
			(*p).noteDone = true;
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
