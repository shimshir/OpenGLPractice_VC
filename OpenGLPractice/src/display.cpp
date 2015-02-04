#include "display.h"

void Display::init() {
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
}

SDL_Window* Display::createWindow() {
	m_window = SDL_CreateWindow(m_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
		m_width, m_height, SDL_WINDOW_OPENGL/* | SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_SHOWN*/);

    return m_window;
}

SDL_GLContext Display::createContext() {
    m_context = SDL_GL_CreateContext(m_window);
    SDL_GL_SetSwapInterval(0);

    glewExperimental = GL_TRUE;
    GLenum result = glewInit();

    if(result != GLEW_OK)
        std::cerr << "Glew failed to initialize!" << std::endl;

    std::cout << "GL Version: " << glGetString(GL_VERSION) << "\n";
    std::cout << "GL Vendor: " << glGetString(GL_VENDOR) << "\n" << std::endl;

    glEnable(GL_DEPTH_TEST);

	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
    //glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
    //glEnable(GL_MULTISAMPLE);
    

    return m_context;
}

void Display::clearColor(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Display::swapBuffers() {
    SDL_GL_SwapWindow(m_window);
}

Display::~Display() {
    SDL_GL_DeleteContext(m_context);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}
