#pragma once
#include "glm.hpp"
#include "gtc\matrix_transform.hpp"

enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	ROLLL,
	ROLLR
};

class Camera
{
public:
	// Camera Attributes
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;
	// Euler Angles
	double Yaw;
	double Pitch;
	double Roll;
	// Camera options
	float MovementSpeed;
	double MouseSensitivity;

	Camera();
	glm::mat4 GetViewMatrix();
	void ProcessKeyboard(Camera_Movement direction, float deltaTime);
	void ProcessMouseMovement(double xoffset, double yoffset);
	void updateCameraVectors();
	glm::mat3 eulerAnglesToRotationMatrix(glm::vec3 & theta);
};

