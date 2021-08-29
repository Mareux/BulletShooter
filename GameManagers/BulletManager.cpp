//
// Created by Mariia Nosko on 27.08.2021.
//

#include "BulletManager.h"

void BulletManager::Update(float time) {
    if ((time - prevTime) >= FRAME_CONTROL) {

        bulletList.remove_if([=](Bullet &bullet) {
            return bullet.isDead(time);
        });

        auto wallList = m_wallManager->getWallList();
        for (auto &bullet: bulletList) {
            bullet.Move();
            for (auto &wall : wallList) {
                bullet.collideWithWall(wall);
            }
            bullet.Draw(*m_renderer);
        }
        m_wallManager->deleteDeadWalls();
        m_wallManager->Update();
    }
}

void BulletManager::Fire(Vector2D pos, Vector2D dir, float speed, float time, float life_time) {
    bulletList.emplace_back(pos, dir, speed, time, life_time);
}

BulletManager::BulletManager(const std::shared_ptr<WallManager> &wallManager, const std::shared_ptr<Renderer> &renderer)
        : m_wallManager(wallManager), m_renderer(renderer), prevTime(0) {

}

BulletManager::BulletManager() {

}


