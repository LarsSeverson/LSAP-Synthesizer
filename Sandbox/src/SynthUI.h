#pragma once
#include <LSAP.h>
class SynthUI : public LSAP::Layer
{
public:
	SynthUI();
	~SynthUI();

	virtual void onLayerUpdate() override;
	virtual void onLayerAttach() override;
	virtual void onLayerDetach() override;
	virtual void onLayerEvent(LSAP::Event& event) override;

	virtual void onImGuiRenderer() override;

private:

};

