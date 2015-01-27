#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtx/transform.hpp>
#include <SDL2/SDL.h>
#include <iostream>

class Camera
{
public:
	Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar) : m_world_up(glm::vec3(0.0f, 1.0f, 0.0f))
	{
		m_pos = pos;
		m_forward = glm::vec3(0.0f, 0.0f, 1.0f);
		m_camera_up = glm::vec3(0.0f, 1.0f, 0.0f);
		m_projection = glm::perspective(fov, aspect, zNear, zFar);
	}

	inline glm::mat4 getViewProjection() const
	{
		return m_projection * glm::lookAt(m_pos, m_pos + m_forward, m_camera_up);
	}

	void moveUp(float amt)
	{
		m_pos += m_camera_up * amt;
	}

	void moveDown(float amt)
	{
		moveUp(-amt);
	}

	void moveForward(float amt)
	{
		m_pos += m_forward * amt;
	}

	void moveBackward(float amt)
	{
		moveForward(-amt);
	}

	void moveLeft(float amt)
	{
		m_pos += glm::normalize(glm::cross(m_camera_up, m_forward)) * amt;
	}

	void moveRight(float amt)
	{
		moveLeft(-amt);
	}

	void rotateX(float angle)
	{
		glm::vec3 left = glm::normalize(glm::cross(m_camera_up, m_forward));

		glm::mat4 rotation = glm::rotate(angle, left);

		m_forward = glm::vec3(glm::normalize(rotation * glm::vec4(m_forward, 0.0)));
		m_camera_up = glm::vec3(glm::normalize(rotation * glm::vec4(m_camera_up, 0.0)));
	}

	void rotateY(float angle)
	{
		glm::mat4 rotation = glm::rotate(angle, m_camera_up);
		m_forward = glm::vec3(glm::normalize(rotation * glm::vec4(m_forward, 0.0)));
	}

	void rotateZ(float angle)
	{
		glm::mat4 rotation = glm::rotate(angle, m_forward);
		m_camera_up = glm::vec3(glm::normalize(rotation * glm::vec4(m_camera_up, 0.0)));
	}
	void adjust(SDL_Event& windowEvent, SDL_Window* window)
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
	}

	void move()
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

protected:
private:
	glm::mat4 m_projection;
	glm::vec3 m_pos;
	glm::vec3 m_forward;
	const glm::vec3 m_world_up;
	glm::vec3 m_camera_up;

	bool m_move_forward = false, m_move_backward = false,
		m_move_left = false, m_move_right = false,
		m_rotate_left = false, m_rotate_right = false,
		m_move_up = false, m_move_down = false, 
		m_right_mousebutton_down = false;

	int m_mouse_position_x = 0, m_mouse_position_y = 0;

	const float m_mouse_sensivity = 0.003f;
	const float m_move_speed = 0.002f;
};


#endif //CAMERA_H