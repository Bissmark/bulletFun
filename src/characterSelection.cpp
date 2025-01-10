#include "characterSelection.h"

CharacterSelection::CharacterSelection(Player& player) 
    : player(player)
    , warriorButton({ 0 })
    , mageButton({ 0 })
    , archerButton({ 0 })
    , warriorButtonPressed(false)
    , mageButtonPressed(false)
    , archerButtonPressed(false)
{
    warriorButton = { 100, 100, 200, 100 };
    mageButton = { 100, 250, 200, 100 };
    archerButton = { 100, 400, 200, 100 };
}

void CharacterSelection::Update()
{
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mousePosition = GetMousePosition();
        if (CheckCollisionPointRec(mousePosition, warriorButton)) {
            warriorButtonPressed = true;
            player.playerType = Player::PlayerType::WARRIOR;
        }
        if (CheckCollisionPointRec(mousePosition, mageButton)) {
            mageButtonPressed = true;
            player.playerType = Player::PlayerType::MAGE;
        }
        if (CheckCollisionPointRec(mousePosition, archerButton)) {
            archerButtonPressed = true;
            player.playerType = Player::PlayerType::ARCHER;
        }
    }
}

void CharacterSelection::Draw() const
{
    DrawRectangleRec(warriorButton, warriorButtonPressed ? RED : BLUE);
    DrawRectangleRec(mageButton, mageButtonPressed ? RED : BLUE);
    DrawRectangleRec(archerButton, archerButtonPressed ? RED : BLUE);

    DrawText("W", warriorButton.x + warriorButton.width / 2 - 10, warriorButton.y + warriorButton.height / 2 - 10, 20, WHITE);
    DrawText("M", mageButton.x + mageButton.width / 2 - 10, mageButton.y + mageButton.height / 2 - 10, 20, WHITE);
    DrawText("A", archerButton.x + archerButton.width / 2 - 10, archerButton.y + archerButton.height / 2 - 10, 20, WHITE);
}

bool CharacterSelection::IsCharacterSelected() const
{
    return warriorButtonPressed || mageButtonPressed || archerButtonPressed;
}

Player::PlayerType CharacterSelection::GetSelectedPlayerType() const
{
    if (warriorButtonPressed) return Player::PlayerType::WARRIOR;
    if (mageButtonPressed) return Player::PlayerType::MAGE;
    if (archerButtonPressed) return Player::PlayerType::ARCHER;
    return Player::PlayerType::WARRIOR; // Default to WARRIOR if none selected
}