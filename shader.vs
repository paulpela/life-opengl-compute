#version 450 core
layout (location = 8) uniform float timer;
layout (location = 9) uniform float rand;

layout (location = 1) uniform vec2 in_offs;

out vec2 offs;

void main() {
    vec2 verts[6] = {
        vec2(-1.0f, -1.0f),
        vec2( 1.0f, -1.0f),
        vec2( 1.0f,  1.0f),
        vec2(-1.0f, -1.0f),
        vec2( 1.0f,  1.0f),
        vec2(-1.0f,  1.0f),
    };


    gl_Position = vec4(verts[gl_VertexID], 0.0, 1.0);
    offs = in_offs;
}
