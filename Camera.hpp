# ifndef CAMERA_HPP
# define CAMERA_HPP

# include "h.hpp"
# include <glm/glm.hpp>
# include <vector>

// const glm::float64 YAW = -90.0f;
// const glm::float64 PITCH =  0.0f;
// const glm::dvec3 cam_front_start = glm::dvec3(0.0f, 0.0f, -1.0f);
// const glm::dvec3 cam_up_start = glm::dvec3(0.0f, -1.0f, 0.0f);
// const glm::dvec3 cam_right_start = glm::normalize(glm::cross(cam_front_start, cam_up_start));


// # define HEIGHT 3.0f
// # define WIDTH 3.0f
// extern glm::float64 delta_time;
// // class Camera camera;
// extern bool keys[1024];


class Camera
{
public:
	Camera();
	~Camera() {}

	glm::dmat4 get_view();
	void process_keyboard();
	void process_mouse(double d_x, double d_y);
	void update_cam_vectors();

	glm::dvec3 front;
	glm::dvec3 up;
	glm::dvec3 right;
	glm::dvec3 position;
	glm::float64 Yaw;
	glm::float64 Pitch;
    double sense;
	glm::float64 speed;
	glm::dvec3 world_up;
	glm::dquat orientation;
};


extern Camera camera;

# endif
