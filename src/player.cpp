#include "player.h"
#include <iostream>

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
    framesSpeed = 5;

    numFrames = 4;
    frameWidth = playerIdle.width / numFrames;

    playerIdle = LoadTexture("src/Spritesheet/player/Idle.png");
    playerWalk = LoadTexture("src/Spritesheet/player/Walk.png");

    currentTexture = playerIdle;

    frameRec = { 0.0f, 0.0f, (float)playerIdle.width / numFrames, (float)playerIdle.height };
    playerPosition = { (float)screenWidth / 2, (float)screenHeight / 2 };
}

void Player::Update()
{
    // Update the frame rectangle to the current frame
    frameRec.x = (float)currentFrame * (float)currentTexture.width / numFrames;

    // Draw the player with the current texture and frame
    //DrawTextureRec(currentTexture, frameRec, playerPosition, WHITE);
}

void Player::Move()
{
    bool isMoving = false;

    if (IsKeyDown(KEY_D)) {
        playerPosition.x += speedX;
        isMoving = true;
        direction = RIGHT;
    }
    if (IsKeyDown(KEY_A)) {
        playerPosition.x -= speedX;
        isMoving = true;
        direction = LEFT;
    }
    if (IsKeyDown(KEY_W)) {
        playerPosition.y -= speedY;
        isMoving = true;
    }
    if (IsKeyDown(KEY_S)) {
        playerPosition.y += speedY;
        isMoving = true;
    }

    if (isMoving) {
        if (currentTexture.id != playerWalk.id) {
            currentTexture = playerWalk;
            numFrames = 6;
            frameWidth = playerWalk.width / numFrames;
        }

        ++framesCounter;

        if (framesCounter >= (60 / framesSpeed)) {
            framesCounter = 0;
            ++currentFrame;
            currentFrame %= numFrames;
            frameRec.x = (float)frameWidth * currentFrame;
        }
    } else {
        if (currentTexture.id != playerIdle.id) {
            currentTexture = playerIdle;
            numFrames = 4;
            frameWidth = playerIdle.width / numFrames;
        }

        ++framesCounter;

        if (framesCounter >= (60 / framesSpeed)) {
            framesCounter = 0;
            ++currentFrame;
            currentFrame %= numFrames;
            frameRec.x = (float)frameWidth * currentFrame;
        }
    }
}

void Player::Draw() const
{
    if (direction == RIGHT) {
        DrawTextureRec(currentTexture, frameRec, playerPosition, WHITE);
    } else {
        // Flip the texture horizontally for left direction
        Rectangle flippedFrameRec = frameRec;
        flippedFrameRec.width = -frameRec.width;
        DrawTextureRec(currentTexture, flippedFrameRec, playerPosition, WHITE);
    }
}