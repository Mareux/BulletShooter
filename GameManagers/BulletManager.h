//
// Created by Mariia Nosko on 27.08.2021.
//

#ifndef BULLETSHOOTER_BULLETMANAGER_H
#define BULLETSHOOTER_BULLETMANAGER_H

#include <opencl-c-base.h>
#include <list>
#include "../Vector2D.h"
#include "WallManager.h"

class BulletManager {
public:
    BulletManager(std::shared_ptr<WallManager> wallManager);
    /*
     * void Update (float time), where time – global update time in seconds.
     * This method calculates bullet movement in given time, and in case of collision with the wall,
     * removes the wall from the list and bullet continues movement with its trajectory reflected.
     */
    void Update(float time);

    /*
     * void Fire (float2 pos, float2 dir, float speed, float time, float life_time),
     * where pos – starting point of the bullet on the plane (in meters),
     * dir – direction, speed – bullet speed (m/s),
     * time – when the bullet will be fired, life_time – time before bullet disappears.
     * This method adds bullet to manager for further updates.
     */
    void Fire(Vector2D pos, Vector2D dir, float speed, float time, float life_time);

private:
    struct Bullet {
        Vector2D pos;
        Vector2D dir;
        float speed;
        float time;
        float life_time;
    };

    std::list<Bullet> bulletList;

    std::shared_ptr<WallManager> m_wallManager;
};


#endif //BULLETSHOOTER_BULLETMANAGER_H
