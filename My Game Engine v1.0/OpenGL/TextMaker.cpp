#include "TextMaker.h"

TextMaker* TextMaker::MInstance = 0;
TextMaker& TextMaker::Instance()
{
	if (MInstance == 0)
		MInstance = new TextMaker();
	return *MInstance;
}

TextMaker::TextMaker(void)
{
	atexit(&CleanUp);

	glGenBuffers(1,&PositionBuffer);
	glGenBuffers(1,&ColorBuffer);
	glGenBuffers(1, &UVBuffer);
	glGenBuffers(1,&MatrixBuffer);

}


TextMaker::~TextMaker(void)
{
}

void TextMaker::CleanUp()
{
	delete MInstance;
	MInstance = 0;

}

void TextMaker::LoadFont(const char* a_pFontSheet)
{
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLNode *rootNode, *currentNode;
	tinyxml2:: XMLElement *childElement;
	std::string str;

	char ch;
	doc.LoadFile(a_pFontSheet); // load the font file
	rootNode = doc.FirstChildElement("TextureAtlas");// root node in the xmlsheet
	currentNode = rootNode;

	childElement = currentNode->ToElement();
	FontAtlas.sSheet = childElement->Attribute("imagePath");
	FontAtlas.v2Size.m_fX = (float)childElement->IntAttribute("width"); 
	FontAtlas.v2Size.m_fY = (float)childElement->IntAttribute("height");
	FontAtlas.fKerning = (float)childElement->IntAttribute("kerning");

	iSprite.LoadTexture(FontAtlas.sSheet.c_str());
	iSprite.m_uvScale = FontAtlas.v2Size;
	GLint uvAttrib = glGetAttribLocation(iSprite.m_ShaderProgram,"texcoord");
	glEnableVertexAttribArray(uvAttrib);
	iSprite.matrix_location = glGetUniformLocation (iSprite.m_ShaderProgram, "matrix");

	for (childElement = currentNode->FirstChildElement(); childElement != NULL; childElement = childElement->NextSiblingElement())
	{
		str = childElement->Attribute("name");
		if(str.length() > 1)
		{
		
			if(str == "&amp")
			ch = '&';
			
			else if(str =="&apos")
				ch = '\'';
			
			else if(str ==	"&astr")
				ch = '*';
			
			else if(str ==	"&bar" )
				ch = '|';
			
			else if(str ==	"&bslsh")
				ch = '\\';
			
			else if(str ==	"&col" )
				ch = ':';
			
			else if(str ==	"&fslsh")
				ch = '/';
			
			else if(str ==	"&gt" )
				ch = '>';
			
			else if(str ==	"&lt" )
				ch = '<';
			
			else if(str ==	"&quest") 
				ch = '?';
			
			else if(str ==	"&quot" )
				ch = '\"';
			
			else if(str ==	"&under")
				ch = '_';


		}
		else{
			ch = str.at(0);
		}
		charMap[ch].Name = str;
		charMap[ch].x0 = childElement->IntAttribute("x");
		charMap[ch].y0 = childElement->IntAttribute("y");
		charMap[ch].width = childElement->IntAttribute("width");
		charMap[ch].height =childElement->IntAttribute("height");
		charMap[ch].x1 = charMap[ch].x0 + charMap[ch].width;	
		charMap[ch].y1 = charMap[ch].y0 + charMap[ch].height;
		charMap[ch].Offset = childElement->IntAttribute("offset");
		}

	ch = ' ';
	charMap[ch].Name = " ";
	charMap[ch].x0 = 0;
	charMap[ch].y0 = 0;
	charMap[ch].width = 8;
	charMap[ch].height =8;
	charMap[ch].x1 = 0;	
	charMap[ch].y1 = 0;
	charMap[ch].Offset = 0;
	ch = '\n';
	charMap[ch].Name = "&ret";
	charMap[ch].x0 = 0;
	charMap[ch].y0 = 0;
	charMap[ch].width = 0;
	charMap[ch].height =0;
	charMap[ch].x1 = 0;	
	charMap[ch].y1 = 0;
	charMap[ch].Offset = 0;
}

void TextMaker::LoadString(std::string str)
{
	DrawList.clear();
	char c;
	for(CharCount = 0; CharCount < str.length(); CharCount++)
	{
		c = str.at(CharCount);
		DrawList.push_back(charMap[c]);
	}

}

void TextMaker::DrawString(std::string str, Vector2 pos, float scale)
{
	LoadString(str);
	Char c;
	float newPos = 0;
	for(int i = 0; i < DrawList.size(); i++)
	{
		c= DrawList[i];
		
		if(i !=0)
		{
			if(c.Name == "&ret")
			{
				pos.m_fX -= 20;
				newPos = pos.m_fY-4;
			}

			else
			{
				newPos = iSprite.GetPosition().m_fX + (c.width/2) + (DrawList[i-1].width/2) + FontAtlas.fKerning;
			}

			iSprite.SetPosition(Vector3(newPos, pos.m_fY, 0.0f));
		}

		else
		{
			iSprite.SetPosition(Vector3((pos.m_fX + c.width/2),pos.m_fY, 0.f));
		}
			
		iSprite.m_minUVCoords = Vector2(c.x0,c.y0) ;
		iSprite.m_maxUVCoords = Vector2(c.x1,c.y1) ;
		iSprite.SetScale(c.width*scale,c.height*scale);

		iSprite.SetUVData();

		iSprite.modelMatrix->m_afArray[0]  = iSprite.GetScale().m_fX *iSprite.m_fZoom;
		iSprite.modelMatrix->m_afArray[5]  = iSprite.GetScale().m_fY *iSprite.m_fZoom;
		iSprite.modelMatrix->m_afArray[12] = iSprite.GetPosition().m_fX;
		iSprite.modelMatrix->m_afArray[13] = iSprite.GetPosition().m_fY  - (c.Offset *iSprite.m_fZoom); 
		iSprite.modelMatrix->m_afArray[14] = iSprite.GetPosition().m_fZ;

		*iSprite.MVP =  (*Ortho * *iSprite.modelMatrix) ;

		iSprite.Quad::Draw();
	}
}