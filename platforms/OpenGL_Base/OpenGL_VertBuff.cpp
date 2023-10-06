#include"OpenGL_VertBuff.h"

namespace Sandbox
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
	
	void OpenGL_VertBuff::Append(float *data, uint count)
	{
		this->m_data.Append(data, count);
	}

	void OpenGL_VertBuff::Clear()
	{
		this->m_data.Clear();
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