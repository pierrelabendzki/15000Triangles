#version 300 es
precision mediump float;

in vec3 vs_color;
in vec3 vNormal;
in vec3 vPosition_vs;

in vec3 _uKd;
in vec3 _uKs;
in vec3 _uLightDir_vs;
in vec3 _uLightIntensity;
in float _uShininess;

//vec3 vNormal_vs = vec3(1,1,1);
//vec3 halfVector = vec3(1,1,1);

// vec3 halfVector() {
// return (normalize(-vPosition_vs)+_uLightDir_vs)/2.;
// };



 vec3 blinnPhong(){
     vec3 halfVector = (normalize(-vPosition_vs)+_uLightDir_vs)*0.5;

    return _uLightIntensity*(_uKd*(dot(_uLightDir_vs, vNormal))+_uKs*pow(dot(halfVector, vNormal),_uShininess));
 }

// vec3 BlinnPhong(){
// 	vec3 w_0 = normalize(-vPosition_vs);
// 	vec3 w_i  = normalize(-_uLightDir_vs);
// 	vec3 halfVector = 0.5*(w_i +w_0);
// 	_uKd = vec3(0.6,0.6,0.6);
// 	//float distance = distance(_uLightDir_vs);
// 	return _uLightIntensity *( (_uKd*dot(w_i,vNormal))+(_uKs*pow(2.,dot(halfVector,vNormal),_uShininess)));
// }


out vec3 FragColor;


void main() {
	// FragColor = vs_color*blinnPhong();
	//FragColor = vs_color+blinnPhong();
	
	vec3 diffuse = vec3(0.,0.,0.);
	float diffuseFactor = dot(vNormal,vec3(1,-1,0.5));
	if(diffuseFactor > 0.){
		diffuse = vec3(1.,1.,1.)*diffuseFactor;
	}


	

	FragColor = (vs_color*0.7) + (0.2*diffuse);
}
