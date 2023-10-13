#pragma once

#include"../../includes/GLAD/glad.h"
#include"../../includes/GLFW/glfw3.h"

#include"../../Core/Base/VertexBuffer.h"

namespace OpenGL
{
	class OpenGL_VertBuff : private Abs::VertexBuffer
	{
		public:
		OpenGL_VertBuff(uint size = 2);
		
		void LoadBuffer(uint loadMode = GL_DYNAMIC_DRAW) override;
		void DirectLoad(float *data, uint count, uint loadMode = GL_DYNAMIC_DRAW);
		void Append(float *data, uint count) override;
		void Clear() override;
		void Bind() override;
		void Unbind() override;
		float* GetVertexData() {	return m_data.GetData();	}

		private:
		uint m_id;
	};

}