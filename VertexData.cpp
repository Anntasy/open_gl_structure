# include "h.hpp"


VertexData::VertexData()
{
}

VertexData::~VertexData()
{
}


void VertexData::move_to_buffer()
{
	glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(Vertex), vertices.data(), GL_DYNAMIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(Element), indices.data(), GL_DYNAMIC_DRAW);
}


void VertexData::mark_buffer()
{
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
    sizeof(Vertex), (GLvoid*) 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
    sizeof(Vertex), (GLvoid*) (3*sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
    sizeof(Vertex), (GLvoid*) (6*sizeof(GLfloat)));
    glEnableVertexAttribArray(2);
};


void VertexData::add_triangle(float x_1, float y_1, float x_2, float y_2, float x_3, float y_3, float r, float g, float b)
{
	vertices.push_back({{x_1, y_1, 0}, {r, g, b}, {0, 0}});
	vertices.push_back({{x_2, y_2, 0}, {r, g, b}, {0.5, 1}});
	vertices.push_back({{x_3, y_3, 0}, {r, g, b}, {1, 0}});

	// vertices.push_back({{x_1, y_1, 0}, {r, g, b}, {Vertex.texture[0], Vertex.texture[1]}});
	// vertices.push_back({{x_2, y_2, 0}, {r, g, b}, {Vertex.texture[0], Vertex.texture[1]}});
	// vertices.push_back({{x_3, y_3, 0}, {r, g, b}, {Vertex.texture[0], Vertex.texture[1]});

	indices.push_back({{vertices.size()-3, vertices.size()-2, vertices.size()-1}});
}


void VertexData::add_rectangle(float x_1, float y_1, float x_2, float y_2, float r, float g, float b)
{

	vertices.push_back({{x_1, y_1, 0}, {r, g, b}, {0, 0}});
	vertices.push_back({{x_1, y_2, 0}, {r, g, b}, {0, 1}});
	vertices.push_back({{x_2, y_2, 0}, {r, g, b}, {1, 1}});
	vertices.push_back({{x_2, y_1, 0}, {r, g, b}, {1, 0}});

	// vertices.push_back({{x_1, y_1, 0}, {r, g, b}, {Vertex.texture[0], Vertex.texture[1]}});
	// vertices.push_back({{x_1, y_2, 0}, {r, g, b}, {Vertex.texture[0], Vertex.texture[1]}});
	// vertices.push_back({{x_2, y_2, 0}, {r, g, b}, {Vertex.texture[0], Vertex.texture[1]}});
	// vertices.push_back({{x_2, y_1, 0}, {r, g, b}, {Vertex.texture[0], Vertex.texture[1]}});

	indices.push_back({{vertices.size()-4, vertices.size()-3, vertices.size()-2}});
	indices.push_back({{vertices.size()-1, vertices.size()-4, vertices.size()-2}});
}
