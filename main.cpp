#include "h.hpp"
#include "VertexData.hpp"


int main()
{
	if (!glfwInit())
	{
		std::cerr << "No glfw >:(";
		return -1;
	}
	GLFWwindow* window = glfwCreateWindow(800, 500, "My first glfw3 window", NULL, NULL);
	glfwMakeContextCurrent(window);


	if (glewInit() != GLEW_OK)
	{
		std::cerr << "No GLEW >;(";
		return -1;
	}
	// v_capacity, v_step, i_capacity, i_step
	VertexData vertex_data(4, 6, 2, 3);

	vertex_data.add_triangle(-0.5f, 0.5f, 1.0f, 0.0f, 0.5f, 0.5f, 0.7f, 0.2f, 0.5f);

	// GLfloat vertices[] = {
	// 	-0.5f, 0.5f, 0.0f,  1.0f, 0.0f, 1.0f, 
	// 	0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 
	// 	0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 
	// 	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f
	// };
	// vertex_data.add_vertex(-0.5f, 0.5f, 0.0f,  1.0f, 0.0f, 1.0f);

	// GLuint indices[]{
	// 	0, 1, 2,
	// 	0, 3, 1
	// };

	GLuint element_buffer;

    GLuint vertex_buffer, vertex_array;

    Shader shader("vertex_shader", "fragment_shader");

	glGenBuffers(1, &vertex_buffer);
	glGenVertexArrays(1, &vertex_array);
	glGenBuffers(1, &element_buffer);

	glBindVertexArray(vertex_array);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer);

    vertex_data.move_to_buffer();
    vertex_data.mark_buffer();

    glBindVertexArray(0);

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
			
		shader.use();

		// red_value = (sin(glfwGetTime()) / 2) + 0.5;
		// glUniform4f(vertex_color_location, red_value, 0.0f, 0.0f, 1.0f);

        glBindVertexArray(vertex_array);
        glDrawElements(GL_TRIANGLES, vertex_data.i_size, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
