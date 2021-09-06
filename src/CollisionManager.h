//
// Created by Mariia Nosko on 04.09.2021.
//

#ifndef BULLETSHOOTER_COLLISIONMANAGER_H
#define BULLETSHOOTER_COLLISIONMANAGER_H


#include "Vector2D.h"

class CollisionManager {
public:

    static bool LineLineCollision(Vector2D point1, Vector2D point2, Vector2D point3, Vector2D point4);
    static bool LineRectCollision(Vector2D point1, Vector2D point2, Vector2D point3, Vector2D point4);
};


#endif //BULLETSHOOTER_COLLISIONMANAGER_H
