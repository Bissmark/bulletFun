#include "player.h"

Player::Player()
    : x(100)
    , y(100)
    , speedX(5)
    , speedY(5)
    , radius(15)
{
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    currentFrame = 0;

    framesCounter = 0;
    framesSpeed = 8;

    playerIdle = LoadTexture("src/Spritesheet/player/Idle.png");
    playerWalk = LoadTexture("src/Spritesheet/player/Walk.png");

    currentTexture = playerIdle;

    frameRec = { 0.0f, 0.0f, (float)playerIdle.width / 6, (float)playerIdle.height };
    playerPosition = { (float)screenWidth / 2, (float)screenHeight / 2 };
}

void Player::Update()
{

}

void Player::Move()
{
    bool isMoving = false;

    if (IsKeyDown(KEY_D)) {
        playerPosition.x += 5;
        //frameRec.y = 0;

        ++framesCounter;

        if (framesCounter >= (60 / framesSpeed)) {
            framesCounter = 0;
            currentFrame++;

            if (currentFrame > 5) currentFrame = 0;

            frameRec.x = (float)currentFrame * (float)playerIdle.width / 6;
        }
    }
    if (IsKeyDown(KEY_A)) {
        playerPosition.x -= 5;

        ++framesCounter;

        if (framesCounter >= (60 / framesSpeed)) {
            framesCounter = 0;
            currentFrame++;

            if (currentFrame > 5) currentFrame = 0;

            frameRec.x = (float)currentFrame * (float)playerIdle.width / 6;
        }
    }
    if (IsKeyDown(KEY_W)) {
        playerPosition.y -= 5;

        ++framesCounter;

        if (framesCounter >= (60 / framesSpeed)) {
            framesCounter = 0;
            currentFrame++;

            if (currentFrame > 5) currentFrame = 0;

            frameRec.x = (float)currentFrame * (float)playerIdle.width / 6;
        }
    }
    if (IsKeyDown(KEY_S)) {
        playerPosition.y += 5;

        ++framesCounter;

        if (framesCounter >= (60 / framesSpeed)) {
            framesCounter = 0;
            currentFrame++;

            if (currentFrame > 5) currentFrame = 0;

            frameRec.x = (float)currentFrame * (float)playerIdle.width / 6;
        }
    }
}

void Player::Draw() const
{
    DrawTextureRec(playerIdle, frameRec, playerPosition, WHITE);
}