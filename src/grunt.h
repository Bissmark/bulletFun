#pragma once
#include "enemy.h"

class Grunt : public Enemy
{
    public:
        Grunt(Player& player);
        void Update() override;
        void Draw() const override;
        void Attack(float deltaTime) override;

};