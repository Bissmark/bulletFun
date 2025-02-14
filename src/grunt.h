#pragma once
#include "enemy.h"

class Grunt : public Enemy
{
    public:
        Grunt(Player& player, Vector2 position, TerrainCollision& tileCollision);
        void Update(float deltaTime) override;
        void Draw() const override;
        void Attack(float deltaTime) override;

    private:
        Texture2D idleTexture;
        Texture2D walkTexture;
        Texture2D currentTexture;
};