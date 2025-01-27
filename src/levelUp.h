#pragma once
#include "player.h"
#include "upgrades.h"
#include <vector>
#include <map>

class LevelUp
{
    public:
        LevelUp(Player& player);
        void DrawLevelUpBox();
        void ApplyUpgrade(const Upgrade& upgrade);
        std::vector<Upgrade> currentUpgrades;
        std::vector<Upgrade> GetRandomUpgrades();

    private:
        Player& player;
        std::vector<Upgrade> upgrades;
        void InitializeUpgrades();
};