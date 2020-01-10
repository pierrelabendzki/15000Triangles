#version 300 es
precision mediump float;


layout (location = 0) in vec3 aPosition; 
//layout (location = 1) in vec3 vertexColor ;
layout (location = 1) in vec3 aNormal ;

uniform mat4 Mprojo;
uniform mat4 MVMatrix;
uniform mat4 NormalMatrix;
uniform mat4 MatrixView;



uniform vec3 uColor;


out vec3 fvertexColor;
out vec3 vs_color;



out vec3 vNormal;
out vec3 vPosition_vs;

void main() {	
		vec4 vertexNormal = vec4(aNormal,0);
		vNormal = vec3(NormalMatrix*vertexNormal);	
		
		vs_color = uColor;
	
		vec4 vertexPosition = vec4(aPosition, 1);		
		vPosition_vs = vec3(MVMatrix * vertexPosition);

		

		gl_Position = Mprojo*MatrixView*MVMatrix *NormalMatrix*vec4(aPosition , 1.0);
		


	}