#include "Sandbox2D.h"
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLShader.h"

#include <chrono>

Sandbox2D::Sandbox2D() : Layer("Sandbox 2D"), m_CameraController(1280.0f / 720.0f), m_WorstTime(0)
{
}

void Sandbox2D::OnAttach()
{
	m_CheckerboardTexture = Presto::Texture2D::Create("assets/textures/Checkerboard.png");
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Presto::Timestep ts)
{
	PRESTO_PROFILE_FUNCTION();

	{
		PRESTO_PROFILE_SCOPE("CameraController::OnUpdate");

		m_CameraController.OnUpdate(ts);
	}
	
	Presto::Renderer2D::ResetStats();
	{
		PRESTO_PROFILE_SCOPE("Renderer prep");

		Presto::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Presto::RenderCommand::Clear();
	}

	{
		PRESTO_PROFILE_SCOPE("Renderer draw");

		Presto::Renderer2D::BeginScene(m_CameraController.GetCamera());
		Presto::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		Presto::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		Presto::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_CheckerboardTexture);
		Presto::Renderer2D::DrawRotatedQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, 45, m_CheckerboardTexture);
		Presto::Renderer2D::EndScene();
	}
}

void Sandbox2D::OnImGuiRender()
{
	PRESTO_PROFILE_FUNCTION();

	ImGui::Begin("Statistics");
	auto stats = Presto::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quads: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());
	ImGui::End();
}

void Sandbox2D::OnEvent(Presto::IEvent& e)
{
	m_CameraController.OnEvent(e);
}
