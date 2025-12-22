#include "h.hpp"

// glm::vec3 cam_pos = glm::vec3(0.0f, 0.0f, 10.0f);
// glm::vec3 cam_front = glm::vec3(0.0f, 0.0f, -1.0f);
// glm::vec3 cam_up = glm::vec3(0.0f, -1.0f, 0.0f);

// glm::vec3 cam_front_start = glm::vec3(0.0f, 0.0f, -1.0f);
// glm::vec3 cam_up_start = glm::vec3(0.0f, -1.0f, 0.0f);

// bool keys[1024];
bool first_mouse = true;
// glm::quat alpha = glm::angleAxis(glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f)); 
double x_last = 400;
double y_last = 400;

// GLfloat delta_time = 0;
GLfloat last_frame = 0;
std::ostream& operator<<(std::ostream& os, const glm::quat& q) { os << "quat(" << q.w << ", " << q.x << ", " << q.y << ", " << q.z << ")"; return os; }

// wait about 1 extra second b4 going in w/ the mouse!!!! 
// (the cursor should be outside of the window)

//glm::quat q = glm::angleAxis(glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
//glm::toMat4(q);

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
    if ((x_pos >= x_last && x_pos <= x_last) && (y_pos >= y_last && y_pos <= y_last))
    	return;

    GLfloat x_offset = -x_pos + x_last;
    GLfloat y_offset = y_last - y_pos;
    x_last = x_pos;
    y_last = y_pos;
    camera.process_mouse(x_offset, y_offset);

    // GLfloat sense = 0.001;
    // x_offset *= sense;
    // y_offset *= sense;
    // if (beta > 89)
    // 	beta = 89;
    // else if (beta < -89)
    // 	beta = -89;

    // if (alpha < -180)
    // 	alpha = -180;
    // else if (alpha > 180)
    // 	alpha = 180;
	// glm::vec3 cam_right = glm::normalize(glm::cross(cam_front, cam_up));

	// glm::vec3 v = x_offset*cam_up+y_offset*cam_right;


    // glm::quat rotation = glm::angleAxis((float)sqrt(x_offset*x_offset+y_offset*y_offset) * sense, glm::normalize(v));
    // alpha = rotation*alpha;
    // alpha = glm::normalize(alpha);

    // glm::quat y_rotation = glm::angleAxis(glm::radians(y_offset), cam_right);
    // x_rotation = x_rotation; //*y_rotation
    // x_rotation = glm::normalize(x_rotation);

    // alpha += x_offset;
    // beta += y_offset;
    // glm::vec3 front;
    // front.x = cos(glm::radians(alpha)) * cos(glm::radians(beta));
	// front.y = sin(glm::radians(beta));
	// front.z = sin(glm::radians(alpha)) * cos(glm::radians(beta));
	// cam_front = glm::normalize(alpha*cam_front_start);
	// cam_up = glm::normalize(alpha*cam_up_start);
	// std::cout << rotation << std::endl;

	// for (int i=0; i < 3; i++)
	// 	std::cout << cam_front[i] << ' ';
	// std::cout << '\n';

}


// void make_move()
// {
//     GLfloat cam_speed = 1.2*delta_time;

// 	if (keys[GLFW_KEY_W])
//     {
//         cam_pos += cam_speed*cam_front;
//     }
//     if (keys[GLFW_KEY_S])
//     {
//         cam_pos -= cam_speed*cam_front;
//     }
//     if (keys[GLFW_KEY_A])
//     {
//         cam_pos -= glm::normalize(glm::cross(cam_front, cam_up)) * cam_speed;
//     }
//     if (keys[GLFW_KEY_D])
//     {
//         cam_pos += glm::normalize(glm::cross(cam_front, cam_up)) * cam_speed;
//     }
// }

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

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	glfwFocusWindow(window);
    
    // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	// glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);


	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    if (glfwRawMouseMotionSupported())
        glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);


    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);

	glfwGetCursorPos(window, &x_last, &y_last);

	glewExperimental = GL_TRUE;

	check_glew();

	glEnable(GL_DEPTH_TEST);

	VertexData vertex_data;
	Texture texture_data;

	GLuint texture = texture_data.add_texture("images/fr_4.png");
	GLuint texture2 = texture_data.add_texture("images/wall.png");

	// vertex_data.add_triangle(0.25f, 0.25f, 1.0f, 0.0f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f);
	// vertex_data.add_rectangle(-0.5f, -0.5f, 0.5f, 0.5f, 0.3f, 0.3f, 0.5f);
	vertex_data.add_cube({-0.5f, -0.5f, 0.0f}, {-0.5f, 0.5f, 0.0f}, {0.5f, 0.5f, 0.0f}, {1.0f, 1.0f, 0.1f});
	vertex_data.add_cube({-1.0f, -1.0f, 1.0f}, {-1.0f, 1.0f, 1.0f}, {0.5f, 0.5f, 1.0f}, {1.0f, 1.0f, 1.0f});
	// vertex_data.cube2();

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

	// glm::mat4 view = glm::lookAt(
	// cam_pos,
    // cam_pos+cam_front,
    // cam_up);

	glm::mat4 view = camera.get_view();
    

	glm::mat4 projection(1.0f);
	projection = glm::perspective(glm::radians(45.0f), HEIGHT/WIDTH, 0.05f, 50.0f);
	// show_m(projection);

	glm::mat4 transformation(1);
	transformation = projection*view*model;
	// show_m(transformation);

	while (!glfwWindowShouldClose(window))
	{
		// glClear(GL_COLOR_BUFFER_BIT);


		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		GLfloat cur_frame = glfwGetTime();
		delta_time = cur_frame - last_frame;
		last_frame = cur_frame;
		
		shader.use();

		glm::mat4 view = camera.get_view();

		// glm::mat4 rotation = glm::toMat4(alpha);
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
		glfwGetCursorPos(window, &x_last, &y_last);
		camera.process_keyboard();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
