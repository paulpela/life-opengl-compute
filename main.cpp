#include "config.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "keyboard.h"
#include "shader.h"
#include "window.h"
#include "utils.h"
#include "colors.h"

using namespace glm;

#define TEX_SIZE_X 1200
#define TEX_SIZE_Y 1200
#define STEP_SIZE 10.0f;

vec4 colorDead = vec4(0.980f, 0.980f, 0.824f, 1.0f);
vec4 colorLive = vec4(1.0f, 0.271f, 0.0f, 1.0f);

vec2 offset = vec2(0.0f, 0.0f);

extern int magnification;

extern bool directionalKeys[4];

extern bool paused;

int main(int argc, char** argv) {
    srand(time(NULL));
    glfwInit();

    GLFWwindow* window = glfwCreateWindow(800, 600, "title", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, keyCallback);

    glewExperimental = true;
    glewInit();

    printf("Renderer: %s\n", glGetString(GL_VERSION));

    glViewport(0, 0, 800, 600);
    glfwSetWindowSizeCallback(window, onWindowResize);

    //glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_FRAMEBUFFER_SRGB);

    GLuint vs = getShader("shader.vs", GL_VERTEX_SHADER);
    GLuint fs = getShader("shader.fs", GL_FRAGMENT_SHADER);
    GLuint program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glDeleteShader(vs);
    glDeleteShader(fs);

    GLuint cs = getShader("shader.compute", GL_COMPUTE_SHADER);
    GLuint cprogram = glCreateProgram();
    glAttachShader(cprogram, cs);
    glLinkProgram(cprogram);
    glDeleteShader(cs);

    GLuint vao;
    glCreateVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    GLuint tex1;
    glCreateTextures(GL_TEXTURE_2D, 1, &tex1);
    glTextureStorage2D(tex1, 1, GL_RGBA32F, TEX_SIZE_X, TEX_SIZE_Y);
    
    GLfloat* data1 = (GLfloat*) calloc(TEX_SIZE_X * TEX_SIZE_Y * 4, sizeof(GLfloat));
    
    for(size_t i = 0; i < TEX_SIZE_Y; i++) {
        for(size_t j = 0; j < TEX_SIZE_X; ) {
            data1[i * TEX_SIZE_X * 4 + j * 4 + 0] = colorLive.r;
            data1[i * TEX_SIZE_X * 4 + j * 4 + 1] = colorLive.g;
            data1[i * TEX_SIZE_X * 4 + j * 4 + 2] = colorLive.b;
            data1[i * TEX_SIZE_X * 4 + j * 4 + 3] = colorLive.a;
            j += rand() % 4;
        }
    }
    glTextureSubImage2D(tex1, 0, 0, 0, TEX_SIZE_X, TEX_SIZE_Y, GL_RGBA, GL_FLOAT, data1);
    free(data1);
    glBindTexture(GL_TEXTURE_2D, tex1);
    
    GLuint tex2;
    glCreateTextures(GL_TEXTURE_2D, 1, &tex2);
    glTextureStorage2D(tex2, 1, GL_RGBA32F, TEX_SIZE_X, TEX_SIZE_Y);
    
    GLfloat* data2 = (GLfloat*) calloc(TEX_SIZE_X * TEX_SIZE_Y * 4, sizeof(GLfloat));
    
    for(size_t i = 0; i < TEX_SIZE_Y; i += 4) {
        for(size_t j = 0; j < TEX_SIZE_X; ) {
            data2[i * TEX_SIZE_X * 4 + j * 4 + 0] = colorDead.r;
            data2[i * TEX_SIZE_X * 4 + j * 4 + 1] = colorDead.g;
            data2[i * TEX_SIZE_X * 4 + j * 4 + 2] = colorDead.b;
            data2[i * TEX_SIZE_X * 4 + j * 4 + 3] = colorDead.a;
            j += rand() % 4;
        }
    }
    glTextureSubImage2D(tex2, 0, 0, 0, TEX_SIZE_X, TEX_SIZE_Y, GL_RGBA, GL_FLOAT, data2);
    free(data2);
    glBindTexture(GL_TEXTURE_2D, tex2);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    
    GLint t1 = 0;
    GLint t2 = 1;
    GLint temp = 0;

    while(!glfwWindowShouldClose(window)) {

        if(!paused) {
            glBindImageTexture(t1, tex1, 0, GL_FALSE, 0, GL_READ_ONLY, GL_RGBA32F);
            glBindImageTexture(t2, tex2, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F);
            glUseProgram(cprogram);
            glUniform4fv(1, 1, value_ptr(colorLive));
            glUniform4fv(2, 1, value_ptr(colorDead));
            glDispatchCompute(TEX_SIZE_X / 20, TEX_SIZE_Y / 20, 1);

            glUseProgram(program);
            glBindTexture(GL_TEXTURE_2D, tex1);
            glClearBufferfv(GL_COLOR, 0, colorDarkGrey);
            glClearBufferfv(GL_DEPTH, 0, &depthDefault);
            glUniform1f(8, (float) glfwGetTime());
            glUniform1f(9, (float) rand());
            glUniform2fv(1, 1, value_ptr(offset));
            glUniform1i(3, magnification);
            glDrawArrays(GL_TRIANGLES, 0, 6); 
            glfwSwapBuffers(window);

            glBindTexture(GL_TEXTURE_2D, tex2);
            glClearBufferfv(GL_COLOR, 0, colorDarkGrey);
            glClearBufferfv(GL_DEPTH, 0, &depthDefault);
            glUniform1f(8, (float) glfwGetTime());
            glUniform1f(9, (float) rand());
            glUniform2fv(1, 1, value_ptr(offset));
            glUniform1i(3, magnification);
            glDrawArrays(GL_TRIANGLES, 0, 6); 
            glfwSwapBuffers(window);

            temp = t1;
            t1 = t2;
            t2 = temp;
        }
        glfwPollEvents();

        if(directionalKeys[0]) {
            offset.y += STEP_SIZE;
            printf("offset: %d,%d\n", (int) offset.x, (int) offset.y);
        }
        if(directionalKeys[1]) {
            offset.y -= STEP_SIZE;
            printf("offset: %d,%d\n", (int) offset.x, (int) offset.y);
        }
        if(directionalKeys[2]) {
            offset.x -= STEP_SIZE;
            printf("offset: %d,%d\n", (int) offset.x, (int) offset.y);
        }
        if(directionalKeys[3]) {
            offset.x += STEP_SIZE;
            printf("offset: %d,%d\n", (int) offset.x, (int) offset.y);
        }
    }

    glfwTerminate();


    return 0;
}
