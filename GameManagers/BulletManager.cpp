//
// Created by Mariia Nosko on 27.08.2021.
//

#include <iostream>
#include "BulletManager.h"

void BulletManager::Update(float time) {
    bulletMutex.lock();
    std::cout << 1000 / (time - prevTime) << std::endl;

    prevTime = time;
    bulletList.remove_if([=](Bullet &bullet) {
        return bullet.isDead(time);
    });

    auto &wallList = m_wallManager->getWallList();
    for (auto &bullet: bulletList) {
        for (auto &wall: wallList) {
            bullet.collideWithWall(wall);
        }
        bullet.Move();
        bullet.collideWithWindowBorders(m_renderer->getWindowWidth() / 2, m_renderer->getWindowHeight() / 2);
        // later refactor to check if already collided with wall to not change direction for second time, probably add collider manager
        bullet.Draw(*m_renderer);
    }
    m_wallManager->deleteDeadWalls();
    m_wallManager->Update();

    bulletMutex.unlock();
}

void BulletManager::Fire(Vector2D pos, Vector2D dir, float speed, float time, float life_time) {
    bulletMutex.lock();
    bulletList.emplace_back(pos, dir, speed, time, life_time);
    bulletMutex.unlock();
}

BulletManager::BulletManager(const std::shared_ptr<WallManager> &wallManager, const std::shared_ptr<Renderer> &renderer)
        : m_wallManager(wallManager), m_renderer(renderer), prevTime(0) {

}

BulletManager::BulletManager() {

}


