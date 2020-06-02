#include "Veiculo.h"

Veiculo::Veiculo() :
	Position(0), Up(0.f, 1.f, 0.f), Yaw(0), Pitch(0), Roll(0), Front(0, 0, -1), MovementSpeed(2.5f), MouseSensitivity(0.2f), WorldUp(0, 1, 0)
{
}

Veiculo::~Veiculo()
{
}

void Veiculo::ProcessKeyBoard(Veiculo_Movement direction,float deltaTime, MVP &mvp) {

	if (direction == FORWARDV)
		Aceleration = Front;
	if (direction == BACKWARDV) 
		Aceleration = -Front;
	if (direction == LEFTV) 
		Aceleration = -Right;
	if (direction == RIGHTV)
		Aceleration = Right;
	if (direction == UP)
		Aceleration = Up;
	if (direction == DOWN)
		Aceleration = -Up;
	if (direction == STATIC) {
		Velocity *= 0.997f;
		if (0.5f > sqrt(pow(Velocity.x, 2) + pow(Velocity.y, 2) + pow(Velocity.z, 2)))
			Velocity *= 0.99f;
	} 

	updateVeiculoVectors();
}

void Veiculo::ProcessMouseMovement(float xoffset, float yoffset)
{
	xoffset *= MouseSensitivity;
	yoffset *= MouseSensitivity;

	Yaw += xoffset;
	Pitch += yoffset;

	if (Pitch > 89.0f)
		Pitch = 89.0f;
	if (Pitch < -89.0f)
		Pitch = -89.0f;

	updateVeiculoVectors();
}

void Veiculo::updateVeiculoVectors()
{
	glm::vec3 front;
	float yaw = glm::radians(Yaw);
	float pitch = 0;
	float roll = glm::radians(Roll);
	glm::vec3 angulos(pitch, yaw, roll);
	glm::mat3 RMatrix = eulerAnglesToRotationMatrix(angulos);
	front = RMatrix * glm::vec3(0, 0, 1);
	Front = glm::normalize(front);
	Right = glm::normalize(glm::cross(Front, WorldUp));
	Up = glm::normalize(glm::cross(Right, Front));

	glm::vec3 AntVelocity = Velocity;
	Velocity += Aceleration*0.0025f;

	float tam = sqrt(pow(Velocity.x, 2) + pow(Velocity.y, 2) + pow(Velocity.z, 2));
	angulo = -3 * tam;

	if ((int)(tam*10) >= 50)
		Velocity = AntVelocity;

	CrossVelocity = glm::cross(Velocity, WorldUp);
}

glm::mat3 Veiculo::eulerAnglesToRotationMatrix(glm::vec3 &theta)
{
	// Calculate rotation about x axis Yaw
	glm::mat3 RX(
		1, 0, 0,
		0, cos(theta[0]), -sin(theta[0]),
		0, sin(theta[0]), cos(theta[0])
	);

	// Calculate rotation about y axis Pitch
	glm::mat3 RY(
		cos(theta[1]), 0, sin(theta[1]),
		0, 1, 0,
		-sin(theta[1]), 0, cos(theta[1])
	);

	// Calculate rotation about z axis Roll
	glm::mat3 RZ(
		cos(theta[2]), -sin(theta[2]), 0,
		sin(theta[2]), cos(theta[2]), 0,
		0, 0, 1
	);

	return RZ * RY * RX;
}

void Veiculo::calculations(MVP &mvp, float deltaTime) {
	Position += Velocity * deltaTime * 4.f;
	mvp.resetModel();
	mvp.translate(Position);
	mvp.scale(0.007f);
	if (angulo != 0)
		mvp.rotate(angulo, CrossVelocity);
	mvp.rotateY(-Yaw);
}
