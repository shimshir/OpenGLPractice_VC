#include "util.h"
#include <iostream>
#include <algorithm>

FrameCounter::FrameCounter()
{
	m_prev_frame_count = 0;
	m_curr_frame_count = 0;
}
void FrameCounter::showFramerate(Uint32 interval)
{
	std::cout << "Framerate: " << 1000 * (m_curr_frame_count - m_prev_frame_count) / (float)interval << std::endl;
	m_prev_frame_count = m_curr_frame_count;
}
FrameCounter FrameCounter::operator++(int)
{
	++m_curr_frame_count;
	return *this;
}

Mesh* getSkyBox()
{
	std::vector<glm::vec3> positions = {
		// up
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(-1.0f, 1.0f, -1.0f),
		glm::vec3(1.0f, 1.0f, -1.0f),

		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(-1.0f, 1.0f, -1.0f),
		glm::vec3(-1.0f, 1.0f, 1.0f),

		// front
		glm::vec3(-1.0f, 1.0f, 1.0f),
		glm::vec3(1.01f, -1.0f, 1.0f),
		glm::vec3(-1.0f, -1.0f, 1.0f),

		glm::vec3(-1.0f, 1.0f, 1.0f),
		glm::vec3(1.01f, -1.0f, 1.0f),
		glm::vec3(1.01f, 1.0f, 1.0f),

		//left 
		glm::vec3(1.0f, 1.0f, -1.0f),
		glm::vec3(1.0f, -1.0f, 1.0f),
		glm::vec3(1.0f, -1.0f, -1.0f),

		glm::vec3(1.0f, 1.0f, -1.0f),
		glm::vec3(1.0f, -1.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),

		//right
		glm::vec3(-1.0f, 1.0f, 1.0f),
		glm::vec3(-1.0f, -1.0f, -1.0f),
		glm::vec3(-1.0f, -1.0f, 1.0f),

		glm::vec3(-1.0f, 1.0f, 1.0f),
		glm::vec3(-1.0f, -1.0f, -1.0f),
		glm::vec3(-1.0f, 1.0f, -1.0f),

		// back
		glm::vec3(-1.0f, 1.0f, -1.0f),
		glm::vec3(1.0f, -1.0f, -1.0f),
		glm::vec3(-1.0f, -1.0f, -1.0f),

		glm::vec3(-1.0f, 1.0f, -1.0f),
		glm::vec3(1.0f, -1.0f, -1.0f),
		glm::vec3(1.0f, 1.0f, -1.0f),

		// bottom
		glm::vec3(1.0f, -1.0f, 1.0f),
		glm::vec3(-1.0f, -1.0f, -1.0f),
		glm::vec3(1.0f, -1.0f, -1.0f),

		glm::vec3(1.0f, -1.0f, 1.0f),
		glm::vec3(-1.0f, -1.0f, -1.0f),
		glm::vec3(-1.0f, -1.0f, 1.0f)
	};

	std::vector<GLuint> indices;
	for (GLuint i = 0; i < positions.size(); i++) indices.push_back(i);


	Model model(positions, { 
		// up texture coords
		glm::vec2(0.001, 0.33), glm::vec2(0.249, 0.0), glm::vec2(0.001, 0.001),
		glm::vec2(0.001, 0.33), glm::vec2(0.249, 0.0), glm::vec2(0.249, 0.33),
		// front texture coords
		glm::vec2(0.25, 0.333), glm::vec2(0.0, 0.667), glm::vec2(0.25, 0.667),
		glm::vec2(0.25, 0.333), glm::vec2(0.0, 0.667), glm::vec2(0.0, 0.333),
		// left texture coords
		glm::vec2(0.75, 0.334), glm::vec2(1.0, 0.666), glm::vec2(0.75, 0.666),
		glm::vec2(0.75, 0.334), glm::vec2(1.0, 0.666), glm::vec2(1.0, 0.334),
		// right texture coords
		glm::vec2(0.25, 0.334), glm::vec2(0.5, 0.666), glm::vec2(0.25, 0.666),
		glm::vec2(0.25, 0.334), glm::vec2(0.5, 0.666), glm::vec2(0.5, 0.334),
		// back texture coords
		glm::vec2(0.5, 0.334), glm::vec2(0.75, 0.666), glm::vec2(0.5, 0.666),
		glm::vec2(0.5, 0.334), glm::vec2(0.75, 0.666), glm::vec2(0.75, 0.334),
		// bottom texture coords
		glm::vec2(0.001, 0.66), glm::vec2(0.249, 1.0), glm::vec2(0.001, 1.0),
		glm::vec2(0.001, 0.66), glm::vec2(0.249, 1.0), glm::vec2(0.249, 0.66)

	}, indices);

	Mesh *mesh = new Mesh(model, "res/textures/skybox/skybox.jpg");
	return mesh;
}