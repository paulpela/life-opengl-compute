#ifdef INCLUDE_CUBE

#include <GL/glew.h>

static const GLfloat cubeVertices[] = {
    -0.25f, -0.05f, -0.25f,
    -0.25f,  0.05f, -0.25f,
     0.25f, -0.05f, -0.25f,
     0.25f,  0.05f, -0.25f,
     0.25f, -0.05f,  0.25f,
     0.25f,  0.05f,  0.25f,
    -0.25f, -0.05f,  0.25f,
    -0.25f,  0.05f,  0.25f
};

static const GLushort cubeIndices[] = {
    0, 1, 2,
    2, 1, 3,
    2, 3, 4,
    4, 3, 5,
    4, 5, 6,
    6, 5, 7,
    6, 7, 0, 
    0, 7, 1,
    6, 0, 2,
    2, 4, 6,
    7, 5, 3,
    7, 3, 1
};

static const GLfloat cubeTexcoords[] = {
    1.0f, 1.0f,
    1.0f, 0.0f,
    0.0f, 1.0f,
    0.0f, 0.0f,
    1.0f, 1.0f,
    1.0f, 0.0f,
    0.0f, 1.0f,
    0.0f, 0.0f
};

#endif
