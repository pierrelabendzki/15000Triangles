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