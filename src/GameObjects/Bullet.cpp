//
// Created by Mariia Nosko on 28.08.2021.
//

#include "Bullet.h"

void Bullet::Draw(Renderer &renderer) {
    renderer.drawPoint(pos);
}

Bullet::~Bullet() = default;

void Bullet::Move() {
    pos = pos + dir * speed;
}

Bullet::Bullet(Vector2D pos, Vector2D dir, float speed, float spawnTime, float lifetime)
    : pos(pos)
    , dir(dir)
    , speed(speed)
    , spawnTime(spawnTime)
    , lifetime(lifetime) {

}

bool Bullet::isDead(float time) const {
    if (spawnTime + lifetime >= time)
        return false;
    return true;
}

void Bullet::collideWithWall(bool isHit) {
    if (isHit)
        dir = dir * -1;
}

void Bullet::collideWithWindowBorders(float width, float height) {
    if ((pos.getX() >= width || pos.getX() <= 0)
        ||(pos.getY() >= height || pos.getY() <= 0)) {
        dir = dir * -1;
    }
}

Vector2D Bullet::getPosition() {
    return pos;
}

Vector2D Bullet::getDirection() {
    return dir;
}

float Bullet::getSpeed() const {
    return speed;
}

