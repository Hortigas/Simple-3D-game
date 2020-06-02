#include "Shader.h"

Shader::Shader(std::string VS, std::string FS) {
	JuntarShader(VS, FS);
}

unsigned int Shader::GerarShader(std::string Shader,unsigned int tipo) {
	std::ifstream arquivo;
	std::string linha;
	std::stringstream texto;
	unsigned int id = glCreateShader(tipo);
	std::string local = "res/shaders/"+Shader;

	arquivo.open(local);
	if (!arquivo.is_open())
		std::cout << "erro ao abrir o arquivo\n";
	
	while (getline(arquivo, linha)) 
		texto << linha << '\n';

	const std::string tmp = texto.str();
	const char* txt = tmp.c_str();
	glShaderSource(id, 1, &txt, nullptr);
	glCompileShader(id);
	checkCompileErrors(id, "Shader");
	return id;
}

void Shader::JuntarShader(std::string VS, std::string FS) {
	unsigned int programa = glCreateProgram();
	unsigned int VertexShader = GerarShader(VS, GL_VERTEX_SHADER);
	unsigned int FragmentShader = GerarShader(FS, GL_FRAGMENT_SHADER);
	glAttachShader(programa, VertexShader);
	glAttachShader(programa, FragmentShader);
	glLinkProgram(programa);
	checkCompileErrors(programa, "PROGRAM");

	glDeleteShader(VertexShader);
	glDeleteShader(FragmentShader);
	ID_Program = programa;
}

unsigned int Shader::GetID() {
	return ID_Program;
}

void Shader::Bind() {
	glUseProgram(ID_Program);
}

void Shader::setBool(const std::string &name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID_Program, name.c_str()), (int)value);
}
// ------------------------------------------------------------------------
void Shader::setInt(const std::string &name, int value) const
{
	glUniform1i(glGetUniformLocation(ID_Program, name.c_str()), value);
}
// ------------------------------------------------------------------------
void Shader::setFloat(const std::string &name, float value) const
{
	glUniform1f(glGetUniformLocation(ID_Program, name.c_str()), value);
}
// ------------------------------------------------------------------------
void Shader::setVec2(const std::string &name, const glm::vec2 &value) const
{
	glUniform2fv(glGetUniformLocation(ID_Program, name.c_str()), 1, &value[0]);
}
void Shader::setVec2(const std::string &name, float x, float y) const
{
	glUniform2f(glGetUniformLocation(ID_Program, name.c_str()), x, y);
}
// ------------------------------------------------------------------------
void Shader::setVec3(const std::string &name, const glm::vec3 &value) const
{
	glUniform3fv(glGetUniformLocation(ID_Program, name.c_str()), 1, &value[0]);
}
void Shader::setVec3(const std::string &name, float x, float y, float z) const
{
	glUniform3f(glGetUniformLocation(ID_Program, name.c_str()), x, y, z);
}
// ------------------------------------------------------------------------
void Shader::setVec4(const std::string &name, const glm::vec4 &value) const
{
	glUniform4fv(glGetUniformLocation(ID_Program, name.c_str()), 1, &value[0]);
}
void Shader::setVec4(const std::string &name, float x, float y, float z, float w)
{
	glUniform4f(glGetUniformLocation(ID_Program, name.c_str()), x, y, z, w);
}
// ------------------------------------------------------------------------
void Shader::setMat2(const std::string &name, const glm::mat2 &mat) const
{
	glUniformMatrix2fv(glGetUniformLocation(ID_Program, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void Shader::setMat3(const std::string &name, const glm::mat3 &mat) const
{
	glUniformMatrix3fv(glGetUniformLocation(ID_Program, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const
{
	glUniformMatrix4fv(glGetUniformLocation(ID_Program, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::checkCompileErrors(int shader, std::string type)
{
	GLint success;
	GLchar infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
}

void Shader::defLights() {
	// material shininess
		setFloat("material.shininess", 32.0f);
	// light switch
	// directional light
	setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
	setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
	setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
	setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
	// point light 1
	setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
	setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
	setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
	setFloat("pointLights[0].constant", 1.0f);
	setFloat("pointLights[0].linear", 0.09f);
	setFloat("pointLights[0].quadratic", 0.032f);
	// point light 2
	setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
	setVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
	setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
	setFloat("pointLights[1].constant", 1.0f);
	setFloat("pointLights[1].linear", 0.09f);
	setFloat("pointLights[1].quadratic", 0.032f);

	// spotLight
	setVec3("spotLight.direction", 0.0f, -1.0f, 0.0f);
	setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
	setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
	setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
	setFloat("spotLight.constant", 0.1f);
	setFloat("spotLight.linear", 0.01f);
	setFloat("spotLight.quadratic", 0.0002f);
	setFloat("spotLight.cutOff", glm::cos(glm::radians(6.5f)));
	setFloat("spotLight.outerCutOff", glm::cos(glm::radians(10.0f)));

}