#version 330 core

layout(location = 0) in vec2 aVertexPosition;
layout(location = 1) in vec3 aVertexColor;

out vec3 vFragColor;
out vec2 vFragPosition;

mat3 scale(float sx, float sy) {
    return mat3(vec3(sx, 0, 0), vec3(0, sy, 0), vec3(0, 0, 1));
};

void main() {
    vFragPosition = aVertexPosition;
    vFragColor = aVertexColor;

    mat3 S = scale(6, 6);
    mat3 M = S;

    vec2 transformed = (M * vec3(aVertexPosition, 1)).xy;

    gl_Position = vec4(transformed, 0, 1);
};
