#pragma once

#include"../../Core/Base/Text.h"
#include"./OpenGL_Sha.h"
#include"./OpenGL_Win.h"
#include"./OpenGL_VertBuff.h"

#include "../../includes/freetypeinc/ft2build.h"
#include "../../includes/freetypeinc/freetype/freetype.h"

namespace OpenGL
{
    class FreetypeText : Abs::Text
    {
        public:
        FreetypeText(OpenGL_Win &target, String text = "Untitled");

        void RenderText(OpenGL_Sha &shader, float x, float y, float scale, dVec3 color);
    
        private:
        void initFreetypeFont();
        OpenGL_VertBuff VBO;
        uint VAO;
        // target window to render text, required for getting user pointer..
        OpenGL_Win &m_target;
        // yet to implement the font directory/ to load..
        // String m_fontdir;
    };
}