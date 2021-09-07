//
// Created by Mariia Nosko on 04.09.2021.
//

#include "CollisionManager.h"

bool CollisionManager::LineLineCollision(Vector2D point1, Vector2D point2, Vector2D point3, Vector2D point4) {
    float x1 = point1.GetX();
    float y1 = point1.GetY();
    float x2 = point2.GetX();
    float y2 = point2.GetY();
    float x3 = point3.GetX();
    float y3 = point3.GetY();
    float x4 = point4.GetX();
    float y4 = point4.GetY();

    float uA = ((x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3)) / ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));
    float uB = ((x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3)) / ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));

    // if uA and uB are between 0-1, lines are colliding
    if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1) {
        return true;
    }

    return false;
}

bool CollisionManager::LineRectCollision(Vector2D point1, Vector2D point2, Vector2D point3, Vector2D point4) {
    bool left = LineLineCollision(point1, point2, point3, {point3.GetX(), point4.GetY()});
    bool right = LineLineCollision(point1, point2, {point4.GetX(), point3.GetY()}, point4);
    bool top = LineLineCollision(point1, point2, point3, {point4.GetX(), point3.GetY()});
    bool bottom = LineLineCollision(point1, point2, {point3.GetX(), point4.GetY()}, point4);

    if (left || right || top || bottom)
        return true;

    return false;
}
