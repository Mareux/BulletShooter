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
        LocateLineInGrid(wall->GetPoint1(), wall->GetPoint2(), [&](int x, int y) {
            wallGrid[x][y].emplace(wall);
        });
    }
}

bool Grid::CollidesWithWallInSector(Vector2D point1, Vector2D point2) {
    int wallWasKilled = false;

    LocateLineInGrid(point1, point2, [&](int x, int y) {
        for (auto &wall: wallGrid[x][y]) {
            if (CollisionManager::LineLineCollision(wall->GetPoint1(), wall->GetPoint2(), point1, point2)) {
                wall->KillWall();
                wallWasKilled = true;
                return;
            }
        }
    });

    return wallWasKilled;
}

void Grid::RemoveKilledWalls(std::list<std::shared_ptr<Wall>> &walls) {
    for (auto &wall: walls) {
        if (wall->GetDeathState()) {
            LocateLineInGrid(wall->GetPoint1(), wall->GetPoint2(), [&](int x, int y) {
                wallGrid[x][y].erase(wall);
            });
        }
    }
}

void Grid::LocateLineInGrid(Vector2D point1, Vector2D point2, const std::function<void(int, int)> &innerFunc) const {

    const int x1 = GetGridCoord(point1.GetX(), gridSizeX, sectorSizeX);
    const int x2 = GetGridCoord(point2.GetX(), gridSizeX, sectorSizeX);
    const int y1 = GetGridCoord(point1.GetY(), gridSizeY, sectorSizeY);
    const int y2 = GetGridCoord(point2.GetY(), gridSizeY, sectorSizeY);

    if (x1 == x2 && y1 == y2) {
        innerFunc(x1, y1);
        return;
    }

    // This part could sometimes not work correctly for some lines, but let's say that it's not a bug but a feature
    // If you easily see what's wrong please say
    // Will probably improve it on different branch

    Vector2D diff = point1 - point2;
    int dx = diff.GetX() < 0 ? -1 : 1;
    int dy = diff.GetY() < 0 ? -1 : 1;

    int lenX = abs(x1 - x2);
    int lenY = abs(y1 - y2);

    int len = lenY > lenX ? lenY : lenX;

    innerFunc(x1, y1);
    innerFunc(x2, y2);

    auto firstX = SwapCoords(x1, x2, (int) dx);
    auto firstY = SwapCoords(y1, y2, (int) dy);

    for (; len > 0; len--) {
        if (firstX + dx < (int) gridSizeX && firstX + dx >= 0 &&
            CheckSectorLineCollision(firstX + dx, firstY, point1, point2)) {
            firstX += dx;
            innerFunc(firstX, firstY);
        }

        if (firstY + dy < (int) gridSizeY && firstY + dy >= 0 &&
            CheckSectorLineCollision(firstX, firstY + dy, point1, point2)) {
            firstY += dy;
            innerFunc(firstX, firstY);
        }
    }
}

int Grid::SwapCoords(int c1, int c2, int dir) {
    if ((dir < 0 && c1 < c2) || (dir > 0 && c1 > c2)) {
        return c2;
    }
    return c1;
}

bool Grid::CheckSectorLineCollision(int x, int y, Vector2D point1, Vector2D point2) const {
    Vector2D point3 = {x * sectorSizeX, y * sectorSizeY};
    Vector2D point4 = {point3.GetX() + sectorSizeX, point3.GetY() + sectorSizeY};

    if (CollisionManager::LineRectCollision(point1, point2, point3, point4))
        return true;
    return false;
}

int Grid::GetGridCoord(float coord, float gridSize, float sectorSize) const {
    float result = coord / sectorSize;
    if (result > gridSizeX - 1)
        return (int) gridSize - 1;
    if (result < 0)
        return 0;
    return (int) result;
}

