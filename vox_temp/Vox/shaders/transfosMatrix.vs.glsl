#version 330 core

layout(location = 0) in vec2 aVertexPosition;
layout(location = 1) in vec3 aVertexColor;

out vec3 vFragColor;

mat3 translate(float tx, float ty) {
    return mat3(vec3(1, 0, 0), vec3(0, 1, 0), vec3(tx, ty, 1));
};

mat3 scale(float sx, float sy) {
    return mat3(vec3(sx, 0, 0), vec3(0, sy, 0), vec3(0, 0, 1));
};

mat3 rotate(float a) {
    float rad = radians(a);
    return mat3(
        vec3(cos(rad), sin(rad), 0),
        vec3(-sin(rad), cos(rad), 0),
        vec3(0, 0, 1)
    );
};

void main() {
    vFragColor = aVertexColor;

    mat3 T = translate(0.5, 0);
    mat3 S = scale(0.5, 0.5);
    mat3 R1 = rotate(45);
    mat3 R2 = rotate(-45);

    mat3 M = T * R1 * S * R2;

    vec2 transformed = (M * vec3(aVertexPosition, 1)).xy;
    gl_Position = vec4(transformed, 0, 1);
};

