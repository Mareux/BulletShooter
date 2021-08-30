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

bool Wall::IsHit(Vector2D pos) {
    float dist1 = (point1 - pos).vectorLength();
    float dist2 = (point2 - pos).vectorLength();

    float lineLength = (point1 - point2).vectorLength();

    float buffer = 0.1f;

    if (dist1 + dist2 >= lineLength - buffer
        && dist1 + dist2 <= lineLength + buffer) {
        isDead = true;
        return true;
    }
    return false;
}

bool Wall::getDeathState() const {
    return isDead;
}
