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
    std::list<std::shared_ptr<Wall>>& getWallList();
    void deleteDeadWalls();
    void Update();

    WallManager(std::shared_ptr<Renderer> renderer);

private:
    std::list<std::shared_ptr<Wall>> wallList;
    std::shared_ptr<Renderer> m_renderer;
};


#endif //BULLETSHOOTER_WALLMANAGER_H
