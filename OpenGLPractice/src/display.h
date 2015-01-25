#ifndef DISPLAY_H
#define DISPLAY_H
#include <string>
#include <iostream>
#include <glew.h>
#include <SDL.h>

class Display {
public:
    Display(const std::string& title, int width, int height):
        m_title(title),
        m_width(width),
        m_height(height) {}

    void init();
    SDL_Window* createWindow();
    SDL_GLContext createContext();
    void clearColor(float r, float g, float b, float a);
    void swapBuffers();
    virtual ~Display();
protected:
private:
    std::string m_title;
    int m_width;
    int m_height;

    SDL_Window* m_window;
    SDL_GLContext m_context;
};

#endif // DISPLAY_H
