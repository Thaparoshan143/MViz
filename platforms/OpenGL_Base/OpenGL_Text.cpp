#include"./OpenGL_Text.h"

namespace OpenGL
{
    FreetypeText::FreetypeText(OpenGL_Win &target, String &text) : Text(text), m_target(target)
    {
        initFreetypeFont();
		// std::cout << "The given text is :" << this->m_text << std::endl;
    }

    void FreetypeText::initFreetypeFont()
    {
        FT_Library ft;
		if (FT_Init_FreeType(&ft))
		{
			std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
			exit(1);
		}

		FT_Face face;
		if (FT_New_Face(ft, "../res/Fonts/Roboto.ttf", 0, &face)) {
			std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
			exit(1);
		}
		else {
			FT_Set_Pixel_Sizes(face, 0, 48);

			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

			for (unsigned char c = 0; c < 128; c++)
			{
				if (FT_Load_Char(face, c, FT_LOAD_RENDER))
				{
					std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
					continue;
				}

				unsigned int texture;
				glGenTextures(1, &texture);
				glBindTexture(GL_TEXTURE_2D, texture);
				glTexImage2D(
					GL_TEXTURE_2D,
					0,
					GL_RED,
					face->glyph->bitmap.width,
					face->glyph->bitmap.rows,
					0,
					GL_RED,
					GL_UNSIGNED_BYTE,
					face->glyph->bitmap.buffer
				);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

				Abs::Character character = {
					texture,
					iVec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
					iVec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
					static_cast<uint>(face->glyph->advance.x)
				};
				Characters.insert(std::pair<char, Abs::Character>(c, character));
			}
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		FT_Done_Face(face);
		FT_Done_FreeType(ft);
		VAO.Bind();
        VBO.Bind();
		// For text rendering we require only position (x,y) and texture (u,v).. for 6*4 (i.e using two triangle method to draw quad to draw text on top)
		VBO.ReserveBuffer(6*4, GL_DYNAMIC_DRAW);
		// Here 4 is the total vertex buffer size i.e two position and two texture data 
		VAO.EnableVertexAttribMan(4);
		// unbinding is not manditory, optional
		VAO.Unbind();
		VBO.Unbind();
    }

    void FreetypeText::RenderText(uint shaderID, float x, float y, float scale, Color color, bool normalize)
    {
		glUseProgram(shaderID);
		uint location = glGetUniformLocation(shaderID, "textColor");
		glUniform3f(location, color.r, color.g, color.b);
		glActiveTexture(GL_TEXTURE0);
		VAO.Bind();

        OpenGL_Win *targetWindow = (OpenGL_Win*)glfwGetWindowUserPointer(m_target.m_window);
        iVec2 winDim = targetWindow->GetWindowSize();
        // Reducing to half size 
        winDim = winDim/2;

		if(!normalize)
		{
			x = x * (winDim.x) + winDim.x;
			y = -1 * y * (winDim.y) + winDim.y;
		}

		scale = scale * ((float(winDim.x + winDim.y)/(400+300)));

		// iterate through all characters
		std::string::const_iterator c;
		for (c = m_text.begin(); c != m_text.end(); c++) 
		{
			Abs::Character ch = Characters[*c];
			float xpos = ((x + ch.Bearing.x * scale * BASE_FONT_SIZE)-(winDim.x))/(winDim.x);
			float ypos = ((-y - (ch.Size.y - ch.Bearing.y) * scale * BASE_FONT_SIZE)+(winDim.y))/(winDim.y);

			float w = (ch.Size.x * scale * BASE_FONT_SIZE)/(winDim.x);
			float h = (ch.Size.y * scale * BASE_FONT_SIZE)/(winDim.y);

			float vertices[6][4] = {
				{ xpos,     ypos + h,   0.0f, 0.0f },            
				{ xpos,     ypos,       0.0f, 1.0f },
				{ xpos + w, ypos,       1.0f, 1.0f },

				{ xpos,     ypos + h,   0.0f, 0.0f },
				{ xpos + w, ypos,       1.0f, 1.0f },
				{ xpos + w, ypos + h,   1.0f, 0.0f }
			};
			// render glyph texture over quad
			glBindTexture(GL_TEXTURE_2D, ch.TextureID);
			// update content of VBO memory
			VBO.LoadSubBuffer(6*4, *vertices);
			VBO.Unbind();
			// render quad
			glDrawArrays(GL_TRIANGLES, 0, 6);
			// now advance cursors for next glyph (note that advance is number of 1/64 pixels)
			x += ((ch.Advance >> 6) * scale * BASE_FONT_SIZE); // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
		}
		VAO.Unbind();
		glBindTexture(GL_TEXTURE_2D, 0);
    }

	void FreetypeText::RenderText(OpenGL_Sha &shader, float x, float y, float scale, Color color, bool normalize)
	{
		this->RenderText(shader.GetProgramID(), x, y, scale, color, normalize);
	}
}