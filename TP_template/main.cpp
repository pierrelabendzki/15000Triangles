#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <glimac/FilePath.hpp>
#include <glimac/Program.hpp>

#include <utility>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <algorithm>

#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp>
#include "glimac/FreeflyCamera.hpp"
#include "glimac/Cube3D.hpp"
#include "glimac/Scene.hpp"
#include "glimac/Cursor.hpp"



using namespace glimac;


int main(int argc, char** argv) {

    FreeflyCamera camera;
    Scene scene;
    Cursor cursor;
    

    // Initialize SDL and open a window
    float speed= 20; 
    int LONGUEUR = 800;
    int HAUTEUR = 800;
    float RATIO = LONGUEUR/HAUTEUR;
    SDLWindowManager windowManager(LONGUEUR, HAUTEUR, "GLImac");
    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }
    glEnable(GL_DEPTH_TEST); 
    glClearColor(1.,0.95,0.7,1.);
    
    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;


    FilePath applicationPath(argv[0]);
    Program program = loadProgram(applicationPath.dirPath() + "shaders/"+argv[1],applicationPath.dirPath() + "shaders/"+argv[2]);
    program.use();

    Cube3D cube;
    // Cube3D cube1(2.,10.,0.);

    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/
    GLuint vbPositionsID;
    glGenBuffers(1,&vbPositionsID);
    glBindBuffer(GL_ARRAY_BUFFER, vbPositionsID);
    

