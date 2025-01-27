#include "levelUp.h"
#include <iostream>
#include <random>
#include <algorithm>

LevelUp::LevelUp(Player& player) : player(player)
{
    InitializeUpgrades();
}

void LevelUp::InitializeUpgrades()
{
    upgrades = {
        { UpgradeType::CritChance, "Crit Chance", "Increase your crit chance by 3%", nullptr, Rarity::Common, 3.0f, GREEN },
        { UpgradeType::CritChance, "Crit Chance", "Increase your crit chance by 5%", nullptr, Rarity::Rare, 5.0f, BLUE },
        { UpgradeType::CritChance, "Crit Chance", "Increase your crit chance by 8%", nullptr, Rarity::Epic, 8.0f, PURPLE },
        { UpgradeType::CritDamage, "Crit Damage", "Increase your crit damage by 50%", nullptr, Rarity::Common, 50.0f, GREEN },
        { UpgradeType::CritDamage, "Crit Damage", "Increase your crit damage by 75%", nullptr, Rarity::Rare, 75.0f, BLUE },
        { UpgradeType::CritDamage, "Crit Damage", "Increase your crit damage by 100%", nullptr, Rarity::Epic, 100.0f, PURPLE },
        { UpgradeType::CooldownReduction, "Cooldown Reduction", "Reduce all ability cooldowns by 10%", nullptr, Rarity::Common, 10.0f, GREEN },
        { UpgradeType::CooldownReduction, "Cooldown Reduction", "Reduce all ability cooldowns by 15%", nullptr, Rarity::Rare, 15.0f, BLUE },
        { UpgradeType::CooldownReduction, "Cooldown Reduction", "Reduce all ability cooldowns by 20%", nullptr, Rarity::Epic, 20.0f, PURPLE },
        { UpgradeType::Health, "Health", "Increase your max health by 10%", nullptr, Rarity::Common, 10.0f, GREEN },
        { UpgradeType::Health, "Health", "Increase your max health by 15%", nullptr, Rarity::Rare, 15.0f, BLUE },
        { UpgradeType::Health, "Health", "Increase your max health by 20%", nullptr, Rarity::Epic, 20.0f, PURPLE },
        { UpgradeType::Damage, "Damage", "Increase your base damage by 10%", nullptr, Rarity::Common, 10.0f, GREEN },
        { UpgradeType::Damage, "Damage", "Increase your base damage by 15%", nullptr, Rarity::Rare, 15.0f, BLUE },
        { UpgradeType::Damage, "Damage", "Increase your base damage by 20%", nullptr, Rarity::Epic, 20.0f, PURPLE }
    };
}

std::vector<Upgrade> LevelUp::GetRandomUpgrades()
{
    std::vector<Upgrade> selectedUpgrades;
    std::random_device rd;
    std::mt19937 gen(rd());

    // Group upgrades by type
    std::map<UpgradeType, std::vector<Upgrade>> groupedUpgrades;
    for (const auto& upgrade : upgrades) {
        groupedUpgrades[upgrade.type].push_back(upgrade);
    }

    std::map<Rarity, int> rarityWeights = {
        { Rarity::Common, 70 },
        { Rarity::Rare, 25 },
        { Rarity::Epic, 5 }
    };

    // Randomly select one upgrade from each group based on weighted probabilities
    for (const auto& group : groupedUpgrades) {
        std::vector<int> weights;
        for (const auto& upgrade : group.second) {
            weights.push_back(rarityWeights[upgrade.rarity]);
        }

        std::discrete_distribution<> dis(weights.begin(), weights.end());
        int index = dis(gen);
        selectedUpgrades.push_back(group.second[index]);
    }

    // Shuffle the selected upgrades to randomize their order
    std::shuffle(selectedUpgrades.begin(), selectedUpgrades.end(), gen);

    // Limit the number of selected upgrades to 3
    if (selectedUpgrades.size() > 3) {
        selectedUpgrades.resize(3);
    }

    return selectedUpgrades;
}

void LevelUp::DrawLevelUpBox()
{
    if (player.leveledUpWindowActive) {
        int mainBoxWidth = 300;
        int mainBoxHeight = 200;
        int mainBoxX = GetScreenWidth() / 2 - mainBoxWidth / 2;
        int mainBoxY = GetScreenHeight() / 2 - mainBoxHeight / 2;
        DrawRectangle(mainBoxX, mainBoxY, mainBoxWidth + 20, mainBoxHeight, BLUE);

        if (currentUpgrades.size() < 3) {
            currentUpgrades = GetRandomUpgrades();
        }
\
        int smallBoxWidth = 80;
        int smallBoxHeight = 80;
        int spacing = 20;
        int smallBoxY = mainBoxY + (mainBoxHeight - smallBoxHeight) / 2;

        for (int i = 0; i < 3; ++i) {
            int smallBoxX = mainBoxX + spacing + i * (smallBoxWidth + spacing);
            DrawRectangle(smallBoxX, smallBoxY, smallBoxWidth, smallBoxHeight, WHITE);
            DrawText(currentUpgrades[i].name, smallBoxX + 10, smallBoxY + 10, 10, currentUpgrades[i].color);
        
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                Vector2 mousePosition = GetMousePosition();
                if (CheckCollisionPointRec(mousePosition, { (float)smallBoxX, (float)smallBoxY, (float)smallBoxWidth, (float)smallBoxHeight })) {
                    ApplyUpgrade(currentUpgrades[i]);
                    player.leveledUpWindowActive = false;
                    player.leveledUp = false;
                    player.gamePaused = false;
                }
            }
        }
    }
}

void LevelUp::ApplyUpgrade(const Upgrade& upgrade)
{
    switch (upgrade.type) {
        case UpgradeType::CritChance:
            player.critChance += upgrade.increaseAmount;
            break;
        case UpgradeType::CritDamage:
            player.critDamage += upgrade.increaseAmount;
            break;
        case UpgradeType::CooldownReduction:
            //player.abilityManager.ReduceCooldowns();
            player.cooldownReduction += upgrade.increaseAmount;
            break;
        case UpgradeType::Health:
            player.maxHealth += upgrade.increaseAmount;
            break;
        case UpgradeType::Damage:
            player.baseDamage += upgrade.increaseAmount;
            break;
    }
}