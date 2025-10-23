# ifndef VERTEXDATA_HPP
# define VERTEXDATA_HPP

# include "h.hpp"

# define EXTEND 2


class VertexData
{
public:
	VertexData(std::size_t v_capacity, std::size_t v_step, std::size_t i_capacity, std::size_t i_step);
	~VertexData();

	void move_to_buffer();
	void mark_buffer();
	void vertex_add(short unsigned num_v, float vert...);
	void index_add(short unsigned num_i, int ind...);
	void add_triangle(float x_1, float y_1, float x_2, float y_2, float x_3, float y_3, float r, float g, float b);
	void add_rectangle(float x_1, float y_1, float x_2, float y_2, float r, float g, float b);
	void extend_v_capacity();
	void extend_i_capacity();


	std::size_t v_size;
	std::size_t i_size;
	std::size_t v_capacity;
	std::size_t i_capacity;
	std::size_t v_step;
	std::size_t i_step;

	GLfloat *vertices;
	GLuint *indices;

};


# endif
