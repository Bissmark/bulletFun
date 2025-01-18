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
        void Draw() const;
        void AddSkill(std::unique_ptr<Ability> skill);

    private:
        std::vector<std::unique_ptr<Ability>> skills;
};