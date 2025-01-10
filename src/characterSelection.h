#pragma once
#include <raylib.h>
#include "player.h"

class CharacterSelection
{
    public:
        CharacterSelection(Player& player);
        void Update();
        void Draw() const;
        bool IsCharacterSelected() const;
        Player::PlayerType GetSelectedPlayerType() const;

    private:
        Player& player;
        Rectangle warriorButton;
        Rectangle mageButton;
        Rectangle archerButton;
        bool warriorButtonPressed;
        bool mageButtonPressed;
        bool archerButtonPressed;

};