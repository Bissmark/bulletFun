#include "grunt.h"
#include "player.h"
#include <raymath.h>
#include <iostream>

Grunt::Grunt(Player& player) : Enemy(player)
{
    currentTexture = LoadTexture("src/Spritesheet/enemy/Idle.png");
    numFrames = 4;
    frameWidth = currentTexture.width / numFrames;
    frameRec = { 0.0f, 0.0f, (float)currentTexture.width / numFrames, (float)currentTexture.height };
}

void Grunt::Update()
{
    Enemy::Update();

    UpdateFrame();
}

void Grunt::Draw() const
{
    Enemy::Draw();
}

void Grunt::Attack(float deltaTime)
{
    Enemy::Attack(deltaTime);
}