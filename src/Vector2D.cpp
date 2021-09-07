//
// Created by Mariia Nosko on 27.08.2021.
//

#include <cmath>
#include "Vector2D.h"

Vector2D Vector2D::operator+(const Vector2D &vec) const {
    Vector2D newPos{};

    newPos.x = x + vec.x;
    newPos.y = y + vec.y;

    return newPos;
}

Vector2D Vector2D::operator-(const Vector2D &vec) const {
    Vector2D newPos{};

    newPos.x = x - vec.x;
    newPos.y = y - vec.y;

    return newPos;
}

Vector2D::Vector2D(float x, float y) {
    this->x = x;
    this->y = y;
}

Vector2D Vector2D::operator*(const float &num) const {
    return Vector2D({this->x * num, this->y * num});
}

float Vector2D::GetX() const {
    return x;
}

float Vector2D::GetY() const {
    return y;
}
