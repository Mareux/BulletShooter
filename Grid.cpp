//
// Created by Mariia Nosko on 02.09.2021.
//

#include "Grid.h"
#include "CollisionManager.h"

Grid::Grid(int x, int y, int canvasWidth, int canvasHeight) : gridSizeX(x), gridSizeY(y), canvasWidth(canvasWidth),
                                                              canvasHeight(canvasHeight) {
    sectorSizeX = canvasWidth / x;
    sectorSizeY = canvasHeight / y;

    std::vector<std::list<Wall>> innerVector(y);
    for (int i = 0; i < y; i++) {
        innerVector[i] = {};
    }

    for (int i = 0; i < x; i++) {
        wallGrid.push_back(innerVector);
    }

}

void Grid::LocateWallsInGrid(std::list<Wall> &walls) {
    for (auto &wall: walls) {
        const int x1 = wall.getPoint1().getX() / sectorSizeX > gridSizeX - 1 ? gridSizeX - 1 : wall.getPoint1().getX() /
                                                                                               sectorSizeX;
        const int x2 = wall.getPoint2().getX() / sectorSizeX > gridSizeX - 1 ? gridSizeX - 1 : wall.getPoint2().getX() /
                                                                                               sectorSizeX;
        const int y1 = wall.getPoint1().getY() / sectorSizeY > gridSizeY - 1 ? gridSizeY - 1 : wall.getPoint1().getY() /
                                                                                               sectorSizeY;
        const int y2 = wall.getPoint2().getY() / sectorSizeY > gridSizeY - 1 ? gridSizeY - 1 : wall.getPoint2().getY() /
                                                                                               sectorSizeY;

        if (x1 == x2) {
            int first = y1 < y2 ? y1 : y2;
            int last = y1 > y2 ? y1 : y2;
            for (; first < last; first++) {
                wallGrid[x1][first].push_back(wall);
            }
        } else if (y1 == y2) {
            int first = x1 < x2 ? x1 : x2;
            int last = x1 > x2 ? x1 : x2;
            for (; first < last; first++) {
                wallGrid[first][y1].push_back(wall);
            }
        } else {
            Vector2D diff = wall.getPoint1() - wall.getPoint2();
            Vector2D dir = {float(diff.getX() < 0 ? -1 : 1), float(diff.getY() < 0 ? -1 : 1)};

            wallGrid[x1][y1].push_back(wall);
            wallGrid[x2][y2].push_back(wall);

            int firstX = dir.getX() < 0 && x1 < x2 || dir.getX() > 0 && x1 > x2 ? x2 : x1;
            int firstY = dir.getY() < 0 && y1 < y2 || dir.getY() > 0 && y1 > y2 ? y2 : y1;

            int lastX = firstX == x1 ? x2 : x1;
            int lastY = firstY == y1 ? y2 : y1;
            for (; firstX != lastX && firstY != lastY;) {
                if (CollisionManager::LineRectCollision(wall.getPoint1(), wall.getPoint2(),
                                                        {(firstX + dir.getX()) * sectorSizeX,
                                                         (float) firstY * sectorSizeY},
                                                        {(firstX + dir.getX()) * sectorSizeX + sectorSizeX - 1,
                                                         (float) firstY * sectorSizeY + sectorSizeY - 1})) {
                    firstX += dir.getX();
                    wallGrid[firstX][firstY].push_back(wall);
                } else if (CollisionManager::LineRectCollision(wall.getPoint1(), wall.getPoint2(),
                                                               {(float) firstX * sectorSizeX,
                                                                (float) (firstY + dir.getY()) * sectorSizeY},
                                                               {(float) firstX * sectorSizeX + sectorSizeX - 1,
                                                                (float) (firstY + dir.getY()) * sectorSizeY +
                                                                sectorSizeY - 1})) {
                    firstY += dir.getY();
                    wallGrid[firstX][firstY].push_back(wall);
                } else if (CollisionManager::LineRectCollision(wall.getPoint1(), wall.getPoint2(),
                                                               {(float) (firstX + dir.getX()) * sectorSizeX,
                                                                (float) (firstY + dir.getY()) * sectorSizeY},
                                                               {(float) (firstX + dir.getX()) * sectorSizeX +
                                                                sectorSizeX - 1,
                                                                (float) (firstY + dir.getY()) * sectorSizeY +
                                                                sectorSizeY - 1})) {
                    firstX += dir.getX();
                    firstY += dir.getY();
                    wallGrid[firstX][firstY].push_back(wall);
                }
            }
        }
    }

}

