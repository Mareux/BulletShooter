#include <iostream>
#include "GameManagers/WallManager.h"
#include "GameManagers/BulletManager.h"
#include "EventHandler.h"
#include "Randomizer.h"

int main() {
    auto renderer = std::make_shared<Renderer>();
    auto wallManager = std::make_shared<WallManager>(renderer);

    wallManager->createWalls(20);

    auto bulletManager = std::make_unique<BulletManager>(wallManager, renderer);
    auto eventHandler = std::make_unique<EventHandler>();

    bool running = true;

    eventHandler->AddEvent(EventHandler::QUIT, [&](){
        running = false;
    });
    eventHandler->AddEvent(EventHandler::ON_MOUSE_DOWN, [&](){
        bulletManager->Fire(EventHandler::getMousePos(),
                            { Randomizer::RandomBetweenTwoFloat(-2,1), Randomizer::RandomBetweenTwoFloat(-2, 1)},
                            Randomizer::RandomBetweenTwoFloat(0, 3),
                            (float)SDL_GetTicks(),
                            100);
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
