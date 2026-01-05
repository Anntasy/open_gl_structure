# include "../include/h.hpp"


VertexData::VertexData()
{
	count_obj = 0;
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
    glVertexAttribLPointer(0, 3, GL_DOUBLE,
    sizeof(Vertex), (GLvoid*) 0);
    glEnableVertexAttribArray(0);

    glVertexAttribLPointer(1, 3, GL_DOUBLE,
    sizeof(Vertex), (GLvoid*) (3*sizeof(glm::float64)));
    glEnableVertexAttribArray(1);

    glVertexAttribLPointer(2, 2, GL_DOUBLE,
    sizeof(Vertex), (GLvoid*) (6*sizeof(glm::float64)));
    glEnableVertexAttribArray(2);
};


void VertexData::add_triangle(float x_1, float y_1, float x_2, float y_2, float x_3, float y_3, float r, float g, float b)
{
	x_2 -= x_1;
	x_3 -= x_1;
	y_2 -= y_1;
	y_3 -= y_1;

	vertices.push_back({{0, 0, 0}, {r, g, b}, {0, 0}});
	vertices.push_back({{x_2, y_2, 0}, {r, g, b}, {0.5, 1}});
	vertices.push_back({{x_3, y_3, 0}, {r, g, b}, {1, 0}});

	indices.push_back({{vertices.size()-3, vertices.size()-2, vertices.size()-1}});

	count_obj++;
	identify.push_back(1);
	models.push_back(glm::dvec3(x_1, y_1, 0));
}


void VertexData::add_rectangle(float x_1, float y_1, float x_2, float y_2, float r, float g, float b)
{
	x_2 -= x_1;
	y_2 -= y_1;

	vertices.push_back({{0, 0, 0}, {r, g, b}, {0, 0}});
	vertices.push_back({{0, y_2, 0}, {r, g, b}, {0, 1}});
	vertices.push_back({{x_2, y_2, 0}, {r, g, b}, {1, 1}});
	vertices.push_back({{x_2, 0, 0}, {r, g, b}, {1, 0}});

	indices.push_back({{vertices.size()-4, vertices.size()-3, vertices.size()-2}});
	indices.push_back({{vertices.size()-1, vertices.size()-4, vertices.size()-2}});

	count_obj++;
	identify.push_back(2);
	models.push_back(glm::dvec3(x_1, y_1, 0));
}

void f(Vertex v)
{	
	std::cout << "pos:" << v.position.x << " " << v.position.y << " " << v.position.z << '\n';
	std::cout << "color:" << v.color.x << " " << v.color.y << " " << v.color.z << '\n';
	std::cout << "texture:" << v.texture.x << " " << v.texture.y << '\n';

}


void VertexData::add_cube(glm::dvec3 v1, glm::dvec3 v2, glm::dvec3 v3, glm::dvec3 color)
{
	glm::dvec3 copy_v1 = v1;
	v2 -= v1;
	v3 -= v1;
	v1 -= v1;

	vertices.push_back({v1, color, {0, 1}});
	vertices.push_back({v2, color, {1, 1}});
	vertices.push_back({v3, color, {1, 0}});

	glm::dvec3 a = v3 - v2 ;
	vertices.push_back({v1 + a, color, {0, 0}});

	glm::dvec3 b = v1 - v2 ;
	glm::dvec3 c = glm::cross(b, a) * (1/glm::length(a));

	vertices.push_back({v1 + a + c, color, {1, 0}});
	vertices.push_back({v3 + c, color, {0, 0}});
	vertices.push_back({v2 + c, color, {0, 1}});
	vertices.push_back({v1 + c, color, {1, 1}});

	// replace repeating coord
	vertices.push_back({v1 + a + c, color, {0, 1}});
	vertices.push_back({v3 + c, color, {1, 1}});
	vertices.push_back({v2 + c, color, {1, 0}});
	vertices.push_back({v1 + c, color, {0, 0}});


	indices.push_back({{vertices.size()-12, vertices.size()-11, vertices.size()-10}});
	indices.push_back({{vertices.size()-10, vertices.size()-9, vertices.size()-12}});

	indices.push_back({{vertices.size()-12, vertices.size()-9, vertices.size()-8}});
	indices.push_back({{vertices.size()-8, vertices.size()-5, vertices.size()-12}});

	indices.push_back({{vertices.size()-5, vertices.size()-8, vertices.size()-7}});
	indices.push_back({{vertices.size()-7, vertices.size()-6, vertices.size()-5}});

	indices.push_back({{vertices.size()-7, vertices.size()-6, vertices.size()-11}});
	indices.push_back({{vertices.size()-11, vertices.size()-10, vertices.size()-7}});


	indices.push_back({{vertices.size()-12, vertices.size()-1, vertices.size()-2}});
	indices.push_back({{vertices.size()-2, vertices.size()-11, vertices.size()-12}});

	indices.push_back({{vertices.size()-9, vertices.size()-4, vertices.size()-3}});
	indices.push_back({{vertices.size()-3, vertices.size()-10, vertices.size()-9}});

	count_obj++;
	identify.push_back(12);
	models.push_back(copy_v1);
}


void VertexData::cube2()
{
	glm::dvec3 color = {1.0f, 0.0f, 1.0f};

	glm::float64 all_vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
		};

		for (int i=0; i<12; i++)
		{
			vertices.push_back({
			{all_vertices[i*3*5],
			all_vertices[i*3*5+1],
		    all_vertices[i*3*5+2]},
			color,
			{all_vertices[i*3*5+3],
			all_vertices[i*3*5+4]}
            });


			vertices.push_back({
			{all_vertices[i*3*5+5],
			all_vertices[i*3*5+6],
		    all_vertices[i*3*5+7]},
			color,
			{all_vertices[i*3*5+8],
			all_vertices[i*3*5+9]}
            });


			vertices.push_back({
			{all_vertices[i*3*5+10],
			all_vertices[i*3*5+11],
		    all_vertices[i*3*5+12]},
			color,
			{all_vertices[i*3*5+13],
			all_vertices[i*3*5+14]}
            });

        	indices.push_back({{vertices.size()-3, vertices.size()-2, vertices.size()-1}});
		}

	count_obj++;
	identify.push_back(12);
}