#version 330 core

layout(location = 0) in vec2 aVertexPosition;
layout(location = 1) in vec3 aVertexColor;

out vec3 vFragColor;

void main() {
  vFragColor = aVertexColor;
  
  float x = aVertexPosition.x;
  float y = aVertexPosition.y;

  //x += 0.5;
  //y += 0.5;

  //x *= 2;
  //y *= 2;

  x *= 2;
  y *= 0.5;

  gl_Position = vec4(x, y, 0, 1);
};