bool Grid::bulletInSectorCollided(Vector2D point1, Vector2D point2) {
    const int x1 = point1.getX() / sectorSizeX > gridSizeX - 1 ? gridSizeX - 1 : point1.getX() / sectorSizeX;
    const int x2 = point2.getX() / sectorSizeX > gridSizeX - 1 ? gridSizeX - 1 : point2.getX() / sectorSizeX;
    const int y1 = point1.getY() / sectorSizeY > gridSizeY - 1 ? gridSizeY - 1 : point1.getY() / sectorSizeY;
    const int y2 = point2.getY() / sectorSizeY > gridSizeY - 1 ? gridSizeY - 1 : point2.getY() / sectorSizeY;

    Vector2D diff = point1 - point2;
    Vector2D dir = {float(diff.getX() < 0 ? -1 : 1), float(diff.getY() < 0 ? -1 : 1)};

    int firstX = dir.getX() < 0 && x1 < x2 || dir.getX() > 0 && x1 > x2 ? x2 : x1;
    int firstY = dir.getY() < 0 && y1 < y2 || dir.getY() > 0 && y1 > y2 ? y2 : y1;

    int lastX = firstX == x1 ? x2 : x1;
    int lastY = firstY == y1 ? y2 : y1;

    for (auto &wall: wallGrid[x1][y1]) {
        if (CollisionManager::LineRectCollision(wall.getPoint1(), wall.getPoint2(), point1, point2)) {
            wall.setDeathState(true);
            return true;
        }
    }

    for (auto &wall: wallGrid[x2][y2]) {
        if (CollisionManager::LineRectCollision(wall.getPoint1(), wall.getPoint2(), point1, point2)) {
            wall.setDeathState(true);
            return true;
        }
    }

    for (; firstX != lastX && firstY != lastY;) {
        if (CollisionManager::LineRectCollision(point1, point2,
                                                {(firstX + dir.getX()) * sectorSizeX, (float) firstY * sectorSizeY},
                                                {(firstX + dir.getX()) * sectorSizeX + sectorSizeX - 1,
                                                 (float) firstY * sectorSizeY + sectorSizeY - 1})) {
            firstX += dir.getX();
            for (auto &wall: wallGrid[firstX][firstY]) {
                if (CollisionManager::LineRectCollision(wall.getPoint1(), wall.getPoint2(), point1, point2)) {
                    wall.setDeathState(true);
                    return true;
                }
            }
        } else if (CollisionManager::LineRectCollision(point1, point2, {(float) firstX * sectorSizeX,
                                                                        (float) (firstY + dir.getY()) * sectorSizeY},
                                                       {(float) firstX * sectorSizeX + sectorSizeX - 1,
                                                        (float) (firstY + dir.getY()) * sectorSizeY + sectorSizeY -
                                                        1})) {
            firstY += dir.getY();
            for (auto &wall: wallGrid[firstX][firstY]) {
                if (CollisionManager::LineRectCollision(wall.getPoint1(), wall.getPoint2(), point1, point2)) {
                    wall.setDeathState(true);
                    return true;
                }
            }
        } else if (CollisionManager::LineRectCollision(point1, point2, {(float) (firstX + dir.getX()) * sectorSizeX,
                                                                        (float) (firstY + dir.getY()) * sectorSizeY},
                                                       {(float) (firstX + dir.getX()) * sectorSizeX + sectorSizeX - 1,
                                                        (float) (firstY + dir.getY()) * sectorSizeY + sectorSizeY -
                                                        1})) {
            firstX += dir.getX();
            firstY += dir.getY();
            for (auto &wall: wallGrid[firstX][firstY]) {
                if (CollisionManager::LineRectCollision(wall.getPoint1(), wall.getPoint2(), point1, point2)) {
                    wall.setDeathState(true);
                    return true;
                }
            }
        }
    }
    return false;
}

