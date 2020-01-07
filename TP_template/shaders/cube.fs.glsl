#version 300 es
precision mediump float;

in vec3 vs_color;
in vec3 fvertexColor;


in vec3 vNormal;

out vec4 FragColor;


void main() {
	vec3 color = vNormal;
	FragColor = vec4(vs_color,0.5);
//FragColor = vec4(color,1.0);
}