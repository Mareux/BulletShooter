//
// Created by Mariia Nosko on 28.08.2021.
//

#include <iostream>
#include "Wall.h"

Wall::~Wall() {

}

void Wall::Draw(Renderer &renderer) {
    renderer.drawLine(point1, point2);
}

Wall::Wall(Vector2D point1, Vector2D point2) : point1(point1), point2(point2), isDead(false){
    std::cout << "Wall with point1(" << point1.getX() << ", " << point1.getY() << ") and point2("
        << point2.getX() << ", " << point2.getY() << ") created\n";
}

bool Wall::getDeathState() const {
    return isDead;
}

bool Wall::operator<(const Wall &wall) {
    return false;
}

Vector2D Wall::getPoint1() {
    return point1;
}

Vector2D Wall::getPoint2() {
    return point2;
}

void Wall::setDeathState(bool isHit) {
    isDead = isHit;
}
