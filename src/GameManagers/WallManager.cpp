//
// Created by Mariia Nosko on 28.08.2021.
//

#include "WallManager.h"

#include <utility>
#include "../Randomizer.h"

void WallManager::createWalls(int wallsNum) {
    float canvasWidth = m_renderer->getWindowWidth();
    float canvasHeight = m_renderer->getWindowHeight();

    for (int i = 0; i < wallsNum; i++) {
        int randomInt = std::rand() % 3 + 1;
        if (randomInt == 1) {
            float x = Randomizer::RandomBetweenTwoFloat(0, canvasWidth);
            float y1 = Randomizer::RandomBetweenTwoFloat(0, canvasHeight);
            float y2 = Randomizer::RandomBetweenTwoFloat(0, canvasHeight);

            wallList.emplace_back(std::make_shared<Wall>(Vector2D(x, y1), Vector2D(x, y2)));
        }
        else if (randomInt == 2) {
            float y = Randomizer::RandomBetweenTwoFloat(0, canvasHeight);
            float x1 = Randomizer::RandomBetweenTwoFloat(0, canvasWidth);
            float x2 = Randomizer::RandomBetweenTwoFloat(0, canvasWidth);

            wallList.emplace_back(std::make_shared<Wall>(Vector2D(x1, y), Vector2D(x2, y)));
        }
        else {
            float y1 = Randomizer::RandomBetweenTwoFloat(0, canvasHeight);
            float y2 = Randomizer::RandomBetweenTwoFloat(0, canvasHeight);
            float x1 = Randomizer::RandomBetweenTwoFloat(0, canvasWidth);
            float x2 = Randomizer::RandomBetweenTwoFloat(0, canvasWidth);

            wallList.emplace_back(std::make_shared<Wall>(Vector2D(x1, y1), Vector2D(x2, y2)));
        }
    }
}

std::list<std::shared_ptr<Wall>>& WallManager::getWallList() {
    return wallList;
}

void WallManager::deleteDeadWalls() {
    wallList.remove_if([=](std::shared_ptr<Wall> &wall) {
        return wall->getDeathState();
    });
}

void WallManager::Update() {
    deleteDeadWalls();
    for (auto &wall : wallList){
        wall->Draw(*m_renderer);
    }
}

WallManager::WallManager(std::shared_ptr<Renderer> renderer) : m_renderer(std::move(renderer)){

}
