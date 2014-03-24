#include "Utilities.h"

int g_gl_width = 1280;
int g_gl_height = 720;
double deltaTime = 0; 

Matrix4 * Ortho;
void Orthographic(float a_fLeft, float a_fRight, float a_fTop, float a_fBottom, float a_fNear, float a_fFar, tbyte::Matrix4 * mat)
{
float deltaX = a_fRight - a_fLeft;
float deltaY = a_fTop - a_fBottom;
float deltaZ = a_fNear - a_fFar;

mat->m_afArray[0] = 2.f / deltaX;
mat->m_afArray[1] = 0.f;
mat->m_afArray[2] = 0.f;
mat->m_afArray[3] = 0.f;
mat->m_afArray[4] = 0.f;
mat->m_afArray[5] = 2.f / deltaX;
mat->m_afArray[6] = 0.f;
mat->m_afArray[7] = 0.f;
mat->m_afArray[8] = 0.f;
mat->m_afArray[9] = 0.f;
mat->m_afArray[10] = 2.f / deltaX;
mat->m_afArray[11] = 0.f;
mat->m_afArray[12] = ((a_fLeft + a_fRight)/(a_fLeft - a_fRight));
mat->m_afArray[13] = ((a_fBottom + a_fTop)/(a_fBottom - a_fTop));
mat->m_afArray[14] = ((a_fNear + a_fFar)/(a_fNear - a_fFar));
mat->m_afArray[15] = 1.f;
}


double getDeltaTime()
{
return deltaTime;
}

void resetDeltaTime()
{
deltaTime = glfwGetTime();
glfwSetTime(0);
}
