// #include "Cube3D.hpp"
#include <glimac/FilePath.hpp>

#include <glimac/Program.hpp>

class Scene{
	int nbCubes;
	// Program program = loadProgram(applicationPath.dirPath() + "shaders/cube.vs.glsl",applicationPath.dirPath() + "shaders/cube.fs.glsl");

	// Scene(){
	// 	// m_tabPositions = {
	// 	// 	0.5,0.5,0.5,
	// 	// 	-0.5,0.5,0.5,
	// 	// 	-0.5,-0.5,0.5,
	// 	// 	0.5,-0.5,0.5,
	// 	// 	0.5,-0.5,-0.5,
	// 	// 	0.5,0.5,-0.5,
	// 	// 	-0.5,0.5,-0.5,
	// 	// 	-0.5,-0.5,-0.5
	// 	// };
	// 	// m_indexSommets={
	//  //        0,1,2, 0,2,3, // les deux premiers blocs de 3 coordonnées correspondent à la première face.
	//  //        4,7,6, 4,6,5,
	//  //        1,6,7, 1,7,2,
	//  //        0,3,4, 0,4,5,
	//  //        2,7,4, 2,4,3,
	//  //        0,5,6, 0,6,1
	//  //    };
	// }
public:
	void initProgram(){}

	// void pavage(int programID){
	// 	 for (int i = -30; i < 30 ; i++) {//on crée un pavage de 60 cubes sur 60 centré en 0.
 //            for(int j = -30; j < 30 ; j++) {
 //                for(int k =-2; k<1;k++){
 //                    Cube3D cubePave(i,j,k);
 //                    scene.addCube(cubePave,program.getGLId());
 //                    // MVMatrix= glm::translate(glm::mat4(), glm::vec3(i, k, j));
 //                    // glUniformMatrix4fv(MVMatrixID,1,GL_FALSE,glm::value_ptr(MVMatrix));
 //                    // MatrixView = camera.getViewMatrix();
 //                    // glUniformMatrix4fv(MatrixViewID,1,GL_FALSE,glm::value_ptr(MatrixView));
 //                    // glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
 //                }
 //            }
 //        }
	// }


	void addCube(Cube3D cube, int programID){
		glm::mat4 MVMatrix= glm::translate(glm::mat4(), glm::vec3(cube.getPosition()[0],cube.getPosition()[1], cube.getPosition()[2]));
    	GLuint MVMatrixID = glGetUniformLocation(programID,"MVMatrix");

    	glUniformMatrix4fv(MVMatrixID,1,GL_FALSE,glm::value_ptr(MVMatrix));
    	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    	nbCubes++;
    }

    void show(bool appear,Cube3D cube, int programID){
		if(appear)
			addCube(cube,programID);
	}

	bool destroy(Cube3D cube, int programID){
		show(false, cube, programID);
		// std::cout<<"alerte"<<std::endl;
		cube.~Cube3D();
		return false;
	}
};