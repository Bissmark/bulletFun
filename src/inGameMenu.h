#pragma once
#include "player.h"
#include "skillBar.h"
#include "imgui.h"
#include "rlImGui.h"

class InGameMenu
{
    public:
        InGameMenu();
        void Draw(Player& player, SkillBar& skillBar, bool &showStartMenu);

    private:
};