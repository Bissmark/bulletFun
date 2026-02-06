#version 330

in vec2 vertexPosition;  // Vertex positions in world space
uniform mat4 u_camera;   // Camera matrix

out vec2 fragWorldPos;   // Pass the transformed position to fragment shader

void main()
{
    // Transform the vertex position into camera space
    fragWorldPos = (u_camera * vec4(vertexPosition, 0.0, 1.0)).xy;
    gl_Position = vec4(vertexPosition, 0.0, 1.0);  // Keep the original world position for the fragment shader
}
