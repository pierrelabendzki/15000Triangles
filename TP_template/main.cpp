#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <glimac/FilePath.hpp>
#include <glimac/Program.hpp>
#include <iostream>
#include <vector>
#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp>

using namespace glimac;

int main(int argc, char** argv) {
    // Initialize SDL and open a window
    
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

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;


    FilePath applicationPath(argv[0]);
    Program program = loadProgram(applicationPath.dirPath() + "shaders/"+argv[1],applicationPath.dirPath() + "shaders/"+argv[2]);
    program.use();


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


    GLuint vertexArrayID;

    glGenVertexArrays(1,&vertexArrayID);
    glBindVertexArray(vertexArrayID);
    glBindBuffer(GL_ARRAY_BUFFER,vbPositionsID);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),0);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);

    glm::mat4 Mprojo = glm::perspective(glm::radians(70.f),RATIO,0.1f,100.f);
    GLuint MprojoID = glGetUniformLocation(program.getGLId(),"Mprojo");
    glUniformMatrix4fv(MprojoID,1,GL_FALSE,glm::value_ptr(Mprojo));
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

        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/
        glBindVertexArray(vertexArrayID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibPositionsID);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        // Update the display
        windowManager.swapBuffers();
    }

    return EXIT_SUCCESS;
}
