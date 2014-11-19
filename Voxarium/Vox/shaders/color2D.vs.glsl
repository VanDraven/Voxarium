#version 330 core

layout(location = 0) in vec3 vertexPosition; // The coordinates of a vertex of the generic cube
layout(location = 1) in vec3 cubePosition; // The coordinates of the center the specific cube being rendered
//layout(location = 2) in vec3 cubeType;

out vec3 vFragColor;


void main() {
	vFragColor = vec3(1.,1.,1.);
  gl_Position = vec4(vertexPosition + cubePosition, 1);
};