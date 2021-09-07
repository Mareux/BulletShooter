//
// Created by Mariia Nosko on 07.09.2021.
//

#include "TheGame.h"
#include "Randomizer.h"

TheGame::TheGame(int wallsNum, int bulletNum) : bulletNum(bulletNum), running(true) {
    renderer = std::make_shared<Renderer>();

    wallManager = std::make_shared<WallManager>(renderer);
    grid = std::make_shared<Grid>(20, 20, renderer->GetWindowWidth(), renderer->GetWindowHeight());

    wallManager->CreateWalls(wallsNum);
    grid->LocateWallsInGrid(wallManager->GetWallList());

    bulletManager = std::make_unique<BulletManager>(grid, renderer);
    eventHandler = std::make_unique<EventHandler>();

    auto handler = [this]() {
        running = false;
    };

    eventHandler->AddEvent(EventHandler::QUIT, handler);
    eventHandler->AddEvent(EventHandler::QUIT_ESC, handler);
    eventHandler->AddEvent(EventHandler::ON_MOUSE_DOWN, [&]() {
        Vector2D pos = EventHandler::GetMousePos();
        FireBullets(bulletManager, pos);
    });
}

void TheGame::FireBullets(std::unique_ptr<BulletManager> &bulletManager, Vector2D &pos) {
    std::thread([=, &bulletManager]() {
        for (int i = 0; i < bulletNum; i++) {
            Vector2D dir = {Randomizer::RandomBetweenTwoFloat(-2, 1), Randomizer::RandomBetweenTwoFloat(-2, 1)};
            auto speed = Randomizer::RandomBetweenTwoFloat(1, 3);
            auto time1 = (float) SDL_GetTicks();

            bulletManager->Fire(pos,
                                dir.Normalize(),
                                speed,
                                time1,
                                10000);
        }
    }).detach();
}

void TheGame::RunTheGame() {
    while (running) {
        renderer->ClearScreen();
        eventHandler->HandleEvents();
        bulletManager->Update(SDL_GetTicks());
        grid->RemoveKilledWalls(wallManager->GetWallList());
        wallManager->Update();
        renderer->Update();
    }
}

