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
	Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar);

	glm::mat4 getViewProjection() const;

	inline void moveUp(float amt){ m_pos += m_up * amt; }
	inline void moveDown(float amt){ moveUp(-amt); }
	inline void moveForward(float amt){ m_pos += m_forward * amt; }
	inline void moveBackward(float amt){ moveForward(-amt); }
	inline void moveLeft(float amt){ m_pos += glm::normalize(glm::cross(m_up, m_forward)) * amt; }
	inline void moveRight(float amt){ moveLeft(-amt); }

	void rotateX(float angle);
	void rotateY(float angle);
	void rotateZ(float angle);

	void adjust(SDL_Event& windowEvent, SDL_Window* window);
	void move();
	void reset();

private:
	glm::mat4 m_projection;

	glm::vec3 m_pos;
	const glm::vec3 m_init_pos;
	glm::vec3 m_forward;
	const glm::vec3 m_init_forward;
	glm::vec3 m_up;
	const glm::vec3 m_init_up;

	float m_fov;
	float m_aspect;
	float m_zNear;
	float m_zFar;

	const float m_init_fov;
	const float m_init_aspect;
	const float m_init_zNear;
	const float m_init_zFar;

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