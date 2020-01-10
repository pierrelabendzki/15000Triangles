#version 300 es
precision mediump float;

in vec3 vs_color;
in vec3 vNormal;
in vec3 vPosition_vs;


out vec3 FragColor;


void main() {

	vec3 diffuse = vec3(0.,0.,0.);
	float diffuseFactor = dot(vNormal,vec3(1,-1,0.5));
	if(diffuseFactor > 0.){
		diffuse = vec3(1.,1.,1.)*diffuseFactor;
	}

	FragColor = (vs_color*0.7) + (0.2*diffuse);
}
