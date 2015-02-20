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

	

	std::vector<GLuint> indices;
	for (GLuint i = 0; i < positions1.size(); i++) indices.push_back(i);

	Model model1(positions1, { glm::vec2(0.0, 1.0), glm::vec2(1.0, 1.0), glm::vec2(0.5, 0.0),
		glm::vec2(0.0, 1.0), glm::vec2(1.0, 1.0), glm::vec2(0.5, 0.0),
		glm::vec2(0.0, 1.0), glm::vec2(1.0, 1.0), glm::vec2(0.5, 0.0),
		glm::vec2(0.0, 1.0), glm::vec2(1.0, 1.0), glm::vec2(0.5, 0.0) }, indices);
	// -----------------------------------------------------------------------------------------------------
	// -----------------------------------------------------------------------------------------------------

	AssimpWrapper assimpWrapper;
	std::vector<Mesh*> plane_meshes = assimpWrapper.getMeshes("res/models/boeing_747/B-747.obj");
	Transform my_obj_transform;

	Mesh mesh1(model1, "res/textures/tex1.jpg");
	Mesh *skybox_mesh = getSkyBox();

	Transform transform1;
	Transform skybox_transform;
	skybox_transform.setScale(100.0f * glm::vec3(1, 1, 1));

	Camera camera(glm::vec3(0.0f, 1.0f, 5.0f), 70.0f, DISPLAY_WIDTH / (float)DISPLAY_HEIGHT, 0.1f, 1000.0f);
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

		shader.update(skybox_transform, camera);
		skybox_mesh->draw();

		shader.update(transform1, camera);
		mesh1.draw();

		shader.update(my_obj_transform, camera);
		for (Mesh* mesh : plane_meshes)
			mesh->draw();

		display.swapBuffers();
	}

	delete skybox_mesh;
	SDL_Quit();
	return 0;
}
