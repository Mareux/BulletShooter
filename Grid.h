//
// Created by Mariia Nosko on 02.09.2021.
//

#ifndef BULLETSHOOTER_GRID_H
#define BULLETSHOOTER_GRID_H


#include <vector>
#include <list>
#include <optional>
#include "GameObjects/Wall.h"

class Grid {
public:

    Grid(int x, int y, int canvasWidth, int canvasHeight);
    void LocateWallsInGrid(std::list<Wall> &walls);
    bool bulletInSectorCollided(Vector2D point1, Vector2D point2);

private:
    int gridSizeX;
    int gridSizeY;
    int canvasWidth;
    int canvasHeight;
    int sectorSizeX;
    int sectorSizeY;

    std::vector<std::vector<std::list<Wall>>> wallGrid;
};


#endif //BULLETSHOOTER_GRID_H
