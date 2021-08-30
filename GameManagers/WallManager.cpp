//
// Created by Mariia Nosko on 28.08.2021.
//

#include "WallManager.h"
#include "../Randomizer.h"

void WallManager::createWalls(int wallsNum) {
    for (int i = 0; i < wallsNum; i++) {
        wallList.emplace_back(Vector2D(Randomizer::RandomBetweenTwoFloat(-1000, 1000),
                                       Randomizer::RandomBetweenTwoFloat(-1000, 1000)),
                              Vector2D(Randomizer::RandomBetweenTwoFloat(-1000, 1000),
                                       Randomizer::RandomBetweenTwoFloat(-1000, 1000)));//TODO:randomize
    }
}

std::list<Wall>& WallManager::getWallList() {
    return wallList;
}

void WallManager::deleteDeadWalls() {
    wallList.remove_if([=](Wall &wall) {
        return wall.getDeathState();
    });
}

void WallManager::Update() {
    for (auto &wall : wallList){
        wall.Draw(*m_renderer);
    }
}

WallManager::WallManager(std::shared_ptr<Renderer> renderer) : m_renderer(renderer){

}
