#pragma once

#include "Presto.h"

class Sandbox2D : public Presto::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Presto::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Presto::IEvent& e) override;
private:
	Presto::OrthographicCameraController m_CameraController;

	Presto::Ref<Presto::VertexArray> m_SquareVA;
	Presto::Ref<Presto::Shader> m_FlatColorShader;
	Presto::Ref<Presto::Texture2D> m_CheckerboardTexture;

	float m_WorstTime;

	glm::vec4 m_SquareColor = {0.2f, 0.3f, 0.8f, 1.0f};
};