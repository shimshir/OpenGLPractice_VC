#include <iostream>
#include <vector>

#include "display.h"
#include "shader.h"
#include "model.h"
#include "mesh.h"
#include "texture.h"

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

    SDL_Event windowEvent;
    Uint32 lastTime = SDL_GetTicks();
    Uint32 frameNumber = 0;
    while (true) {
        if (SDL_PollEvent(&windowEvent)) {
            if (windowEvent.type == SDL_QUIT || (windowEvent.type == SDL_KEYUP && windowEvent.key.keysym.sym == SDLK_ESCAPE))
                break;
        }
        display.clearColor(0.0, 0.0, 0.0, 1.0);
        mesh.draw();
        display.swapBuffers();
        frameNumber++;
        if (frameNumber > 1000) {
            std::cout << 1000 * frameNumber / (SDL_GetTicks() - lastTime) << std::endl;
            lastTime = SDL_GetTicks();
            frameNumber = 0;
        }
    }
	
    SDL_Quit();
    return 0;
}
