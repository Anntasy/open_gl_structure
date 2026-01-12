# ifndef VARS_HPP
# define VARS_HPP


constexpr glm::float64 YAW = -90.0f;
constexpr glm::float64 PITCH =  0.0f;
extern glm::dvec3 cam_front_start;
extern glm::dvec3 cam_up_start;
extern glm::dvec3 cam_right_start;

# define HEIGHT 3.0f
# define WIDTH 3.0f
extern glm::float64 delta_time;
extern class Camera camera;
extern bool keys[1024];

# endif