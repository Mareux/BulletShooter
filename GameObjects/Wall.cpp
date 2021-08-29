//
// Created by Mariia Nosko on 28.08.2021.
//

#include <iostream>
#include "Wall.h"

Wall::~Wall() {

}

void Wall::Draw(Renderer &renderer) {
    renderer.drawLine(leftSide, rightSide);
}

Wall::Wall(Vector2D point1, Vector2D point2) : leftSide(point1), rightSide(point2), isDead(false){
    std::cout << "Wall with point1(" << point1.getX() << ", " << point1.getY() << ") and point2("
        << point2.getX() << ", " << point2.getY() << ") created\n";
}

bool Wall::IsHit(Vector2D pos) {
    float dist1 = (leftSide - pos).vectorLength();
    float dist2 = (rightSide - pos).vectorLength();

    float lineLength = (leftSide - rightSide).vectorLength();

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
