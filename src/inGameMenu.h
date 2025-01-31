#pragma once
#include "player.h"
#include "rlimGui.h"
#include "imgui.h"

class InGameMenu
{
    public:
        InGameMenu();
        void Draw(Player& player, bool &showStartMenu);

    private:
};