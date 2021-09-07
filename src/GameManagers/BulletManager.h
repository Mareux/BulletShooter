//
// Created by Mariia Nosko on 27.08.2021.
//

#ifndef BULLETSHOOTER_BULLETMANAGER_H
#define BULLETSHOOTER_BULLETMANAGER_H

#include <list>
#include <mutex>
#include "../Vector2D.h"
#include "WallManager.h"
#include "../GameObjects/Bullet.h"
#include "../Grid.h"

class BulletManager {
public:

    BulletManager(std::shared_ptr<Grid> grid, std::shared_ptr<Renderer> renderer);

    void Update(float time);

    void Fire(Vector2D pos, Vector2D dir, float speed, float time, float life_time);

private:

    std::mutex bulletMutex;
    std::list<Bullet> bulletList;

    std::shared_ptr<Grid> grid;
    std::shared_ptr<Renderer> renderer;

    float prevTime;
};


#endif //BULLETSHOOTER_BULLETMANAGER_H
