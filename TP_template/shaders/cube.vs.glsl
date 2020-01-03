#version 310 es
precision mediump float;


layout (location = 0) in vec3 aPosition; 
//layout (location = 1) in vec3 aPositionCube;

uniform mat4 Mprojo;
uniform float iterZ;
uniform float iterX;

out float col;
void main() {
	//for (float i =0.; i<3.;i+=1.){
		//vec3 aPositionCube = vec3(0.1*(i)-2.,-0.7,-3.5);
	float a = iterZ;
	float b = iterX;
	col = iterZ;
		gl_Position = Mprojo* vec4(aPosition - vec3(1.2*b,2.,1.2*a), 1.0);
	}
