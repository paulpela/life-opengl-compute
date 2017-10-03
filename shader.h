#pragma once

#include <GL/glew.h>

GLuint getShader(const char* path, GLenum type);
void printShaderInfoLog(GLuint shader);
