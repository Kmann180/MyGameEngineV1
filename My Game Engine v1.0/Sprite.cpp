#include "Sprite.h"

Sprite::Sprite(void)
{
	//Default Shaders for Default constructor

	const char * VertexShader =	// Vertex Shaders deal with objects in 3D space
		"#version 330\n"
		"layout(location = 0) in vec3 position;"
		"layout(location = 1) in vec4 color;"
		//"in vec2 texcoord;"
		"out vec4 vColor;"
		"void main() {"
		"	vColor = color;"
		"	gl_Position = vec4 (position, 1.0);"
		"}";

	const char * FragmentShader =	// Fragment Shaders dela with pixel data
		"#version 330\n"
		"in vec4 vColor;"
		//"in vec2 texcoord;"
		"out vec4 outColour;"
		"void main () {"
		"	outColour = vColor;"
		"}";
	// Compile Vertex Shader
	m_VertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(m_VertexShader, 1, &VertexShader, NULL);
	glCompileShader(m_VertexShader);
	printShaderInfoLog(m_VertexShader);

	// Compile Fragment Shader
	m_FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(m_FragmentShader, 1, &FragmentShader, NULL);
	glCompileShader(m_FragmentShader);
	printShaderInfoLog(m_FragmentShader);

	// Link Shaders into Shader Program
	m_ShaderProgram = glCreateProgram();

	glAttachShader(m_ShaderProgram, m_FragmentShader);
	glAttachShader(m_ShaderProgram, m_VertexShader);

	glLinkProgram(m_ShaderProgram);
	printProgramInfoLog(m_ShaderProgram);

	glUseProgram(m_ShaderProgram);

}


