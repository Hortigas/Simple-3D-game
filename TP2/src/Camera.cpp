#include "Camera.h"
#include <iostream>

Camera::Camera() :
	Position(0, 1.f, 0), Up(0.f, 1.f, 0.f), Yaw(0), Pitch(0), Roll(0), Front(0, 0, -1), MovementSpeed(4.f), MouseSensitivity(0.2f), WorldUp(0, 1, 0)
{
}

glm::mat4 Camera::GetViewMatrix()
{
	glm::mat4 ViewMatrix = glm::lookAt(Position, glm::vec3(Position + Front), Up);
	return ViewMatrix;
}

void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
	float velocity = MovementSpeed * deltaTime;
	if (direction == FORWARD)
		Position += Front * velocity;
	if (direction == BACKWARD)
		Position -= Front * velocity;
	if (direction == LEFT)
		Position -= Right * velocity;
	if (direction == RIGHT)
		Position += Right * velocity;
	if (direction == ROLLL) {
		//Roll -= 0.1;
		//if (Roll < -89)
		//	Roll = -89;

	}
	if (direction == ROLLR) {
		//Roll += 0.1;
		//if (Roll > 89)
		//	Roll = 89;
	}
	updateCameraVectors();
}

void Camera::ProcessMouseMovement(double xoffset, double yoffset)
{

	xoffset *= MouseSensitivity;
	yoffset *= MouseSensitivity;

	Yaw += xoffset;
	Pitch += yoffset;

	if (Pitch > 89.0f)
		Pitch = 89.0f;
	if (Pitch < -89.0f)
		Pitch = -89.0f;

	updateCameraVectors();
}

void Camera::updateCameraVectors()
{
	glm::vec3 front;
	float yaw = glm::radians(Yaw);
	float pitch = glm::radians(Pitch);
	float roll = glm::radians(Roll);
	glm::vec3 angulos(pitch, yaw, roll);
	glm::mat3 RMatrix = eulerAnglesToRotationMatrix(angulos);
	front = RMatrix * glm::vec3(0, 0, 1);
	Front = glm::normalize(front);
	Right = glm::normalize(glm::cross(Front, WorldUp));
	Up = glm::normalize(glm::cross(Right, Front));
}

glm::mat3 Camera::eulerAnglesToRotationMatrix(glm::vec3 &theta)
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
