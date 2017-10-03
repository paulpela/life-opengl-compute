#version 450 core

uniform sampler2D s;

in vec2 offs;
layout (location = 3) uniform int magnification = 1;

out vec4 color;

void main() {
    color = texelFetch(s, ivec2(gl_FragCoord.x + offs.x, gl_FragCoord.y + offs.y) / magnification, 0);

    if(color == vec4(0)) {
        color = vec4(0.980f, 0.980f, 0.824f, 1.0f);
    }
}
