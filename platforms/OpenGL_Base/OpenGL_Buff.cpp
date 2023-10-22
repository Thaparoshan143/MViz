#include"OpenGL_Buff.h"

namespace OpenGL
{
	// Vertex Buffer Object part
	OpenGL_VertBuffObj::OpenGL_VertBuffObj(uint size) : VertexBufferObject(size)
	{
		glGenBuffers(1, &this->m_id);
	}

	void OpenGL_VertBuffObj::LoadBuffer(uint loadMode)
	{
		glBindBuffer(GL_ARRAY_BUFFER, this->m_id);
		glBufferData(GL_ARRAY_BUFFER, this->m_data.GetCount() * sizeof(float), this->m_data.GetData(), loadMode);
	}

	void OpenGL_VertBuffObj::DirectLoad(float *data, uint count, uint loadMode)
	{
		glBindBuffer(GL_ARRAY_BUFFER, this->m_id);
		glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), data, loadMode);
	}

	uint OpenGL_VertBuffObj::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, this->m_id);
		return this->m_id;
	}

	void OpenGL_VertBuffObj::Unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	// Vertex Array Object part
	OpenGL_VertArrObj::OpenGL_VertArrObj(Abs::BufferFormat bf) : VertexArrayObject(bf)
	{
		glGenVertexArrays(1, &m_id);
	}

	uint OpenGL_VertArrObj::Bind()
	{
		glBindVertexArray(m_id);
		return m_id;
	}

	void OpenGL_VertArrObj::Unbind()
	{
		glBindVertexArray(0);
	}

	uint OpenGL_VertArrObj::getVBOStride()
	{
		return (getMask(BUFFER_MASKPPP)+ (getMask(BUFFER_MASKRGB)>>3) + (getMask(BUFFER_MASKTEX)>>6));
	}
}