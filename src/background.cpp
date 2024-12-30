#include "background.h"
#include <iostream>

Background::Background()
{
    background = LoadTexture("src/Spritesheet/background.png");
    screenHeight = GetScreenHeight();
    screenWidth = GetScreenWidth();
    position1 = { 0.0f, 0.0f };
    position2 = { (float)screenWidth, 0.0f };
}

void Background::Update(Vector2 playerPosition)
{
    // Check if the player is close to the edge of the current background and create new tiles if needed
    if (playerPosition.x >= position2.x) {
        position1.x = position2.x;
        position2.x += background.width;
    }
    if (playerPosition.x <= position1.x) {
        position2.x = position1.x;
        position1.x -= background.width;
    }
    if (playerPosition.y >= position2.y) {
        position1.y = position2.y;
        position2.y += background.height;
    }
    if (playerPosition.y <= position1.y) {
        position2.y = position1.y;
        position1.y -= background.height;
    }

    DrawText(TextFormat("Position 1: (%.2f, %.2f)", position1.x, position1.y), 10, 70, 20, RED);
}

void Background::Draw() const
{
    // Draw the background textures in a grid pattern
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            DrawTexture(background, position1.x + i * background.width, position1.y + j * background.height, WHITE);
            DrawTexture(background, position2.x + i * background.width, position2.y + j * background.height, WHITE);
        }
    }
}

void Background::Unload()
{
    UnloadTexture(background);
}