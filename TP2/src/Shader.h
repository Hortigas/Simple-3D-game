#pragma once
#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <string>
#include "glm.hpp"
#include "gtc\matrix_transform.hpp"

class Shader {
private:
	unsigned int ID_Program;
public:
	Shader(std::string VS, std::string FS);
	unsigned int GerarShader(std::string Shader,unsigned int tipo);
	void JuntarShader(std::string VS, std::string FS);
	unsigned int GetID();
	void Bind();
	void setBool(const std::string & name, bool value) const;
	void setInt(const std::string & name, int value) const;
	void setFloat(const std::string & name, float value) const;
	void setVec2(const std::string & name, const glm::vec2 & value) const;
	void setVec2(const std::string & name, float x, float y) const;
	void setVec3(const std::string & name, const glm::vec3 & value) const;
	void setVec3(const std::string & name, float x, float y, float z) const;
	void setVec4(const std::string & name, const glm::vec4 & value) const;
	void setVec4(const std::string & name, float x, float y, float z, float w);
	void setMat2(const std::string & name, const glm::mat2 & mat) const;
	void setMat3(const std::string & name, const glm::mat3 & mat) const;
	void setMat4(const std::string & name, const glm::mat4 & mat) const;
	void checkCompileErrors(int shader, std::string type);
	void defLights();
};