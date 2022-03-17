#pragma once

#include "Tilia/Renderer/GraphicsContext.h"

#include <GLFW/glfw3.h>

namespace Tilia {


	class OpenGLContext : public GraphicsContext 
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	};
}