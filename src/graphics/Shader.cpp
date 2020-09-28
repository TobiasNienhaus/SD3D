//
// Created by Tobias on 9/22/2020.
//

#include <iostream>
#include <sstream>
#include <fstream>

#include "Shader.h"

char Shader::errorLogBuffer[512];

Shader::Shader(const char *vertexPath, const char *fragmentPath)
{
	auto vertexSource{read_file_contents(vertexPath)};
	auto fragmentSource{read_file_contents(fragmentPath)};

	// TODO maybe there is a better way
	const auto *vertexSourceCstr{vertexSource.c_str()};
	const auto *fragmentSourceCstr{fragmentSource.c_str()};

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSourceCstr, nullptr);
	glCompileShader(vertexShader);
	if(!check_shader_error(vertexShader)) std::cout << "VERTEX STAGE\n";

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSourceCstr, nullptr);
	glCompileShader(fragmentShader);
	if(!check_shader_error(fragmentShader)) std::cout << "FRAGMENT STAGE\n";

	m_id = glCreateProgram();
	glAttachShader(m_id, vertexShader);
	glAttachShader(m_id, fragmentShader);
	glLinkProgram(m_id);

	check_program_error(m_id);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

[[maybe_unused]] void Shader::use() const
{
	glUseProgram(ID);
}

std::string Shader::read_file_contents(const char *path)
{
	std::stringstream ret{};
	std::ifstream shaderFile;
	try
	{
		shaderFile.open(path);
		ret << shaderFile.rdbuf();
		shaderFile.close();
	}
	catch(const std::ifstream::failure& e)
	{
		std::cout << "ERROR when opening file\n" << e.what() << '\n';
	}
	return ret.str();
}

int Shader::check_shader_error(GLuint shaderId)
{
	int success;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(shaderID, 512, nullptr, errorLogBuffer);
		std::cout << "SHADER STAGE ERROR!\n" << errorLogBuffer << '\n';
	}
	return success;
}

int Shader::check_program_error(GLuint programId)
{
	int success;
	glGetShaderiv(programId, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetProgramInfoLog(programID, 512, nullptr, errorLogBuffer);
		std::cout << "SHADER PROGRAM ERROR!\n" << errorLogBuffer << '\n';
	}
	return success;
}
