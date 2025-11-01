#include "h.hpp"


int main()
{
	check_glfw();

    GLFWwindow* window = glfwCreateWindow(800, 500, "My first glfw3 window", NULL, NULL);
    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, key_callback);

	check_glew();

	VertexData vertex_data;
	Texture texture_data;

	GLuint texture = texture_data.add_texture("wall.png");
	vertex_data.add_triangle(0.25f, 0.25f, 1.0f, 0.0f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f);
	vertex_data.add_rectangle(0.6f, 0.7f, 0.3f, 0.0f, 1.0f, 0.0f, 0.0f);

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

	glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		
		shader.use();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glUniform1i(glGetUniformLocation(shader.program, "texture_sample1"), 0);

        glBindVertexArray(vertex_array);
        glDrawElements(GL_TRIANGLES, vertex_data.indices.size()*3, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glBindTexture(GL_TEXTURE_2D, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
