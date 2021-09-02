#include <iostream>
#include <thread>
#include "GameManagers/WallManager.h"
#include "GameManagers/BulletManager.h"
#include "EventHandler.h"
#include "Randomizer.h"

void fireBullets(std::unique_ptr<BulletManager> &bulletManager, Vector2D &pos);

int main() {
    auto renderer = std::make_shared<Renderer>();

    auto wallManager = std::make_shared<WallManager>(renderer);

    wallManager->createWalls(1000);

    auto bulletManager = std::make_unique<BulletManager>(wallManager, renderer);
    auto eventHandler = std::make_unique<EventHandler>();

    bool running = true;

    eventHandler->AddEvent(EventHandler::QUIT, [&]() {
        running = false;
    });

    eventHandler->AddEvent(EventHandler::ON_MOUSE_DOWN, [&]() {
        Vector2D pos = EventHandler::getMousePos() - Vector2D{renderer->getWindowWidth() / 2, renderer->getWindowHeight() / 2};
        fireBullets(bulletManager, pos);
    });

    while (running) {
        renderer->clearScreen();
        eventHandler->HandleEvents();

        bulletManager->Update(SDL_GetTicks());
        renderer->update();
    }
    return 0;
}

void fireBullets(std::unique_ptr<BulletManager> &bulletManager, Vector2D &pos) {
    std::thread([=,&bulletManager]() {
        for (int i = 0; i < 1; i++) {
            Vector2D dir = {Randomizer::RandomBetweenTwoFloat(-2, 1), Randomizer::RandomBetweenTwoFloat(-2, 1)};
            auto speed = Randomizer::RandomBetweenTwoFloat(1, 3);
            auto time1 = (float) SDL_GetTicks();

            bulletManager->Fire(pos,
                                dir,
                                speed,
                                time1,
                                10000);
        }
    }).detach();
}
