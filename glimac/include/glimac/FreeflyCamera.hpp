class FreeflyCamera{
	glm::vec3 m_Position;
	float m_fPhi;
	float m_fTheta;
	glm::vec3 m_FrontVector;
	glm::vec3 m_LeftVector;
	glm::vec3 m_UpVector;

public:
	//constructeur par défaut
	FreeflyCamera();

	//constructeur
	FreeflyCamera(const float x, const float y, const float z, const float Phi, const float Teta);

	void rotateLeft(float degrees);
	void rotateUp(float degrees);
	void moveLeft(float t);
	void moveFront(float t);
	void moveUp(float t);
	glm::mat4 getViewMatrix()const;

	

	glm::vec3 getPosition();
	void drawCursor(glm::mat4 matriceProj,glm::mat4 MVMatrix,glm::mat4 NormalMatrix,int programID);

};

