#pragma once
#include "player.h"
#include "upgrades.h"
#include <vector>

class LevelUp
{
    public:
        LevelUp(Player& player);
        void DrawLevelUpBox();
        void ApplyUpgrade(const Upgrade& upgrade);

    private:
        Player& player;
        std::vector<Upgrade> upgrades;
        void InitializeUpgrades();
};