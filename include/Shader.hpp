#ifndef SHADER_HPP
#define SHADER_HPP

#include "h.hpp"

#define INFO_LOG_SIZE 512

class Shader
{
public:
	Shader(const char* vertex_shader_path, const char* fragment_shader_path);

	void use();

	GLuint program;
};


#endif