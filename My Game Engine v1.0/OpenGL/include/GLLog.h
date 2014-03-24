#define GL_LOG_FILE "gl.log"
#ifndef _GLLOG_H_
#define _GLLOG_H_
#include <time.h>
#include <fstream>
#include <iostream>
#include <glew.h>


bool restart_gl_log () ;

bool gl_log (const char* message, const char* filename, int line); 
bool printShaderInfoLog(GLuint obj);

bool printProgramInfoLog(GLuint obj);


void log_gl_params ();

#endif //_GL_LOG_H_