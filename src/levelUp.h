#pragma once
#include <raylib.h>
#include "player.h"

class LevelUp
{
    public:
        LevelUp(Player& player);
        void DrawLevelUpBox();

    private:
        Player& player;
};