#pragma once

#include"../../includes/GLAD/glad.h"
#include"../../includes/GLFW/glfw3.h"

#include"../../Core/Base/Buffer.h"

namespace OpenGL
{
	class OpenGL_VertBuffObj : public Abs::VertexBufferObject
	{
		public:
		OpenGL_VertBuffObj(uint size = 2);
		
		void LoadBuffer(uint loadMode = GL_DYNAMIC_DRAW) override;
		void DirectLoad(float *data, uint count, uint loadMode = GL_DYNAMIC_DRAW);
		uint Bind() override;
		void Unbind() override;
		float* GetVertexData() {	return m_data.GetData();	}

		private:
		uint m_id;
	};

	class OpenGL_VertArrObj : public Abs::VertexArrayObject
	{
		public:
		OpenGL_VertArrObj(Abs::BufferFormat bf=Abs::BufferFormat::PP);

		uint Bind() override;
		void Unbind() override;


		private:
		uint m_id;
		// uint m_usage;
		// OpenGL_VertBuffObj *m_VBO;

		uint getVBOStride();
	};

}