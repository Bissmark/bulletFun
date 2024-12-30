#pragma once
#include "raylib.h"

class Bullet {
    public:
        Vector2 position;
        Vector2 direction;
        float speed;
        Color color;
        Bullet(Vector2 position, Vector2 direction, float speed, Color color);
        void Move();
        void Draw() const;
};