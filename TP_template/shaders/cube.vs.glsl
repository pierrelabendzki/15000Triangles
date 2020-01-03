#version 300 es
precision mediump float;


layout (location = 0) in vec3 aPosition; 
uniform mat4 Mprojo;

void main() {
	gl_Position = Mprojo* vec4(aPosition - vec3(1.,1.,3.), 1.0);
}