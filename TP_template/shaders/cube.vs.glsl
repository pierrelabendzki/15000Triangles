#version 310 es
precision mediump float;


layout (location = 0) in vec3 aPosition; 
layout (location = 1) in vec3 vertexColor ;

uniform mat4 Mprojo;
uniform mat4 MVMatrix;
uniform mat4 NormalMatrix;
uniform mat4 MatrixView;

// uniform vec3 uKd;
uniform vec3 uKs;
uniform vec3 uLightDir_vs;
uniform vec3 uLightIntensity;
uniform float uShininess;


uniform vec3 uColor;


out vec3 fvertexColor;
out vec3 vs_color;

// out vec3 _uKd;
out vec3 _uKs;
out vec3 _uLightDir_vs;
out vec3 _uLightIntensity;
out float _uShininess;


void main() {
		fvertexColor = vertexColor;
		vs_color = uColor;
		
		// _uKd = uKd;
		_uKs = uKs;
		_uLightDir_vs = _uLightDir_vs;
		_uLightIntensity = uLightIntensity;

		gl_Position = Mprojo*MatrixView*MVMatrix *NormalMatrix*vec4(aPosition , 1.0);
		


	}
