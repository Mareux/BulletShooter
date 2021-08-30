//
// Created by Mariia Nosko on 28.08.2021.
//

#ifndef BULLETSHOOTER_WALL_H
#define BULLETSHOOTER_WALL_H


#include "../Renderer.h"

class Wall  {
public:
    Wall(Vector2D point1, Vector2D point2);
    ~Wall() ;
    void Draw(Renderer &renderer) ;
    bool IsHit(Vector2D pos);
    bool getDeathState() const;

private:

    Vector2D point1;
    Vector2D point2;
    bool isDead;
};


#endif //BULLETSHOOTER_WALL_H
