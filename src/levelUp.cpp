#include "levelUp.h"
#include <iostream>

LevelUp::LevelUp(Player& player) : player(player)
{
}

void LevelUp::DrawLevelUpBox()
{
    if (player.leveledUp) {
        // Draw the main blue box
        int mainBoxWidth = 300;
        int mainBoxHeight = 200;
        int mainBoxX = GetScreenWidth() / 2 - mainBoxWidth / 2;
        int mainBoxY = GetScreenHeight() / 2 - mainBoxHeight / 2;
        DrawRectangle(mainBoxX, mainBoxY, mainBoxWidth + 20, mainBoxHeight, BLUE);

        // Draw three smaller boxes inside the main box
        int smallBoxWidth = 80;
        int smallBoxHeight = 80;
        int spacing = 20;
        int smallBoxY = mainBoxY + (mainBoxHeight - smallBoxHeight) / 2;

        for (int i = 0; i < 3; ++i) {
            int smallBoxX = mainBoxX + spacing + i * (smallBoxWidth + spacing);
            DrawRectangle(smallBoxX, smallBoxY, smallBoxWidth, smallBoxHeight, WHITE);

            // Draw textures inside the smaller boxes (replace with actual textures)
            // Example: DrawTexture(texture, smallBoxX, smallBoxY, WHITE);
            // For now, we'll just draw a placeholder rectangle
            DrawRectangle(smallBoxX + 10, smallBoxY + 10, smallBoxWidth - 20, smallBoxHeight - 20, GRAY);
        
            // Check for mouse clicks within the bounding rectangles of the small boxes
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                Vector2 mousePosition = GetMousePosition();
                if (CheckCollisionPointRec(mousePosition, { (float)smallBoxX, (float)smallBoxY, (float)smallBoxWidth, (float)smallBoxHeight })) {
                    player.leveledUp = false;
                    player.gamePaused = false;
                }
            }
        }
    }
}