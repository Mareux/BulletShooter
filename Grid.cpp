//
// Created by Mariia Nosko on 02.09.2021.
//

#include "Grid.h"
#include "CollisionManager.h"

Grid::Grid(int x, int y, int canvasWidth, int canvasHeight) : gridSizeX(x), gridSizeY(y), canvasWidth(canvasWidth),
                                                              canvasHeight(canvasHeight) {
    sectorSizeX = canvasWidth / x;
    sectorSizeY = canvasHeight / y;

    std::vector<std::set<std::shared_ptr<Wall>>> innerVector(y);
    for (int i = 0; i < y; i++) {
        innerVector[i] = {};
    }

    for (int i = 0; i < x; i++) {
        wallGrid.push_back(innerVector);
    }

}

void Grid::LocateWallsInGrid(std::list<std::shared_ptr<Wall>> &walls) {
    for (auto &wall: walls) {
        locateLineInGrid(wall->getPoint1(), wall->getPoint2(), [&](int x, int y) {
            wallGrid[x][y].emplace(wall);
        });
    }
}

bool Grid::bulletInSectorCollided(Vector2D point1, Vector2D point2) {
    int state = false;

    locateLineInGrid(point1, point2, [&](int x, int y) {
        x = x < 0 ? 0 : x;
        y = y < 0 ? 0 : y;
        for (auto &wall: wallGrid[x][y]) {
            if (CollisionManager::LineLineCollision(wall->getPoint1(), wall->getPoint2(), point1, point2)) {
                wall->setDeathState(true);
                state = true;
                return;
            }
        }
    });

    return state;
}

void Grid::DeleteWallsInGrid(std::list<std::shared_ptr<Wall>> &walls) {
    for (auto &wall: walls) {
        if (wall->getDeathState()) {
            locateLineInGrid(wall->getPoint1(), wall->getPoint2(), [&](int x, int y) {
                wallGrid[x][y].erase(wall);
            });
        }
    }
}

void Grid::locateLineInGrid(Vector2D point1, Vector2D point2, const std::function<void(int, int)> &innerFunc) {

    const int x1 = point1.getX() / sectorSizeX > gridSizeX - 1 ? gridSizeX - 1 : point1.getX() /
                                                                                 sectorSizeX;
    const int x2 = point2.getX() / sectorSizeX > gridSizeX - 1 ? gridSizeX - 1 : point2.getX() /
                                                                                 sectorSizeX;
    const int y1 = point1.getY() / sectorSizeY > gridSizeY - 1 ? gridSizeY - 1 : point1.getY() /
                                                                                 sectorSizeY;
    const int y2 = point2.getY() / sectorSizeY > gridSizeY - 1 ? gridSizeY - 1 : point2.getY() /
                                                                                 sectorSizeY;

    if (x1 == x2 && y1 == y2 && gridSizeX <= 2 && gridSizeY <=2) {
        innerFunc(x1, y1);
        return;
    }

    // This part is not working correctly for some lines, but I want it to stay to improve further

    Vector2D diff = point1 - point2;
    Vector2D dir = {float(diff.getX() < 0 ? diff.getX() == 0 ? 0 : -1 : 1),
                    float(diff.getY() < 0 ? diff.getY() == 0 ? 0 : -1 : 1)};

    int lenX = abs(x1 - x2);
    int lenY = abs(y1 - y2);

    float len = lenY > lenX ? lenY : lenX;

    innerFunc(x1, y1);
    innerFunc(x2, y2);

    int firstX = dir.getX() < 0 && x1 < x2 || dir.getX() > 0 && x1 > x2 ? x2 : x1;
    int firstY = dir.getY() < 0 && y1 < y2 || dir.getY() > 0 && y1 > y2 ? y2 : y1;


    for (; len > 0; len--) {
        if (firstX + dir.getX() < gridSizeX && firstX + dir.getX() >= 0 && CollisionManager::LineRectCollision(point1, point2,
                                                                                   {(firstX + dir.getX()) * sectorSizeX,
                                                                                    (float) firstY * sectorSizeY},
                                                                                   {(firstX + dir.getX()) *
                                                                                    sectorSizeX + sectorSizeX,
                                                                                    (float) firstY * sectorSizeY +
                                                                                    sectorSizeY})) {
            firstX += dir.getX();
            innerFunc(firstX, firstY);
        } if (firstY + dir.getY() < gridSizeY && firstY + dir.getY() >= 0  && CollisionManager::LineRectCollision(point1, point2,
                                                                                          {(float) firstX * sectorSizeX,
                                                                                           (float) (firstY +
                                                                                                    dir.getY()) *
                                                                                           sectorSizeY},
                                                                                          {(float) firstX *
                                                                                           sectorSizeX + sectorSizeX,
                                                                                           (float) (firstY +
                                                                                                    dir.getY()) *
                                                                                           sectorSizeY +
                                                                                           sectorSizeY})) {
            firstY += dir.getY();
            innerFunc(firstX, firstY);
        } if (firstX + dir.getX() < gridSizeX && firstY + dir.getY() < gridSizeY &&
                    firstX + dir.getX() >= 0 && firstY + dir.getY() >= 0 &&
                   CollisionManager::LineRectCollision(point1, point2,
                                                       {(float) (firstX + dir.getX()) * sectorSizeX,
                                                        (float) (firstY + dir.getY()) * sectorSizeY},
                                                       {(float) (firstX + dir.getX()) * sectorSizeX +
                                                        sectorSizeX,
                                                        (float) (firstY + dir.getY()) * sectorSizeY +
                                                        sectorSizeY})) {
            firstX += dir.getX();
            firstY += dir.getY();
            innerFunc(firstX, firstY);
        }
    }
}

