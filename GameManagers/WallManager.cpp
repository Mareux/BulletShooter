//
// Created by Mariia Nosko on 28.08.2021.
//

#include "WallManager.h"

void WallManager::createWalls(int wallsNum) {
    for (int i = 0; i < wallsNum; i++) {
        wallList.emplace_back(Vector2D(i + 10, i + 10), Vector2D(i + 20, i + 20));//TODO:randomize
    }
}

std::list<Wall> WallManager::getWallList() {
    return wallList;
}

void WallManager::deleteDeadWalls() {
    wallList.remove_if([=](Wall &wall) {
        return wall.getDeathState();
    });
}
