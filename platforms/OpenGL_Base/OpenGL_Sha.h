#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include<map>

#include"../../includes/GLAD/glad.h"
#include"../../includes/GLFW/glfw3.h"

#include"../../Core/Base/Shader.h"

namespace OpenGL
{
	class OpenGL_Sha : public Abs::Shader
	{
		public:
		OpenGL_Sha();
		OpenGL_Sha(String path);

		~OpenGL_Sha();

		uint CreateProgram() override;
		void DeleteProgram() override;
		void UseProgram() override;
		void SetUniformInt(String name, int value);
		void SetUniformFloat(String name, float value);
		void SetUniformVec3(String name, fVec3 value);
		void SetUniformMat4(String name, fMat4 value);

		private:
		// It could have been squized in the abstract class if shader parsing remains same for all platform..
		uint compileShader(uint t);
		String parseShader(String sha);
		uint queryUniformMapping(String name);
		std::map<String, uint> m_uniformList;
	};

}