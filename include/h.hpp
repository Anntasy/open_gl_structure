#ifndef H_HPP
#define H_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <cstdarg>
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <SOIL/SOIL.h>
// #include <glm/dvec3.hpp>
// #include <vector>
// #include <utility>

#include "Shader.hpp"
#include "VertexData.hpp"
#include "Texture.hpp"
#include "Camera.hpp"
# include "vars.hpp"


// # define HEIGHT 3.0f
// # define WIDTH 3.0f
// extern glm::float64 delta_time = 0;
// // class Camera camera;
// extern bool keys[1024];


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void check_glfw();
void check_glew();
std::ostream& operator<<(std::ostream& os, const glm::dquat& q);
std::ostream& operator<<(std::ostream& os, const glm::dvec3& v);

#endif