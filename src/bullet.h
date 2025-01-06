#pragma once
#include "raylib.h"

class Player;
class Enemy;

class Bullet 
{
    public:
        Bullet(Vector2 position, Vector2 direction, float speed, Color color, Player* player);
        void Move();
        void Draw() const;
        bool Collision(Enemy& enemy);

    private:
        Vector2 position;
        Vector2 direction;
        float speed;
        Color color;
        Player* player;
};