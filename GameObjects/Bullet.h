//
// Created by Mariia Nosko on 28.08.2021.
//

#ifndef BULLETSHOOTER_BULLET_H
#define BULLETSHOOTER_BULLET_H


#include "Figure.h"

class Bullet : public Figure{
public:
    void Draw(const Renderer &renderer) override;
    ~Bullet() override;
};


#endif //BULLETSHOOTER_BULLET_H
