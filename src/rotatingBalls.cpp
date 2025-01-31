#include "rotatingBalls.h"
#include <cmath>

RotatingBalls::RotatingBalls(float cooldown, float radius, float speed, int numBalls)
    : cooldown(cooldown)
    , cooldownTime(0.0f)
    , radius(radius)
    , speed(speed)
    , numBalls(numBalls)
    , isActive(false)
    , name("Rotating Balls")
{
    balls.resize(numBalls);
    for (int i = 0; i < numBalls; ++i)
    {
        balls[i].isActive = true;
    }
}

void RotatingBalls::Update(const Player& player, std::vector<std::unique_ptr<Enemy>>& enemies, float deltaTime)
{
    if (cooldownTime > 0.0f)
    {
        cooldownTime -= deltaTime;
    }

    if (isActive)
    {
        for (int i = 0; i < numBalls; ++i)
        {
            if (balls[i].isActive)
            {
                // Update ball position to rotate around the player
                float angle = (2 * PI / numBalls) * i + GetTime() * speed;
                balls[i].position = { player.playerPosition.x + radius * cos(angle), player.playerPosition.y + radius * sin(angle) };

                // If the skill is activated, shoot the balls outward
                if (IsKeyPressed(KEY_SPACE)) // Replace with the appropriate key or button press
                {
                    balls[i].velocity = { cos(angle) * speed, sin(angle) * speed };
                    balls[i].isActive = false;
                }
            }
        }
    }
}

void RotatingBalls::Activate()
{
    if (cooldownTime <= 0.0f)
    {
        isActive = true;
        cooldownTime = cooldown;
        for (int i = 0; i < numBalls; ++i)
        {
            balls[i].isActive = true;
            balls[i].velocity = { 0.0f, 0.0f };
        }
    }
}

void RotatingBalls::Draw(const Player& player, const Camera2D& camera) const
{
    if (isActive)
    {
        for (const auto& ball : balls)
        {
            if (ball.isActive)
            {
                DrawCircleV(ball.position, 5.0f, RED); // Draw the ball
            }
        }
    }
}

bool RotatingBalls::CheckCollision(const Player& player, Enemy& enemy)
{
    for (const auto& ball : balls)
    {
        if (CheckCollisionCircles(ball.position, 5.0f, enemy.enemyPosition, enemy.radius))
        {
            return true;
        }
    }
    return false;
}

float RotatingBalls::GetCooldownTime() const
{
    return cooldownTime;
}

float RotatingBalls::GetCooldownDuration() const
{
    return cooldown;
}

std::string RotatingBalls::GetName() const
{
    return name;
}