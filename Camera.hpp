# ifndef CAMERA_HPP
# define CAMERA_HPP

# include "h.hpp"
# include <glm/glm.hpp>
# include <vector>

const GLfloat YAW = -90.0f;
const GLfloat PITCH =  0.0f;
const glm::vec3 cam_front_start = glm::vec3(0.0f, 0.0f, -1.0f);
const glm::vec3 cam_up_start = glm::vec3(0.0f, -1.0f, 0.0f);
const glm::vec3 cam_right_start = glm::normalize(glm::cross(cam_front_start, cam_up_start));


class Camera
{
public:
	Camera();
	~Camera() {}

	glm::mat4 get_view();
	void process_keyboard();
	void process_mouse(GLfloat d_x, GLfloat d_y);
	void update_cam_vectors();

	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 position;
	GLfloat Yaw;
	GLfloat Pitch;
    GLfloat sense;
	GLfloat speed;
	glm::vec3 world_up;
	glm::quat orientation;
};


extern Camera camera;

# endif
