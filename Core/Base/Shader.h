#pragma once

#include<iostream>

#include "../../includes/GLM/glm/glm.hpp"
#include "../../includes/GLM/glm/gtc/matrix_transform.hpp"
#include "../../includes/GLM/glm/gtc/type_ptr.hpp"

#include"./Types.h"

namespace Abs
{
	class Shader
	{
		public:
		Shader(String path = "../res/Shaders/") {	m_dirPath = path;	}

		virtual uint CreateProgram() = 0;
		void UpdatePath(String path) {	m_dirPath = path;	};
		inline uint GetProgramID() {	return m_programID;	};
		virtual void DeleteProgram() = 0;
		virtual void UseProgram() = 0;

		protected:
		String m_dirPath;
		uint m_programID;

		// for now inherited had implemented 
		// virtual uint compileShader(uint t) {}
		// virtual String parseShader(String sha) {}
	};
}