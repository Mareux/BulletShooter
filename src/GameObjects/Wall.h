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
    bool getDeathState() const;
    void setDeathState(bool isHit);

    Vector2D getPoint1();
    Vector2D getPoint2();

private:

    Vector2D point1;
    Vector2D point2;
    bool isDead;
};


#endif //BULLETSHOOTER_WALL_H
