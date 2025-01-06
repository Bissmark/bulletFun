#pragma once
#include "enemy.h"

class Archer : public Enemy
{
    public:
        Archer(Player& player);
        void Update(float deltaTime) override;
        void Draw() const override;
        void Attack(float deltaTime) override;

    private:
        Texture2D currentTexture;
};