#pragma once
#include <LSAP.h>

namespace LSAP {
	class SynthUI : public Layer
	{
	public:
		SynthUI();
		~SynthUI();

		virtual void onLayerUpdate() override;
		virtual void onLayerAttach() override;
		virtual void onLayerDetach() override;
		virtual void onLayerEvent(Event& event) override;

		virtual void onImGuiRenderer() override;
	};
}
