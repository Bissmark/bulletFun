#include "skillBar.h"
#include "auraDmg.h"

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

void SkillBar::Draw() const
{
    int mainBoxWidth = 300;
    int mainBoxHeight = 60;
    int mainBoxX = GetScreenWidth() / 2 - mainBoxWidth / 2;
    int mainBoxY = GetScreenHeight() - 80;

    DrawRectangle(mainBoxX, mainBoxY, mainBoxWidth, mainBoxHeight, GRAY);

    // Draw 4 smaller boxes inside the main box
    int smallBoxWidth = 60;
    int smallBoxHeight = 60;
    int spacing = 10;
    int smallBoxY = mainBoxY;

    for (int i = 0; i < 4; ++i) {
        int smallBoxX = mainBoxX + spacing + i * (smallBoxWidth + spacing);
        DrawRectangle(smallBoxX, smallBoxY, smallBoxWidth, smallBoxHeight, WHITE);

        // Draw the skill icon inside the smaller boxes if a skill is present
        if (i < skills.size()) {
            // Placeholder for skill icon drawing
            DrawRectangle(smallBoxX + 10, smallBoxY + 10, smallBoxWidth - 20, smallBoxHeight - 20, RED);//skills[i]->GetColor());
        }
    }
}

void SkillBar::AddSkill(std::unique_ptr<Ability> skill)
{
    if (skills.size() < 4) skills.push_back(std::move(skill));
}