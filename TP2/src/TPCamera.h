#pragma once
#include "glm.hpp"
#include "gtc\matrix_transform.hpp"

#include "MVP.h"
#include "Veiculo.h"

class TPCamera
{
public:
	// TPCamera Attributes
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;
	// Euler Angles
	double Yaw;
	double Pitch;
	double Roll;
	// TPCamera options
	float MovementSpeed;
	double MouseSensitivity;
	// Veiculo
	Veiculo veiculo;
	float distanceFV;

	TPCamera();
	glm::mat4 GetViewMatrix(Veiculo veiculo);
	void ProcessMouseMovement(double yoffset);
	void updateTPCameraVectors();
	glm::mat3 eulerAnglesToRotationMatrix(glm::vec3 & theta);
};

