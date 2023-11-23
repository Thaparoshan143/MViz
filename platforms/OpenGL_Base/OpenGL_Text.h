#pragma once

#include"../../Core/Base/Text.h"
#include"./OpenGL_Sha.h"
#include"./OpenGL_Win.h"
#include"./OpenGL_Buff.h"

#include "../../includes/freetypeinc/ft2build.h"
#include "../../includes/freetypeinc/freetype/freetype.h"

namespace OpenGL
{
    #define BASE_FONT_SIZE 1/2.0
    // Map 
    // String (font family name) as key and CharMap as value (which is also map..)
    using FontMap = std::map<String, Abs::CharMap>;

    class FreetypeText : public Abs::Text
    {
        public:
        FreetypeText(String &text, String fontFamily="Roboto");

        static void UpdateTarget(GLFWwindow *target)   {   m_target = target;  }
        void UpdateText(String &text) { m_text = text; }
        void UpdateFontFamily(String fontFamily)   {   m_fontFamily = fontFamily;  initFreetypeFont();  }

        void RenderText(uint shaderID, float x, float y, float scale, Color color, bool normalize=true);
        void RenderText(OpenGL_Sha &shader, float x, float y, float scale, Color color, bool normalize=true);
    
        private:
        void initFreetypeFont();
        OpenGL_VertBuffObj m_VBO;
        OpenGL_VertArrObj m_VAO;
        // OpenGL_Win &m_target;
        // target window to render text, required for getting user pointer..
        static GLFWwindow *m_target;
        static FontMap m_fontFamilyList;
    };
}