#include "slime.h"
#include "player.h"
#include <raymath.h>
#include <iostream>

Slime::Slime(Player& player, Vector2 position) : Enemy(player, position)
{
    std::cout << "Initializing Slime" << std::endl;
    currentTexture = LoadTexture("Spritesheet/enemy/Idle.png");
    if (currentTexture.id == 0) {
        std::cerr << "Failed to load texture: Spritesheet/enemy/Idle.png" << std::endl;
    }
    numFrames = 4;
    frameWidth = currentTexture.width / numFrames;
    frameRec = { 0.0f, 0.0f, (float)currentTexture.width / numFrames, (float)currentTexture.height };

    maxHealth = 30;
    health = maxHealth;
    std::cout << "Slime initialized" << std::endl;
}

void Slime::Update(float deltaTime)
{
    std::cout << "Updating Slime" << std::endl;
    Enemy::Update(deltaTime);
    std::cout << "Slime updated" << std::endl;
}

void Slime::Draw() const
{
    std::cout << "Drawing Slime" << std::endl;
    Enemy::Draw();
    std::cout << "Finished drawing Slime" << std::endl;
}

void Slime::Attack(float deltaTime)
{
    Enemy::Attack(deltaTime);
}