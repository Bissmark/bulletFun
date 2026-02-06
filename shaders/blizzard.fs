#version 330

uniform vec2 u_center;  // Blizzard center in world space
uniform float u_radius; // Blizzard radius
uniform float u_time;   // Time for animation

in vec2 fragWorldPos;   // World-space position passed from vertex shader
out vec4 fragColor;     // Output fragment color

// Pseudo-random function
float rand(vec2 co) {
    return fract(sin(dot(co.xy, vec2(12.9898, 78.233))) * 43758.5453);
}

void main()
{
    float dist = distance(fragWorldPos, u_center);

    // Discard pixels outside the Blizzard circle
    if (dist > u_radius) {
        discard;
    }

    // Default Blizzard mist color
    fragColor = vec4(0.5, 0.6, 1.0, 0.1);

    // Snowflake animation parameters
    float numFlakes = 200.0;
    float speed = 50.0;

    // Generate snowflakes inside the Blizzard circle
    for (float i = 0.0; i < numFlakes; i++) {
        float offsetX = rand(vec2(i * 1.0, 0.0));
        float offsetY = rand(vec2(i * 2.3, 1.0));

        float x = (offsetX - 0.5) * u_radius * 2.0;  // Generate positions within the radius
        float y = mod(offsetY * u_radius * 2.0 + u_time * speed, u_radius * 2.0) - u_radius;
        vec2 flakePos = u_center + vec2(x, y);

        if (distance(fragWorldPos, flakePos) < 1.5) {  
            fragColor = vec4(1.0, 1.0, 1.0, 1.0);  // White snowflake
            return;
        }
    }
}
