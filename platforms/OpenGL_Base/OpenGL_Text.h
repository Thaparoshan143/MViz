#pragma once

#include"../../Core/Base/Text.h"
#include"./OpenGL_Sha.h"
#include"./OpenGL_Win.h"
#include"./OpenGL_Buff.h"

#include "../../includes/freetypeinc/ft2build.h"
#include "../../includes/freetypeinc/freetype/freetype.h"

namespace OpenGL
{
    // defining the base starting size for font using constant varient
    #define BASE_FONT_SIZE 1/2.0

    class FreetypeText : public Abs::Text
    {
        public:
        FreetypeText(OpenGL_Win &target, String &text);

        void UpdateText(String &text) { m_text = text; }

        void RenderText(uint shaderID, float x, float y, float scale, Color color, bool normalize=true);
        void RenderText(OpenGL_Sha &shader, float x, float y, float scale, Color color, bool normalize=true);
    
        private:
        void initFreetypeFont();
        OpenGL_VertBuffObj VBO;
        OpenGL_VertArrObj VAO;
        // target window to render text, required for getting user pointer..
        OpenGL_Win &m_target;
        // yet to implement the font directory/ to load..
        // String m_fontdir;
    };
}