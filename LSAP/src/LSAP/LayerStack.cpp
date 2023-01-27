#include "lspch.h"
#include "LayerStack.h"

namespace LSAP {
	LayerStack::LayerStack()
	{
		layerInsert = layers.begin();
	}
	LayerStack::~LayerStack()
	{
		for (Layer* layer : layers) {
			delete layer;
		}
	}
	void LayerStack::pushLayer(Layer* layer)
	{
		layerInsert = layers.emplace(layerInsert, layer);
		layer->onLayerAttach();
	}
	void LayerStack::pushOverlay(Layer* overlay)
	{
		layers.emplace_back(overlay);
		overlay->onLayerAttach();
	}
	void LayerStack::popLayer(Layer* layer)
	{
		auto it = std::find(layers.begin(), layers.end(), layer);
		if (it != layers.end()) {
			layers.erase(it);
			layerInsert--;
		}
	}
	void LayerStack::popOverlay(Layer* overlay)
	{
		auto it = std::find(layers.begin(), layers.end(), overlay);
		if (it != layers.end()) {
			layers.erase(it);
		}
	}
}