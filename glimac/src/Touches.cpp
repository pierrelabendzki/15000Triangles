#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <glimac/FilePath.hpp>
#include <glimac/Program.hpp>
#include <iostream>
#include <vector>
#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp>
#include <math.h>
#include "glimac/Touches.hpp"
#include "glimac/Cube3D.hpp"
#include "glimac/FreeflyCamera.hpp"



void Touches::deplacementsClavier(FreeflyCamera &camera,float speed){
    if (pKeyboard[SDLK_z]) camera.moveFront(-0.01*speed);
    if (pKeyboard[SDLK_s]) camera.moveFront(0.01*speed);
    if (pKeyboard[SDLK_q]) camera.moveLeft(-0.01*speed);
    if (pKeyboard[SDLK_d]) camera.moveLeft(0.01*speed);
    if (pKeyboard[SDLK_UP]) camera.moveUp(0.01*speed);
    if (pKeyboard[SDLK_DOWN]) camera.moveUp(-0.01*speed);
}

