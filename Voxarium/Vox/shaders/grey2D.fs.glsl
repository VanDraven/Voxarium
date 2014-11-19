#version 330 core

in vec3 vFragColor;

out vec3 fFragColor;

void main() {
	float m = (vFragColor.x + vFragColor.y + vFragColor.z) / 3;
    fFragColor = vec3(m, m, m) ;
};
