#include "tlpch.h"
#include "OpenGLContext.h"

#include <glad/glad.h>

namespace Tilia {



	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		TL_CORE_ASSERT(windowHandle, "Window handle is null!");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		TL_CORE_ASSERT(status, "Failed to initialize Glad!");

		TL_CORE_INFO("OpenGL: Info: ");
		TL_CORE_INFO("\t Vendor: {0}", glGetString(GL_VENDOR));
		TL_CORE_INFO("\t Renderer: {0}", glGetString(GL_RENDERER));
		TL_CORE_INFO("\t Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}


}