//
// Created by Mariia Nosko on 27.08.2021.
//

#include <iostream>
#include <utility>
#include "BulletManager.h"
#include "../thread_pool.h"

thread_pool pool;

void BulletManager::Update(float time) {
    std::lock_guard<std::mutex> lockGuard(bulletMutex);

    m_renderer->drawFps(1000 / (time - prevTime));

    prevTime = time;
    bulletList.remove_if([=](Bullet &bullet) {
        return bullet.isDead(time);
    });

    for (auto &bullet: bulletList) {
        pool.push_task([&]() {
            auto isHit = m_grid->bulletInSectorCollided(bullet.getPosition(),
                                                        bullet.getPosition() +
                                                        bullet.getDirection() * bullet.getSpeed());
            bullet.collideWithWall(isHit);
            bullet.Move();
        });
    }

    pool.wait_for_tasks();

    for (auto &bullet: bulletList) {
        bullet.collideWithWindowBorders(m_renderer->getWindowWidth(), m_renderer->getWindowHeight());
        bullet.Draw(*m_renderer);
    }

}

void BulletManager::Fire(Vector2D pos, Vector2D dir, float speed, float time, float life_time) {
    std::lock_guard<std::mutex> lockGuard(bulletMutex);
    bulletList.emplace_back(pos, dir, speed, time, life_time);
}

BulletManager::BulletManager(std::shared_ptr<Grid> grid, std::shared_ptr<Renderer> renderer)
        : m_grid(std::move(grid)), m_renderer(std::move(renderer)), prevTime(0) {

}



