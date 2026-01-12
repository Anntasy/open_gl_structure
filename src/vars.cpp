# include "../include/h.hpp"


glm::float64 delta_time = 0;
class Camera camera;
bool keys[1024];

glm::dvec3 cam_front_start = glm::dvec3(0.0f, 0.0f, -1.0f);
glm::dvec3 cam_up_start = glm::dvec3(0.0f, -1.0f, 0.0f);
glm::dvec3 cam_right_start = glm::normalize(glm::cross(cam_front_start, cam_up_start));