float tabPositions[] = {
            0.5,0.5,0.5,
            -0.5,0.5,0.5,
            -0.5,-0.5,0.5,
            0.5,-0.5,0.5,
            0.5,-0.5,-0.5,
            0.5,0.5,-0.5,
            -0.5,0.5,-0.5,
            -0.5,-0.5,-0.5
        };
    // for (int i=0; i<24; i++){
    //     // std::cout<<cube.m_tabPositions[i]<<std::endl;
    //     tabPositions[i]=cube.getPositions()[i];
    // }

    glBufferData(GL_ARRAY_BUFFER, sizeof(tabPositions), tabPositions, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    

    GLuint ibPositionsID;
    glGenBuffers(1, &ibPositionsID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibPositionsID);

    int indexSommets[]={
            0,1,2, 0,2,3, // les deux premiers blocs de 3 coordonnées correspondent à la première face.
            4,7,6, 4,6,5,
            1,6,7, 1,7,2,
            0,3,4, 0,4,5,
            2,7,4, 2,4,3,
            0,5,6, 0,6,1
        };
    // for (int i=0; i<36; i++){
    //     // std::cout<<cube.m_tabPositions[i]<<std::endl;
    //     indexSommets[i]=cube.getIndexSommets()[i];
    // }

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexSommets), indexSommets, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    


    GLuint vbPositionsCubesID;
    glGenBuffers(1, &vbPositionsCubesID); 
    glBindBuffer(GL_ARRAY_BUFFER, vbPositionsCubesID); 


    GLuint vertexArrayID;



    glGenVertexArrays(1,&vertexArrayID);
    glBindVertexArray(vertexArrayID);
    glBindBuffer(GL_ARRAY_BUFFER,vbPositionsID);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),0);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);

    glm::mat4 Mprojo = glm::perspective(glm::radians(70.f),RATIO,0.1f,1000.f);
    GLuint MprojoID = glGetUniformLocation(program.getGLId(),"Mprojo");
    glUniformMatrix4fv(MprojoID,1,GL_FALSE,glm::value_ptr(Mprojo));
  
    glm::mat4 MVMatrix= glm::translate(glm::mat4(), glm::vec3(0., 0., 0.));
    GLuint MVMatrixID = glGetUniformLocation(program.getGLId(),"MVMatrix");
    glUniformMatrix4fv(MVMatrixID,1,GL_FALSE,glm::value_ptr(MVMatrix));

    glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
    GLuint NormalMatrixID = glGetUniformLocation(program.getGLId(),"NormalMatrix");
    glUniformMatrix4fv(NormalMatrixID,1,GL_FALSE,glm::value_ptr(NormalMatrix));

    glm::mat4 MatrixView = camera.getViewMatrix();
    GLuint MatrixViewID = glGetUniformLocation(program.getGLId(),"MatrixView");

    Uint8* pKeyboard = SDL_GetKeyState(NULL); //pour vérifier l'état des touches enfoncées.
    




    Cube3D cube2(1.,10.,2.,  1.,1.,1.);
    Cube3D cube3(10.,10.,2., 0.,0.,0.);
    Cube3D cube4(10.,1.,5.,  1.,0.,1.);
    Cube3D cube5(10.,5.,5., 0.,1.,0.);

    std::vector<Cube3D> cubesList = {cube2,cube3,cube4,cube5};
   for (int i = -10; i < 10 ; i++) {//on crée un pavage de 60 cubes sur 60 centré en 0.
            for(int j = -10; j < 10 ; j++) {
                for(int k =-2; k<1;k++){
                    Cube3D cubePave(i,k,j, 0.5,0.6,0.7);
                    cubesList.push_back(cubePave);
                    // MVMatrix= glm::translate(glm::mat4(), glm::vec3(i, k, j));
                    // glUniformMatrix4fv(MVMatrixID,1,GL_FALSE,glm::value_ptr(MVMatrix));
                    
                    // glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
                }
            }
        }

    bool affiche = true;
       
    // Application loop:
    bool done = false;
    while(!done) {
        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }
           


        }
           
        // déplacements au clavier.    
        if (pKeyboard[SDLK_z]) camera.moveFront(-0.01*speed);
        if (pKeyboard[SDLK_s]) camera.moveFront(0.01*speed);
        if (pKeyboard[SDLK_q]) camera.moveLeft(-0.01*speed);
        if (pKeyboard[SDLK_d]) camera.moveLeft(0.01*speed);
        if (pKeyboard[SDLK_UP]) camera.moveUp(0.01*speed);
        if (pKeyboard[SDLK_DOWN]) camera.moveUp(-0.01*speed);
        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glBindVertexArray(vertexArrayID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibPositionsID);

        //  MVMatrix= glm::translate(glm::mat4(), glm::vec3(3., 10., 0.));
        //             glUniformMatrix4fv(MVMatrixID,1,GL_FALSE,glm::value_ptr(MVMatrix));
        //             MatrixView = camera.getViewMatrix();
        //             glUniformMatrix4fv(MatrixViewID,1,GL_FALSE,glm::value_ptr(MatrixView));
        //             glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        // MVMatrix= glm::translate(glm::mat4(), glm::vec3(1., 10., 0.));
        //             glUniformMatrix4fv(MVMatrixID,1,GL_FALSE,glm::value_ptr(MVMatrix));
        //             MatrixView = camera.getViewMatrix();
        //             glUniformMatrix4fv(MatrixViewID,1,GL_FALSE,glm::value_ptr(MatrixView));

        // affiche=scene.destroy(cube3,program.getGLId());

        for (int i =0; i < cubesList.size(); i++){
            scene.show(cubesList[i].getDisplay(),cubesList[i],program.getGLId());
        }
        
        
        

        std::vector<int> listCubesCandidats;  

        glm::vec3 coordWindowCub;
        // scene.destroy(cube3,program.getGLId());
        for(int i = 0; i<cubesList.size(); i++){
            coordWindowCub[0]=(MatrixView*MVMatrix*NormalMatrix*glm::vec4(cubesList[i].getPosition(),1.0))[0];   
            coordWindowCub[1]=(MatrixView*MVMatrix*NormalMatrix*glm::vec4(cubesList[i].getPosition(),1.0))[1];
            // std::cout<<"norm  de "<<i+2<<" :  "<<coordWindowCub[0]*coordWindowCub[0] +coordWindowCub[1]*coordWindowCub[1]<<std::endl;    
            if(coordWindowCub[0]*coordWindowCub[0] +coordWindowCub[1]*coordWindowCub[1] < 0.5){
                listCubesCandidats.push_back(i);
                // std::cout<<"cube visé : "<< i <<std::endl;

            }
            else{
                // std::cout<<"pas de cube visé"<<std::endl;
                // listCubesCandidats.push_back(-1);
            }
        }


                // std::cout<< (glm::inverse(Mprojo*MatrixView*MVMatrix)*glm::vec4(1,10,2,1))[0]<<(glm::inverse(Mprojo*MatrixView*MVMatrix *NormalMatrix)*glm::vec4(1,10,2,1))[1]<<std::endl;

        float minimumZ = 100000.;
        int indiceMinimumCubeZ = -1;

        for(int i = 0; i<listCubesCandidats.size(); i++){
            for(int j = 0; j<listCubesCandidats.size();j++){
                // std::cout<<listCubesCandidats[j]<<',';
            }
            // std::cout<<" "<<std::endl;
             // std::cout<<"           cube visé avant le IF    : "<< listCubesCandidats[i] <<std::endl;
                if(abs((MatrixView*MVMatrix*NormalMatrix*glm::vec4(cubesList[listCubesCandidats[i]].getPosition(),1.0))[2]) < minimumZ){
                    // std::cout<<"cube visé aapres le IF : "<< listCubesCandidats[i] <<std::endl;
                    minimumZ = abs((MatrixView*MVMatrix*NormalMatrix*glm::vec4(cubesList[listCubesCandidats[i]].getPosition(),1.0))[2]);
                    indiceMinimumCubeZ = listCubesCandidats[i];
                }
                    // std::cout<<"min : "<<minimumZ<<std::endl;
                     // std::cout<<(MatrixView*MVMatrix*NormalMatrix*glm::vec4(cube3.getPosition(),1.0))<<std::endl;
        // std::cout<<(MatrixView*MVMatrix*NormalMatrix*glm::vec4(cube2.getPosition(),1.0))<<std::endl;

        }
        // std::cout<<"indice min : "<<indiceMinimumCubeZ<<std::endl;

        //std::cout<<"Cube selectionne :: ==>>>  cube "<<indiceMinimumCubeZ + 2<<std::endl;
           

             

             switch(e.type){
                case SDL_MOUSEBUTTONUP:
                    std::cout<<"clic en "<<e.button.x<<"  ; "<<e.button.y<<std::endl;

                   break;
                case SDL_MOUSEMOTION:
                    if (SDL_BUTTON(SDL_BUTTON_LEFT) & e.motion.state)
                    {   
                        camera.rotateLeft(e.motion.xrel);
                        camera.rotateUp(e.motion.yrel);
                    }
                    break;
                case SDL_KEYDOWN:
                    // AXE : x=0 y=1 z=2
                    if (e.key.keysym.sym == SDLK_h && indiceMinimumCubeZ >=0 ) {
                        cubesList[indiceMinimumCubeZ].setDisplay(!cubesList[indiceMinimumCubeZ].getDisplay());
                    }

                    if (e.key.keysym.sym == SDLK_c && indiceMinimumCubeZ >=0){           
                        std::cout<<"J'appuie sur C"<< cubesList[indiceMinimumCubeZ].getColor()<<std::endl;
                        cubesList[indiceMinimumCubeZ].setColor(glm::vec3(1.,0.,0.));
                    }
                    if (e.key.keysym.sym == SDLK_x && indiceMinimumCubeZ >=0){           
             // std::cout<<"J'appuie sur x pour supprimer le cube "<< cubesList[indiceMinimumCubeZ]<<std::endl;
                        std::swap(cubesList[indiceMinimumCubeZ],cubesList[cubesList.size()-1]);
                        cubesList.pop_back();
                    }
                    break;
                    /*if (e.key.keysym.sym == SDLK_z) {
                        camera.moveFront(-0.1);
                    }
                    else if (e.key.keysym.sym == SDLK_s) {
                        camera.moveFront(0.1);
                    }
                    else if (e.key.keysym.sym == SDLK_q) {
                        camera.moveLeft(-0.1);
                    }
                    else if (e.key.keysym.sym == SDLK_d) {
                        camera.moveLeft(0.1);
                    }
                    else if (e.key.keysym.sym == SDLK_UP) {
                        camera.moveUp(0.1);
                    }
                    else if (e.key.keysym.sym == SDLK_DOWN) {
                        camera.moveUp(-0.1);
                    }
                case SDL_KEYUP:
                    if (e.key.keysym.sym == SDLK_z) {
                        camera.moveFront(-0.1);
                    }
                    //  else if (e.key.keysym.scancode == SDL_SCANCODE_Y) {
                    //     axe = 1;
                    // } else if (e.key.keysym.scancode == SDL_SCANCODE_W) { 
                    //     axe = 2; 
                    // }

                    // if (e.key.keysym.sym == SDLK_UP) {
                    //     cursor.changeCoord(axe, 1);
                    //     std::cout<<"en haut"<<std::endl;
                    // } else if (e.key.keysym.sym == SDLK_DOWN){
                    //     cursor.changeCoord(axe, -1);
                    //     std::cout<<"en bas"<< cursor.coord <<std::endl;
                    // }*/
            }

        // glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        
        
        MatrixView = camera.getViewMatrix();
        glUniformMatrix4fv(MatrixViewID,1,GL_FALSE,glm::value_ptr(MatrixView));

        // cursor.drawCursor(program.getGLId(),Mprojo*MatrixView ,camera.getPosition());
        camera.drawCursor(Mprojo,MVMatrix, NormalMatrix,program.getGLId());
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        
       

        // Update the display
        windowManager.swapBuffers();
    }

    return EXIT_SUCCESS;
}
