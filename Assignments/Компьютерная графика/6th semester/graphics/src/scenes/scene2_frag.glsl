#version 430

in vec3 g_position;
in vec3 g_normal;
in vec4 g_color;

out vec4 color;

uniform vec3 light_direction;

const vec3 ambient_color = vec3(0.2, 0.2, 0.2);
const vec3 diffuse_color = vec3(0.5, 0.5, 0.5);
const vec3 specular_color = vec3(1.0, 1.0, 1.0);

void main() {
    float diffuse = max(dot(normalize(g_normal), normalize(light_direction)), 0.0);

    vec3 camera_dir = normalize(-g_position);
    vec3 half_direction = normalize(normalize(light_direction) + camera_dir);
    // float specular = pow(max(dot(half_direction, normalize(g_normal)), 0.0), 16.0);
    // vec4 lighting_color = vec4(ambient_color + diffuse * diffuse_color + specular * specular_color, 1.0);
    vec4 lighting_color = vec4(ambient_color + diffuse * diffuse_color, 1.0);

    color = g_color * lighting_color;
}
