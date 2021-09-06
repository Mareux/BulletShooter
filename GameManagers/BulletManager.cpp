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

    for (auto &bullet: bulletList) {
        bullet.collideWithWall(m_grid->bulletInSectorCollided(bullet.getPosition(), bullet.getPosition() + bullet.getDirection() * bullet.getSpeed()));
        bullet.Move();
        bullet.collideWithWindowBorders(m_renderer->getWindowWidth(), m_renderer->getWindowHeight());
        bullet.Draw(*m_renderer);
    }

    bulletMutex.unlock();
}

void BulletManager::Fire(Vector2D pos, Vector2D dir, float speed, float time, float life_time) {
    bulletMutex.lock();
    bulletList.emplace_back(pos, dir, speed, time, life_time);
    bulletMutex.unlock();
}

BulletManager::BulletManager(const std::shared_ptr<Grid> &grid, const std::shared_ptr<Renderer> &renderer)
        : m_grid(grid), m_renderer(renderer), prevTime(0) {

}

BulletManager::BulletManager() {

}


