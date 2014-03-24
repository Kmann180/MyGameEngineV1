#pragma once
#ifndef _TEXTMAKER_H_
#define _TEXTMAKER_H_

#include "Utilities.h"
#include <tinyxml2.h>
#include "Sprite.h"

struct Char // makes a struct called Char that contains two structs,
	//one dealing with Vectors and the other dealing with floats
{
	union
	{
		struct
		{
			std::string sName;
			Vector2 v2Size;
			Vector4 v4Location;
			float yOffset;
		};
		struct
		{
			std::string Name;
			float width;
			float height;
			float x0;
			float x1;
			float y0;
			float y1;
			float Offset;

		};
	};
};

struct Font // struct that stores the size, sheet and the kerning of the font
{
	Vector2 v2Size;
	std::string sSheet;
	float fKerning;
};

class TextMaker
{
public:
	static TextMaker& Instance(); //Static member function that dynamically instances each character's sprite.
	void LoadFont(const char * a_pFontSheet); // self explanitory.
	void DrawString(std::string str, Vector2 pos, float scale); // draws the string you put into it.

protected:
	static void CleanUp(); // self explanitory

	TextMaker(void);
	~TextMaker(void);

	void LoadString(std::string str);
	Sprite iSprite;
	Font FontAtlas;
	std::map<char, Char> charMap; // maps where each thing is on the XML sheet
	std::vector<Char> DrawList; // list of hings to draw.
	int CharCount; // how many characters are in the string

	static TextMaker* MInstance;  // stores the instance

	GLuint PositionBuffer; // buffers!
	GLuint ColorBuffer;
	GLuint UVBuffer;
	GLuint MatrixBuffer;



};
#endif // _FONT_MANAGER_H_


