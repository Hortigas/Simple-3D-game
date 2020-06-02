#include "TPCamera.h"

TPCamera::TPCamera() :
	Position(0, 1.f, 0), Up(0.f, 1.f, 0.f), Yaw(0), Pitch(0), Roll(0), Front(0, 0, -1), MovementSpeed(2.5f), MouseSensitivity(0.2f), WorldUp(0, 1, 0), distanceFV(15)
{
	updateTPCameraVectors();
}

glm::mat4 TPCamera::GetViewMatrix(Veiculo veiculo)
{
	this->veiculo = veiculo;
	Front.x *= distanceFV;
	Front.y *= distanceFV;
	Front.z *= distanceFV;
	Position = veiculo.Position - Front;
	glm::mat4 ViewMatrix = glm::lookAt(Position, veiculo.Position, Up);
	updateTPCameraVectors();
	return ViewMatrix;
}

void TPCamera::ProcessMouseMovement(double yoffset)
{

	yoffset *= MouseSensitivity;
	Pitch += yoffset;

	if (Pitch > 89.0f)
		Pitch = 89.0f;
	if (Pitch < -89.0f)
		Pitch = -89.0f;

	updateTPCameraVectors();
}

void TPCamera::updateTPCameraVectors()
{
	float yaw = glm::radians(veiculo.Yaw);
	float pitch = glm::radians(Pitch);
	float roll = glm::radians(Roll);
	glm::vec3 angulos(pitch, yaw, roll);
	glm::mat3 RMatrix = eulerAnglesToRotationMatrix(angulos);
	glm::vec3 front = RMatrix * glm::vec3(0, 0, 1);
	Front = glm::normalize(front);
	Right = glm::normalize(glm::cross(Front, WorldUp));
	Up = glm::normalize(glm::cross(Right, Front));

}

glm::mat3 TPCamera::eulerAnglesToRotationMatrix(glm::vec3 &theta)
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
