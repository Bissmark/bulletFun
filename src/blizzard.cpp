#include "blizzard.h"
#include <iostream>
#include "raymath.h"

Blizzard::Blizzard(float radius, int speed, int baseDamage, Color color, Player& player)
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
    , positionSet(false)
{
    blizzardShader = LoadShader(0, "shaders/blizzard.fs");

    if (blizzardShader.id == 0) {
        std::cout << "Failed to load Blizzard shader!" << std::endl;
    }

    //castPosition = player.playerPosition;
}

void Blizzard::Update(const Player& player, std::vector<std::unique_ptr<Enemy>>& enemies, float deltaTime)
{
    if (isActive) {
        elapsedTime += deltaTime;
        blizzardTime += deltaTime * speed;

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

void DrawQuad(Vector2 topLeft, Vector2 topRight, Vector2 bottomLeft, Vector2 bottomRight, Color color)
{
    // Define the two triangles making up the quad
    Vector2 vertices[4] = { topLeft, topRight, bottomLeft, bottomRight };

    // Draw the quad as a triangle strip
    DrawTriangleStrip(vertices, 4, color);
}


// void Blizzard::Draw(const Player& player, const Camera2D& camera)
// {
//     if (isActive)
//     {
//         Vector2 screenPlayerPosition = GetWorldToScreen2D(castPosition, camera);
//         Vector2 worldCenter = castPosition;  
//         Matrix cameraMat = GetCameraMatrix2D(camera);

//         // Pass uniforms to the shader.
//         SetShaderValue(blizzardShader, GetShaderLocation(blizzardShader, "u_center"), &screenPlayerPosition, SHADER_UNIFORM_VEC2);
//         //SetShaderValueMatrix(blizzardShader, GetShaderLocation(blizzardShader, "u_camera"), cameraMat);
//         SetShaderValue(blizzardShader, GetShaderLocation(blizzardShader, "u_radius"), &radius, SHADER_UNIFORM_FLOAT);
//         SetShaderValue(blizzardShader, GetShaderLocation(blizzardShader, "u_time"), &blizzardTime, SHADER_UNIFORM_FLOAT);

//         BeginMode2D(camera);

//             // First, draw the Blizzard circle in world space

//             // Now, render the particle effects by drawing the Blizzard area as a quad
//             BeginShaderMode(blizzardShader);
//                 //DrawCircleV(castPosition, radius, Fade(color, 0.2f));
//             EndShaderMode();

//         EndMode2D();
//     }
// }

void Blizzard::Draw(const Player& player, const Camera2D& camera)
{
    if (isActive)
    {
        BeginMode2D(camera);

        // Pass uniforms to the shader
        Vector2 worldCenter = castPosition;
        Matrix cameraMat = GetCameraMatrix2D(camera);

        SetShaderValue(blizzardShader, GetShaderLocation(blizzardShader, "u_center"), &worldCenter, SHADER_UNIFORM_VEC2);
        SetShaderValueMatrix(blizzardShader, GetShaderLocation(blizzardShader, "u_camera"), cameraMat);
        SetShaderValue(blizzardShader, GetShaderLocation(blizzardShader, "u_radius"), &radius, SHADER_UNIFORM_FLOAT);
        SetShaderValue(blizzardShader, GetShaderLocation(blizzardShader, "u_time"), &blizzardTime, SHADER_UNIFORM_FLOAT);

        // Begin shader
        //BeginShaderMode(blizzardShader);

        // Draw a circle using a triangle fan
        const int segments = 40;  // More segments = smoother circle
        Vector2 vertices[segments + 2];
        vertices[0] = castPosition; // Center of the circle

        for (int i = 0; i <= segments; i++)
        {
            float angle = (2.0f * PI * i) / segments;
            vertices[i + 1] = {
                castPosition.x + cos(angle) * radius,
                castPosition.y + sin(angle) * radius
            };
        }

        DrawTriangleFan(vertices, segments + 2, WHITE);

        //EndShaderMode();

        EndMode2D();
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
