class Cube3D;

class GestionCube
{
public:
    // GestionCube();
    // ~GestionCube();

void creationCube(GLuint &vao, GLuint &ibPositionsID);
glm::vec4 vec3D_vers_2D(glm::mat4 &MatrixView, glm::mat4 &MVMatrix, glm::mat4 &NormalMatrix,Cube3D cube);
std::vector <int> listCubesCandidats(glm::mat4 &MatrixView, glm::mat4 &MVMatrix, glm::mat4 &NormalMatrix,std::vector<Cube3D> &cubesList); // cette méthode renvoie la liste des cubes qui sont dans l'axe de visée du curseur.
int indiceMinimumCubeZ(glm::mat4 &MatrixView, glm::mat4 &MVMatrix, glm::mat4 &NormalMatrix,std::vector<Cube3D> &cubesList);


};