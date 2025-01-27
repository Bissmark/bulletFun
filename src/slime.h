#pragma once
#include "enemy.h"

class Slime : public Enemy
{
    public:
        Slime(Player& player, Vector2 position);
        void Update(float deltaTime) override;
        void Draw() const override;
        void Attack(float deltaTime) override;

    private:
        Texture2D idleTexture;
        Texture2D walkTexture;
        Texture2D currentTexture;
};