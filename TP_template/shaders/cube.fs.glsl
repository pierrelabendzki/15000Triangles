#version 310 es
precision mediump float;

in float col;
out vec4 FragColor;
void main() {
	vec3 color = vec3(0.2+0.1*col, 0.3, 0.7-0.01*col);
	FragColor = vec4(color,1.0);
}
