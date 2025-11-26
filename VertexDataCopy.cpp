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

void VertexData::mark_buffer()
{
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
    sizeof(GLfloat)*v_step, (GLvoid*) 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
    sizeof(GLfloat)*v_step, (GLvoid*) (3*sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
};


void VertexData::move_to_buffer();
{
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

