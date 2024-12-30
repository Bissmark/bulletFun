#pragma once
#include <raylib.h>

class Background
{
    public:
        Background();
        void Draw() const;
        void Update(Vector2 playerPosition);
        void Unload();

    private:
        Texture2D background;
        int screenWidth;
        int screenHeight;
        Vector2 position1;
        Vector2 position2;
};