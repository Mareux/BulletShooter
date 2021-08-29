//
// Created by Mariia Nosko on 28.08.2021.
//

#ifndef BULLETSHOOTER_WALLMANAGER_H
#define BULLETSHOOTER_WALLMANAGER_H


#include <list>
#include "../GameObjects/Wall.h"

class WallManager {
public:
    void createWalls(int wallsNum);
    std::list<Wall> getWallList();
    void deleteDeadWalls();

private:
    std::list<Wall> wallList;
};


#endif //BULLETSHOOTER_WALLMANAGER_H
