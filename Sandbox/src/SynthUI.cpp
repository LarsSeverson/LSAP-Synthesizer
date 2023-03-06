#include "SynthUI.h"
#include "Synth.h"
#include <imGui/imgui.h>
#include <imGui/imgui_internal.h>

namespace LSAP {
#define SYNTH_BIND(x) std::bind(&x, LSAP::Synth::getSynth(), std::placeholders::_1)
    SynthUI::SynthUI()
        : Layer("SynthUI")
    {

    }

    SynthUI::~SynthUI()
    {
    }

    void SynthUI::onLayerUpdate()
    {

    }

    void SynthUI::onLayerAttach()
    {

    }

    void SynthUI::onLayerDetach()
    {

    }

    void SynthUI::onLayerEvent(LSAP::Event& event)
    {
        LSAP::EventDispatcher dispatcher(event);

        dispatcher.dispatch<LSAP::KeyPressedEvent>(SYNTH_BIND(LSAP::Synth::onKeyPressed));
        dispatcher.dispatch<LSAP::KeyReleasedEvent>(SYNTH_BIND(LSAP::Synth::onKeyReleased));
    }

    void SynthUI::onImGuiRenderer()
    {
        static bool dockspace = true;
        static bool opt_fullscreen = true;
        static bool opt_padding = false;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
        // because it would be confusing to have two docking targets within each others.
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        if (opt_fullscreen)
        {
            const ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->WorkPos);
            ImGui::SetNextWindowSize(viewport->WorkSize);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        }
        else
        {
            dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
        }

        // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
        // and handle the pass-thru hole, so we ask Begin() to not render a background.
        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;

        // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
        // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
        // all active windows docked into it will lose their parent and become undocked.
        // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
        // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
        if (!opt_padding)
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        window_flags |= ImGuiWindowFlags_NoScrollbar;
        ImGui::Begin("DockSpace", &dockspace, window_flags);
        if (!opt_padding)
            ImGui::PopStyleVar();

        if (opt_fullscreen)
            ImGui::PopStyleVar(2);

        // Submit the DockSpace
        ImGuiIO& io = ImGui::GetIO();
        dockspace_flags |= ImGuiDockNodeFlags_NoResize;
        
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }
        ImGuiWindowClass window_class;
        window_class.DockNodeFlagsOverrideSet = ImGuiDockNodeFlags_NoTabBar;
        ImGui::SetNextWindowClass(&window_class);
        ImGui::Begin("##Topbar");
        ImGui::SetCursorPosX(ImGui::GetWindowWidth() - 100);
            if (ImGui::BeginMenu("File"))
            {
                ImGui::Separator();
                if (ImGui::MenuItem("Exit")) {
                    LSAP::Application::getApplication().closeWindow();
                    dockspace = false;
                }
                ImGui::EndMenu();
            }

        LSAP::Synth::getSynth()->getOscStack().onImGuiRender();
        mEnvelopePanel.onImGuiRender();
        ImGui::Begin("ViewPort");
        ImGui::End();

        // To mostly be implemented in the corresponding classes
        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.2f, 0.2f, 0.2f, 1.0f));
        ImGui::Begin("Effects Panel");
        ImGui::Begin("Filter A");
        ImGui::Begin("Filter B");
        ImGui::PopStyleColor();
        ImGui::End();

        ImGui::End();
        ImGui::End();
        ImGui::End();
        ImGui::End();
    }
}