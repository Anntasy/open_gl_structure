# include "h.hpp"


VertexData::VertexData(std::size_t v_capacity_, std::size_t v_step_, std::size_t i_capacity_, std::size_t i_step_)
{
	v_size = 0;
	i_size = 0;
	v_capacity = v_capacity_;
	i_capacity = i_capacity_;
	v_step = v_step_;
	i_step = i_step_;

	vertices = new GLfloat[v_capacity*v_step];
	indices = new GLuint[i_capacity*i_step];
}

VertexData::~VertexData()
{
	delete[] vertices;
	delete[] indices;
}


void VertexData::move_to_buffer()
{
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}


void VertexData::mark_buffer()
{
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
    sizeof(GLfloat)*v_step, (GLvoid*) 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
    sizeof(GLfloat)*v_step, (GLvoid*) (3*sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
};


// num_v must be equal to the number of passed vertices!!!!!!!!!!
void VertexData::vertex_add(short unsigned num_v, float vert...)
{
	if (num_v != v_step)
	{
		std::cerr << "Number of vertices should equal to v_step & len(vert)" << '\n';
		return;
	}
	va_list args;
	va_start(args, vert);
	float v;

	while (vert > 0)
	{
		v = va_arg(args, float);
		vertices[v_size++] = v;
		vert--;
	}
	va_end(args);
}

void VertexData::index_add(short unsigned num_i, int ind...)
{
	if (num_i != i_step)
	{
		std::cerr << "Number of indices should equal to i_step & len(ind)" << '\n';
		return;
	}
	va_list args;
	va_start(args, ind);
	int i;

	while (ind > 0)
	{
		i = va_arg(args, int);
		indices[i_size++] = i;
		ind--;
	}
	va_end(args);
}


void VertexData::add_triangle(float x_1, float y_1, float x_2, float y_2, float x_3, float y_3, float r, float g, float b)
{

	if (v_capacity < v_step*3 + v_size)
	{
		extend_v_capacity();
	}

	if (i_capacity < i_step + i_size)
	{
		extend_i_capacity();
	}

	vertices[v_size++] = x_1;
	vertices[v_size++] = y_1;
	vertices[v_size++] = 0.0f;
	vertices[v_size++] = r;
	vertices[v_size++] = g;
	vertices[v_size++] = b;
	
	vertices[v_size++] = x_2;
	vertices[v_size++] = y_2;
	vertices[v_size++] = 0.0f;
	vertices[v_size++] = r;
	vertices[v_size++] = g;
	vertices[v_size++] = b;

	vertices[v_size++] = x_3;	
	vertices[v_size++] = y_3;
	vertices[v_size++] = 0.0f;
	vertices[v_size++] = r;
	vertices[v_size++] = g;
	vertices[v_size++] = b;

	indices[i_size++] = v_size/v_step-3;
	indices[i_size++] = v_size/v_step-2;
	indices[i_size++] = v_size/v_step-1;

}


void VertexData::add_rectangle(float x_1, float y_1, float x_2, float y_2, float r, float g, float b)
{
	if (v_capacity < v_step*4 + v_size)
	{
		extend_v_capacity();
	}

	if (i_capacity < i_step*2 + i_size)
	{
		extend_i_capacity();
	}

	vertices[v_size++] = x_1;
	vertices[v_size++] = y_1;
	vertices[v_size++] = 0.0f;
	vertices[v_size++] = r;
	vertices[v_size++] = g;
	vertices[v_size++] = b;

	vertices[v_size++] = x_1;
	vertices[v_size++]= y_2;
	vertices[v_size++] = 0.0f;
	vertices[v_size++] = r;
	vertices[v_size++] = g;
	vertices[v_size++] = b;

	vertices[v_size++] = x_2;
	vertices[v_size++] = y_2;
	vertices[v_size++] = 0.0f;
	vertices[v_size++] = r;
	vertices[v_size++] = g;
	vertices[v_size++] = b;

	vertices[v_size++] = x_2;
	vertices[v_size++] = y_1;
	vertices[v_size++] = 0.0f;
	vertices[v_size++] = r;
	vertices[v_size++] = g;
	vertices[v_size++] = b;

	indices[i_size++] = v_size/v_step-4;
	indices[i_size++] = v_size/v_step-3;
	indices[i_size++] = v_size/v_step-2;
	indices[i_size++] = v_size/v_step-1;
	indices[i_size++] = v_size/v_step-4;
	indices[i_size++] = v_size/v_step-2;
}

void VertexData::extend_v_capacity()
{
	GLfloat *new_arr = new GLfloat[v_capacity*EXTEND];
	for (std::size_t i=0; i<v_size; i++)
		new_arr[i] = vertices[i];
	delete vertices;

	vertices = new_arr;
	v_capacity = v_capacity*EXTEND;
}

void VertexData::extend_i_capacity()
{
	GLuint *new_arr = new GLuint[i_capacity*EXTEND];
	for (std::size_t i=0; i<i_size; i++)
		new_arr[i] = indices[i];
	delete indices;
	
	indices = new_arr;
	i_capacity = i_capacity*EXTEND;
}
