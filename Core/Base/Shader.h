#pragma once

#include<iostream>

#include "../../includes/GLM/glm/glm.hpp"
#include "../../includes/GLM/glm/gtc/matrix_transform.hpp"
#include "../../includes/GLM/glm/gtc/type_ptr.hpp"

typedef std::string String;

namespace Abs
{
	class Shader
	{
		public:
		Shader() {}

		virtual uint CreateProgram() = 0;
		virtual void UpdatePath(String path) = 0;
		virtual inline uint GetProgramID() = 0;
		virtual void DeleteProgram() = 0;
		virtual void UseProgram() = 0;

		protected:
		String m_dirPath;

		// for now inherited had implemented 
		// virtual uint compileShader(uint t) {}
		// virtual String parseShader(String sha) {}
	};
}