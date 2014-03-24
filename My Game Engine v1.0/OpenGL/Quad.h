#ifndef _QUAD_H_
#define _QUAD_H_

#include <glew.h>
#include "GLLog.h"
//#include "GlobalUtilities.h" removed this because CollisionObjects.h has access to GlobalUtilities.h 
#include "TextFileReader.h"
#include "CollisionBox.h"

class Quad
{
public:
	Quad(void);
	~Quad(void);

	GLuint m_VBO;
	GLuint m_VAO;
	GLuint m_EBO;
	
	GLuint m_FragmentShader;
	GLuint m_VertexShader;

	GLuint m_ShaderProgram;

	Vertex m_aoVerts[4];

	
	Vector2 m_minUVCoords;
	Vector2 m_maxUVCoords;
	Vector2 m_uvScale;
	float m_fZoom;

	Matrix4* modelMatrix;
	Matrix4* viewMatrix;
	Matrix4* MVP;

	unsigned int m_uiTexture;
	GLFWwindow * GameWindow;
	
	unsigned int	m_uSourceBlendMode;
	unsigned int	m_uDestinationBlendMode;
	int tex_location;
	int matrix_location;
	int proj_location;
	int view_location;
	char* iFacing; // variable to track which way a quad is facing, may be obsolete now due to new structure.
	

	void Draw();
	bool LoadVertShader(const char*);

	bool LoadFragShader(const char*);
	bool LinkShaders();
	void LoadTexture(const char* a_pTexture);
	void SetUVData();
	void SetColor();
	void SetColor(Vector4 a_v4Color);
	void SetColor(Vector4 a_v4Color0,Vector4 a_v4Color1,Vector4 a_v4Color2,Vector4 a_v4Color3);
	void SwapUVs(Facing eFacing); // tries to flip the uv's to turn the sprite and flip the animation.
	bool FacingCheck(char* facing); // checks the facing.. see above
	

private:

};
#endif // _QUAD_
