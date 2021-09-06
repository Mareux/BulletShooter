//
// Created by Mariia Nosko on 04.09.2021.
//

#include "CollisionManager.h"

bool CollisionManager::LineLineCollision(Vector2D point1, Vector2D point2, Vector2D point3, Vector2D point4) {
    float x1 = point1.getX();
    float y1 = point1.getY();
    float x2 = point2.getX();
    float y2 = point2.getY();
    float x3 = point3.getX();
    float y3 = point3.getY();
    float x4 = point4.getX();
    float y4 = point4.getY();

    float uA = ((x4-x3)*(y1-y3) - (y4-y3)*(x1-x3)) / ((y4-y3)*(x2-x1) - (x4-x3)*(y2-y1));
    float uB = ((x2-x1)*(y1-y3) - (y2-y1)*(x1-x3)) / ((y4-y3)*(x2-x1) - (x4-x3)*(y2-y1));

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
