#pragma once

namespace LSAP {
	class EnvelopePanel
	{
	public:
		EnvelopePanel();
		~EnvelopePanel() = default;

		void onGuiRender();

		float& getAttack()  { return attack; }
		float& getDecay() { return decay; }
		float& getSustain() { return sustainLevel; }
		float& getRelease() { return release; }
	private:
		bool mIsOpen = true;

		float attackKnob;
		float decayKnob;
		float sustainLevel;
		float releaseKnob;

		float attack;
		float decay;
		float release;
	};
}
