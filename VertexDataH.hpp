# ifndef VERTEXDATA_HPP
# define VERTEXDATA_HPP

# include "h.hpp"


class VertexData
{
public:
	VertexData(std::size_t v_capacity, std::size_t v_step, std::size_t i_capacity, std::size_t i_step);
	~VertexData();

	void move_to_buffer();
	void mark_buffer();

	std::size_t v_size;
	std::size_t i_size;
	std::size_t v_capacity;
	std::size_t i_capacity;
	std::size_t v_step;
	std::size_t i_step;

	glm::float64 *vertices;
	GLuint *indices;

};


# endif
