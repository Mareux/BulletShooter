//
// Created by Mariia Nosko on 02.09.2021.
//

#include "Grid.h"
#include "CollisionManager.h"

Grid::Grid(int x, int y, int canvasWidth, int canvasHeight) : gridSizeX((float) x), gridSizeY((float) y) {
    sectorSizeX = (float) canvasWidth / gridSizeX;
    sectorSizeY = (float) canvasHeight / gridSizeY;

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

void Grid::locateLineInGrid(Vector2D point1, Vector2D point2, const std::function<void(int, int)> &innerFunc) const {

    const int x1 = getGridCoord(point1.getX(), gridSizeX, sectorSizeX);
    const int x2 = getGridCoord(point2.getX(), gridSizeX, sectorSizeX);
    const int y1 = getGridCoord(point1.getY(), gridSizeY, sectorSizeY);
    const int y2 = getGridCoord(point2.getY(), gridSizeY, sectorSizeY);

    if (x1 == x2 && y1 == y2) {
        innerFunc(x1, y1);
        return;
    }

    // This part could sometimes not work correctly for some lines, but let's say that it's not a bug but a feature
    // If you easily see what's wrong please say
    // Probably improve it on different branch

    Vector2D diff = point1 - point2;
    int dx = diff.getX() < 0 ? -1 : 1;
    int dy = diff.getY() < 0 ? -1 : 1;

    int lenX = abs(x1 - x2);
    int lenY = abs(y1 - y2);

    int len = lenY > lenX ? lenY : lenX;

    innerFunc(x1, y1);

    auto firstX = swapCoordinates(x1, x2, (int) dx);
    auto firstY = swapCoordinates(y1, y2, (int) dy);

    for (; len > 0; len--) {
        if (firstX + dx < (int) gridSizeX && firstX + dx >= 0 &&
            checkSectorLineCollision(firstX + dx, firstY, point1, point2)) {
            firstX += dx;
            innerFunc(firstX, firstY);
        }

        if (firstY + dy < (int) gridSizeY && firstY + dy >= 0 &&
            checkSectorLineCollision(firstX, firstY + dy, point1, point2)) {
            firstY += dy;
            innerFunc(firstX, firstY);
        }
    }
}

int Grid::swapCoordinates(int c1, int c2, int dir) {
    if ((dir < 0 && c1 < c2) || (dir > 0 && c1 > c2)) {
        return c2;
    }
    return c1;
}

bool Grid::checkSectorLineCollision(int x, int y, Vector2D point1, Vector2D point2) const {
    Vector2D point3 = {x * sectorSizeX, y * sectorSizeY};
    Vector2D point4 = {point3.getX() + sectorSizeX, point3.getY() + sectorSizeY};

    if (CollisionManager::LineRectCollision(point1, point2, point3, point4))
        return true;
    return false;
}

int Grid::getGridCoord(float coord, float gridSize, float sectorSize) const {
    float result = coord / sectorSize;
    if (result > gridSizeX - 1)
        return (int) gridSize - 1;
    if (result < 0)
        return 0;
    return (int) result;
}

