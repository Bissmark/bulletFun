#include "inGameMenu.h"
#include <iostream>

InGameMenu::InGameMenu()
{
}

void InGameMenu::Draw(Player& player, SkillBar& skillBar, bool &showStartMenu)
{
    rlImGuiBegin();

    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(GetScreenWidth(), GetScreenHeight()), ImGuiCond_Always);

    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.2f, 0.2f, 0.2f, 0.9f));
    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(1.0f, 1.0f, 1.0f, 0.5f));
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.8f, 0.1f, 0.1f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.0f, 0.2f, 0.2f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.6f, 0.0f, 0.0f, 1.0f));

    ImGui::Begin("In-Game Menu", &showStartMenu, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus);

    float windowWidth = ImGui::GetWindowSize().x;

    // ==== Display Player Stats ====
    const char* playerStats[] = {
        "Health: %d", "Level: %d", "Enemies Killed: %d",
        "Attack Speed: %d", "Auto Attack Damage: %d", 
        "Crit Chance: %d", "Crit Damage: %d"
    };

    int playerValues[] = {
        player.healthPoints, player.level, player.enemiesKilled,
        player.attackSpeed, player.baseDamage,
        player.critChance, player.critDamage
    };

    int numPlayerStats = sizeof(playerValues) / sizeof(playerValues[0]);

    ImGui::Text("Player Stats");
    ImGui::Separator();
    for (int i = 0; i < numPlayerStats; i++) {
        float textWidth = ImGui::CalcTextSize(playerStats[i]).x;
        ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
        ImGui::Text(playerStats[i], playerValues[i]);
    }

    ImGui::Spacing();

    // ==== Display Ability Stats ====
    ImGui::Text("Abilities");
    ImGui::Separator();

    for (const auto& ability : skillBar.GetAbilities()) {
        std::cout << ability->GetName() << std::endl;
        ImGui::Text("%s", ability->GetName().c_str());
        ImGui::Text("Cooldown: %.2f seconds", ability->GetCooldownDuration());
        ImGui::Text("Damage: %d", ability->GetDamage());
        ImGui::Separator();
    }

    ImGui::Spacing();

    // ==== Resume Button ====
    float buttonWidth = 120;
    float buttonX = (windowWidth - buttonWidth) * 0.5f;
    ImGui::SetCursorPosX(buttonX);
    if (ImGui::Button("Resume", ImVec2(buttonWidth, 40))) {
        showStartMenu = false;
        player.gamePaused = false;
    }

    // ==== Exit Button ====
    ImGui::SetCursorPosX(buttonX);
    if (ImGui::Button("Exit", ImVec2(buttonWidth, 40))) {
        CloseWindow();
        exit(0);
    }

    ImGui::PopStyleColor(5); // Pop all style changes
    ImGui::End();
    rlImGuiEnd();
}
