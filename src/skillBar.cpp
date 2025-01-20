#include "skillBar.h"
#include "auraDmg.h"
#include <iostream>

SkillBar::SkillBar()
{
}

void SkillBar::Update(const Player& player, std::vector<std::unique_ptr<Enemy>>& enemies, float deltaTime)
{
    for (auto& skill : skills) {
        skill->Update(player, enemies, deltaTime);
    }

    // Check for skill activation (e.g., pressing keys 1-4)
    if (IsKeyPressed(KEY_ONE) && skills.size() > 0) {
        if (auto* auraSkill = dynamic_cast<AuraDmg*>(skills[0].get())) {
            auraSkill->Activate();
        }
    }
    if (IsKeyPressed(KEY_TWO) && skills.size() > 1) {
        if (auto* auraSkill = dynamic_cast<AuraDmg*>(skills[1].get())) {
            auraSkill->Activate();
        }
    }
    if (IsKeyPressed(KEY_THREE) && skills.size() > 2) {
        if (auto* auraSkill = dynamic_cast<AuraDmg*>(skills[2].get())) {
            auraSkill->Activate();
        }
    }
    if (IsKeyPressed(KEY_FOUR) && skills.size() > 3) {
        if (auto* auraSkill = dynamic_cast<AuraDmg*>(skills[3].get())) {
            auraSkill->Activate();
        }
    }
}

void SkillBar::Draw(Player& player, Camera2D camera) const
{
    // Draw the skill bar in screen space
    int mainBoxWidth = 300;
    int mainBoxHeight = 60;
    int mainBoxX = GetScreenWidth() / 2 - mainBoxWidth / 2;
    int mainBoxY = GetScreenHeight() - 80;

    DrawRectangle(mainBoxX, mainBoxY, mainBoxWidth, mainBoxHeight, GRAY);

    // Draw smaller boxes for skills
    int smallBoxWidth = 60;
    int smallBoxHeight = 60;
    int spacing = 10;
    int smallBoxY = mainBoxY;

    for (int i = 0; i < 4; ++i) {
        int smallBoxX = mainBoxX + spacing + i * (smallBoxWidth + spacing);
        DrawRectangle(smallBoxX, smallBoxY, smallBoxWidth, smallBoxHeight, WHITE);

        // Draw the skill icon inside the boxes
        if (i < skills.size()) {
            DrawRectangle(smallBoxX + 10, smallBoxY + 10, smallBoxWidth - 20, smallBoxHeight - 20, RED);
        
            const std::string skillName = skills[i]->GetName();
            int textWidth = MeasureText(skillName.c_str(), 10);
            int textX = smallBoxX + (smallBoxWidth - textWidth) / 2;
            int textY = smallBoxY + (smallBoxHeight - 10) / 2;
            DrawText(skillName.c_str(), textX, textY, 10, BLACK);
        }
    }

    // Draw skills (e.g., abilities) in world space
    //Vector2 screenPlayerPosition = GetWorldToScreen2D(player.playerPosition, camera);
    for (const auto& skill : skills) {
        skill->Draw(player, camera);
    }
}

void SkillBar::AddSkill(std::unique_ptr<Ability> skill)
{
    if (skills.size() < 4) skills.push_back(std::move(skill));
}