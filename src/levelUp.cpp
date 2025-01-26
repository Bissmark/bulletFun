#include "levelUp.h"
#include <iostream>

LevelUp::LevelUp(Player& player) : player(player)
{
    InitializeUpgrades();
}

void LevelUp::InitializeUpgrades()
{
    upgrades = {
        { UpgradeType::CritChance, "Crit Chance", "Increase your crit chance by 5%", nullptr },
        { UpgradeType::CritDamage, "Crit Damage", "Increase your crit damage by 50%", nullptr },
        { UpgradeType::CooldownReduction, "Cooldown Reduction", "Reduce all ability cooldowns by 10%", nullptr },
        { UpgradeType::Health, "Health", "Increase your max health by 10%", nullptr },
        { UpgradeType::Damage, "Damage", "Increase your base damage by 10%", nullptr }
    };
}

void LevelUp::DrawLevelUpBox()
{
    if (player.leveledUp) {
        // Draw the main blue box
        int mainBoxWidth = 300;
        int mainBoxHeight = 200;
        int mainBoxX = GetScreenWidth() / 2 - mainBoxWidth / 2;
        int mainBoxY = GetScreenHeight() / 2 - mainBoxHeight / 2;
        DrawRectangle(mainBoxX, mainBoxY, mainBoxWidth + 20, mainBoxHeight, BLUE);

        // Draw three smaller boxes inside the main box
        int smallBoxWidth = 80;
        int smallBoxHeight = 80;
        int spacing = 20;
        int smallBoxY = mainBoxY + (mainBoxHeight - smallBoxHeight) / 2;

        for (int i = 0; i < 3; ++i) {
            int smallBoxX = mainBoxX + spacing + i * (smallBoxWidth + spacing);
            DrawRectangle(smallBoxX, smallBoxY, smallBoxWidth, smallBoxHeight, WHITE);

            // Draw textures inside the smaller boxes (replace with actual textures)
            // Example: DrawTexture(texture, smallBoxX, smallBoxY, WHITE);
            // For now, we'll just draw a placeholder rectangle
            //DrawRectangle(smallBoxX + 10, smallBoxY + 10, smallBoxWidth - 20, smallBoxHeight - 20, GRAY);
            DrawText(upgrades[i].name, smallBoxX + 10, smallBoxY + 10, 10, BLACK);
        
            // Check for mouse clicks within the bounding rectangles of the small boxes
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                Vector2 mousePosition = GetMousePosition();
                if (CheckCollisionPointRec(mousePosition, { (float)smallBoxX, (float)smallBoxY, (float)smallBoxWidth, (float)smallBoxHeight })) {
                    ApplyUpgrade(upgrades[i]);
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
            player.critChance += 3.0f;
            break;
        case UpgradeType::CritDamage:
            player.critDamage += 50.0f;
            break;
        case UpgradeType::CooldownReduction:
            //player.abilityManager.ReduceCooldowns();
            player.cooldownReduction += 10.0f;
            break;
        case UpgradeType::Health:
            player.maxHealth += 10;
            break;
        case UpgradeType::Damage:
            player.baseDamage += 5;
            break;
    }
}