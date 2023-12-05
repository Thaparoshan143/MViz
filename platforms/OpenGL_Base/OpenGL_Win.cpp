#include"OpenGL_Win.h"
#include"./OpenGL_UI.h"

namespace OpenGL
{
	GLFWwindow* OpenGL_Win::m_window = nullptr;
	OpenGL_Win::OpenGL_Win(WindowInfo &wi, Abs::Application *targetApp)
	{
		m_targetApp = targetApp;
		this->m_winInfo = wi;
		m_keySubscriber = nullptr;
		initializeOpenGLWindow(wi.width, wi.height, wi.title);
		#ifdef __APPLE__
			glViewport(0, 0, wi.width*2.0, wi.height*2.0);
		#else
			glViewport(0, 0, wi.width, wi.height);
		#endif
	}

	OpenGL_Win::~OpenGL_Win()
	{
		glfwTerminate();
	}

	void OpenGL_Win::SetActive()
	{
		glfwMakeContextCurrent(this->m_window);		
	}

	void OpenGL_Win::SetColor(float r, float g, float b, float a)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(r, g, b, a);
	}

	void OpenGL_Win::SwapFrameBuffer()
	{
		glfwSwapBuffers(this->m_window);
	}

	uint OpenGL_Win::GetShaderID(String path)
	{
		return GetRawShader(path)->GetProgramID();
	}

	OpenGL_Sha* OpenGL_Win::GetRawShader(String path)
	{
		if(m_shaderList.count(path)==0)
		{
			m_shaderList.insert({path, OpenGL_Sha(path)});
			m_shaderList[path].CreateProgram();
		}

		return &m_shaderList[path];
	}

	void OpenGL_Win::initializeOpenGLWindow(int w, int h, String t)
	{
		// loading basic glfw library and more
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_SAMPLES, 4);

		#ifdef __APPLE__
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		#endif
		if(!glfwInit())
		{
			exit(-1);
		}

		this->m_window = glfwCreateWindow(w, h, t.c_str(), NULL, NULL);
		this->SetActive();

		// loader glad check if everything is loaded for use 
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			exit(-2);
		}
		
		// Setting user pointer is left to do properly
		glfwSetWindowUserPointer(this->m_window, this);

		// Registering all the callbacks for mouse and keyboard (static method inside OpenGL_Inp)
		glfwSetMouseButtonCallback(this->m_window, static_mouse_button_callback);
		glfwSetCursorPosCallback(this->m_window, static_mouse_position_callback);
		// For now using charkey callback for easy key mapping rather than mod based key callback
		glfwSetKeyCallback(this->m_window, static_key_callback);
		glfwSetCharCallback(this->m_window, static_charkey_callback);

		glfwSetFramebufferSizeCallback(this->m_window, static_framesize_callback);
	}

	void OpenGL_Win::listenActiveKeyInterrupts(int key, int mod)
	{
		if(key==GLFW_KEY_ENTER)
		{
			std::cout << "Enter key pressed!!" << std::endl;
			m_keySubscriber = nullptr;
		}
		else if(key==GLFW_KEY_BACKSPACE)
		{
			if(m_lastStringScan.size()!=0)
			{
				m_lastStringScan.pop_back();
				*m_keySubscriber = m_lastStringScan;
			}
			else
			{
				std::cout << "No input to clear!!" << std::endl;
			}
		}
		std::cout << m_lastStringScan << std::endl;
	}

	void OpenGL_Win::listenActiveKeyInterrupts(uint charKey)
	{
		m_lastStringScan += char(charKey);
		*m_keySubscriber = m_lastStringScan;
	}


	// All the static methods for input definition 
	static void static_mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
    {
		OpenGL_Win *win = (OpenGL_Win*)glfwGetWindowUserPointer(window);
		OpenGL_UI *UI = (OpenGL_UI*)win->m_targetApp->GetReference(Abs::AppRef::UI);
        if(action == GLFW_PRESS)
        {
			UI->DispatchMouseEvents(win->m_mouPos, button);
        }
    }

	static void static_mouse_position_callback(GLFWwindow *window, double xpos, double ypos)
	{
		OpenGL_Win *win = (OpenGL_Win*)glfwGetWindowUserPointer(window);
		win->m_mouPos = dVec2(xpos, ypos);
	}

	static void static_key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
	{
		OpenGL_Win *win = (OpenGL_Win*)glfwGetWindowUserPointer(window);
		if(action == GLFW_PRESS)
		{
			if(win->m_keySubscriber!=nullptr)
			{
				win->listenActiveKeyInterrupts(key, mods);
			}
		}
	}

	static void static_charkey_callback(GLFWwindow *window, uint charKey)
	{
		OpenGL_Win *win = (OpenGL_Win*)glfwGetWindowUserPointer(window);
		OpenGL_UI *UI = (OpenGL_UI*)win->m_targetApp->GetReference(Abs::AppRef::UI);
		if(win->m_keySubscriber!=nullptr)
		{
			win->listenActiveKeyInterrupts(charKey);
			std::cout << "Subscriber text - " << win->m_lastStringScan << std::endl;
			UI->m_keySubscriber->OnFieldChange();
		}
	}

	static void static_framesize_callback(GLFWwindow *window, int width, int height)
	{
		OpenGL_Win *win = (OpenGL_Win*)glfwGetWindowUserPointer(window);

		// for the initialize window the provided size is different that the size later provided by callback so required adjustment..
		// Screen size has to be halfed for proper functining, once take a look why? for now leave it..
		#ifdef __APPLE__
			win->m_winInfo.width = width/2.0;
			win->m_winInfo.height = height/2.0;
			glViewport(0, 0, width, height);
		#else
			win->m_winInfo.width = width;
			win->m_winInfo.height = height;
			glViewport(0, 0, width, height);
		#endif
	}
}