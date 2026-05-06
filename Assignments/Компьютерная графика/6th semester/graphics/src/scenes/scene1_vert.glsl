#version 430

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec4 color;

out vec3 v_normal;
out vec3 v_position;
out vec4 v_color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    gl_Position = projection * view * model * vec4(position, 1.0);
    v_position = gl_Position.xyz / gl_Position.w;
    v_normal = mat3(transpose(inverse(model))) * normal;
    v_color = color;
}
