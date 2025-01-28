#include "slime.h"
#include "player.h"
#include <raymath.h>
#include <iostream>

Slime::Slime(Player& player, Vector2 position) : Enemy(player, position)
{
    currentTexture = LoadTexture("Spritesheet/enemy/Idle.png");
    frameWidth = currentTexture.width / numFrames;
    frameRec = { 0.0f, 0.0f, (float)currentTexture.width / numFrames, (float)currentTexture.height };

    maxHealth = 30;
    health = maxHealth;
}

void Slime::Update(float deltaTime)
{
    Enemy::Update(deltaTime);
}

void Slime::Draw() const
{
    Enemy::Draw();
}

void Slime::Attack(float deltaTime)
{
    Enemy::Attack(deltaTime);
}