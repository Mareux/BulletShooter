//
// Created by Mariia Nosko on 07.09.2021.
//

#ifndef BULLETSHOOTER_THEGAME_H
#define BULLETSHOOTER_THEGAME_H


#include <memory>
#include "Renderer.h"
#include "GameManagers/WallManager.h"
#include "Grid.h"
#include "GameManagers/BulletManager.h"
#include "EventHandler.h"
#include <thread>

class TheGame {
public:

    TheGame(int wallsNum, int bulletNum);
    ~TheGame() = default;
    void RunTheGame();

private:
    void FireBullets(std::unique_ptr<BulletManager> &bulletManager, Vector2D &pos);

    std::shared_ptr<Renderer> renderer;
    std::shared_ptr<WallManager> wallManager;
    std::shared_ptr<Grid> grid;
    std::unique_ptr<BulletManager> bulletManager;
    std::unique_ptr<EventHandler> eventHandler;

    int bulletNum;
    bool running;
};


#endif //BULLETSHOOTER_THEGAME_H
