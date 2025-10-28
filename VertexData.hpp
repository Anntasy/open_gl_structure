# ifndef VERTEXDATA_HPP
# define VERTEXDATA_HPP

# include "h.hpp"
# include <glm/glm.hpp>
# include <vector>


struct Vertex
{
	glm::vec3 position;
	glm::vec3 color;
};

struct Element
{
	glm::uvec3 triangle;
};

# define EXTEND 2


class VertexData
{
public:
	VertexData();
	~VertexData();

	void move_to_buffer();
	void mark_buffer();
	void add_triangle(float x_1, float y_1, float x_2, float y_2, float x_3, float y_3, float r, float g, float b);
	void add_rectangle(float x_1, float y_1, float x_2, float y_2, float r, float g, float b);

	std::vector<Vertex> vertices;
	std::vector<Element> indices;

};


# endif
