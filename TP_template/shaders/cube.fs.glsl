#version 310 es
precision mediump float;


out vec4 FragColor;
void main() {
	vec3 color = vec3(0.2+0.1, 0.3, 0.7-0.01);
	FragColor = vec4(color,1.0);
}
