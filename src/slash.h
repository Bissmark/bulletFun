#pragma once
#include <raylib.h>

class Player;
class Enemy;

class Slash
{
    public:
        Slash(Vector2 position, float radius, Player* player);
        void Update();
        void Draw() const;
        bool Collision(Enemy& enemy);

    private:
        Vector2 position;
        float radius;
        Color color;
        Player* player;
        Texture2D slashTexture;
};