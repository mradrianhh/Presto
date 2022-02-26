#include <Presto.h>
#include <Presto/Core/EntryPoint.h>

#include "imgui/imgui.h"

namespace Presto
{

	class ExampleLayer : public Layer
	{
	public:
		ExampleLayer()
			: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
		{
			m_VertexArray.reset(VertexArray::Create());

			float vertices[3 * 3] = {
				-0.5f, -0.5f, 0.0f,
				 0.5f, -0.5f, 0.0f,
				 0.0f,  0.5f, 0.0f
			};

			std::shared_ptr<VertexBuffer> vertexBuffer;
			vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
			vertexBuffer->SetLayout({
				{ ShaderDataType::Float3, "a_Position" },
				});

			m_VertexArray->AddVertexBuffer(vertexBuffer);

			uint32_t indices[3] = { 0, 1, 2 };

			std::shared_ptr<IndexBuffer> indexBuffer;
			indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

			m_VertexArray->SetIndexBuffer(indexBuffer);

			std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);	
			}
		)";

			std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
			}
		)";

			m_Shader.reset(new Shader(vertexSrc, fragmentSrc));
		}

		void OnUpdate(Timestep ts) override
		{
			PRESTO_TRACE("{0} s, ({1} ms)", ts.GetSeconds(), ts.GetMilliseconds());

			if (Presto::Input::IsKeyPressed(PRESTO_KEY_LEFT))
				m_CameraPosition.x += m_CameraMoveSpeed * ts;
			else if (Presto::Input::IsKeyPressed(PRESTO_KEY_RIGHT))
				m_CameraPosition.x -= m_CameraMoveSpeed * ts;

			if (Presto::Input::IsKeyPressed(PRESTO_KEY_UP))
				m_CameraPosition.y -= m_CameraMoveSpeed * ts;
			else if (Presto::Input::IsKeyPressed(PRESTO_KEY_DOWN))
				m_CameraPosition.y += m_CameraMoveSpeed * ts;

			if (Presto::Input::IsKeyPressed(PRESTO_KEY_A))
				m_CameraRotation += m_CameraRotationSpeed * ts;
			if (Presto::Input::IsKeyPressed(PRESTO_KEY_D))
				m_CameraRotation -= m_CameraRotationSpeed * ts;

			Presto::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
			Presto::RenderCommand::Clear();

			m_Camera.SetPosition(m_CameraPosition);
			m_Camera.SetRotation(m_CameraRotation);

			Presto::Renderer::BeginScene(m_Camera);

			Presto::Renderer::Submit(m_Shader, m_VertexArray);

			Presto::Renderer::EndScene();
		}

		virtual void OnImGuiRender() override
		{
			ImGui::Begin("Test");
			ImGui::Text("Hello World");
			ImGui::End();
		}

		void OnEvent(IEvent& event) override
		{
			if (event.GetEventType() == EventType::KeyPressed)
			{
				KeyPressedEvent& e = (KeyPressedEvent&)event;
				if (e.GetKeyCode() == PRESTO_KEY_TAB)
					PRESTO_TRACE("Tab key is pressed (event)!");
				PRESTO_TRACE("{0}", (char)e.GetKeyCode());
			}
		}
	private:
		std::shared_ptr<Presto::Shader> m_Shader;
		std::shared_ptr<Presto::VertexArray> m_VertexArray;

		std::shared_ptr<Presto::Shader> m_BlueShader;
		std::shared_ptr<Presto::VertexArray> m_SquareVA;

		Presto::OrthographicCamera m_Camera;
		glm::vec3 m_CameraPosition;
		float m_CameraMoveSpeed = 0.1f;

		float m_CameraRotation = 0.0f;
		float m_CameraRotationSpeed = 180.0f;
	};

	class PrestissimoApplication : public Application
	{
	public:
		PrestissimoApplication()
		{
			PushLayer(new ExampleLayer());
		}

		~PrestissimoApplication()
		{

		}
	};

	Application* CreateApplication()
	{
		return new PrestissimoApplication();
	}

}
