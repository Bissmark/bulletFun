#include "slime.h"
#include "player.h"
#include <raymath.h>
#include <iostream>

Slime::Slime(Player& player, Vector2 position) : Enemy(player, position)
{
    currentTexture = LoadTexture("src/Spritesheet/enemy/Idle.png");
    numFrames = 4;
    frameWidth = currentTexture.width / numFrames;
    frameRec = { 0.0f, 0.0f, (float)currentTexture.width / numFrames, (float)currentTexture.height };
}

void Slime::Update(float deltaTime)
{
    Enemy::Update(deltaTime);

    UpdateFrame();
}

void Slime::Draw() const
{
    Enemy::Draw();
}

void Slime::Attack(float deltaTime)
{
    Enemy::Attack(deltaTime);
}