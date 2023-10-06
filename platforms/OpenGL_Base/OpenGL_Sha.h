#pragma once

#include <string>
#include <fstream>
#include <sstream>

#include"../../includes/GLAD/glad.h"
#include"../../includes/GLFW/glfw3.h"

#include"../../Core/Base/Shader.h"

typedef glm::fmat4 fMat4;

namespace Sandbox
{
	class OpenGL_Sha : private Abs::Shader
	{
		public:
		OpenGL_Sha();
		OpenGL_Sha(String path);

		~OpenGL_Sha();

		uint CreateProgram() override;
		void UpdatePath(String path) override;
		inline uint GetProgramID() override {	return m_programID;	};
		void DeleteProgram() override;
		void UseProgram() override;
		void SetUniformInt(String name, int value);
		void SetUniformFloat(String name, float value);
		void SetUniformVec3(String name, glm::fvec3 value);
		void SetUniformMat4(String name, fMat4 value);

		private:
		uint m_programID;

		// It could have been squized in the abstract class if shader parsing remains same for all platform..
		uint compileShader(uint t);
		String parseShader(String sha);

	};

}