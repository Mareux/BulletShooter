//
// Created by Mariia Nosko on 28.08.2021.
//

#include "Bullet.h"

void Bullet::Draw(Renderer &renderer) {
    renderer.DrawPoint(pos);
}

Bullet::~Bullet() = default;

void Bullet::Move() {
    pos = pos + dir * speed;
}

Bullet::Bullet(Vector2D pos, Vector2D dir, float speed, float spawnTime, float lifetime)
        : pos(pos), dir(dir), speed(speed), spawnTime(spawnTime), lifetime(lifetime) {

}

bool Bullet::IsDead(float time) const {
    if (spawnTime + lifetime >= time)
        return false;
    return true;
}

void Bullet::CollideWithWall() {
    dir = dir * -1;
}

void Bullet::CollideWithWindowBorders(float width, float height) {
    if ((pos.GetX() >= width || pos.GetX() <= 0)
        || (pos.GetY() >= height || pos.GetY() <= 0)) {
        dir = dir * -1;
    }
}

Vector2D Bullet::GetPosition() {
    return pos;
}

Vector2D Bullet::GetDirection() {
    return dir;
}

float Bullet::GetSpeed() const {
    return speed;
}

