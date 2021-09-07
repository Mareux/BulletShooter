//
// Created by Mariia Nosko on 02.09.2021.
//

#ifndef BULLETSHOOTER_GRID_H
#define BULLETSHOOTER_GRID_H


#include <vector>
#include <functional>
#include <list>
#include <optional>
#include <set>
#include "GameObjects/Wall.h"

class Grid {
public:

    Grid(int x, int y, int canvasWidth, int canvasHeight);

    void LocateWallsInGrid(std::list<std::shared_ptr<Wall>> &walls);

    void RemoveKilledWalls(std::list<std::shared_ptr<Wall>> &walls);

    bool CollidesWithWallInSector(Vector2D point1, Vector2D point2);


private:

    void LocateLineInGrid(Vector2D point1, Vector2D point2, const std::function<void(int, int)> &innerFunc) const;

    static int SwapCoords(int c1, int c2, int dir);

    bool CheckSectorLineCollision(int x, int y, Vector2D point1, Vector2D point2) const;

    int GetGridCoord(float coord, float gridSize, float sectorSize) const;

    float gridSizeX;
    float gridSizeY;
    float sectorSizeX;
    float sectorSizeY;

    std::vector<std::vector<std::set<std::shared_ptr<Wall>>>> wallGrid;
};


#endif //BULLETSHOOTER_GRID_H
