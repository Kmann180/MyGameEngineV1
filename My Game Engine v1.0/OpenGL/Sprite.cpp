#include "Sprite.h"

#include "Sprite.h"

Sprite::Sprite(void)
{
	srand(time(NULL));
	LoadVertShader("./resources/exampleVert.glsl");
	LoadFragShader("./resources/exampleFrag.glsl");
	LinkShaders();

	m_v4SpriteColor = Vector4(1,1,1,1);
	

	m_aoVerts[0].Color = m_v4SpriteColor;
	m_aoVerts[1].Color = m_v4SpriteColor;
	m_aoVerts[2].Color = m_v4SpriteColor;
	m_aoVerts[3].Color = m_v4SpriteColor;

	m_aoVerts[0].UV = Vector2(1.0f,  0.0f);
	m_aoVerts[1].UV = Vector2(0.0f,  1.0f);
	m_aoVerts[2].UV = Vector2(1.0f,  0.0f);
	m_aoVerts[3].UV = Vector2(1.0f,  1.0f);

	m_v2Scale = Vector2(1,1);

	m_v3Position = Vector3(g_gl_width/2,g_gl_height/2,0);
	Hitbox = CollisionBox(m_aoVerts[0].Pos.m_fX, m_aoVerts[0].Pos.m_fY, m_aoVerts[4].Pos.m_fX, m_aoVerts[4].Pos.m_fY);
	
}


Sprite::~Sprite(void)
{

}
Sprite::Sprite( const char* a_pTexture, int a_iWidth, int a_iHeight, Vector4 a_v4Color ,GLFWwindow * window)
{
	Hitbox = CollisionBox(m_aoVerts[0].Pos.m_fX, m_aoVerts[0].Pos.m_fY, m_aoVerts[4].Pos.m_fX, m_aoVerts[4].Pos.m_fY);
	GameWindow = window;
	
	LoadVertShader("./resources/exampleVert.glsl");
	LoadFragShader("./resources/exampleFrag.glsl");
	LinkShaders();
	GLint uvAttrib = glGetAttribLocation(m_ShaderProgram,"texcoord");
	glEnableVertexAttribArray(uvAttrib);
	matrix_location = glGetUniformLocation (m_ShaderProgram, "matrix");
	LoadTexture(a_pTexture);


	m_v4SpriteColor = a_v4Color;

	
	m_aoVerts[0].Color = m_v4SpriteColor;
	m_aoVerts[1].Color = m_v4SpriteColor;
	m_aoVerts[2].Color = m_v4SpriteColor;
	m_aoVerts[3].Color = m_v4SpriteColor;
	

	m_aoVerts[0].UV = Vector2(0.0f,  0.0f);
	m_aoVerts[2].UV = Vector2(0.0f,  1.0f);
	m_aoVerts[1].UV = Vector2(1.0f,  0.0f);
	m_aoVerts[3].UV = Vector2(1.0f,  1.0f);

	m_v2Scale = Vector2(a_iWidth,a_iHeight);

	m_v3Position = Vector3(g_gl_width/2,g_gl_height/2,0);

	
}

Vector3 Sprite::GetPosition()
{
	return m_v3Position;
}
void Sprite::Draw()
{
	modelMatrix->m_afArray[0]  = m_v2Scale.m_fX * m_fZoom;
	modelMatrix->m_afArray[5]  = m_v2Scale.m_fY * m_fZoom;
	modelMatrix->m_afArray[12] = m_v3Position.m_fX;
	modelMatrix->m_afArray[13] = m_v3Position.m_fY;
	modelMatrix->m_afArray[14] = m_v3Position.m_fZ;


	*MVP =  (*Ortho * *modelMatrix) ;

	

	
	Quad::Draw();
}


void Sprite::SetPosition(Vector3 a_v3Pos)
{
	m_v3Position = a_v3Pos; 

}

void Sprite::SetPosition(float a_fX, float a_fY)
{
	m_v3Position.m_fX  = a_fX;
	m_v3Position.m_fY  = a_fY;

}


void Sprite::SetHitboxFlag(FlagType eFlagType, bool a_OnOff) // toggles hitbox flag (prolly no longer needed as hit box has its own function to do this.)
{
	Hitbox.SetFlag(eFlagType, a_OnOff);
}

void Sprite::SetScale(Vector2 a_v2Scale)
{
	m_v2Scale = a_v2Scale;
}
void Sprite::SetScale(float a_fScale)
{
	m_v2Scale.m_fX = a_fScale;
	m_v2Scale.m_fY = a_fScale;
}

void Sprite::SetScale(float a_fScaleX,float a_fScaleY)
{
	m_v2Scale.m_fX = a_fScaleX;
	m_v2Scale.m_fY = a_fScaleY;
}
Vector2 Sprite::GetScale()
{
	return m_v2Scale;

}