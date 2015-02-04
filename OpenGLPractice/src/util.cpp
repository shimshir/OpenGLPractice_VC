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
	float scale = 100.0f;
	std::vector<glm::vec3> positions = {
		// up
		scale * glm::vec3(1.0f, 1.0f, 1.0f),
		scale * glm::vec3(-1.0f, 1.0f, -1.0f),
		scale * glm::vec3(1.0f, 1.0f, -1.0f),

		scale * glm::vec3(1.0f, 1.0f, 1.0f),
		scale * glm::vec3(-1.0f, 1.0f, -1.0f),
		scale * glm::vec3(-1.0f, 1.0f, 1.0f),

		// front
		scale * glm::vec3(-1.0f, 1.0f, 1.0f),
		scale * glm::vec3(1.01f, -1.0f, 1.0f),
		scale * glm::vec3(-1.0f, -1.0f, 1.0f),

		scale * glm::vec3(-1.0f, 1.0f, 1.0f),
		scale * glm::vec3(1.01f, -1.0f, 1.0f),
		scale * glm::vec3(1.01f, 1.0f, 1.0f),

		//left 
		scale * glm::vec3(1.0f, 1.0f, -1.0f),
		scale * glm::vec3(1.0f, -1.0f, 1.0f),
		scale * glm::vec3(1.0f, -1.0f, -1.0f),

		scale * glm::vec3(1.0f, 1.0f, -1.0f),
		scale * glm::vec3(1.0f, -1.0f, 1.0f),
		scale * glm::vec3(1.0f, 1.0f, 1.0f),

		//right
		scale * glm::vec3(-1.0f, 1.0f, 1.0f),
		scale * glm::vec3(-1.0f, -1.0f, -1.0f),
		scale * glm::vec3(-1.0f, -1.0f, 1.0f),

		scale * glm::vec3(-1.0f, 1.0f, 1.0f),
		scale * glm::vec3(-1.0f, -1.0f, -1.0f),
		scale * glm::vec3(-1.0f, 1.0f, -1.0f),

		// back
		scale * glm::vec3(-1.0f, 1.0f, -1.0f),
		scale * glm::vec3(1.0f, -1.0f, -1.0f),
		scale * glm::vec3(-1.0f, -1.0f, -1.0f),

		scale * glm::vec3(-1.0f, 1.0f, -1.0f),
		scale * glm::vec3(1.0f, -1.0f, -1.0f),
		scale * glm::vec3(1.0f, 1.0f, -1.0f)
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
		glm::vec2(0.5, 0.334), glm::vec2(0.75, 0.666), glm::vec2(0.75, 0.334)

	}, indices);

	Mesh *mesh = new Mesh(model, "res/textures/skybox/skybox.png");
	return mesh;
}