Sprite::~Sprite(void)
{
}
Sprite::Sprite( const char* a_pTexture, int a_iWidth, int a_iHeight, tbyte::Vector4 a_v4Color ,GLFWwindow * window)
{

	GameWindow = window;
	//Default Shaders for Default constructor

	const char * VertexShader =	// Vertex Shaders deal with objects in 3D space
		"#version 330\n"
		"in vec3 position;"
		"in vec4 color;"
		"in vec2 texcoord;"
		"out vec2 UV;"
		"out vec4 vColor;"
		"uniform mat4 matrix;" // our matrix
		"void main() {"
		"	UV = texcoord;"
		"	gl_Position = matrix * vec4 (position, 1.0);"
		"	vColor = color;"
		"}";

	const char * FragmentShader =	// Fragment Shaders dela with pixel data
		"#version 330\n"
		"in vec4 vColor;"
		"in vec2 UV;"
		"out vec4 outColour;"
		"uniform sampler2D diffuseTexture;"
		"void main () {"
		"	outColour =  texture2D(diffuseTexture, UV) * vColor;"
		"}";
	// Compile Vertex Shader
	m_VertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(m_VertexShader, 1, &VertexShader, NULL);
	glCompileShader(m_VertexShader);
	printShaderInfoLog(m_VertexShader);

	// Compile Fragment Shader
	m_FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(m_FragmentShader, 1, &FragmentShader, NULL);
	glCompileShader(m_FragmentShader);
	printShaderInfoLog(m_FragmentShader);

	// Link Shaders into Shader Program
	m_ShaderProgram = glCreateProgram();

	glAttachShader(m_ShaderProgram, m_FragmentShader);
	glAttachShader(m_ShaderProgram, m_VertexShader);

	glLinkProgram(m_ShaderProgram);
	printProgramInfoLog(m_ShaderProgram);
	glUseProgram(m_ShaderProgram);

	m_v4SpriteColor = a_v4Color;

	m_aoVerts[0].Pos = tbyte::Vector3(	-0.5f,  0.5f,  0.0f);
	m_aoVerts[1].Pos = tbyte::Vector3(	0.5f,  0.5f,  0.0f);
	m_aoVerts[2].Pos = tbyte::Vector3(	-0.5f,  -0.5f,  0.0f);
	m_aoVerts[3].Pos = tbyte::Vector3(	0.5f,  -0.5f,  0.0f);
	
	/*
	m_aoVerts[0].Color = tbyte::Vector4(1.0f,  0.0f,  0.0f, 1.0f);
	m_aoVerts[1].Color = tbyte::Vector4(0.0f,  1.0f,  0.0f, 1.0f);
	m_aoVerts[2].Color = tbyte::Vector4(0.0f,  0.0f,  1.0f, 1.0f);
	m_aoVerts[3].Color = tbyte::Vector4(1.0f,  1.0f,  1.0f, 1.0f);
	*/


	m_aoVerts[0].Color = m_v4SpriteColor;
	m_aoVerts[1].Color = m_v4SpriteColor;
	m_aoVerts[2].Color = m_v4SpriteColor;
	m_aoVerts[3].Color = m_v4SpriteColor;



	m_aoVerts[0].UV = tbyte::Vector2(0.0f,  0.0f);
	m_aoVerts[1].UV = tbyte::Vector2(0.0f,  1.0f);
	m_aoVerts[2].UV = tbyte::Vector2(1.0f,  0.0f);
	m_aoVerts[3].UV = tbyte::Vector2(1.0f,  1.0f);

	GLuint elements[] =
	{
		0,1,2,3
	};

	//Gen Buffers
	glGenBuffers(1,&m_VBO);
	glGenBuffers(1,&m_EBO);
	glGenVertexArrays(1, &m_VAO);

	//Bind Buffers
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);

	//Put Data into buffers
	glBufferData(GL_ARRAY_BUFFER, 4* sizeof(Vertex), m_aoVerts, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

	//Enable some attributes
	GLint posAttrib = glGetAttribLocation(m_ShaderProgram,"position");
	glEnableVertexAttribArray(posAttrib);
	GLint colAttrib = glGetAttribLocation(m_ShaderProgram,"color");
	glEnableVertexAttribArray(colAttrib);
	GLint uvAttrib = glGetAttribLocation(m_ShaderProgram,"texcoord");
	glEnableVertexAttribArray(uvAttrib);


	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(colAttrib, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
	glVertexAttribPointer(uvAttrib, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(7 * sizeof(float)));

	glBindVertexArray(0);
	m_v3Position = tbyte::Vector3(0,0,0);
	modelMatrix =new float[16];	
	float temp[]= 
	{
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};
	memcpy(modelMatrix,temp,16*sizeof(float)); //not sure of a better way

	matrix_location = glGetUniformLocation (m_ShaderProgram, "matrix");

	m_uiTexture = 0;
	m_minUVCoords = tbyte::Vector2( 0.f, 0.f );
	m_maxUVCoords = tbyte::Vector2( 1.f, 1.f );
	m_uvScale = tbyte::Vector2( 1.f, 1.f );
	m_uvOffset = tbyte::Vector2( 0.f, 0.f );

	m_uSourceBlendMode	= GL_SRC_ALPHA;
	m_uDestinationBlendMode = GL_ONE_MINUS_SRC_ALPHA;

	glGenTextures(1, &m_uiTexture);
	glActiveTexture (GL_TEXTURE0);

	int width, height;
	unsigned char* image = SOIL_load_image(a_pTexture, &width, &height, 0, SOIL_LOAD_RGBA);
	glBindTexture( GL_TEXTURE_2D,m_uiTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	tex_loc = glGetUniformLocation (m_ShaderProgram, "diffuseTexture");
	glUseProgram (m_ShaderProgram);
	glUniform1i (tex_loc, 0); // use active texture 0

}

void Sprite::Draw()
{
	glBlendFunc (m_uSourceBlendMode, m_uDestinationBlendMode);
	glUseProgram(m_ShaderProgram);
	glActiveTexture(GL_TEXTURE0);
	glUniform1i (tex_loc, 0); 
	
	modelMatrix[12] = m_v3Position.m_fX;
	modelMatrix[13] = m_v3Position.m_fY;
	modelMatrix[14] = m_v3Position.m_fZ;
	
	
	glUniformMatrix4fv (matrix_location, 1, GL_FALSE, modelMatrix);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBindVertexArray(m_VAO);


	glDrawElements(GL_TRIANGLE_STRIP, 4,GL_UNSIGNED_INT,0);	
}

void Sprite::Input()
{
	  if (GLFW_PRESS == glfwGetKey(GameWindow, GLFW_KEY_W))
        {
			m_v3Position += tbyte::Vector3(0.0f, 0.005f, 0.0f);
	  }

        if (GLFW_PRESS == glfwGetKey(GameWindow, GLFW_KEY_A))
        {
                m_v3Position += tbyte::Vector3(-0.005f, 0.0f, 0.0f);
        }

        if (GLFW_PRESS == glfwGetKey(GameWindow, GLFW_KEY_S))
        {
			m_v3Position += tbyte::Vector3(0.0f, -0.005f, 0.0f);
		}

        if (GLFW_PRESS == glfwGetKey(GameWindow, GLFW_KEY_D))
        {
                 m_v3Position += tbyte::Vector3(0.005f, 0.0f, 0.0f);
        }

}

