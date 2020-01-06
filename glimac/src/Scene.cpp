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
		//std::cout<<"color cube : "<<cube.getColor()<<std::endl;
		if(appear)
			addCube(cube,programID);
	}

	void Scene::showGhost(bool appear,Cube3D cube, int programID){
		//std::cout<<"color cube : "<<cube.getColor()<<std::endl;
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