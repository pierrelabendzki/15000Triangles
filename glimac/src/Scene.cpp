#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <glimac/FilePath.hpp>
#include <glimac/Program.hpp>
#include <iostream>
#include <vector>
#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp>
#include <math.h>
#include "glimac/Scene.hpp"
#include "glimac/Cube3D.hpp"

Scene::Scene(){
    nbCubes = 0;
}
void Scene::addCube(Cube3D cube, int programID){
        glm::mat4 MVMatrix= glm::translate(glm::mat4(), glm::vec3(cube.getPosition()[0],cube.getPosition()[1], cube.getPosition()[2]));
        GLuint MVMatrixID = glGetUniformLocation(programID,"MVMatrix");
        glUniformMatrix4fv(MVMatrixID,1,GL_FALSE,glm::value_ptr(MVMatrix));
        
        glm::vec3 uColor = cube.getColor();

        GLuint uColorID = glGetUniformLocation(programID,"uColor");
        glUniform3f(uColorID,uColor[0],uColor[1],uColor[2]);

        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        nbCubes++;
    }

    void Scene::addGhostCube(Cube3D cube, int programID){
        glm::mat4 MVMatrix= glm::translate(glm::mat4(), glm::vec3(cube.getPosition()[0],cube.getPosition()[1], cube.getPosition()[2]));
        GLuint MVMatrixID = glGetUniformLocation(programID,"MVMatrix");
        glUniformMatrix4fv(MVMatrixID,1,GL_FALSE,glm::value_ptr(MVMatrix));
        

        glm::vec3 uColor = cube.getColor();
        GLuint uColorID = glGetUniformLocation(programID,"uColor");
        glUniform3f(uColorID,uColor[0],uColor[1],uColor[2]);
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

        nbCubes++;
    }

    void Scene::show(bool appear,Cube3D cube, int programID){
        if(appear)
            addCube(cube,programID);
    }

    void Scene::showGhost(bool appear,Cube3D cube, int programID){
        if(appear)
            addGhostCube(cube,programID);
    }

    void Scene::setGhostCubePosition(int pos, Cube3D &cubeGhost, Cube3D &cubePere){
        if(pos==0)cubeGhost.setPosition(glm::vec3(cubePere.getPosition()[0],cubePere.getPosition()[1]+1.,cubePere.getPosition()[2]));
        if(pos==1)cubeGhost.setPosition(glm::vec3(cubePere.getPosition()[0]+1,cubePere.getPosition()[1],cubePere.getPosition()[2]));
        if(pos==2)cubeGhost.setPosition(glm::vec3(cubePere.getPosition()[0],cubePere.getPosition()[1],cubePere.getPosition()[2]+1));
        if(pos==3)cubeGhost.setPosition(glm::vec3(cubePere.getPosition()[0]-1,cubePere.getPosition()[1],cubePere.getPosition()[2]));
        if(pos==4)cubeGhost.setPosition(glm::vec3(cubePere.getPosition()[0],cubePere.getPosition()[1],cubePere.getPosition()[2]-1));
        if(pos==5)cubeGhost.setPosition(glm::vec3(cubePere.getPosition()[0],cubePere.getPosition()[1]-1.,cubePere.getPosition()[2]));
 
    }

    void Scene::creationBoule(glm::vec3 centreBoule,std::vector<Cube3D> &cubesList,int _rayon){
    float colorBoule = 5.;
	    float rayon = _rayon * 10.;
	    for (int i = centreBoule[0]-rayon; i < centreBoule[0]+rayon ; i++) {//on crée un pavage de 60 cubes sur 60 centré en 0.
	        for(int j= centreBoule[1]-rayon; j < centreBoule[1]+rayon; j++) {
	            for(int k =centreBoule[2]-rayon; k < centreBoule[2]+rayon;k++){
	                if(((i-centreBoule[0])*(i-centreBoule[0]) +(j-centreBoule[1])*(j-centreBoule[1]) +(k-centreBoule[2])*(k-centreBoule[2]) < rayon)&& !((i-centreBoule[0])*(i-centreBoule[0]) +(j-centreBoule[1])*(j-centreBoule[1]) +(k-centreBoule[2])*(k-centreBoule[2]) < rayon-_rayon*2.)){
	                    Cube3D cubePave(i,k,j, colorBoule*(i-centreBoule[0])/rayon,colorBoule*(j-centreBoule[1])/rayon,colorBoule*(k-centreBoule[2])/rayon);
	                    cubesList.push_back(cubePave);
	                }
	            }
	         }
	    }
    }

    void Scene::creationPavage(std::vector<Cube3D> &cubesList, int longueur, int largeur, float R, float G, float B){
	    for (int i = -longueur*0.5; i < longueur*0.5 ; i++) {
	        for(int j = -largeur*0.5; j < largeur*0.5 ; j++) {
	            for(int k =-2; k<1;k++){
	                Cube3D cubePave(i,k,j, R,G,B);
	                cubesList.push_back(cubePave);
	            }
	        }
	    }
    }