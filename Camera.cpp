# include "h.hpp"


Camera::Camera()
{	
	// glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
	// glm::vec3 up = glm::vec3(0.0f, -1.0f, 0.0f);
	// glm::vec3 right = glm::normalize(glm::cross(cam_front, cam_up));
	position = glm::vec3(0.0f, 0.0f, 10.0f);
	Yaw = YAW;
	Pitch = PITCH;
	orientation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
    sense = 0.001;
	speed = 1.2*delta_time;
	world_up = glm::vec3(0.0f, -1.0f, 0.0f);
}

void Camera::update_cam_vectors()
{
	front = glm::normalize(orientation*cam_front_start);
	right = glm::normalize(orientation*cam_right_start);
	up = glm::normalize(orientation*cam_up_start);
	// right = glm::normalize(glm::cross(front, world_up));
	// up = glm::normalize(glm::cross(right, front));
}

void Camera::process_mouse(GLfloat d_x, GLfloat d_y)
{
	glm::quat q_x = glm::angleAxis(d_x*sense, world_up);
	glm::quat q_y = glm::angleAxis(d_y*sense, right);
	orientation = glm::normalize(q_x*q_y*orientation);
}

void Camera::process_keyboard()
{
	if (keys[GLFW_KEY_W])
    {
        position += speed*front;
    }
    if (keys[GLFW_KEY_S])
    {
        position -= speed*front;
    }
    if (keys[GLFW_KEY_A])
    {
        position -= glm::normalize(glm::cross(front, up)) * speed;
    }
    if (keys[GLFW_KEY_D])
    {
        position += glm::normalize(glm::cross(front, up)) * speed;
    }
}

glm::mat4 Camera::get_view()
{
	return glm::lookAt(
		position,
	    position+front,
	    up);
}
