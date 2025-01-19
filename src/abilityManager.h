#pragma once
#include <raylib.h>
#include <vector>
#include <memory>

class Player;
class Enemy;
class Ability;

class AbilityManager 
{
    public:
        AbilityManager();
        void Update(const Player& player, std::vector<std::unique_ptr<Enemy>>& enemies, float deltaTime);
        void CheckCollisions(Player& player, std::vector<std::unique_ptr<Enemy>>& enemies);
        void Draw(const Player& player, const Camera2D& camera) const;
        void AddAbility(std::unique_ptr<Ability> ability);

    private:
        std::vector<std::unique_ptr<Ability>> abilities;

};