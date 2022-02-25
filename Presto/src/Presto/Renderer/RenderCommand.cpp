#include "prestopch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Presto
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}