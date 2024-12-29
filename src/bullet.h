#include "raylib.h"

class Bullet {
    public:
        Vector2 position;
        float speed;
        Color color;
        Bullet(Vector2 position, float speed, Color color);
        void Move();
        void Draw() const;


};