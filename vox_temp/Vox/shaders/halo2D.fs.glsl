#version 330 core

in vec3 vFragColor;
in vec2 vFragPosition;

out vec3 fFragColor;


void main() {
    float dist = distance(vec2(0, 0), vFragPosition);
    float alpha = 3;
    float beta = -255;
    float a = alpha*exp(beta*(dist*dist));

    fFragColor = vFragColor * a;
};
