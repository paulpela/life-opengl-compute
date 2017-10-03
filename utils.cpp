#include "utils.h"
#include <stdlib.h>

void generateFieldVertices(GLfloat field[], int fieldSize, GLfloat tileSize) {
    for(size_t i = 0; i < fieldSize; i++) {
        for(size_t j = 0; j < fieldSize; j++) {
            field[3 * (i * fieldSize + j) + 0] = (GLfloat) i * tileSize;
            field[3 * (i * fieldSize + j) + 1] = (GLfloat) j * tileSize;
            field[3 * (i * fieldSize + j) + 2] = 0.0f;
        }
    }
}

void generateFieldIndices(GLuint indices[], int fieldSize) {
    for(size_t i = 0; i < fieldSize - 1; i++) {
        for(size_t j = 0; j < fieldSize - 1; j++) {
            indices[6 * (i * fieldSize + j) + 0] = i * fieldSize + j;
            indices[6 * (i * fieldSize + j) + 1] = i * fieldSize + j + fieldSize;
            indices[6 * (i * fieldSize + j) + 2] = i * fieldSize + j;
            indices[6 * (i * fieldSize + j) + 3] = i * fieldSize + j + fieldSize + 1;
            indices[6 * (i * fieldSize + j) + 4] = i * fieldSize + j;
            indices[6 * (i * fieldSize + j) + 5] = i * fieldSize + j + 1;
        }
    }
}

void generateRandomVec3fv(GLfloat* data, size_t count) {
    for(size_t i = 0; i < count; i++) {
        data[i * 3 + 0] = (GLfloat) rand() / RAND_MAX;
        data[i * 3 + 1] = (GLfloat) rand() / RAND_MAX;
        data[i * 3 + 2] = (GLfloat) rand() / RAND_MAX;
    }
}
