#pragma once
#include <LSAP.h>
#include "UIPanels/Settings.h"

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

	private:
		std::shared_ptr<VertexArray> settingsVA, logoVA;
		std::shared_ptr<Shader> settingsShader, logoShader;
		std::shared_ptr<Texture> settingsTexture, logoTexture;

		std::unique_ptr<Settings> settings;
	};
}
