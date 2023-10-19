#pragma once

#include<map>
#include"./Types.h"

namespace Abs
{
	struct Character {
	uint TextureID; // ID handle of the glyph texture
	iVec2   Size;      // Size of glyph
	iVec2   Bearing;   // Offset from baseline to left/top of glyph
	uint Advance;   // Horizontal offset to advance to next glyph
	};

	class Text
	{
		public:
		Text() : m_text("Untitled") {}
		Text(String text) : m_text(text) {}

		String m_text;

		std::map<char, Character> Characters;
	};

}