#include"./OpenGL_Text.h"

namespace OpenGL
{
    FreetypeText::FreetypeText(OpenGL_Win &target, String text) : Text(text), m_target(target)
    {
        initFreetypeFont();
		std::cout << "The given text is :" << this->m_text << std::endl;
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
					static_cast<unsigned int>(face->glyph->advance.x)
				};
				Characters.insert(std::pair<char, Abs::Character>(c, character));
			}
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		FT_Done_Face(face);
		FT_Done_FreeType(ft);
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
        VBO.Bind();
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
    }

    void FreetypeText::RenderText(OpenGL_Sha &shader, float x, float y, float scale, dVec3 color)
    {
        shader.UseProgram();
		glUniform3f(glGetUniformLocation(shader.GetProgramID(), "textColor"), color.x, color.y, color.z);
		glActiveTexture(GL_TEXTURE0);
		glBindVertexArray(VAO);

        OpenGL_Win *targetWindow = (OpenGL_Win*)glfwGetWindowUserPointer(m_target.m_window);
        iVec2 winDim = iVec2(targetWindow->m_wi.width, targetWindow->m_wi.height);
        // Reducing to half size 
        winDim = winDim/2;

		// iterate through all characters
		std::string::const_iterator c;
		for (c = m_text.begin(); c != m_text.end(); c++) 
		{
			Abs::Character ch = Characters[*c];

			float xpos = ((x + ch.Bearing.x * scale)-(winDim.x))/(winDim.x);
			float ypos = ((-y - (ch.Size.y - ch.Bearing.y) * scale)+(winDim.y))/(winDim.y);

			float w = (ch.Size.x * scale)/(winDim.x);
			float h = (ch.Size.y * scale)/(winDim.y);

			// std::cout << "Character : " << *c <<std::endl;
			// std::cout << "Normalize Position (x,y) : " << xpos << ", " << ypos << " || " << x << " , " << y << std::endl;
			// std::cout << "Normalize Width, Height : " << w << ", " << h << std::endl;

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
			glBindBuffer(GL_ARRAY_BUFFER, VBO.Bind());
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			// render quad
			glDrawArrays(GL_TRIANGLES, 0, 6);
			// now advance cursors for next glyph (note that advance is number of 1/64 pixels)
			x += ((ch.Advance >> 6) * scale); // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
		}
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);
    }
}