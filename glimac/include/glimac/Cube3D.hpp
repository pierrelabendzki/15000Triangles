class Cube3D{
public:
	glm::vec3 m_Position /*= glm::vec3(0.,0.,0.)*/;
	glm::vec3 m_Color /*= glm::vec3(1.,1.,1.)*/;
	bool m_display;
	bool m_estDansLaListe;
	// std::vector<float> m_tabPositions/* = {
	// 	0.5,0.5,0.5,
	// 	-0.5,0.5,0.5,
	// 	-0.5,-0.5,0.5,
	// 	0.5,-0.5,0.5,
	// 	0.5,-0.5,-0.5,
	// 	0.5,0.5,-0.5,
	// 	-0.5,0.5,-0.5,
	// 	-0.5,0.5,0.5
	// }*/;
	// std::vector<int> m_indexSommets={
 //        0,1,2, 0,2,3, // les deux premiers blocs de 3 coordonnées correspondent à la première face.
 //        4,7,6, 4,6,5,
 //        1,6,7, 1,7,2,
 //        0,3,4, 0,4,5,
 //        2,7,4, 2,4,3,
 //        0,5,6, 0,6,1
 //    };

public:
	Cube3D();
	Cube3D(const float x, const float y, const float z, const float R, const float G, const float B);

glm::vec3 getPosition();
glm::vec3 getColor();

bool getDisplay();
bool getDansLaListe();

void setDisplay(bool display);
void setDansLaListe(bool l);
void setColor(glm::vec3 color);


~Cube3D() = default;

};