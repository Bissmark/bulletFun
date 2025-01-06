#include "archer.h"
#include "player.h"
#include <raymath.h>
#include <iostream>

Archer::Archer(Player& player) : Enemy(player)
{
    currentTexture = LoadTexture("src/Spritesheet/enemy/Idle.png");
    numFrames = 4;
    frameWidth = currentTexture.width / numFrames;
    frameRec = { 0.0f, 0.0f, (float)currentTexture.width / numFrames, (float)currentTexture.height };
}

void Archer::Update()
{
    Enemy::Update();

    UpdateFrame();
}

void Archer::Draw() const
{
    Enemy::Draw();
}

void Archer::Attack(float deltaTime)
{
    Enemy::Attack(deltaTime);
}