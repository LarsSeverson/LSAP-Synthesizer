#pragma once

#include "LSAP/Input.h"
#include "LSAP/MouseCodes.h"
#include "LSAP/Events/Event.h"
#include "LSAP/Events/KeyEvent.h"

#include "Panels/EnvelopePanel.h"
#include "Panels/OscillatorPanels.h"
#include "Panels/FilterPanels.h"

#include "Wave.h"
#include "Note.h"
#include "SynthBackend.h"
#include "VoicePool.h"

namespace LSAP {
	class Synth : public SynthBackend
	{
	public:
		Synth();
		~Synth();

		void onSynthUpdate();
		void onSynthStop();

		void onGuiRender();

		void pushNote(Notes note);
		void popNote(Notes note);

		bool onKeyPressed(KeyPressedEvent& event);
		bool onKeyReleased(KeyReleasedEvent& event);

		void getNextAudioBlock(const SynthBackend& data) override;

		static Synth* getSynth() { return sSynthInstance; }
		static int sSynthOctave;

	private:
		static Synth* sSynthInstance;

		std::unique_ptr<OscillatorPanels> oscillatorPanel;
		std::unique_ptr<EnvelopePanel> envelopePanel;
		std::unique_ptr<FilterPanels> filterPanel;

		std::unique_ptr<VoicePool> voicePool;
		ParameterSmoother parameterSmoother;

		std::mutex synthMutex;
	};
}

