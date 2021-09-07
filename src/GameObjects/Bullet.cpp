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

void Bullet::CollideWithWall(const std::shared_ptr<Wall> &wall) {
    Vector2D normal = (wall->GetPoint1() - wall->GetPoint2()).Normalize() * -1;

    dir = normal * (dir.DotProduct(normal)  * 2) - dir;
}

void Bullet::CollideWithWindowBorders(float width, float height) {
    Vector2D normal{};
    if (pos.GetX() >= width) {
        normal = (Vector2D{width, 0} - Vector2D{width, height}).Normalize() * -1;
    } else if (pos.GetX() <= 0) {
        normal = (Vector2D{0, 0} - Vector2D{0, height}).Normalize() * -1;
    } else if (pos.GetY() >= height) {
        normal = (Vector2D{0, height} - Vector2D{width, height}).Normalize() * -1;
    } else if (pos.GetY() <= 0) {
        normal = (Vector2D{0, 0} - Vector2D{width, 0}).Normalize() * -1;
    } else {
        return;
    }

    dir = normal * (dir.DotProduct(normal)  * 2) - dir;
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

