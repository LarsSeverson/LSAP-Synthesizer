#pragma once

#include "Core.h"
#include "LSAP/Events/Event.h"

namespace LSAP {
	class LSAP_API Layer 
	{
	public:
		Layer(const std::string& name ) : mDebugName(name){}
		virtual ~Layer() {}

		virtual void onLayerUpdate() {}
		virtual void onLayerAttach() {}
		virtual void onLayerDetatch() {}
		virtual void onImGuiRenderer() {}
		virtual void onLayerEvent(Event& event) {}

		inline const std::string& getDebugName() const { return mDebugName; }
	protected:
		std::string mDebugName;
	};
}