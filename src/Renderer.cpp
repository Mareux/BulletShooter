//
// Created by Mariia Nosko on 27.08.2021.
//

#include <string>
#include "Renderer.h"

void Renderer::Update() {
    SDL_RenderPresent(renderer);
}

void Renderer::DrawLine(Vector2D vec1, Vector2D vec2) {
    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
    SDL_RenderDrawLineF(renderer,
                        vec1.GetX(),
                        vec1.GetY(),
                        vec2.GetX(),
                        vec2.GetY());
}

void Renderer::DrawPoint(Vector2D vec1) {
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_FRect rect = {vec1.GetX(), vec1.GetY(), 2, 2};
    SDL_RenderDrawRectF(renderer, &rect);

}

void Renderer::ClearScreen() {
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);
}

float Renderer::GetWindowWidth() const {
    return windowWidth;
}

float Renderer::GetWindowHeight() const {
    return windowHeight;
}

Renderer::Renderer() {
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();

    font = TTF_OpenFont("assets/ComicSans.TTF", 64);

    SDL_GetDesktopDisplayMode(0, &displayMode);
    windowWidth = 1920;
    windowHeight = 1080;

    window = SDL_CreateWindow("Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, (int) windowWidth,
                              (int) windowHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (!window) {
        return;
    }
    SDL_SetWindowBordered(window, SDL_TRUE);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

Renderer::~Renderer() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();
}

void Renderer::DrawFps(int fps) {
    std::string str = "FPS: " + std::to_string(fps);

    SDL_Color color = {0, 0, 0};
    SDL_Surface *surface = TTF_RenderText_Solid(font, str.c_str(), color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect rect = {0, 0, 50, 30};
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}
