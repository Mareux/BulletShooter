//
// Created by Mariia Nosko on 29.08.2021.
//

#include "EventHandler.h"

void EventHandler::AddEvent(EventHandler::Event event, const std::function<void()>& callback) {
    eventMap.emplace(event, callback);
}

void EventHandler::HandleEvents() {
    SDL_Event e;
    while(SDL_PollEvent(&e)) {
        for(auto &event : eventMap){
            if (e.type == event.first)
                event.second();
        }
    }
}

Vector2D EventHandler::getMousePos() {
    int x, y;
    SDL_GetMouseState(&x, &y);

    return {(float)x, (float)y};
}
