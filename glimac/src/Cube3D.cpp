#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <glimac/FilePath.hpp>
#include <glimac/Program.hpp>
#include <iostream>
#include <vector>
#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp>
#include <math.h>
#include "glimac/Cube3D.hpp"

using namespace glimac;
Cube3D::Cube3D(){

	m_Position = glm::vec3(0.,0.,0.);
	m_Color = glm::vec3(1.,1.,1.);
	m_display = true;
	m_estDansLaListe = false;
	// m_tabPositions = {
	// 	0.5,0.5,0.5,
	// 	-0.5,0.5,0.5,
	// 	-0.5,-0.5,0.5,
	// 	0.5,-0.5,0.5,
	// 	0.5,-0.5,-0.5,
	// 	0.5,0.5,-0.5,
	// 	-0.5,0.5,-0.5,
	// 	-0.5,-0.5,-0.5
	// };
	// m_indexSommets={
 //        0,1,2, 0,2,3, // les deux premiers blocs de 3 coordonnées correspondent à la première face.
 //        4,7,6, 4,6,5,
 //        1,6,7, 1,7,2,
 //        0,3,4, 0,4,5,
 //        2,7,4, 2,4,3,
 //        0,5,6, 0,6,1
 //    };
	}
Cube3D::Cube3D(const float x, const float y, const float z, const float R, const float G, const float B){
	m_Position = glm::vec3(x,y,z);
	m_Color = glm::vec3(R,G,B);
	m_display = true;
	// m_tabPositions = {
	// 	x+0.5,y+0.5,z+0.5,
	// 	x-0.5,y+0.5,z+0.5,
	// 	x-0.5,y-0.5,z+0.5,
	// 	x+0.5,y-0.5,z+0.5,
	// 	x+0.5,y-0.5,z-0.5,
	// 	x+0.5,y+0.5,z-0.5,
	// 	x-0.5,y+0.5,z-0.5,
	// 	x-0.5,y+0.5,z+0.5
	// };
	// m_indexSommets={
 //        0,1,2, 0,2,3, // les deux premiers blocs de 3 coordonnées correspondent à la première face.
 //        4,7,6, 4,6,5,
 //        1,6,7, 1,7,2,
 //        0,3,4, 0,4,5,
 //        2,7,4, 2,4,3,
 //        0,5,6, 0,6,1
 //    };
}

glm::vec3 Cube3D::getPosition(){
	return m_Position;
}
glm::vec3 Cube3D::getColor(){
	return m_Color;
}

bool Cube3D::getDisplay(){
	return m_display;
}
bool Cube3D::getDansLaListe(){
	return m_estDansLaListe;
}

void Cube3D::setDisplay(bool display){
	m_display = display;
}
void Cube3D::setDansLaListe(bool l){
	m_estDansLaListe = l;
}
void Cube3D::setColor(glm::vec3 color){
	m_Color = color;
}


