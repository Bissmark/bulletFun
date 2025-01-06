#pragma once
#include "enemy.h"

class Slime : public Enemy
{
    public:
        Slime(Player& player);
        void Update(float deltaTime) override;
        void Draw() const override;
        void Attack(float deltaTime) override;

    private:
        Texture2D currentTexture;
};