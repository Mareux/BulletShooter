//
// Created by Mariia Nosko on 27.08.2021.
//

#include <iostream>
#include <utility>
#include "BulletManager.h"
#include "../ThirdParty/thread_pool.h"

thread_pool collisions_pool;

void BulletManager::Update(float time) {
    std::lock_guard<std::mutex> lockGuard(bulletMutex);

    renderer->DrawFps(1000 / (time - prevTime));

    prevTime = time;
    bulletList.remove_if([=](Bullet &bullet) {
        return bullet.IsDead(time);
    });

    // Calculate collisions in parallel
    for (auto &bullet: bulletList) {
        collisions_pool.push_task([&]() {
            if (grid->CollidesWithWallInSector(bullet.GetPosition(),
                                               bullet.GetPosition() +
                                               bullet.GetDirection() * bullet.GetSpeed())) {
                bullet.CollideWithWall();
            }
        });
    }

    collisions_pool.wait_for_tasks();

    for (auto &bullet: bulletList) {
        bullet.Move();
        bullet.CollideWithWindowBorders(renderer->GetWindowWidth(), renderer->GetWindowHeight());
        bullet.Draw(*renderer);
    }
}

void BulletManager::Fire(Vector2D pos, Vector2D dir, float speed, float time, float life_time) {
    std::lock_guard<std::mutex> lockGuard(bulletMutex);
    bulletList.emplace_back(pos, dir, speed, time, life_time);
}

BulletManager::BulletManager(std::shared_ptr<Grid> grid, std::shared_ptr<Renderer> renderer)
        : grid(std::move(grid)), renderer(std::move(renderer)), prevTime(0) {

}



