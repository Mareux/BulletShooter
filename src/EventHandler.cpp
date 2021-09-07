//
// Created by Mariia Nosko on 29.08.2021.
//

#include "EventHandler.h"

void EventHandler::AddEvent(EventHandler::Event event, const std::function<void()> &callback) {
    eventMap.emplace(event, callback);
}

void EventHandler::HandleEvents() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        for (auto &event: eventMap) {
            if (e.type == event.first
                || e.key.keysym.scancode == (SDL_Scancode) event.first)
                event.second();
        }
    }
}

Vector2D EventHandler::GetMousePos() {
    int x, y;
    SDL_GetMouseState(&x, &y);

    return {(float) x, (float) y};
}
