//
// Created by Mariia Nosko on 29.08.2021.
//

#ifndef BULLETSHOOTER_EVENTHANDLER_H
#define BULLETSHOOTER_EVENTHANDLER_H


#include <SDL_events.h>
#include "SDL2-2.0.16/include/SDL_scancode.h"
#include "Vector2D.h"
#include <functional>
#include <map>

class EventHandler {
public:

    enum Event {
        QUIT = SDL_SCANCODE_ESCAPE,
        ON_MOUSE_DOWN = SDL_MOUSEBUTTONDOWN
    };

    void AddEvent(Event event, const std::function<void()>& callback);
    void HandleEvents();
    static Vector2D getMousePos();

private:
    std::map<Event, std::function<void()>> eventMap;
};


#endif //BULLETSHOOTER_EVENTHANDLER_H
