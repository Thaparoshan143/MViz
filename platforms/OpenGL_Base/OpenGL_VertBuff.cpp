#include"OpenGL_VertBuff.h"

namespace OpenGL
{
	OpenGL_VertBuff::OpenGL_VertBuff(uint size) : VertexBuffer(size)
	{
		glGenBuffers(1, &this->m_id);
	}

	void OpenGL_VertBuff::LoadBuffer(uint loadMode)
	{
		glBindBuffer(GL_ARRAY_BUFFER, this->m_id);
		glBufferData(GL_ARRAY_BUFFER, this->m_data.GetCount() * sizeof(float), this->m_data.GetData(), loadMode);
	}

	void OpenGL_VertBuff::DirectLoad(float *data, uint count, uint loadMode)
	{
		glBindBuffer(GL_ARRAY_BUFFER, this->m_id);
		glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), data, loadMode);
	}

	void OpenGL_VertBuff::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, this->m_id);
	}

	void OpenGL_VertBuff::Unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}