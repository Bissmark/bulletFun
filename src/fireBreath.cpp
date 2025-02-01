#include "fireBreath.h"
#include <raymath.h>
#include <cmath>

FireBreath::FireBreath(float width, float length, int speed, int baseDamage, Color color)
    : width(width), length(length), speed(speed), baseDamage(baseDamage), color(color), rotationAngle(0.0f), name("FireBreath"), elapsedTime(0.0f), maxSections(5), isActive(false)
{
    centerPosition = { 0.0f, 0.0f };
    numSections = 1; // Start with 1 beam
}

void FireBreath::Update(const Player& player, std::vector<std::unique_ptr<Enemy>>& enemies, float deltaTime)
{
    if (elapsedTime < 1.0f) { // Expand for 1 second
        elapsedTime += deltaTime * speed;
        numSections = 1 + static_cast<int>(elapsedTime * maxSections); // Gradually increase beams
    }

    if (numSections > maxSections) {
        isActive = false;
    }

    centerPosition = { player.playerPosition.x + player.frameRec.width / 2, player.playerPosition.y + player.frameRec.height / 2 };

    for (auto& enemy : enemies) {
        CheckCollision(player, *enemy);
    }
}

void FireBreath::Activate()
{
    if (cooldownTime <= 0.0f)
    {
        elapsedTime = 0.0f;
        numSections = 1;
        cooldownTime = cooldown;
        isActive = true;  // Set the FireBreath as active
    }
}

void FireBreath::Draw(const Player& player, const Camera2D& camera) const
{
    // Only draw the FireBreath if it is active
    if (!isActive)
        return;

    // Calculate the center of the player in screen space.
    Vector2 adjustedCenterPosition = {
        player.playerPosition.x + (player.frameRec.width * player.scale + 5.0f) / 2.0f,
        player.playerPosition.y + (player.frameRec.height * player.scale) / 2.0f
    };
    Vector2 screenPlayerPosition = GetWorldToScreen2D(adjustedCenterPosition, camera);

    // Get the player's facing angle (in degrees) and convert to radians.
    float playerAngle = player.GetFacingAngle(); // For example: 0° for right, 180° for left.
    float angleRad = playerAngle * DEG2RAD;

    // Determine the forward and perpendicular vectors.
    Vector2 forward = { cosf(angleRad), sinf(angleRad) };
    // Perpendicular vector: rotate forward by 90 degrees.
    Vector2 perpendicular = { -sinf(angleRad), cosf(angleRad) };

    // Optional: spacing between squares in the same row.
    float spacing = 0.0f; // Set to 0 if you want them directly adjacent.
    
    // Loop through each beam section (each row of the pyramid).
    // Assume numBeams indicates the total number of rows in the pyramid.
    for (int i = 0; i < numSections; ++i)
    {
        int squaresInRow = i + 1; // Row 0 has 1 square, row 1 has 2, etc.
        // The forward distance for this row.
        float forwardDistance = (i + 1) * length;

        // For each square in the current row.
        for (int j = 0; j < squaresInRow; ++j)
        {
            // Calculate a lateral offset.
            // This centers the row: if there are N squares, we want the middle square at offset 0.
            // The offset for each square is:
            float offset = (j - (squaresInRow - 1) / 2.0f) * (width + spacing);

            // Compute the final position:
            // Start at the player's center, move forward, then shift perpendicular by the offset.
            Vector2 squarePos = {
                screenPlayerPosition.x + forward.x * forwardDistance + perpendicular.x * offset,
                screenPlayerPosition.y + forward.y * forwardDistance + perpendicular.y * offset
            };

            // Draw the square. Using DrawRectanglePro, we rotate the rectangle to match the player's angle.
            DrawRectanglePro(
                { squarePos.x, squarePos.y, length, width },
                { length / 2, width / 2 },
                playerAngle,
                color
            );
        }
    }
}

bool FireBreath::CheckCollision(const Player& player, Enemy& enemy)
{
    for (int i = 0; i < numSections; ++i) {
        // Slightly spread the flames outward (optional, to create a cone)
        float angleOffset = ((i - (numSections / 2)) * 10.0f); // Adjust this for wider/narrower cones
        float angle = player.GetFacingAngle() + angleOffset;

        // Position the flames, making each subsequent flame slightly further ahead
        Vector2 forwardOffset = { cosf(angle * DEG2RAD) * (i * length), sinf(angle * DEG2RAD) * (i * length) };
        Vector2 beamPosition = Vector2Add(player.playerPosition, forwardOffset);

        // Check collision with enemy
        if (CheckCollisionPointRec(enemy.enemyPosition, { beamPosition.x, beamPosition.y, length, width })) {
            enemy.health -= baseDamage;
            if (enemy.health <= 0) {
                enemy.Destroy();
            }
            return true;
        }
    }
    return false;
}

float FireBreath::GetCooldownTime() const
{
    return cooldownTime;
}

float FireBreath::GetCooldownDuration() const
{
    return cooldown;
}

std::string FireBreath::GetName() const
{
    return name;
}
