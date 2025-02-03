#version 330

uniform vec2 u_center;  // Center of the Blizzard in screen space
uniform float u_radius; // Blizzard's radius
uniform float u_time;   // Time for animation

out vec4 fragColor; // Output fragment color

// Pseudo-random function
float rand(vec2 co) {
    return fract(sin(dot(co.xy, vec2(12.9898, 78.233))) * 43758.5453);
}

void main()
{
    vec2 uv = gl_FragCoord.xy; // Get screen position
    float dist = distance(uv, u_center);  // Distance from the center

    // Default background: Blizzard mist
    fragColor = vec4(0.5, 0.6, 1.0, 0.1); // Blizzard mist 

    // Parameters for snowflakes
    float numFlakes = 200.0;   // Number of flakes
    float speed = 50.0;        // Falling speed

    // Loop over flakes
    for (float i = 0.0; i < numFlakes; i++) {
        // Use fixed random offsets, independent of player movement
        float offsetX = rand(vec2(i * 1.0, 0.0));  // Ensure randomness is consistent
        float offsetY = rand(vec2(i * 2.3, 1.0));  // Ensure randomness is consistent

        // Calculate flake position relative to the Blizzard's center
        float x = (offsetX - 0.5) * u_radius * 2.0;  // Horizontal spread based on Blizzard's radius
        float y = mod(offsetY * u_radius * 2.0 + u_time * speed, u_radius * 2.0) - u_radius; // Falling motion
        vec2 flakePos = u_center + vec2(x, y);  // Final position of the snowflake

        // If this pixel is close to a snowflake, color it white
        if (distance(uv, flakePos) < 1.5) {  
            fragColor = vec4(1.0, 1.0, 1.0, 1.0);  // White flake
            return; // Exit immediately if a snowflake is found
        }
    }
}
