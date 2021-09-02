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

bool Wall::IsHit(Vector2D pos1, Vector2D pos2) {
    float uA = ((pos2.getX()-pos1.getX())*(point1.getY()-pos1.getY())
                    - (pos2.getY()-pos1.getY())*(point1.getX()-pos1.getX()))
                    / ((pos2.getY()-pos1.getY())*(point2.getX()-point1.getX())
                    - (pos2.getX()-pos1.getX())*(point2.getY()-point1.getY()));
    float uB = ((point2.getX()-point1.getX())*(point1.getY()-pos1.getY())
                    - (point2.getY()-point1.getY())*(point1.getX()-pos1.getX()))
                    / ((pos2.getY()-pos1.getY())*(point2.getX()-point1.getX())
                    - (pos2.getX()-pos1.getX())*(point2.getY()-point1.getY()));

    // if uA and uB are between 0-1, lines are colliding
    if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1) {

        // optionally, draw a circle where the lines meet
        float intersectionX = point1.getX() + (uA * (point2.getX()-point1.getX()));
        float intersectionY = point1.getY() + (uA * (point2.getY()-point1.getY()));
        isDead = true;
        return true;
    }
    return false;
}

bool Wall::getDeathState() const {
    return isDead;
}
