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
#include "glimac/GestionCube.hpp"
#include "glimac/Touches.hpp"
#define PI 3.141592
using namespace glimac;


int main(int argc, char** argv) {

    FreeflyCamera camera;
    Scene scene;
    GestionCube gestion;
    Touches touche;
    

    // Initialize SDL and open a window
    float speed= 20; 
    int LONGUEUR = 800;
    int HAUTEUR = 800;
    float RATIO = LONGUEUR/HAUTEUR;
    SDLWindowManager windowManager(LONGUEUR, HAUTEUR, "THE 15000 TRIANGLES EXPERIENCE");
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
    Program program = loadProgram(applicationPath.dirPath() + "shaders/"+"cube.vs.glsl",applicationPath.dirPath() + "shaders/"+"directionallight.fs.glsl");
    program.use();

    GLuint vao;
    GLuint ibPositionsID;
    gestion.creationCube(vao,ibPositionsID);



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

    Cube3D cubeGhost; // on crée le cube fantôme qui indique la place du futur cube.
    std::vector<Cube3D> cubesList = {}; // on initialise la liste qui contiendra tous nos cubes.

    scene.creationBoule(glm::vec3(0,-30,15),cubesList,10);//on crée une boule de diamètre 15 cubes à la position 0, -30, 15.
    scene.creationPavage(cubesList,15,15, 0.,0.5,0.5); //on crée un pavage de  15x15.
   
    //couleurs initiales. À la première création le cube est rouge.
    float R = 1.;
    float G = 0.;
    float B = 0.;

    float x = 0;

    int countPushTab = 0;
    int pos = 0;
    int TabIsPressed = 0;
    int HIsPressed = 0;
    bool affiche = true;
       
    // Application loop:
    bool done = false;
    bool fall = false;
    while(!done) {
        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }
         
         switch(e.type){
            
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
        
        touche.deplacementsClavier(camera,speed);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glBindVertexArray(vao);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibPositionsID);

        for (int i =0; i < cubesList.size(); i++){ // on affiche tous les cubes de la liste.
            scene.show(cubesList[i].getDisplay(),cubesList[i],program.getGLId());
        }

        // à la ligne qui suit on détermine le cube selectionné par le curseur. Tout se fait dans la classe GestionCube.
        int indiceMinimumCubeZ = gestion.indiceMinimumCubeZ(MatrixView,MVMatrix,NormalMatrix,cubesList);


        scene.showGhost(cubeGhost.getDisplay(),cubeGhost,program.getGLId());
        scene.setGhostCubePosition(pos,cubeGhost,cubesList[indiceMinimumCubeZ]); // on indique au cube Fantôme ses positions en fonction de son cube Père.
        cubeGhost.setColor(glm::vec3(1-cubesList[indiceMinimumCubeZ].getColor()[0],1-cubesList[indiceMinimumCubeZ].getColor()[1],1-cubesList[indiceMinimumCubeZ].getColor()[2]));
      
        if (pKeyboard[SDLK_c] && indiceMinimumCubeZ >=0){           
            cubesList[indiceMinimumCubeZ].setColor(glm::vec3(R,G,B));
        }

        if (pKeyboard[SDLK_p] && indiceMinimumCubeZ >=0){  // la touche p a l'effet d'une pipette.
            R = cubesList[indiceMinimumCubeZ].getColor()[0];
            G = cubesList[indiceMinimumCubeZ].getColor()[1];
            B = cubesList[indiceMinimumCubeZ].getColor()[2];
        }

        if (pKeyboard[SDLK_x] && indiceMinimumCubeZ >=0){ // on appuie sur x pour supprimer le cube.      
            std::swap(cubesList[indiceMinimumCubeZ],cubesList[cubesList.size()-1]);
            cubesList.pop_back();
        }

        if(pKeyboard[SDLK_h] && indiceMinimumCubeZ >=0){
            HIsPressed = 1;
        }
        if (HIsPressed==1){
            if(!pKeyboard[SDLK_h]){
                HIsPressed = 0;
                cubesList[indiceMinimumCubeZ].setDisplay(!cubesList[indiceMinimumCubeZ].getDisplay());
            }  
        }
          
        if (pKeyboard[SDLK_n] && indiceMinimumCubeZ >=0 ) {//ici on crée les nouveaux cubes.
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
            if(e.button.button == SDL_BUTTON_WHEELUP){ //On tourne la molette pour augmenter la luminosité...
                R = cubesList[indiceMinimumCubeZ].getColor()[0];
                G = cubesList[indiceMinimumCubeZ].getColor()[1];
                B = cubesList[indiceMinimumCubeZ].getColor()[2];
                if(R<=3. && G<=3. && B<=3.){
                    R +=0.01;
                    G +=0.01;
                    B +=0.01;
                }
                cubesList[indiceMinimumCubeZ].setColor(glm::vec3(R,G,B));//...Ou la baisser.
            }
            if(e.button.button == SDL_BUTTON_WHEELDOWN){
                R = cubesList[indiceMinimumCubeZ].getColor()[0];
                G = cubesList[indiceMinimumCubeZ].getColor()[1];
                B = cubesList[indiceMinimumCubeZ].getColor()[2];
                if(R>=-2. && G>=-2. && B>=-2.){
                    R -=0.01;
                    G -=0.01;
                    B -=0.01;
                }
                cubesList[indiceMinimumCubeZ].setColor(glm::vec3(R,G,B));
            }
        }

        if (SDL_GetMouseState(NULL,NULL)&SDL_BUTTON(SDL_BUTTON_LEFT)){  
        
            x+=0.02;
            R = (cos(x));
            G = (cos((x)+2.*PI/3.));
            B = (cos((x)-2.*PI/3.));

            cubesList[indiceMinimumCubeZ].setColor(glm::vec3(R, G, B));

        }
        if (SDL_GetMouseState(NULL,NULL)&SDL_BUTTON(SDL_BUTTON_RIGHT)){

            x-=0.02;
            R = (cos(x));
            G = (cos(x+2.*PI/3.));
            B = (cos(x-2.*PI/3.));
        
            cubesList[indiceMinimumCubeZ].setColor(glm::vec3(R,G,B));
        }
        
        MatrixView = camera.getViewMatrix();
        glUniformMatrix4fv(MatrixViewID,1,GL_FALSE,glm::value_ptr(MatrixView));


        // on crée le curseur ici.
        camera.drawCursor(Mprojo,MVMatrix, NormalMatrix,program.getGLId());

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        

        // Update the display
        windowManager.swapBuffers();
    }

    return EXIT_SUCCESS;
}