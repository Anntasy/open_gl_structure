#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "h.hpp"


class Texture
{
public:
	Texture(){}
	~Texture(){}

	GLuint add_texture(const char* file_name);

};


#endif