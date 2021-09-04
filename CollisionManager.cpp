//
// Created by Mariia Nosko on 04.09.2021.
//

#include "CollisionManager.h"

bool CollisionManager::LineLineCollision(Vector2D point1, Vector2D point2, Vector2D point3, Vector2D point4) {
    float uA = ((point4.getX()-point3.getX())*(point1.getY()-point3.getY())
                - (point4.getY()-point3.getY())*(point1.getX()-point3.getX()))
               / ((point4.getY()-point3.getY())*(point2.getX()-point1.getX())
                  - (point4.getX()-point3.getX())*(point2.getY()-point1.getY()));
    float uB = ((point2.getX()-point1.getX())*(point1.getY()-point3.getY())
                - (point2.getY()-point1.getY())*(point1.getX()-point3.getX()))
               / ((point4.getY()-point3.getY())*(point2.getX()-point1.getX())
                  - (point4.getX()-point3.getX())*(point2.getY()-point1.getY()));

    // if uA and uB are between 0-1, lines are colliding
    if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1) {
        return true;
    }

    return false;
}

bool CollisionManager::LineRectCollision(Vector2D point1, Vector2D point2, Vector2D point3, Vector2D point4) {
    bool left = LineLineCollision(point1, point2, point3, {point3.getX(), point4.getY()});
    bool right = LineLineCollision(point1, point2, {point4.getX(), point3.getY()}, point4);
    bool top = LineLineCollision(point1, point2, point3, {point4.getX(), point3.getY()});
    bool bottom = LineLineCollision(point1, point2, {point3.getX(), point4.getY()}, point4);

    if (left || right || top || bottom)
        return true;

    return false;
}
