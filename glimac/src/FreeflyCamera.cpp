#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <glimac/FilePath.hpp>
#include <glimac/Program.hpp>
#include <iostream>
#include <vector>
#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp>
#include <math.h>
#include "glimac/FreeflyCamera.hpp"

using namespace glimac;

#define PI 3.141592


FreeflyCamera::FreeflyCamera(){
	m_Position = glm::vec3(0.,0.,0.);
	m_fPhi = PI;
	m_fTheta = 0.;
	m_FrontVector = glm::vec3(0.,0.,-1.);
	m_LeftVector = glm::vec3(1.,0.,0.);
	m_UpVector = glm::vec3(0.,-1.,0.);
}

FreeflyCamera::FreeflyCamera(const float x, const float y, const float z, const float Phi, const float Teta){
	m_Position = glm::vec3(x,y,z);
	m_fPhi = Phi;
	m_fTheta = Teta;
	m_FrontVector = glm::vec3(cos(m_fTheta)*sin(m_fPhi), sin(m_fTheta),cos(m_fTheta)*cos(m_fPhi));
	m_LeftVector = glm::vec3(sin(m_fPhi + PI*0.5),0,cos(m_fPhi + PI*0.5));
	m_UpVector = glm::cross(m_FrontVector,m_LeftVector);
}

void FreeflyCamera::moveLeft(float t){
	m_Position+=t*glm::vec3(1.,0.,0.);
}

void FreeflyCamera::moveFront(float t){
	m_Position+=t*glm::vec3(0.,0.,1.);
}

void FreeflyCamera::moveUp(float t){
	m_Position+=t*glm::vec3(0.,1.,0.);
}


void FreeflyCamera::rotateLeft(float degrees){
	float rad = degrees*0.0174533;
	m_fPhi +=rad;
	m_FrontVector = glm::vec3(cos(m_fTheta)*sin(m_fPhi), sin(m_fTheta),cos(m_fTheta)*cos(m_fPhi));
	m_LeftVector = glm::vec3(sin(m_fPhi + PI*0.5),0,cos(m_fPhi + PI*0.5));
	m_UpVector = glm::cross(m_FrontVector,m_LeftVector);

}

void FreeflyCamera::rotateUp(float degrees){
	float rad = degrees*0.0174533;
	m_fTheta += rad;
	m_FrontVector = glm::vec3(cos(m_fTheta)*sin(m_fPhi), sin(m_fTheta),cos(m_fTheta)*cos(m_fPhi));
	m_LeftVector = glm::vec3(sin(m_fPhi + PI*0.5),0,cos(m_fPhi + PI*0.5));
	m_UpVector = glm::cross(m_FrontVector,m_LeftVector);

}

glm::mat4 FreeflyCamera::getViewMatrix() const {
	return glm::lookAt(m_Position,m_Position+m_FrontVector,m_UpVector);
}
