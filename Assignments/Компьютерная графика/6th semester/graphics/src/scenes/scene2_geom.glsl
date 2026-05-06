#version 330 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in vec3 v_position[];
in vec4 v_color[];

out vec3 g_position;
out vec3 g_normal;
out vec4 g_color;

uniform mat4 projection;

void main() {
    vec3 edge1 = v_position[1] - v_position[0];
    vec3 edge2 = v_position[2] - v_position[0];

    vec3 normal = normalize(cross(edge1, edge2));

    for(int i = 0; i < 3; i++) {
        gl_Position = projection * gl_in[i].gl_Position;
        g_position = v_position[i];
        g_color = v_color[i];
        g_normal = normal;

        EmitVertex();
    }
    EndPrimitive();
}
