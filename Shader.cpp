#include "Shader.hpp"


Shader::Shader(const char* vertex_shader_path, const char* fragment_shader_path)
{
	std::string vertex_text, fragment_text;
	std::ifstream vertex_stream, fragment_stream;

	std::stringstream vertex_str_stream, fragment_str_stream;

	vertex_stream.open(vertex_shader_path);
	fragment_stream.open(fragment_shader_path);

	vertex_str_stream << vertex_stream.rdbuf();
	fragment_str_stream << fragment_stream.rdbuf();

	vertex_stream.close();
	fragment_stream.close();

	vertex_text = vertex_str_stream.str();
	fragment_text = fragment_str_stream.str();

	const char * vertex_shader_text = vertex_text.c_str();
	const char * fragment_shader_text = fragment_text.c_str();

	GLuint vertex, fragment;

	GLint success;
	GLchar info_log[INFO_LOG_SIZE];

	vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertex_shader_text, NULL);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {
    	glGetShaderInfoLog(vertex, INFO_LOG_SIZE, NULL, info_log);
    	std::cerr << "Vertex shader compile error:\n" << info_log << '\n';
    }

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragment_shader_text, NULL);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success)
    {
    	glGetShaderInfoLog(fragment, INFO_LOG_SIZE, NULL, info_log);
    	std::cerr << "Fragment shader compile error:\n" << info_log << '\n';
    }

    program = glCreateProgram();

    glAttachShader(program, vertex);
    glAttachShader(program, fragment);
    
    glLinkProgram(program);

    glGetShaderiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
    	glGetShaderInfoLog(program, INFO_LOG_SIZE, NULL, info_log);
    	std::cerr << "Program compile error:\n" << info_log << '\n';
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment); 
}

void Shader::use()
{
    glUseProgram(program);
}
