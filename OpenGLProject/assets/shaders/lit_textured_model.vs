#version 450 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normal;

out vec2 TexCoord;
out vec3 Normal;
out vec3 FragWorldPos;

uniform mat4 view_projection;
uniform mat4 model;

void main() {
    gl_Position = view_projection * model * vec4(position, 1.0);
    TexCoord = texCoord;
    FragWorldPos = vec3(model * vec4(position, 1.0));
    Normal = mat3(transpose(inverse(model))) * normal;
}