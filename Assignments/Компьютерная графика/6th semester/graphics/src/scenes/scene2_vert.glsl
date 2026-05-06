#version 430

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;

out vec3 v_position;
out vec3 v_normal;
out vec4 v_color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    v_position = vec3(model * vec4(position, 1.0));
    gl_Position = view * vec4(v_position, 1.0);
    v_color = color;
}
