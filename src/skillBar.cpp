#include "skillBar.h"
#include <iostream>

SkillBar::SkillBar()
{
}

void SkillBar::Update(const Player& player, std::vector<std::unique_ptr<Enemy>>& enemies, float deltaTime)
{
    for (auto& skill : skills) {
        skill->Update(player, enemies, deltaTime);
    }

    // Function to set Blizzard position before activation
    // auto ActivateSkill = [&](int index) {
    //     if (index < skills.size()) {
    //         // Check if the skill is a Blizzard instance
    //         Blizzard* blizzard = dynamic_cast<Blizzard*>(skills[index].get());
    //         if (blizzard) {
    //             //if (!blizzard->IsPositionSet()) {
    //                 Vector2 castPos = {
    //                     // player.playerPosition.x + player.frameRec.width / 2,
    //                     // player.playerPosition.y + player.frameRec.height / 2
    //                     GetScreenWidth() / 2, GetScreenHeight() / 2
    //                 };
    //                 blizzard->SetCastPosition(castPos);
    //                 //blizzard->SetPositionState(true);
    //             //}
    //         }
    //         skills[index]->Activate();
    //     }
    // };

    if (IsKeyPressed(KEY_ONE)) {
        if (skills[0]) skills[0]->Activate();
    }
    if (IsKeyPressed(KEY_TWO)) {
        if (skills[1]) skills[1]->Activate();
    }
    if (IsKeyPressed(KEY_THREE)) {
        if (skills[2]) skills[2]->Activate();
    }
    if (IsKeyPressed(KEY_FOUR)) {
        if (skills[3]) skills[3]->Activate();
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

            // Cooldown Visualization
            float cooldownTime = skills[i]->GetCooldownTime();
            float cooldownDuration = skills[i]->GetCooldownDuration();
            if (cooldownTime > 0.0f) {
                float cooldownPercentage = cooldownTime / cooldownDuration;
                int cooldownHeight = static_cast<int>((smallBoxHeight - 20) * cooldownPercentage);
                DrawRectangle(smallBoxX + 10, smallBoxY + 10 + (smallBoxHeight - 20 - cooldownHeight), smallBoxWidth - 20, cooldownHeight, Fade(BLACK, 0.5f));
            }
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

const std::vector<std::unique_ptr<Ability>>& SkillBar::GetAbilities() const
{
    return skills;
}