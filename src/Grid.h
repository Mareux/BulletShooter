//
// Created by Mariia Nosko on 02.09.2021.
//

#ifndef BULLETSHOOTER_GRID_H
#define BULLETSHOOTER_GRID_H


#include <vector>
#include <list>
#include <optional>
#include <set>
#include "GameObjects/Wall.h"

class Grid {
public:

    Grid(int x, int y, int canvasWidth, int canvasHeight);
    void LocateWallsInGrid(std::list<std::shared_ptr<Wall>> &walls);
    void DeleteWallsInGrid(std::list<std::shared_ptr<Wall>> &walls);
    bool bulletInSectorCollided(Vector2D point1, Vector2D point2);


private:

    void locateLineInGrid(Vector2D point1, Vector2D point2, const std::function<void(int, int)> &innerFunc);
    Vector2D getPointSector(Vector2D point) const;

    int gridSizeX;
    int gridSizeY;
    int canvasWidth;
    int canvasHeight;
    int sectorSizeX;
    int sectorSizeY;

    std::vector<std::vector<std::set<std::shared_ptr<Wall>>>> wallGrid;
};


#endif //BULLETSHOOTER_GRID_H
