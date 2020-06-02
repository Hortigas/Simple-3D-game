#pragma once
#include "glm.hpp"
#include "gtc\matrix_transform.hpp"
#include "MVP.h"

enum Veiculo_Movement {
	FORWARDV,
	BACKWARDV,
	LEFTV,
	RIGHTV,
	UP,
	DOWN,
	STATIC
};

class Veiculo
{
private:
public:
	glm::vec3 Position;
	glm::vec3 AntPosition;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;
	glm::vec3 Velocity;
	glm::vec3 CrossVelocity;
	glm::vec3 Aceleration;
	// Euler Angles
	float Yaw;
	float Pitch;
	float Roll;
	//Veiculo Options
	float MovementSpeed;
	float MouseSensitivity;
	float maxSpeed;
	float angulo;

	Veiculo();
	~Veiculo();
	void ProcessKeyBoard(Veiculo_Movement direction, float deltaTime, MVP &mvp);
	void ProcessMouseMovement(float xoffset, float yoffset);
	void updateVeiculoVectors();
	glm::mat3 eulerAnglesToRotationMatrix(glm::vec3 & theta);
	void calculations(MVP &mvp, float delta);
};

