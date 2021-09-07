//
// Created by Mariia Nosko on 28.08.2021.
//

#include <iostream>
#include "Wall.h"

Wall::~Wall() = default;

void Wall::Draw(Renderer &renderer) {
    renderer.DrawLine(point1, point2);
}

Wall::Wall(Vector2D point1, Vector2D point2) : point1(point1), point2(point2), isDead(false) {}

bool Wall::GetDeathState() const {
    return isDead;
}

Vector2D Wall::GetPoint1() {
    return point1;
}

Vector2D Wall::GetPoint2() {
    return point2;
}

void Wall::KillWall() {
    isDead = true;
}
