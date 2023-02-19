#pragma once
#include <LSAP.h>
class SandboxSynth : public LSAP::Synth
{
public:
	SandboxSynth();
	~SandboxSynth() = default;
	void onSynthUpdate() override;

private:
	uint16_t mOctave;
};
