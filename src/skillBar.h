#pragma once
#include <raylib.h>
#include <vector>
#include <memory>
#include "ability.h"
#include "player.h"
#include "enemy.h"

class SkillBar
{
    public:
        SkillBar();
        void Update(const Player& player, std::vector<std::unique_ptr<Enemy>>& enemies, float deltaTime);
        void Draw(Player& player, Camera2D camera) const;
        void AddSkill(std::unique_ptr<Ability> skill);
        const std::vector<std::unique_ptr<Ability>>& GetAbilities() const;

    private:
        std::vector<std::unique_ptr<Ability>> skills;
};