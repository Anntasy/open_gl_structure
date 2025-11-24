#include "h.hpp"

glm::vec3 cam_pos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cam_front = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cam_up = glm::vec3(0.0f, -1.0f, 0.0f);
bool keys[1024];
bool first_mouse = true;
GLfloat alpha = -90; 
GLfloat beta = 0;
GLfloat x_last = 400;
GLfloat y_last = 400;


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);

    if (action == GLFW_PRESS)
    {
    	keys[key] = true;
    }
    else if (action == GLFW_RELEASE)
    {
    	keys[key] = false;
    }
}


void mouse_callback(GLFWwindow* window, double x_pos, double y_pos)
{
    if (first_mouse)
   	{
		x_last = x_pos;
		y_last = y_pos;
		first_mouse = false;
		return;
    }
    GLfloat x_offset = x_pos - x_last;
    GLfloat y_offset = y_last - y_pos;
    x_last = x_pos;
    y_last = y_pos;
    GLfloat sense = 0.001;
    x_offset *= sense;
    y_offset *= sense;
    if (beta > 89)
    	beta = 89;
    else if (beta < -89)
    	beta = -89;
    alpha += x_offset;
    beta += y_offset;
    glm::vec3 front;
    front.x = cos(glm::radians(alpha)) * cos(glm::radians(beta));
	front.y = sin(glm::radians(beta));
	front.z = sin(glm::radians(alpha)) * cos(glm::radians(beta));
	cam_front = glm::normalize(front);
	for (int i=0; i < 3; i++)
		std::cout << cam_front[i] << ' ';
	std::cout << '\n';
}


void make_move()
{
    GLfloat cam_speed = 0.01f;

	if (keys[GLFW_KEY_W])
    {
        cam_pos += cam_speed*cam_front;
    }
    if (keys[GLFW_KEY_S])
    {
        cam_pos -= cam_speed*cam_front;
    }
    if (keys[GLFW_KEY_A])
    {
        cam_pos -= glm::normalize(glm::cross(cam_front, cam_up)) * cam_speed;
    }
    if (keys[GLFW_KEY_D])
    {
        cam_pos += glm::normalize(glm::cross(cam_front, cam_up)) * cam_speed;
    }
}

// void show_m(const glm::mat4 &m)
// {
// 	for (int x=0; x<4; x++) 
// 	{
//         for (int y=0; y<4; y++) 
//             std::cout << m[x][y] << "\t";

//     	std::cout << std::endl;
// 	}
// 	std::cout << std::endl;
// 	std::cout << std::endl;	
// }


int main()
{
	check_glfw();

    GLFWwindow* window = glfwCreateWindow(800, 800, "window", NULL, NULL);
    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, key_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);


	check_glew();

	VertexData vertex_data;
	Texture texture_data;

	GLuint texture = texture_data.add_texture("images/e4.png");
	GLuint texture2 = texture_data.add_texture("images/wall.png");

	// vertex_data.add_triangle(0.25f, 0.25f, 1.0f, 0.0f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f);
	// vertex_data.add_rectangle(-0.5f, -0.5f, 0.5f, 0.5f, 0.3f, 0.3f, 0.5f);
	vertex_data.add_cube({-0.5f, -0.5f, 0.0f}, {-0.5f, 0.5f, 0.0f}, {0.5f, 0.5f, 0.0f}, {1.0f, 1.0f, 0.1f});


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

    // glEnable(GL_CULL_FACE);

	glm::mat4 model(1.0f); 
	// model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	// show_m(model);

	// glm::mat4 view(1.0f);
	// view = glm::translate(view, glm::vec3(0.3f, 0.4f, -1.0f));
	// show_m(view);

	glm::mat4 view = glm::lookAt(
	cam_pos,
    cam_pos+cam_front,
    cam_up);

	glm::mat4 projection(1.0f);
	projection = glm::perspective(glm::radians(45.0f), HEIGHT/WIDTH, 0.05f, 50.0f);
	// show_m(projection);

	glm::mat4 transformation(1);
	transformation = projection*view*model;
	// show_m(transformation);

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		
		shader.use();

		glm::mat4 view = glm::lookAt(
		cam_pos,
	    cam_pos+cam_front,
	    cam_up);

		transformation = projection*view*model;

		GLint matrix_id = glGetUniformLocation(shader.program, "transformation");
		glUniformMatrix4fv(matrix_id, 1, GL_FALSE, glm::value_ptr(transformation)); // &transformation[0][0]

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glUniform1i(glGetUniformLocation(shader.program, "texture_sample1"), 0);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
		glUniform1i(glGetUniformLocation(shader.program, "texture_sample2"), 1);

        glBindVertexArray(vertex_array);
        glDrawElements(GL_TRIANGLES, vertex_data.indices.size()*3, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glBindTexture(GL_TEXTURE_2D, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
		make_move();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
