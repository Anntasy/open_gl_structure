#include "h.hpp"
// #include "VertexData.hpp"



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

	VertexData vertex_data;

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

    // for (auto v: vertex_data.vertices)
    // {
    // 	std::cout << v.position[0] << '\n';
    // 	std::cout << v.position[1] << '\n'; 
    // 	std::cout << v.position[2] << '\n'; 
    // 	std::cout << v.color[0] << '\n'; 
    // 	std::cout << v.color[1] << '\n';
    // 	std::cout << v.color[2] << '\n';   
    // }

    // for (auto e: vertex_data.indices)
    // {
    // 	std::cout << e.triangle[0] << '\n';
    // 	std::cout << e.triangle[1] << '\n'; 
    // 	std::cout << e.triangle[2] << '\n';  
    // }

    // std::cout << "i_size: " << vertex_data.i_size << ", v_size: " << vertex_data.v_size << '\n';

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
			
		shader.use();

        glBindVertexArray(vertex_array);
        glDrawElements(GL_TRIANGLES, vertex_data.indices.size()*3, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
