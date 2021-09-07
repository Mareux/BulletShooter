//
// Created by Mariia Nosko on 27.08.2021.
//

#ifndef BULLETSHOOTER_RENDERER_H
#define BULLETSHOOTER_RENDERER_H

#include <memory>
#include <SDL.h>
#include <SDL_ttf.h>

#undef main

#include "Vector2D.h"

class Renderer {
public:
    Renderer();

    ~Renderer();

    void Update();

    void ClearScreen();

    void DrawLine(Vector2D vec1, Vector2D vec2);

    void DrawFps(int fps);

    void DrawPoint(Vector2D vec1);

    float GetWindowWidth() const;

    float GetWindowHeight() const;

private:
    SDL_DisplayMode displayMode{};
    SDL_Window *window;
    SDL_Renderer *renderer;
    TTF_Font *font;
    float windowWidth;
    float windowHeight;
};


#endif //BULLETSHOOTER_RENDERER_H
