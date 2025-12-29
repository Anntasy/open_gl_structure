# ifndef VERTEXDATA_HPP
# define VERTEXDATA_HPP

# include "h.hpp"
# include <glm/glm.hpp>
# include <vector>


typedef struct Vertex
{
	glm::dvec3 position;
	glm::dvec3 color;
	glm::dvec2 texture;
}Vertex;

typedef struct Element
{
	glm::uvec3 triangle;
}Element;

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
	void add_cube(glm::dvec3 v1, glm::dvec3 v2, glm::dvec3 v3, glm::dvec3 color);
	void cube2();

	std::vector<Vertex> vertices;
	std::vector<Element> indices;

};


# endif
