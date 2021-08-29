//
// Created by Mariia Nosko on 27.08.2021.
//

#include "Renderer.h"

void Renderer::init() {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_GetDesktopDisplayMode(0, &displayMode);
    window = SDL_CreateWindow("Window", 0, 0, displayMode.w, displayMode.h, SDL_WINDOW_SHOWN);
    if (!window) {
        return;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

void Renderer::deinit() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Renderer::update() {
    SDL_RenderPresent(renderer);
}

void Renderer::drawLine(Vector2D vec1, Vector2D vec2) {
    SDL_SetRenderDrawColor( renderer, 0xFF, 0x00, 0x00, 0xFF );
    SDL_RenderDrawLineF(renderer, vec1.getX(), vec1.getY(), vec2.getX(), vec2.getY());
}

void Renderer::drawPoint(Vector2D vec1) {
    SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0xFF, 0xFF );
    SDL_RenderDrawPointF(renderer, vec1.getX(), vec1.getY());

}

void Renderer::clearScreen() {
    SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_RenderClear( renderer );
}

void Renderer::drawRect(Vector2D vec1, Vector2D vec2) {
    SDL_SetRenderDrawColor( renderer, 0x00, 0xFF, 0x00, 0xFF );
    //TODO: draw rect
}
