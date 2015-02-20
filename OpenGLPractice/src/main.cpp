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
#include "assimp_wrapper.h"
// test
static const int DISPLAY_WIDTH = 800;
static const int DISPLAY_HEIGHT = 600;

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


	AssimpWrapper assimpWrapper;
	std::vector<Mesh*> plane_meshes = assimpWrapper.getMeshes("res/models/Airbus_330/A-330.obj");
	Transform my_obj_transform;
	Mesh *skybox_mesh = getSkyBox();

	Transform transform1;
	Transform skybox_transform;
	skybox_transform.setScale(500.0f * glm::vec3(1, 1, 1));

	Camera camera(glm::vec3(0.0f, 50.0f, 20.0f), 70.0f, DISPLAY_WIDTH / (float)DISPLAY_HEIGHT, 0.1f, 2000.0f);
	float speed_multiplier = 0.001f;
	SDL_Event event;
	while (true)
	{
		if (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT || (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE))
				break;
			camera.adjust(event, window);
		}

		camera.move();

		transform1.getPos().x = 2 * cosf(2 * speed_multiplier * SDL_GetTicks());
		transform1.getPos().y = 2 * sinf(2 * speed_multiplier * SDL_GetTicks());
		transform1.getRot().x = 2 * speed_multiplier * SDL_GetTicks();
		transform1.getRot().y = 2 * speed_multiplier * SDL_GetTicks();

		display.clearColor(0.0f, 0.1f, 0.35f, 1.0f);

		shader.update(skybox_transform, camera, 0);
		skybox_mesh->draw();

		my_obj_transform.setScale(glm::vec3(0.5, 0.5, 0.5));
		my_obj_transform.getPos().y = 50;
		glm::vec3 lightDirection;
		lightDirection.x = cosf(speed_multiplier * SDL_GetTicks());
		lightDirection.y = cosf(2 * speed_multiplier * SDL_GetTicks());
		lightDirection.z = sinf(speed_multiplier * SDL_GetTicks());

		shader.update(my_obj_transform, camera, 1, lightDirection);
		for (Mesh* mesh : plane_meshes)
			mesh->draw();

		display.swapBuffers();
	}

	delete skybox_mesh;
	SDL_Quit();
	return 0;
}
