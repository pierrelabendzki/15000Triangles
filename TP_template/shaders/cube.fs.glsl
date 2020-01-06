#version 310 es
precision mediump float;

in vec3 vs_color;
in vec3 fvertexColor;
in vec3 _uKs;
in vec3 _uLightDir_vs;
in vec3 _uLightIntensity;
in float _uShininess;



vec3 blinnPhong = _uLightIntensity *(vs_color*(dot(_uLightDir_vs, vNoral_vs))+_uKs*pow(dot(halfVector,Vnormal_vs),_uShininess));

out vec4 FragColor;


void main() {
	FragColor = vec4(vs_color,0.5);
}
