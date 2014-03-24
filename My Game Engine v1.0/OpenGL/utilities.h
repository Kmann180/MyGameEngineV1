#ifndef _UTIL_H_
#define _UTIL_H_

#include <glew.h>
#include <glfw3.h>
#include <SOIL.h>

//Terry's Math lib
#include <TerrehByteMath.h>
//other helper functions
#include "GLLog.h"
#include "TextFileReader.h"

#include <string>
#include <queue>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <assert.h>
#include <functional>
#include <time.h>

using namespace tbyte;

extern Matrix4 * Ortho;
void Orthographic(float a_fLeft, float a_fRight, float a_fTop, float a_fBottom, float a_fNear, float a_fFar, tbyte::Matrix4 * mat);
#include <cstdlib>
#include <vector>




using namespace tbyte;

extern Matrix4 * Ortho;


//Window sizes to reference to later
extern int g_gl_width;
extern int g_gl_height;



struct Vertex // makin verts with position, color and uv
{

	union
	{
		struct 
		{
			Vector3 Pos;
			Vector4 Color;
			Vector2 UV;
		};
		
		struct
		{
			float X, Y, Z;
			float R, G, B, A;
			float U, V;
		};
	};
	

	bool operator == (const Vertex& rhs)
	{
		return (X == rhs.X && Y == rhs.Y && Z == rhs.Z && U == rhs.U && V == rhs.V && R == rhs.R && G == rhs.G && B == rhs.B && A == rhs.A );
	}
};

enum PlayType //play back style for animations
{
	ONCE,
	LOOP,
	LOOPSECTION,
	PINGPONG,
	REVERSE,
	RANDOMLOOP,
	RANDOM,
	SINGLE
};

enum Facing // TO FLIP QUAD FOR SPRITE FACING
{
	LEFT,
	RIGHT,
	UP,
	DOWN
};

enum FlagType // my utility belt for handing situational events
{
	GROUND,
	PLATFORM,
	DANGEROUS,
	DEADLY,
	SWING,
	CLIMB,
	LEDGE,
	SAFE,
	GOAL,
	PLAYER,
	AGGRESSIVE,
	CARRY,
	GROUNDED,
	ENEMY
};

typedef bool Flag; // may have been rendered obsolete by new structure.

	void ViewLookAt( Vector4& eye,  Vector4& to,  Vector4& up,Matrix4 * mat);

	void Orthographic(float a_fLeft, float a_fRight, float a_fTop, float a_fBottom, float a_fNear, float a_fFar,Matrix4 * mat);

	void Orthographic(float a_fWidth, float a_fHeight, float a_fNear, float a_fFar,Matrix4 * mat);

	void Perspective(float a_fUpFOV, float a_fAspectRatio, float a_fNear, float a_fFar,Matrix4 * mat);
	
	double getDeltaTime();
	void resetDeltaTime();

#endif