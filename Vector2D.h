//
// Created by Mariia Nosko on 27.08.2021.
//

#ifndef BULLETSHOOTER_VECTOR2D_H
#define BULLETSHOOTER_VECTOR2D_H


class Vector2D {
private:
        float x;
        float y;

public:
    Vector2D() = default;
    Vector2D(float x, float y);
    Vector2D(int x, int y);
    Vector2D operator+(const Vector2D& vec) const;
    Vector2D operator-(const Vector2D& vec) const;
    Vector2D operator*(const float &num) const;
    float vectorLength() const;
    Vector2D normalize() const;

    float getX() const;
    float getY() const;

};


#endif //BULLETSHOOTER_VECTOR2D_H
