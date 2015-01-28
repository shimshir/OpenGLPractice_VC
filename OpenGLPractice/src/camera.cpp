#include "camera.h"

Camera::Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar) :
m_init_pos(pos),
m_init_forward(glm::vec3(0.0f, 0.0f, 1.0f)),
m_init_up(glm::vec3(0.0f, 1.0f, 0.0f)),
m_init_fov(fov),
m_init_aspect(aspect),
m_init_zNear(zNear),
m_init_zFar(zFar)
{
	m_pos = m_init_pos;
	m_forward = m_init_forward;
	m_up = m_init_up;

	m_fov = m_init_fov;
	m_aspect = m_init_aspect;
	m_zNear = m_init_zNear;
	m_zFar = m_init_zFar;

	m_projection = glm::perspective(m_fov, m_aspect, m_zNear, m_zFar);
}

glm::mat4 Camera::getViewProjection() const
{
	return m_projection * glm::lookAt(m_pos, m_pos + m_forward, m_up);
}

void Camera::rotateX(float angle)
{
	glm::vec3 left = glm::normalize(glm::cross(m_up, m_forward));

	glm::mat4 rotation = glm::rotate(angle, left);

	m_forward = glm::vec3(glm::normalize(rotation * glm::vec4(m_forward, 0.0)));
	m_up = glm::vec3(glm::normalize(rotation * glm::vec4(m_up, 0.0)));
}

void Camera::rotateY(float angle)
{
	glm::mat4 rotation = glm::rotate(angle, m_up);
	m_forward = glm::vec3(glm::normalize(rotation * glm::vec4(m_forward, 0.0)));
}

void Camera::rotateZ(float angle)
{
	glm::mat4 rotation = glm::rotate(angle, m_forward);
	m_up = glm::vec3(glm::normalize(rotation * glm::vec4(m_up, 0.0)));
}

void Camera::adjust(SDL_Event& windowEvent, SDL_Window* window)
{
	if (windowEvent.type == SDL_KEYDOWN && windowEvent.key.keysym.sym == SDLK_w)
		m_move_forward = true;
	if (windowEvent.type == SDL_KEYDOWN && windowEvent.key.keysym.sym == SDLK_s)
		m_move_backward = true;
	if (windowEvent.type == SDL_KEYDOWN && windowEvent.key.keysym.sym == SDLK_a)
		m_move_left = true;
	if (windowEvent.type == SDL_KEYDOWN && windowEvent.key.keysym.sym == SDLK_d)
		m_move_right = true;
	if (windowEvent.type == SDL_KEYDOWN && windowEvent.key.keysym.sym == SDLK_q)
		m_rotate_left = true;
	if (windowEvent.type == SDL_KEYDOWN && windowEvent.key.keysym.sym == SDLK_e)
		m_rotate_right = true;
	if (windowEvent.type == SDL_KEYDOWN && windowEvent.key.keysym.sym == SDLK_SPACE)
		m_move_up = true;
	if (windowEvent.type == SDL_KEYDOWN && windowEvent.key.keysym.sym == SDLK_LSHIFT)
		m_move_down = true;
	if (windowEvent.type == SDL_KEYUP && windowEvent.key.keysym.sym == SDLK_w)
		m_move_forward = false;
	if (windowEvent.type == SDL_KEYUP && windowEvent.key.keysym.sym == SDLK_s)
		m_move_backward = false;
	if (windowEvent.type == SDL_KEYUP && windowEvent.key.keysym.sym == SDLK_a)
		m_move_left = false;
	if (windowEvent.type == SDL_KEYUP && windowEvent.key.keysym.sym == SDLK_d)
		m_move_right = false;
	if (windowEvent.type == SDL_KEYUP && windowEvent.key.keysym.sym == SDLK_SPACE)
		m_move_up = false;
	if (windowEvent.type == SDL_KEYUP && windowEvent.key.keysym.sym == SDLK_LSHIFT)
		m_move_down = false;
	if (windowEvent.type == SDL_KEYUP && windowEvent.key.keysym.sym == SDLK_q)
		m_rotate_left = false;
	if (windowEvent.type == SDL_KEYUP && windowEvent.key.keysym.sym == SDLK_e)
		m_rotate_right = false;

	if (windowEvent.type == SDL_MOUSEBUTTONDOWN && windowEvent.button.button == SDL_BUTTON_RIGHT)
	{
		m_right_mousebutton_down = true;
		SDL_ShowCursor(0);

		m_mouse_position_x = windowEvent.motion.x;
		m_mouse_position_y = windowEvent.motion.y;
	}

	if (windowEvent.type == SDL_MOUSEBUTTONUP && windowEvent.button.button == SDL_BUTTON_RIGHT)
	{
		m_right_mousebutton_down = false;
		SDL_ShowCursor(1);
	}


	if (windowEvent.type == SDL_MOUSEMOTION && m_right_mousebutton_down)
	{
		rotateX(m_mouse_sensivity * (windowEvent.motion.y - m_mouse_position_y));
		rotateY(m_mouse_sensivity * (m_mouse_position_x - windowEvent.motion.x));
		SDL_WarpMouseInWindow(window, m_mouse_position_x, m_mouse_position_y);
	}

	if (windowEvent.type == SDL_MOUSEWHEEL && windowEvent.wheel.y < 0)
		moveBackward(200 * m_move_speed);

	if (windowEvent.type == SDL_MOUSEWHEEL && windowEvent.wheel.y > 0)
		moveForward(200 * m_move_speed);

	// reset camera
	if (windowEvent.type == SDL_KEYDOWN && windowEvent.key.keysym.sym == SDLK_r)
	{
		m_pos = m_init_pos;
		m_forward = m_init_forward;
		m_up = m_init_up;

		m_fov = m_init_fov;
		m_aspect = m_init_aspect;
		m_zNear = m_init_zNear;
		m_zFar = m_init_zFar;

		m_projection = glm::perspective(m_fov, m_aspect, m_zNear, m_zFar);
	}
}

void Camera::move()
{
	if (m_move_forward)
		moveForward(m_move_speed);
	if (m_move_backward)
		moveBackward(m_move_speed);
	if (m_move_left)
		moveLeft(m_move_speed);
	if (m_move_right)
		moveRight(m_move_speed);
	if (m_move_up)
		moveUp(m_move_speed);
	if (m_move_down)
		moveDown(m_move_speed);
	if (m_rotate_left)
		rotateZ(-0.001f);
	if (m_rotate_right)
		rotateZ(0.001f);
}

void Camera::reset()
{
	m_pos = m_init_pos;
	m_forward = m_init_forward;
	m_up = m_init_up;
	m_projection = glm::perspective(m_init_fov, m_init_aspect, m_init_zNear, m_init_zFar);
}