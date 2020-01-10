class Cube3D;

class Scene{
	int nbCubes;
public:
	
	Scene();
	void addCube(Cube3D cube, int programID);
    void addGhostCube(Cube3D cube, int programID);
    void show(bool appear,Cube3D cube, int programID);

	void showGhost(bool appear,Cube3D cube, int programID);
	void setGhostCubePosition(int pos, Cube3D &cube, Cube3D &cubePere);
	void creationBoule(glm::vec3 centreBoule,std::vector<Cube3D> &cubesList,int rayon);
	void creationPavage(std::vector<Cube3D> &cubesList, int longueur, int largeur,float R, float G, float B);
};