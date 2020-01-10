#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <glimac/FilePath.hpp>
#include <glimac/Program.hpp>
#include <iostream>
#include <vector>
#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp>
#include <math.h>
#include "glimac/GestionCube.hpp"
#include "glimac/Cube3D.hpp"


	

  void GestionCube::creationCube(GLuint &vao, GLuint &ibPositionsID){
    GLuint vbPositionsID;
    glGenBuffers(1,&vbPositionsID);
    glBindBuffer(GL_ARRAY_BUFFER, vbPositionsID);
    


    float tabPositions[] = {
        // Front face
        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        // Back face
        -0.5f, -0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
        // Top face
        -0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f, -0.5f,
        // Bot face 
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        // Left face 
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        // Right face 
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
    };


// float tabPositions[] = {
//             0.5,0.5,0.5,
//             -0.5,0.5,0.5,
//             -0.5,-0.5,0.5,
//             0.5,-0.5,0.5,
//             0.5,-0.5,-0.5,
//             0.5,0.5,-0.5,
//             -0.5,0.5,-0.5,
//             -0.5,-0.5,-0.5
//         };
    // for (int i=0; i<24; i++){
    //     // std::cout<<cube.m_tabPositions[i]<<std::endl;
    //     tabPositions[i]=cube.getPositions()[i];
    // }

    glBufferData(GL_ARRAY_BUFFER, sizeof(tabPositions), tabPositions, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER,0);

GLuint normalesPositionsID;
    glGenBuffers(1,&normalesPositionsID);
    glBindBuffer(GL_ARRAY_BUFFER, normalesPositionsID);


float normales[] = {
        // Front face
         0.0f,  0.0f,  1.0f,
         0.0f,  0.0f,  1.0f,
         0.0f,  0.0f,  1.0f,
         0.0f,  0.0f,  1.0f,
        // Back face
         0.0f,  0.0f, -1.0f,
         0.0f,  0.0f, -1.0f,
         0.0f,  0.0f, -1.0f,
         0.0f,  0.0f, -1.0f,
        // Top face
         0.0f,  1.0f,  0.0f,
         0.0f,  1.0f,  0.0f,
         0.0f,  1.0f,  0.0f,
         0.0f,  1.0f,  0.0f,
        // Bot face 
         0.0f, -1.0f,  0.0f,
         0.0f, -1.0f,  0.0f,
         0.0f, -1.0f,  0.0f,
         0.0f, -1.0f,  0.0f,
        // Left face 
        -1.0f,  0.0f,  0.0f,
        -1.0f,  0.0f,  0.0f,
        -1.0f,  0.0f,  0.0f,
        -1.0f,  0.0f,  0.0f,
        // Right face 
         1.0f,  0.0f,  0.0f,
         1.0f,  0.0f,  0.0f,
         1.0f,  0.0f,  0.0f,
         1.0f,  0.0f,  0.0f,
    };
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(normales), normales, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER,0);




    glGenBuffers(1, &ibPositionsID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibPositionsID);


unsigned int indexSommets[] = {
        // Back face
        0, 1, 2,
        0, 2, 3,
        // Front face
        4, 5, 6,
        4, 6, 7,
        // Top face
        8, 9, 10,
        8, 10, 11,
        // Bottom face
        12, 13 , 14,
        12, 14, 15,
        // Left face
        16, 17 , 18,
        16, 18, 19,
        // Right face
        20, 21 , 22,
        20, 22, 23,
    };




    // int indexSommets[]={
    //         0,1,2, 0,2,3, // les deux premiers blocs de 3 coordonnées correspondent à la première face.
    //         4,7,6, 4,6,5,
    //         1,6,7, 1,7,2,
    //         0,3,4, 0,4,5,
    //         2,7,4, 2,4,3,
    //         0,5,6, 0,6,1
    //     };
    // for (int i=0; i<36; i++){
    //     // std::cout<<cube.m_tabPositions[i]<<std::endl;
    //     indexSommets[i]=cube.getIndexSommets()[i];
    // }

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexSommets), indexSommets, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    


    GLuint vertexArrayID;

    glGenVertexArrays(1,&vao);
    glBindVertexArray(vao);
    //glGenVertexArrays(1,&vertexArrayID);
    //glBindVertexArray(vertexArrayID);
    glBindBuffer(GL_ARRAY_BUFFER,vbPositionsID);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),0);
    // glBindBuffer(GL_ARRAY_BUFFER,0);
    // glBindVertexArray(0);

    
   


    GLuint normalesArrayID;

    //glGenVertexArrays(1,&normalesArrayID);
    //glBindVertexArray(normalesArrayID);
    glBindBuffer(GL_ARRAY_BUFFER,normalesPositionsID);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,3*sizeof(float),0);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);

}	
  glm::vec4 GestionCube::vec3D_vers_2D(glm::mat4 &MatrixView, glm::mat4 &MVMatrix, glm::mat4 &NormalMatrix,Cube3D cube){
        return MatrixView*MVMatrix*NormalMatrix*glm::vec4(cube.getPosition(),1.0);
    }

    std::vector <int> GestionCube::listCubesCandidats(glm::mat4 &MatrixView, glm::mat4 &MVMatrix, glm::mat4 &NormalMatrix,std::vector<Cube3D> &cubesList){ // cette méthode renvoie la liste des cubes qui sont dans l'axe de visée du curseur.
        std::vector<int> listCubesCandidats;  
        glm::vec3 coordWindowCub;
        for(int i = 0; i<cubesList.size(); i++){
            coordWindowCub[0] = vec3D_vers_2D(MatrixView,MVMatrix,NormalMatrix,cubesList[i])[0];   
            coordWindowCub[1] = vec3D_vers_2D(MatrixView,MVMatrix,NormalMatrix,cubesList[i])[1];
            if(coordWindowCub[0]*coordWindowCub[0] +coordWindowCub[1]*coordWindowCub[1] < 0.5){
                listCubesCandidats.push_back(i);
            }
        }
        return listCubesCandidats;
    }

    int GestionCube::indiceMinimumCubeZ(glm::mat4 &MatrixView, glm::mat4 &MVMatrix, glm::mat4 &NormalMatrix,std::vector<Cube3D> &cubesList){
        std::vector<int> liste = listCubesCandidats(MatrixView,MVMatrix,NormalMatrix,cubesList);
        float minimumZ = 100000.;
        int indiceMinimumCubeZ = -1;
        for(int i = 0; i<liste.size(); i++){

            if(abs(vec3D_vers_2D(MatrixView,MVMatrix,NormalMatrix,cubesList[liste[i]])[2]) < minimumZ){
                minimumZ = abs(vec3D_vers_2D(MatrixView,MVMatrix,NormalMatrix,cubesList[liste[i]])[2]);
                indiceMinimumCubeZ = liste[i];
            }
        }
        return indiceMinimumCubeZ;
    }