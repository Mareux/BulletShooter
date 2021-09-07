//
// Created by Mariia Nosko on 28.08.2021.
//

#ifndef BULLETSHOOTER_BULLET_H
#define BULLETSHOOTER_BULLET_H


#include "../Renderer.h"
#include "Wall.h"

class Bullet {
public:
    Bullet(Vector2D pos, Vector2D dir, float speed, float spawnTime, float lifetime);

    void Draw(Renderer &renderer);

    void Move();

    bool IsDead(float time) const;

    void CollideWithWall();

    void CollideWithWindowBorders(float width, float height);


    Vector2D GetPosition();

    Vector2D GetDirection();

    float GetSpeed() const;


    ~Bullet();

private:
    Vector2D pos{};
    Vector2D dir{};
    float speed;
    float spawnTime;
    float lifetime;
};


#endif //BULLETSHOOTER_BULLET_H
