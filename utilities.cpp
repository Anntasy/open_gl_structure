# include "h.hpp"


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