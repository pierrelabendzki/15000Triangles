#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <glimac/FilePath.hpp>
#include <glimac/Program.hpp>
#include <iostream>
#include <vector>
#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp>
#include "glimac/FreeflyCamera.hpp"

using namespace glimac;


int main(int argc, char** argv) {

    FreeflyCamera camera;


    // Initialize SDL and open a window
    int nbCubes = 3; 
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


    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;


    FilePath applicationPath(argv[0]);
    Program program = loadProgram(applicationPath.dirPath() + "shaders/"+argv[1],applicationPath.dirPath() + "shaders/"+argv[2]);
    program.use();

    GLuint iterZ = glGetUniformLocation(program.getGLId(),"iterZ");
    glUniform1f(iterZ,1);
    GLuint iterX = glGetUniformLocation(program.getGLId(),"iterX");
    glUniform1f(iterX,1);

    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/
    GLuint vbPositionsID;
    glGenBuffers(1,&vbPositionsID);
    glBindBuffer(GL_ARRAY_BUFFER, vbPositionsID);
    float tabPositions[] = {
         0.5,  0.5,  0.5, //0
        -0.5,  0.5,  0.5, //1
        -0.5, -0.5,  0.5, //2
         0.5, -0.5,  0.5, //3
         0.5, -0.5, -0.5, //4
         0.5,  0.5, -0.5, //5
        -0.5,  0.5, -0.5, //6
        -0.5, -0.5, -0.5, //7
    };


    glBufferData(GL_ARRAY_BUFFER, sizeof(tabPositions), tabPositions, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    

    

    GLuint ibPositionsID;
    glGenBuffers(1, &ibPositionsID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibPositionsID);

    int indexSommets[] = {
        0,1,2, 0,2,3, // les deux premiers blocs de 3 coordonnées correspondent à la première face.
        4,7,6, 4,6,5,
        1,6,7, 1,7,2,
        0,3,4, 0,4,5,
        2,7,4, 2,4,3,
        0,5,6, 0,6,1
    };

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
                case SDL_MOUSEMOTION:
                    if (SDL_BUTTON(SDL_BUTTON_LEFT) & e.motion.state)
                    {
                        camera.rotateLeft(e.motion.xrel);
                        camera.rotateUp(e.motion.yrel);
                    }
                    break;
                case SDL_KEYDOWN:
                    // AXE : x=0 y=1 z=2
                    if (e.key.keysym.sym == SDLK_z) {
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
                    // }
            }
        }

        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glBindVertexArray(vertexArrayID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibPositionsID);
        //glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        
        for (int i = -30; i < 30 ; i++) {//on crée un pavage de 60 cubes sur 60 centré en 0.
            for(int j = -30; j < 30 ; j++) {
                MVMatrix= glm::translate(glm::mat4(), glm::vec3(2*i, -1., 2*j));
                glUniformMatrix4fv(MVMatrixID,1,GL_FALSE,glm::value_ptr(MVMatrix));
                // camera.rotateLeft(0.);
                // camera.moveLeft(0.00001);
                
                MatrixView = camera.getViewMatrix();
                glUniformMatrix4fv(MatrixViewID,1,GL_FALSE,glm::value_ptr(MatrixView));
                glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
            }
        }
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        
       

        // Update the display
        windowManager.swapBuffers();
    }

    return EXIT_SUCCESS;
}
