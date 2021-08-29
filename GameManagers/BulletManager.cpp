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
        }
        m_wallManager->deleteDeadWalls();
    }
}

void BulletManager::Fire(Vector2D pos, Vector2D dir, float speed, float time, float life_time) {
    bulletList.emplace_back(pos, dir, speed, time, life_time);
}

BulletManager::BulletManager(std::shared_ptr<WallManager> wallManager) : m_wallManager(wallManager), prevTime(0) {

}


