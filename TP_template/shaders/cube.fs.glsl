#version 310 es
precision mediump float;

in vec3 vs_color;
in vec3 fvertexColor;

out vec4 FragColor;
void main() {
	FragColor = vec4(vs_color,0.5);
}
