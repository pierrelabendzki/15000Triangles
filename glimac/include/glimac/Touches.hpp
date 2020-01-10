class FreeflyCamera;
class Cube3D;

class Touches{


Uint8* pKeyboard = SDL_GetKeyState(NULL); //pour vérifier l'état des touches enfoncées.

public:

void deplacementsClavier(FreeflyCamera &camera,float speed);
};