//
// Created by Mariia Nosko on 27.08.2021.
//

#include "BulletManager.h"

void BulletManager::Update(float time) {
    for (auto &bullet : bulletList){
        bullet.pos = bullet.pos + (bullet.dir.normalize() * bullet.speed);
    }
}

void BulletManager::Fire(Vector2D pos, Vector2D dir, float speed, float time, float life_time) {
    bulletList.push_back({pos, dir, speed, time, life_time});
}

BulletManager::BulletManager(std::shared_ptr<WallManager> wallManager) : m_wallManager(wallManager) {

}


