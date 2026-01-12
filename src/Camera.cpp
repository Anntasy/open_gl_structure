# include "../include/h.hpp"

Camera::Camera()
{	
	// glm::dvec3 front = glm::dvec3(0.0f, 0.0f, -1.0f);
	// glm::dvec3 up = glm::dvec3(0.0f, -1.0f, 0.0f);
	// glm::dvec3 right = glm::normalize(glm::cross(cam_front, cam_up));
	position = glm::dvec3(0.0f, 0.0f, 10.0f);
	Yaw = YAW;
	Pitch = PITCH;
	orientation = glm::dquat(1.0f, 0.0f, 0.0f, 0.0f);
    sense = 1.e-5*5;
	speed = 1.2*delta_time;
	world_up = glm::dvec3(0.0f, -1.0f, 0.0f);
	update_cam_vectors();
}

void Camera::update_cam_vectors()
{
	front = glm::normalize(orientation*cam_front_start);
	right = glm::normalize(orientation*cam_right_start);
	up = glm::normalize(orientation*cam_up_start);
	// right = glm::normalize(glm::cross(front, world_up));
	// up = glm::normalize(glm::cross(right, front));
	speed = 1.2*delta_time;
}

void Camera::process_mouse(double d_x, double d_y)
{
	glm::dquat q_x = glm::angleAxis(d_x*sense, world_up);
	glm::dquat q_y = glm::angleAxis(d_y*sense, right);
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

glm::dmat4 Camera::get_view()
{
	return glm::lookAt(
		position,
	    position+front,
	    up);
}
