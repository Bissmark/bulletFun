#include "player.h"
#include "bullet.h"
#include <iostream>
#include <raymath.h>

Player::Player()
    : healthPoints(100)
    , speedX(5)
    , speedY(5)
    , radius(15)
    , boxCollision({ 0 })
{
    currentFrame = 0;

    framesCounter = 0;
    framesSpeed = 5;

    level = 1;
    experiencePoints = 0;
    maxExperiencePoints = 100;

    playerIdle = LoadTexture("src/Spritesheet/player/Idle.png");
    playerWalk = LoadTexture("src/Spritesheet/player/Walk.png");

    numFrames = 4;
    frameWidth = playerIdle.width / numFrames;

    currentTexture = playerIdle;

    frameRec = { 0.0f, 0.0f, (float)playerIdle.width / numFrames, (float)playerIdle.height };
    playerPosition = { (float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2 };
}

void Player::Update()
{
    frameRec.x = (float)currentFrame * (float)currentTexture.width / numFrames;

    for (auto& bullet : bullets) {
        bullet.Move();
    }

    LevelUp();
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
    } else {
        if (currentTexture.id != playerIdle.id) {
            currentTexture = playerIdle;
            numFrames = 4;
            frameWidth = playerIdle.width / numFrames;
        }
    }

    UpdateFrame();
}

void Player::UpdateFrame()
{
    ++framesCounter;

    if (framesCounter >= (60 / framesSpeed)) {
        framesCounter = 0;
        ++currentFrame;
        currentFrame %= numFrames;
        frameRec.x = (float)frameWidth * currentFrame;
    }
}

void Player::Fire(const Camera2D& camera)
{
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mousePosition = GetMousePosition();
        std::cout << "Mouse Position: (" << mousePosition.x << ", " << mousePosition.y << ")" << std::endl;

        // Convert player position to screen space
        Vector2 screenPlayerPosition = GetWorldToScreen2D(playerPosition, camera);
        std::cout << "Screen Player Position: (" << screenPlayerPosition.x << ", " << screenPlayerPosition.y << ")" << std::endl;

        Vector2 direction = Vector2Subtract(mousePosition, screenPlayerPosition);
        std::cout << "Direction: (" << direction.x << ", " << direction.y << ")" << std::endl;
        direction = Vector2Normalize(direction);
        bullets.push_back(Bullet(playerPosition, direction, 5, BLUE));
    }
}

void Player::LevelUp()
{
    if (experiencePoints >= maxExperiencePoints) {
        experiencePoints = 0;
        maxExperiencePoints *= 2;
        level++;
    }
}

void Player::Draw() const
{
    if (direction == RIGHT) {
        DrawTextureRec(currentTexture, frameRec, playerPosition, WHITE);
    } else {
        // Flip the texture horizontally
        Rectangle flippedFrameRec = frameRec;
        flippedFrameRec.width = -frameRec.width;
        DrawTextureRec(currentTexture, flippedFrameRec, playerPosition, WHITE);
    }

    for (auto& bullet : bullets) {
        bullet.Draw();
    }
}

void Player::DrawExp() const
{
    float expPercentage = (float)experiencePoints / maxExperiencePoints;
    float barWidth = 650.0f;
    float barHeight = 15.0f;
    Vector2 barPosition = { GetScreenWidth() / 10.0f, GetScreenHeight() - 40.0f };

    // Draw background of the exp bar
    DrawRectangle(barPosition.x, barPosition.y, barWidth, barHeight, GRAY);

    // Draw the exp bar
    DrawRectangle(barPosition.x, barPosition.y, barWidth * expPercentage, barHeight, GOLD);
}