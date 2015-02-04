#include <iostream>
#include <vector>
#include <thread>

#include "display.h"
#include "shader.h"
#include "model.h"
#include "mesh.h"
#include "transform.h"
#include "util.h"
#include "camera.h"

static const int DISPLAY_WIDTH = 640;
static const int DISPLAY_HEIGHT = 480;

int main(int argc, char *argv[]) {
	Display display("OpenGL", DISPLAY_WIDTH, DISPLAY_HEIGHT);
	display.init();
	SDL_Window* window = display.createWindow();
	display.createContext();

	Shader shader;
	shader.addShaderFromFile(GL_VERTEX_SHADER, "res/shaders/vertexShader.glsl");
	shader.addShaderFromFile(GL_FRAGMENT_SHADER, "res/shaders/fragmentShader.glsl");
	shader.createAndCompile();
	shader.linkAndUse();

	std::vector<glm::vec3> positions1 = {
		// bottom
		glm::vec3(0.0f, 0.0f, 0.5f),
		glm::vec3(0.433f, 0.0f, -0.25f),
		glm::vec3(-0.433f, 0.0f, -0.25f),

		glm::vec3(0.0f, 0.0f, 0.5f),
		glm::vec3(0.433f, 0.0f, -0.25f),
		glm::vec3(0.0f, 0.75f, 0.0f),

		glm::vec3(0.0f, 0.0f, 0.5f),
		glm::vec3(-0.433f, 0.0f, -0.25f),
		glm::vec3(0.0f, 0.75f, 0.0f),

		glm::vec3(0.433f, 0.0f, -0.25f),
		glm::vec3(-0.433f, 0.0f, -0.25f),
		glm::vec3(0.0f, 0.75f, 0.0f)
	};

	std::vector<glm::vec3> positions2 = {
		// bottom
		glm::vec3(0.0f, 0.0f, 0.5f),
		glm::vec3(0.433f, 0.0f, -0.25f),
		glm::vec3(-0.433f, 0.0f, -0.25f),

		glm::vec3(0.0f, 0.0f, 0.5f),
		glm::vec3(0.433f, 0.0f, -0.25f),
		glm::vec3(0.0f, 0.75f, 0.0f),

		glm::vec3(0.0f, 0.0f, 0.5f),
		glm::vec3(-0.433f, 0.0f, -0.25f),
		glm::vec3(0.0f, 0.75f, 0.0f),

		glm::vec3(0.433f, 0.0f, -0.25f),
		glm::vec3(-0.433f, 0.0f, -0.25f),
		glm::vec3(0.0f, 0.75f, 0.0f)
	};

	std::vector<glm::vec3> ground_positions = {
		100.0f * glm::vec3(-1.0f, 0.0f, 1.0f),
		100.0f * glm::vec3(1.0f, 0.0f, -1.0f),
		100.0f * glm::vec3(-1.0f, 0.0f, -1.0f),

		100.0f * glm::vec3(-1.0f, 0.0f, 1.0f),
		100.0f * glm::vec3(1.0f, 0.0f, -1.0f),
		100.0f * glm::vec3(1.0f, 0.0f, 1.0f)
	};
	std::vector<GLuint> ground_indices = { 0, 1, 2, 4, 3, 5 };

	std::vector<GLuint> indices;
	for (GLuint i = 0; i < positions1.size(); i++) indices.push_back(i);

	Model model1(positions1, { glm::vec2(0.0, 1.0), glm::vec2(1.0, 1.0), glm::vec2(0.5, 0.0),
		glm::vec2(0.0, 1.0), glm::vec2(1.0, 1.0), glm::vec2(0.5, 0.0),
		glm::vec2(0.0, 1.0), glm::vec2(1.0, 1.0), glm::vec2(0.5, 0.0),
		glm::vec2(0.0, 1.0), glm::vec2(1.0, 1.0), glm::vec2(0.5, 0.0) }, indices);

	Model model2(positions2, { glm::vec2(0.0, 1.0), glm::vec2(1.0, 1.0), glm::vec2(0.5, 0.0),
		glm::vec2(0.0, 1.0), glm::vec2(1.0, 1.0), glm::vec2(0.5, 0.0),
		glm::vec2(0.0, 1.0), glm::vec2(1.0, 1.0), glm::vec2(0.5, 0.0),
		glm::vec2(0.0, 1.0), glm::vec2(1.0, 1.0), glm::vec2(0.5, 0.0) }, indices);

	Model ground_model(ground_positions, { glm::vec2(0.0, 0.0), glm::vec2(50.0, 50.0), glm::vec2(0.0, 50.0),
		glm::vec2(0.0, 0.0), glm::vec2(50.0, 50.0), glm::vec2(50.0, 0.0) }, ground_indices);

	Mesh mesh1(model1, "res/textures/tex1.jpg");
	Mesh mesh2(model2, "res/textures/tex2.jpg");
	Mesh ground_mesh(ground_model, "res/textures/ground.jpg");

	//Mesh* skybox = getSkyBox();

	Transform transform1;
	Transform transform2;
	Transform ground_transform;
	Transform skybox_transform;
	skybox_transform.getPos().y = 20;

	Camera camera(glm::vec3(0.0f, 1.0f, 5.0f), 70.0f, DISPLAY_WIDTH / (float)DISPLAY_HEIGHT, 0.1f, 10000.0f);

	Uint32 curr_ticks = SDL_GetTicks();
	Uint32 prev_ticks = curr_ticks;
	float speed_multiplier = 0.001f;
	FrameCounter frameCounter;

	SDL_Event event;
	while (true)
	{
		if (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT || (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE))
				break;
			camera.adjust(event, window);
		}

		camera.move();

		transform1.getPos().x = 2 * cosf(2 * speed_multiplier * curr_ticks);
		transform1.getPos().y = 2;
		transform1.getPos().z = 2 * sinf(2 * speed_multiplier * curr_ticks);

		transform1.getRot().x = 2 * speed_multiplier * curr_ticks;
		//transform1.getRot().y = 2 * speed_multiplier * curr_ticks;
		//transform1.getRot().z = 2 * speed_multiplier * curr_ticks;
		//transform1.setScale(1.0f * glm::vec3(1.0f, 1.0f, 1.0f));

		transform2.getPos().y = 1 + sinf(2 * speed_multiplier * curr_ticks);
		transform2.getPos().x = 2;
		display.clearColor(0.05f, 0.1f, 0.4f, 1.0f);
		//display.clearColor(1.0f, 1.0f, 1.0f, 1.0f);

		shader.update(transform1, camera);
		mesh1.draw();

		shader.update(transform2, camera);
		mesh2.draw();

		shader.update(ground_transform, camera);
		ground_mesh.draw();

		//shader.update(skybox_transform, camera);
		//skybox->draw();

		display.swapBuffers();

		curr_ticks = SDL_GetTicks();
		//if (curr_ticks - prev_ticks > 2000)
		//{
		//	frameCounter.showFramerate(curr_ticks - prev_ticks);
		//	prev_ticks = curr_ticks;
		//}
		frameCounter++;
	}
	//delete skybox;
	SDL_Quit();
	return 0;
}
