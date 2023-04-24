#include "SynthUI.h"
#include "Core/Synth.h"
#include <imGui/imgui.h>
#include <imGui/imgui_internal.h>

#include "Platform/OpenGL/OpenGLShader.h"

namespace LSAP {
#define SYNTH_BIND(x) std::bind(&x, LSAP::Synth::getSynth(), std::placeholders::_1)
    SynthUI::SynthUI()
        : 
        Layer("SynthUI"),
        settings(std::make_unique<Settings>())
    {
        settingsVA = VertexArray::create();
        logoVA = VertexArray::create();
        float squareVertices[5 * 4] = {
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
             0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
             0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
            -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
        };
        std::shared_ptr<VertexBuffer> squareVB;
        squareVB = VertexBuffer::create(squareVertices, sizeof(squareVertices));
        squareVB->setLayout({
             { ShaderDataType::Float3, "a_Position" },
            { ShaderDataType::Float2, "a_TexCoord" }
            });
        settingsVA->addVertexBuffer(squareVB);
        logoVA->addVertexBuffer(squareVB);

        uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
        std::shared_ptr<IndexBuffer> squareIB = IndexBuffer::create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
        settingsVA->setIndexBuffer(squareIB);
        logoVA->setIndexBuffer(squareIB);
        std::string textureShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec2 a_TexCoord;
			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;
			out vec2 v_TexCoord;
			void main()
			{
				v_TexCoord = a_TexCoord;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

        std::string textureShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec2 v_TexCoord;
			
			uniform sampler2D u_Texture;
			void main()
			{
				color = texture(u_Texture, v_TexCoord);
			}
		)";
        settingsShader = Shader::create(textureShaderVertexSrc, textureShaderFragmentSrc);
        logoShader = Shader::create(textureShaderVertexSrc, textureShaderFragmentSrc);

        settingsTexture = Texture2D::create("src/assets/icons/settings.png", true);
        logoTexture = Texture2D::create("src/assets/icons/logo.png", false);

        std::dynamic_pointer_cast<OpenGLShader>(settingsShader)->bindShader();
        std::dynamic_pointer_cast<OpenGLShader>(settingsShader)->uploadUniformInt("u_Texture", 0);
        std::dynamic_pointer_cast<OpenGLShader>(logoShader)->bindShader();
        std::dynamic_pointer_cast<OpenGLShader>(logoShader)->uploadUniformInt("u_Texture", 0);

    }

    SynthUI::~SynthUI()
    {
    }

    void SynthUI::onLayerUpdate()
    {
        Synth::getSynth()->onSynthUpdate();

        RenderCommand::setClearColor({ 0.1f, 0.1f, 0.1f, 1 });
        RenderCommand::clear();

        settingsTexture->bind();
        Renderer::submit(settingsShader, settingsVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
        logoTexture->bind();
        Renderer::submit(settingsShader, settingsVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
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
        dockspace_flags |= ImGuiDockNodeFlags_NoResize | ImGuiDockNodeFlags_NoTabBar;
        
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }
        ImGuiWindowClass window_class;
        window_class.DockNodeFlagsOverrideSet = ImGuiDockNodeFlags_NoTabBar;
        ImGui::SetNextWindowClass(&window_class);

        ImGui::Begin("##Topbar");
        ImGui::SetCursorPosY(ImGui::GetWindowHeight() - 55);
        ImGui::Image((void*)logoTexture->getRendererID(), ImVec2(40.f, 40.f));
        ImGui::SetCursorPosX(ImGui::GetWindowWidth() - 70);
        ImGui::SetCursorPosY(ImGui::GetWindowHeight() - 55);
        if (ImGui::ImageButton((void*)settingsTexture->getRendererID(), ImVec2(40.f, 40.f), ImVec2(0, 0), ImVec2(1, 1), -1, ImVec4())) {
            settings->open();
        }
        settings->onImGuiRender();

        LSAP::Synth::getSynth()->onGuiRender();
        ImGui::Begin("ViewPort");
        ImGui::End();

        // To mostly be implemented in the corresponding classes
        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.2f, 0.2f, 0.2f, 1.0f));
        ImGui::Begin("Effects Panel");
        ImGui::PopStyleColor();
        ImGui::End();

        ImGui::End();
        ImGui::End();
    }
}