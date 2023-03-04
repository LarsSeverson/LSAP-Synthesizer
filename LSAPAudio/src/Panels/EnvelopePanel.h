#pragma once

namespace LSAP {
	class EnvelopePanel
	{
	public:
		EnvelopePanel();
		~EnvelopePanel() = default;

		void onImGuiRender();
	private:
		bool mIsOpen = true;

		float mAttack;
		float mDecay;
		float mSustainLevel;
		float mRelease;
	};
}
