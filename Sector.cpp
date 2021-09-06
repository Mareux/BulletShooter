//
// Created by Mariia Nosko on 06.09.2021.
//

#include "Sector.h"

Sector::Sector(int x, int y, int w, int h) : x(x), y(y), w(w), h(h), wallList({}) {
    point1 = {x * w, y * h};
    point2 = {x * w + w, y * h + h};
}

Vector2D Sector::getPoint1() {
    return point1;
}

Vector2D Sector::getPoint2() {
    return point2;
}

std::set<std::shared_ptr<Wall>> &Sector::getWallList() {
    return wallList;
}

bool Sector::isColliding(Vector2D point1, Vector2D point2) {
    return false;
}
