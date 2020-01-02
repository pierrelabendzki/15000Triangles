#version 300 es
precision mediump float;

void main() {
	vec3 color = vec3(0.2, 0.3, 0.7);
	gl_FragColor = vec4(color,1.0); 
}