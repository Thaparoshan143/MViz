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

	// Map from stl std::map<char, Character>
	// - Char as key and Character (struct containg text info) as value
	using CharMap = std::map<char, Character>;	

	class Text
	{
		public:
		Text(String &text, String fontFamily) : m_text(text), m_fontFamily(fontFamily) {}

		String &m_text;
		String m_fontFamily;
		CharMap *m_activeCharacters;
	};
}