//
// Created by Mariia Nosko on 28.08.2021.
//

#ifndef BULLETSHOOTER_WALL_H
#define BULLETSHOOTER_WALL_H


#include "Figure.h"

class Wall : public Figure{
    ~Wall() override;
    void Draw(const Renderer &renderer) override = 0;
};


#endif //BULLETSHOOTER_WALL_H
