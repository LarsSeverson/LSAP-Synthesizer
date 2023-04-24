#pragma once
namespace LSAP {
	class FilterGui
	{
	public:
		FilterGui(const std::string& name);

		void onGuiRender();
		void renderMainKnobs();
		void renderMixKnobs();

	private:
		std::string name;

		float cutoff;
		float res;
		float drive;

		float mix;
	};
}
