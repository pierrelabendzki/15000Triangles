#version 310 es
precision mediump float;


layout (location = 0) in vec3 aPosition; 
//layout (location = 1) in vec3 aPositionCube;

uniform mat4 Mprojo;
uniform mat4 MVMatrix;
uniform mat4 NormalMatrix;
uniform mat4 MatrixView;

uniform vec3 uColor;

out vec3 vs_color;
void main() {
		vs_color = uColor;
		gl_Position = Mprojo*MatrixView*MVMatrix *NormalMatrix*vec4(aPosition , 1.0);
		
	}
