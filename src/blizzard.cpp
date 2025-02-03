#include "blizzard.h"
#include <iostream>

Blizzard::Blizzard(float radius, int speed, int baseDamage, Color color)
    : radius(radius)
    , speed(speed)
    , baseDamage(baseDamage)
    , color(color)
    , cooldown(5.0f)
    , cooldownTime(0.0f)
    , elapsedTime(0.0f)
    , activeTime(3.0f)
    , isActive(false)
    , name("Blizzard")
{
    blizzardShader = LoadShader(0, "shaders/blizzard.fs");

    if (blizzardShader.id == 0) {
        std::cout << "Failed to load Blizzard shader!" << std::endl;
    }
}

void Blizzard::Update(const Player& player, std::vector<std::unique_ptr<Enemy>>& enemies, float deltaTime)
{
    if (isActive) {
        elapsedTime += deltaTime;
        blizzardTime -= deltaTime * speed;

        // Apply damage if active
        for (auto& enemy : enemies) {
            if (CheckCollision(player, *enemy)) {
                enemy->health -= baseDamage;
                if (enemy->health <= 0) {
                    enemy->Destroy();
                }
            }
        }

        // Deactivate after activeTime expires
        if (elapsedTime >= activeTime) {
            isActive = false;
            cooldownTime = cooldown;  // Start cooldown
            elapsedTime = 0.0f;       // Reset timer
            blizzardTime = 0.0f;     // Reset timer
            positionSet = false;
        }
    }
    else if (cooldownTime > 0.0f) {
        cooldownTime -= deltaTime; // Reduce cooldown
        if (cooldownTime < 0.0f) {
            cooldownTime = 0.0f;
        }
    }
}

void Blizzard::Activate(Vector2 playerPosition)
{
    if (cooldownTime <= 0.0f) {
        isActive = true;
        elapsedTime = 0.0f;
        blizzardTime = 0.0f;
        positionSet = false;
        
        castPosition = playerPosition;
    }
}

void Blizzard::Activate()
{
    std::cout << "Blizzard requires a position to activate!\n";
}

void Blizzard::Draw(const Player& player, const Camera2D& camera) const
{
    if (isActive) {
        Vector2 screenPosition = GetWorldToScreen2D(castPosition, camera);
        std::cout << "Screen position: " << screenPosition.x << ", " << screenPosition.y << std::endl;

        // Pass data to the shader
        SetShaderValue(blizzardShader, GetShaderLocation(blizzardShader, "u_center"), &screenPosition, SHADER_UNIFORM_VEC2);
        SetShaderValue(blizzardShader, GetShaderLocation(blizzardShader, "u_radius"), &radius, SHADER_UNIFORM_FLOAT);
        SetShaderValue(blizzardShader, GetShaderLocation(blizzardShader, "u_time"), &blizzardTime, SHADER_UNIFORM_FLOAT);

        BeginShaderMode(blizzardShader);
        DrawCircleV(screenPosition, radius, Fade(color, 0.2f)); // Base Blizzard effect
        EndShaderMode();
    }
}

bool Blizzard::CheckCollision(const Player& player, Enemy& enemy)
{
    return CheckCollisionCircleRec(castPosition, radius, enemy.GetBoundingBox());
}

float Blizzard::GetCooldownTime() const
{
    return cooldownTime;
}

float Blizzard::GetCooldownDuration() const
{
    return cooldown;
}

std::string Blizzard::GetName() const
{
    return name;
}

int Blizzard::GetDamage() const
{
    return baseDamage;
}
