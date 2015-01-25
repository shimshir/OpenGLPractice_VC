#include <iostream>
#include <vector>

#include "display.h"
#include "shader.h"
#include "model.h"
#include "mesh.h"
#include "texture.h"
#include "transform.h"
#include "util.h"

int main(int argc, char *argv[]) {
    Display display("OpenGL", 800, 600);
    display.init();
    display.createWindow();
    display.createContext();

    Shader shader;
    shader.addShaderFromFile(GL_VERTEX_SHADER, "res/shaders/vertexShader.glsl");
	shader.addShaderFromFile(GL_FRAGMENT_SHADER, "res/shaders/fragmentShader.glsl");
    shader.createAndCompile();
    shader.linkAndUse();

	// TODO: needs to be adjusted to work for multiple textures (similar to the Shader class)
	Texture texture("res/textures/paint.jpg");
	texture.bind();

    std::vector<glm::vec3> positions = {
										glm::vec3(-0.5f, -0.5f, 0.0f),
                                        glm::vec3(0.5f, -0.5f, 0.0f),
                                        glm::vec3(0.0f, 0.5f, 0.0f)
									   };

    std::vector<GLuint> indices = {0, 1, 2};

	Model model(positions, { glm::vec2(0.0, 1.0), glm::vec2(1.0, 1.0), glm::vec2(0.5, 0.0) }, indices);

    Mesh mesh(model);

	Transform transform;

    SDL_Event windowEvent;
	FrameCounter frameCounter;
	Uint32 prev_ticks = SDL_GetTicks();
	Uint32 curr_ticks = prev_ticks;
    while (true) {
        if (SDL_PollEvent(&windowEvent)) {
            if (windowEvent.type == SDL_QUIT || (windowEvent.type == SDL_KEYUP && windowEvent.key.keysym.sym == SDLK_ESCAPE))
                break;
        }
        display.clearColor(0.0, 0.1, 0.3, 1.0);

		transform.getPos().x = 0.5f * sinf(0.003f * curr_ticks);
		transform.getPos().y = 0.5f * cosf(0.003f * curr_ticks);

		transform.setScale((0.75f + 0.25f * sinf(0.003f * curr_ticks - (float)M_PI / 2)) * glm::vec3(1, 1, 1));

		transform.getRot().x = 0.003f * curr_ticks;
		transform.getRot().y = 0.003f * curr_ticks;
		transform.getRot().z = 0.003f * curr_ticks;

		shader.update(transform);

        mesh.draw();
        display.swapBuffers();

		curr_ticks = SDL_GetTicks();
		if (curr_ticks - prev_ticks > 2000)
		{
			frameCounter.showFramerate(curr_ticks - prev_ticks);
			prev_ticks = curr_ticks;
		}
		frameCounter++;
    }
	
    SDL_Quit();
    return 0;
}
