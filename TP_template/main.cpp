#include <glimac/SDLWindowManager.hpp>
// #include <SDL2/SDL.h>
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
#include "glimac/GestionCube.hpp"

using namespace glimac;


int main(int argc, char** argv) {

    FreeflyCamera camera;
    Scene scene;
    GestionCube gestion;
    

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
    // Uint8 pMouse = SDL_GetMouseState(NULL,NULL); //pour vérifier l'état des touches enfoncées.

    glm::vec3 uKd ;
    GLuint uKdID = glGetUniformLocation(program.getGLId(),"uKd");
    glUniform3f(uKdID,uKd[0],uKd[1],uKd[2]);

    glm::vec3 uKs ;
    GLuint uKsID = glGetUniformLocation(program.getGLId(),"uKs");
    glUniform3f(uKsID,uKs[0],uKs[1],uKs[2]);

    float uShininess ;
    GLuint uShininessID = glGetUniformLocation(program.getGLId(),"uShininess");
    glUniform1f(uShininessID,uShininess);

    glm::vec3 uLightDir_vs = glm::vec3(1.,1.,1.);
    GLuint uLightDir_vsID = glGetUniformLocation(program.getGLId(),"uLightDir_vsd");
    glUniform3f(uLightDir_vsID,uLightDir_vs[0],uLightDir_vs[1],uLightDir_vs[2]);

    glm::vec3 uLightIntensity ;
    GLuint uLightIntensityID = glGetUniformLocation(program.getGLId(),"uLightIntensity");
    glUniform3f(uLightIntensityID,uLightIntensity[0],uLightIntensity[1],uLightIntensity[2]);


    // Cube3D cube2(1.,10.,2.,  1.,1.,1.);
    // Cube3D cube3(10.,10.,2., 0.,0.,0.);
    // Cube3D cube4(10.,1.,5.,  1.,0.,1.);
    // Cube3D cube5(10.,5.,5., 0.,1.,0.);

    


    Cube3D cubeGhost;
    std::vector<Cube3D> cubesList = {};
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

    float R = 1.;
    float G = 0.;
    float B = 0.;
    // float incremR = 1;
    // float incremG = 0;
    // float incremB = 0;

    float x;

    int countPushTab = 0;
    int pos = 0;
    int TabIsPressed = 0;
    int HIsPressed = 0;
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
         
         switch(e.type){
             // case SDL_BUTTON_WHEELDOWN:
             //        std::cout<<"scrool for lumière  "<<std::endl;
             //        R =R+0.01;
             //        G=G+0.01;
             //        B=B +0.01;

             //       break;
            // case SDL_MOUSEBUTTONDOWN:
            //     if (SDL_BUTTON(SDL_BUTTON_LEFT)){
            //         std::cout<<"Clique Gauche"<<std::endl;
            //     }
            //     else if (SDL_BUTTON(SDL_BUTTON_RIGHT)){
            //         std::cout<<"Clique Droit"<<std::endl;
            //     }
                

             case SDL_MOUSEBUTTONUP:
                    // std::cout<<"clic en "<<e.button.x<<"  ; "<<e.button.y<<std::endl;

                   break;
            
            case SDL_MOUSEMOTION:
                    if (SDL_BUTTON(SDL_BUTTON_MIDDLE) & e.motion.state)
                    {   
                        camera.rotateLeft(-e.motion.xrel);
                        camera.rotateUp(-e.motion.yrel);
                    }
                    break;  
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

        for (int i =0; i < cubesList.size(); i++){
            scene.show(cubesList[i].getDisplay(),cubesList[i],program.getGLId());
        }
        
        // à la ligne qui suit on détermine le cube selectionné par le curseur. Tout se fait dans la classe GestionCube.
        int indiceMinimumCubeZ = gestion.indiceMinimumCubeZ(MatrixView,MVMatrix,NormalMatrix,cubesList);

        // R = (cubesList[indiceMinimumCubeZ].getColor())[0]; 
        // G = (cubesList[indiceMinimumCubeZ].getColor())[1];
        // B = (cubesList[indiceMinimumCubeZ].getColor())[2];

        if (pKeyboard[SDLK_c] && indiceMinimumCubeZ >=0){           
            std::cout<<"J'appuie sur C"<< cubesList[indiceMinimumCubeZ].getColor()<<std::endl;
            cubesList[indiceMinimumCubeZ].setColor(glm::vec3(R,G,B));
        }


        if (pKeyboard[SDLK_p] && indiceMinimumCubeZ >=0){           
            R = cubesList[indiceMinimumCubeZ].getColor()[0];
            G = cubesList[indiceMinimumCubeZ].getColor()[1];
            B = cubesList[indiceMinimumCubeZ].getColor()[2];
        }

        if (pKeyboard[SDLK_x] && indiceMinimumCubeZ >=0){           
         // std::cout<<"J'appuie sur x pour supprimer le cube "<< cubesList[indiceMinimumCubeZ]<<std::endl;
            std::swap(cubesList[indiceMinimumCubeZ],cubesList[cubesList.size()-1]);
            cubesList.pop_back();
        }


        
        scene.showGhost(cubeGhost.getDisplay(),cubeGhost,program.getGLId());
        scene.setGhostCubePosition(pos,cubeGhost,cubesList[indiceMinimumCubeZ]); // on indique au cube Fantôme ses positions en fonction de son cube Père.
        cubeGhost.setColor(glm::vec3(1-cubesList[indiceMinimumCubeZ].getColor()[0],1-cubesList[indiceMinimumCubeZ].getColor()[1],1-cubesList[indiceMinimumCubeZ].getColor()[2]));
            
        

        if (pKeyboard[SDLK_n] && indiceMinimumCubeZ >=0 ) {//ici on crée les nouveaux cubes.
            // Cube3D cubeNew(cubesList[indiceMinimumCubeZ].getPosition()[0],cubesList[indiceMinimumCubeZ].getPosition()[1]+1.,cubesList[indiceMinimumCubeZ].getPosition()[2],  1.,1.,1.);
            Cube3D cubeNew(cubeGhost.getPosition()[0],cubeGhost.getPosition()[1],cubeGhost.getPosition()[2],R,G,B);
            

            if(!cubeNew.getDansLaListe() && !(  cubeNew.getPosition() == cubesList.back().getPosition() ) ){ /* La deuxième condition du IF permet d'empêcher la création d'un cube à 
                                                                                                                la même place que celui qui vient d'être construit précédemment.
                                                                                                                Utile lorsqu'on clique deux fois sans faire exprès.
                                                                                                            */
                cubesList.push_back(cubeNew);
                cubeNew.setDansLaListe(true);
            }
        }
        
        if(pKeyboard[SDLK_TAB]){
            TabIsPressed = 1;
        }
        if (TabIsPressed==1){
            if(!pKeyboard[SDLK_TAB]){
                TabIsPressed = 0;
                pos ++;
                pos = pos%6;
            }  
        }

        if (e.type == SDL_MOUSEBUTTONUP){
            if(e.button.button == SDL_BUTTON_WHEELUP){
                std::cout<<"scrollUP"<<std::endl;
            
            // R = cubesList[indiceMinimumCubeZ].getColor()[0];
            // G = cubesList[indiceMinimumCubeZ].getColor()[1];
            // B = cubesList[indiceMinimumCubeZ].getColor()[2];
                R = cubesList[indiceMinimumCubeZ].getColor()[0];
            G = cubesList[indiceMinimumCubeZ].getColor()[1];
            B = cubesList[indiceMinimumCubeZ].getColor()[2];
                if(R<=2. && G<=2. && B<=2.){
                    R +=0.01;
                    G +=0.01;
                    B +=0.01;
                }
                cubesList[indiceMinimumCubeZ].setColor(glm::vec3(R,G,B));
            }
            if(e.button.button == SDL_BUTTON_WHEELDOWN){
                std::cout<<"scrollDown"<<std::endl;
            
            // R = cubesList[indiceMinimumCubeZ].getColor()[0];
            // G = cubesList[indiceMinimumCubeZ].getColor()[1];
            // B = cubesList[indiceMinimumCubeZ].getColor()[2];
                R = cubesList[indiceMinimumCubeZ].getColor()[0];
            G = cubesList[indiceMinimumCubeZ].getColor()[1];
            B = cubesList[indiceMinimumCubeZ].getColor()[2];
                if(R>=-1. && G>=-1. && B>=-1.){
                    R -=0.01;
                    G -=0.01;
                    B -=0.01;
                }
                cubesList[indiceMinimumCubeZ].setColor(glm::vec3(R,G,B));
            }

        }
        if (SDL_GetMouseState(NULL,NULL)&SDL_BUTTON(SDL_BUTTON_LEFT)){  
            std::cout<<"gauche"<<std::endl;
            R = cubesList[indiceMinimumCubeZ].getColor()[0];
            
            G = cubesList[indiceMinimumCubeZ].getColor()[1];
            B = cubesList[indiceMinimumCubeZ].getColor()[2];
            // if(incremG <1. && abs(incremB)<0.05){
            //     incremR-=0.01;
            //     incremG+=0.01;
            // }   
            // if(incremB<1. && abs(incremR)<0.05){
            //     incremG-=0.01;
            //     incremB+=0.01;
            // }
            // if(incremR<1. && abs(incremG)<0.05){
            //     incremB-=0.01;
            //     incremR+=0.01;
            // }
            x+=0.02;
            R = (cos(x));
            G = (cos(x+2.09439*0.5));
            B = (cos(x+2.09439));

            cubesList[indiceMinimumCubeZ].setColor(glm::vec3(R, G, B));

        }
        if (SDL_GetMouseState(NULL,NULL)&SDL_BUTTON(SDL_BUTTON_RIGHT)){
            std::cout<<"droite"<<std::endl;
            R = cubesList[indiceMinimumCubeZ].getColor()[0];
            G = cubesList[indiceMinimumCubeZ].getColor()[1];
            B = cubesList[indiceMinimumCubeZ].getColor()[2];
            
            // if(!(G<1. && abs(B) < 0.05)){
            //     R-=0.01;
            //     G+=0.01;
            // }
            // if(!(B<1. && abs(R)<0.05)){
            //     G-=0.01;
            //     B+=0.01;
            // }
            // if(!(R<1. && abs(G)<0.05)){
            //     B-=0.01;
            //     R+=0.01;
            // }
            x-=0.02;
            R = (cos(x));
            G = (cos(x+2.09439*0.5));
            B = (cos(x+2.09439));
            cubesList[indiceMinimumCubeZ].setColor(glm::vec3(R,G,B));
        }


        if(pKeyboard[SDLK_h] && indiceMinimumCubeZ >=0){
            //std::cout<<"gello"<<std::endl;
            HIsPressed = 1;
        }
        if (HIsPressed==1){
            if(!pKeyboard[SDLK_h]){
                //std::cout<<"gezezezello"<<std::endl;

                HIsPressed = 0;
                cubesList[indiceMinimumCubeZ].setDisplay(!cubesList[indiceMinimumCubeZ].getDisplay());
            }  
        }        
             

        // glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        // R =0.5;
        // G = 0.5;
        // B = 0.5;
        
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
