#include "config.h"
#include <GL/glew.h>
#include <stdlib.h>
#include <stdio.h>
#include "shader.h"

GLuint getShader(const char* path, GLenum type) {
    GLchar* source[1];
    size_t length = 0;
    FILE* f;
    GLuint shader;

    f = fopen(path, "r");

    if(!f) { 
        return 0; 
    }

    fseek(f, 0, SEEK_END);
    length = ftell(f);

    if(!length) {
        fclose(f);
        return 0;
    }

    rewind(f);

    source[0] = (GLchar*) calloc(1, sizeof(GLchar) * (length + 1));

    if(!source[0]) {
        fclose(f);
        return 0;
    }

    fread(source[0], 1, length, f);
    fclose(f);

    shader = glCreateShader(type);
    glShaderSource(shader, 1, source, NULL);
    glCompileShader(shader);

    free(source[0]);

    printShaderInfoLog(shader);

    return shader;
}

void printShaderInfoLog(GLuint shader) {
    GLsizei length;
    GLchar* infoLog = NULL;
    GLint type;
    char* shaderType = NULL;
    
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

    if(length) {
        glGetShaderiv(shader, GL_SHADER_TYPE, &type);

        switch(type) {
            case GL_VERTEX_SHADER:
                shaderType = "VERTEX";
                break;
            case GL_FRAGMENT_SHADER:
                shaderType = "FRAGMENT";
                break;
            default:
                shaderType = "UNKNOWN";
        }

        infoLog = (GLchar*) calloc(1, sizeof(GLchar) * (length + 1));
        if(infoLog) {
            glGetShaderInfoLog(shader, length, NULL, infoLog);
            printf(KRED "Shader %d / %s errors" KNRM ":\n%s\n", shader, shaderType, infoLog);
        }
    }
}
