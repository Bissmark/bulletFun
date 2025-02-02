#include "blizzard.h"

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
    , castPosition({ 0, 0 })
{
}

void Blizzard::Update(const Player& player, std::vector<std::unique_ptr<Enemy>>& enemies, float deltaTime)
{
    if (isActive) {
        elapsedTime += deltaTime;

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
        }
    }
    else if (cooldownTime > 0.0f) {
        cooldownTime -= deltaTime; // Reduce cooldown
        if (cooldownTime < 0.0f) {
            cooldownTime = 0.0f;
        }
    }
}

void Blizzard::Activate()
{
    if (cooldownTime <= 0.0f) {
        isActive = true;
        elapsedTime = 0.0f;
    }
}

void Blizzard::SetCastPosition(Vector2 position)
{
    castPosition = position;
}

void Blizzard::Draw(const Player& player, const Camera2D& camera) const
{
    if (isActive) {
        Vector2 centerPositionCamera = GetWorldToScreen2D(castPosition, camera);
        DrawCircleLinesV(centerPositionCamera, radius, Fade(color, 0.5f));
    }
}

bool Blizzard::CheckCollision(const Player& player, Enemy& enemy)
{
    return CheckCollisionCircleRec(centerPosition, radius, enemy.GetBoundingBox());
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
