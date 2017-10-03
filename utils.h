#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

using namespace glm;

void generateFieldVertices(GLfloat* field, int fieldSize, GLfloat tileSize);
void generateFieldIndices(GLuint* indices, int fieldSize);
void generateRandomVec3fv(GLfloat* data, size_t count);
