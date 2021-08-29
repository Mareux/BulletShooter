//
// Created by Mariia Nosko on 28.08.2021.
//

#ifndef BULLETSHOOTER_FIGURE_H
#define BULLETSHOOTER_FIGURE_H


#include "../Renderer.h"

class Figure {
    virtual ~Figure()= default;
    virtual void Draw(Renderer &renderer) = 0;
};


#endif //BULLETSHOOTER_FIGURE_H
