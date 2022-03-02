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
			: Layer("Example"), m_CameraController(1280.0f / 720.0f)
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
			m_CameraController.OnUpdate(ts);

			Presto::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
			Presto::RenderCommand::Clear();

			Presto::Renderer::BeginScene(m_CameraController.GetCamera());

			auto shader = m_ShaderLibrary.Get("Texture");

			glm::mat4 transform = glm::mat4(1.0f);

			std::dynamic_pointer_cast<OpenGLShader>(shader)->Bind();

			m_Texture->Bind();
			Presto::Renderer::Submit(shader, m_VertexArray, transform);

			Presto::Renderer::EndScene();
		}

		virtual void OnImGuiRender() override
		{

		}

		void OnEvent(IEvent& event) override
		{
			m_CameraController.OnEvent(event);
		}
	private:
		Presto::ShaderLibrary m_ShaderLibrary;
		Presto::Ref<Presto::VertexArray> m_VertexArray;
		Presto::Ref<Presto::Texture2D> m_Texture;

		Presto::OrthographicCameraController m_CameraController;
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
