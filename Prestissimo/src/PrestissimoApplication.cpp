#include <Presto.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"


#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Presto
{

	class ExampleLayer : public Layer
	{
	public:
		ExampleLayer()
			: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f), m_Triangle1Position(0.0f), m_Triangle2Position(0.0f)
		{
			m_VertexArray.reset(VertexArray::Create());

			float vertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
			};

			Presto::Ref<VertexBuffer> vertexBuffer;
			vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
			vertexBuffer->SetLayout({
				{ ShaderDataType::Float3, "a_Position" },
				{ ShaderDataType::Float2, "a_TexCoord" },
				});

			m_VertexArray->AddVertexBuffer(vertexBuffer);

			uint32_t indices[6] = { 0, 1, 2, 2, 3, 0 };

			Presto::Ref<IndexBuffer> indexBuffer;
			indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

			m_VertexArray->SetIndexBuffer(indexBuffer);

			auto shader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

			m_Texture = Presto::Texture2D::Create("assets/textures/presto_red.png");

			std::dynamic_pointer_cast<Presto::OpenGLShader>(shader)->Bind();
			std::dynamic_pointer_cast<Presto::OpenGLShader>(shader)->UploadUniformInt("u_Texture", 0);
		}

		void OnUpdate(Timestep ts) override
		{
			PRESTO_TRACE("{0} s, ({1} ms)", ts.GetSeconds(), ts.GetMilliseconds());

			if (Presto::Input::IsKeyPressed(PRESTO_KEY_LEFT))
				m_Triangle1Position.x -= m_CameraMoveSpeed * ts;
			else if (Presto::Input::IsKeyPressed(PRESTO_KEY_RIGHT))
				m_Triangle1Position.x += m_CameraMoveSpeed * ts;

			if (Presto::Input::IsKeyPressed(PRESTO_KEY_UP))
				m_Triangle1Position.y += m_CameraMoveSpeed * ts;
			else if (Presto::Input::IsKeyPressed(PRESTO_KEY_DOWN))
				m_Triangle1Position.y -= m_CameraMoveSpeed * ts;

			if (Presto::Input::IsKeyPressed(PRESTO_KEY_A))
				m_Triangle2Position.x -= m_CameraMoveSpeed * ts;
			else if (Presto::Input::IsKeyPressed(PRESTO_KEY_D))
				m_Triangle2Position.x += m_CameraMoveSpeed * ts;
			if (Presto::Input::IsKeyPressed(PRESTO_KEY_W))
				m_Triangle2Position.y += m_CameraMoveSpeed * ts;
			else if (Presto::Input::IsKeyPressed(PRESTO_KEY_S))
				m_Triangle2Position.y -= m_CameraMoveSpeed * ts;

			Presto::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
			Presto::RenderCommand::Clear();

			m_Camera.SetPosition(m_CameraPosition);
			m_Camera.SetRotation(m_CameraRotation);

			Presto::Renderer::BeginScene(m_Camera);

			auto shader = m_ShaderLibrary.Get("Texture");

			glm::mat4 transform1 = glm::translate(glm::mat4(1.0f), m_Triangle1Position);
			glm::mat4 transform2 = glm::translate(glm::mat4(1.0f), m_Triangle2Position);

			std::dynamic_pointer_cast<OpenGLShader>(shader)->Bind();

			m_Texture->Bind();
			Presto::Renderer::Submit(shader, m_VertexArray, transform1);

			Presto::Renderer::Submit(shader, m_VertexArray, transform2);

			Presto::Renderer::EndScene();
		}

		virtual void OnImGuiRender() override
		{
			ImGui::Begin("Settings");
			ImGui::ColorEdit3("Square Color", glm::value_ptr(m_Color));
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
		Presto::ShaderLibrary m_ShaderLibrary;
		Presto::Ref<Presto::VertexArray> m_VertexArray;
		Presto::Ref<Presto::Texture2D> m_Texture;

		Presto::OrthographicCamera m_Camera;
		glm::vec3 m_CameraPosition;
		float m_CameraMoveSpeed = 10.0f;

		float m_CameraRotation = 0.0f;
		float m_CameraRotationSpeed = 180.0f;

		glm::vec3 m_Triangle1Position;
		glm::vec3 m_Triangle2Position;

		glm::vec3 m_Color = { 0.2f, 0.3f, 0.8f };
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
