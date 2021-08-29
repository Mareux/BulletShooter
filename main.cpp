#include <iostream>
#include "GameManagers/WallManager.h"
#include "GameManagers/BulletManager.h"
#include "EventHandler.h"


int main() {
    auto wallManager = std::make_shared<WallManager>();
    auto renderer = std::make_shared<Renderer>();

    auto bulletManager = std::make_unique<BulletManager>(wallManager, renderer);
    auto eventHandler = std::make_unique<EventHandler>();

    bool running = true;

    eventHandler->AddEvent(EventHandler::QUIT, [&](){
        running = false;
    });
    eventHandler->AddEvent(EventHandler::ON_MOUSE_DOWN, [&](){
        bulletManager->Fire(EventHandler::getMousePos(), {0, 1}, 0.1f, SDL_GetTicks(), 100);
    });

    renderer->init();
    while (running){
        renderer->clearScreen();
        eventHandler->HandleEvents();
        bulletManager->Update(SDL_GetTicks());
        renderer->update();
    }
    renderer->deinit();
    return 0;
}
