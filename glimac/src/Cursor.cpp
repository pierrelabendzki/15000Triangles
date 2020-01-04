#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <glimac/FilePath.hpp>
#include <glimac/Program.hpp>
#include <iostream>
#include <vector>
#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp>
#include <math.h>
#include "glimac/Cursor.hpp"
#include "glimac/Cube3D.hpp"



Cursor::Cursor(){}


void Cursor::drawCursor(int programID, glm::mat4 matriceView,glm::vec3 vecPosCam){
        Cube3D cubeVert;
        Cube3D cubeHor;
        glDisable(GL_DEPTH_TEST); 
        glm::mat4 MVMatrix= matriceView*glm::translate(glm::mat4(), vecPosCam)*glm::scale(glm::mat4(), glm::vec3(0.01,0.001, 0.001));
        GLuint MVMatrixID = glGetUniformLocation(programID,"MVMatrix");
        glUniformMatrix4fv(MVMatrixID,1,GL_FALSE,glm::value_ptr(MVMatrix));
        

        glm::vec3 uColor = cubeVert.getColor();
        GLuint uColorID = glGetUniformLocation(programID,"uColor");
        glUniform3f(uColorID,uColor[0],uColor[1],uColor[2]);

        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


        MVMatrix=  matriceView*glm::translate(glm::mat4(), vecPosCam)*glm::scale(glm::mat4(), glm::vec3(0.001,0.01, 0.001));
        MVMatrixID = glGetUniformLocation(programID,"MVMatrix");
        glUniformMatrix4fv(MVMatrixID,1,GL_FALSE,glm::value_ptr(MVMatrix));
        

        uColor = cubeHor.getColor();
        uColorID = glGetUniformLocation(programID,"uColor");
        glUniform3f(uColorID,uColor[0],uColor[1],uColor[2]);

        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        glEnable(GL_DEPTH_TEST); 
}