#pragma once
#include "enemy.h"

class Grunt : public Enemy
{
    public:
        Grunt(Player& player, Vector2 position);
        void Update(float deltaTime) override;
        void Draw() const override;
        void Attack(float deltaTime) override;

    private:
        Texture2D idleTexture;
        Texture2D walkTexture;
        Texture2D currentTexture;
        int startingMaxHealth = 50;
};