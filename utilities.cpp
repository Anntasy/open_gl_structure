# include "h.hpp"


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

void check_glfw()
{
    if (!glfwInit())
    {
        std::cerr << "No glfw >:(";
        throw -1;
    }
}

void check_glew()
{
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "No GLEW >;(";
        throw -1;
    }
}