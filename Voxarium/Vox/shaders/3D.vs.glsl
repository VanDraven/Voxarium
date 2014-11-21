#version 330 core

layout(location = 0) in vec3 aVertexPosition;
//layout(location = 1) in vec3 aCubePosition;
//layout(location = 2) in vec2 aVertexTexCoords;

uniform mat4 uMVPMatix;
uniform mat4 uMVMatrix;
//uniform mat4 uNormalMatrix;

out vec3 mvPos;
//out vec3 mvNorm;
//out vec2 fVertexTexCoords;

void main(){
	vec3 pos = aVertexPosition; //*aCubePosition;
	mvPos = vec3(uMVMatrix*vec4(pos, 1));
	//mvNorm = vec3(uNormalMatrix*vec4(aVertexNormal, 0));
	//fVertexTexCoords = aVertexTexCoords;
	gl_Position = uMVPMatix*vec4(pos, 1);
}