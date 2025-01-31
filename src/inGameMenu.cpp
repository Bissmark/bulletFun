#include "inGameMenu.h"

InGameMenu::InGameMenu()
{
}

void InGameMenu::Draw(Player& player, bool &showStartMenu)
{
    rlImGuiBegin();

    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(GetScreenWidth(), GetScreenHeight()), ImGuiCond_Always);
    
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.2f, 0.2f, 0.2f, 0.9f));
    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(1.0f, 1.0f, 1.0f, 0.5f));
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.8f, 0.1f, 0.1f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.0f, 0.2f, 0.2f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.6f, 0.0f, 0.0f, 1.0f));

    ImGui::Begin("In-Game Menu", &showStartMenu, ImGuiWindowFlags_NoCollapse);

    float windowWidth = ImGui::GetWindowSize().x;

    const char* stats[] = {
        "Health: %d", "Level: %d", "Enemies Killed: %d",
        "Attack Speed: %d", "Base Damage: %d", 
        "Crit Chance: %d", "Crit Damage: %d"
    };

    int statValues[] = {
        player.healthPoints, player.level, player.enemiesKilled,
        player.attackSpeed, player.baseDamage,
        player.critChance, player.critDamage
    };

    for (int i = 0; i < 7; i++) {
        float textWidth = ImGui::CalcTextSize(stats[i]).x;
        ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
        ImGui::Text(stats[i], statValues[i]);
    }

    ImGui::Spacing();
    float buttonWidth = 120;
    float buttonX = (windowWidth - buttonWidth) * 0.5f;
    ImGui::SetCursorPosX(buttonX);
    if (ImGui::Button("Resume", ImVec2(buttonWidth, 40))) {
        showStartMenu = false;
    }

    ImGui::SetCursorPosX(buttonX);
    if (ImGui::Button("Exit", ImVec2(buttonWidth, 40))) {
        CloseWindow();
    }

    ImGui::PopStyleColor(5); // Pop all style changes
    ImGui::End();
    rlImGuiEnd();
}
