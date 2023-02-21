#pragma once
#include <LSAP.h>

class SandboxSynth : public LSAP::Synth
{
public:
	SandboxSynth();
	~SandboxSynth() = default;
	virtual void onSynthUpdate() override;

	static SandboxSynth* getSBInstance() { return sSBSynthInstance; }
private:
	uint16_t mOctave;
	static SandboxSynth* sSBSynthInstance;
};
