//
// Created by Mariia Nosko on 06.09.2021.
//

#ifndef BULLETSHOOTER_SECTOR_H
#define BULLETSHOOTER_SECTOR_H


#include <set>
#include "GameObjects/Wall.h"

class Sector {
public:

    Sector(int x, int y, int w, int h);
    Vector2D getPoint1();
    Vector2D getPoint2();
    std::set<std::shared_ptr<Wall>>& getWallList();

    bool isColliding(Vector2D point1, Vector2D point2);

private:
    int x;
    int y;
    int h;
    int w;

    Vector2D point1;
    Vector2D point2;

    std::set<std::shared_ptr<Wall>> wallList;
};


#endif //BULLETSHOOTER_SECTOR_H
