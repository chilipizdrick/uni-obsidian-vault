#version 430

in vec3 v_position;
in vec3 v_world_position;
in vec3 v_normal;
in vec2 v_tex_coords;

out vec4 color;

uniform vec3 directional_light_direction;
uniform vec3 camera_position;
uniform sampler2D tex;
uniform vec3 s_position;
uniform vec3 s_direction;
uniform float s_cut_off;
uniform float s_outer_cut_off;

const vec3 s_diffuse = vec3(0.5);
const vec3 s_specular = vec3(1.0);
const float distance_constant = 0.001;
const float k = 0.1;
const vec3 ambient_color = vec3(0.1);
const vec3 diffuse_color = vec3(0.5);
const vec3 specular_color = vec3(1.0);

vec3 directional_light_color(vec3 normal, vec3 position) {

    float diffuse = max(dot(normalize(normal), normalize(directional_light_direction)), 0.0);

    vec3 camera_dir = normalize(-position);
    vec3 half_direction = normalize(normalize(directional_light_direction) + camera_dir);
    float specular = pow(max(dot(half_direction, normalize(normal)), 0.0), 16.0);

    return ambient_color + diffuse * diffuse_color + specular * specular_color;
}

vec3 spotlight_light_color(vec3 normal, vec3 world_pos) {
    vec3 view_dir = normalize(camera_position - world_pos);
    vec3 light_dir = normalize(s_position - world_pos);

    float theta = dot(light_dir, normalize(-s_direction));
    float epsilon = s_cut_off - s_outer_cut_off;
    float intensity = clamp((theta - s_outer_cut_off) / epsilon, 0.0, 1.0);

    float diff = max(dot(normal, light_dir), 0.0);
    vec3 reflect_dir = reflect(-light_dir, normal);
    float spec = pow(max(dot(view_dir, reflect_dir), 0.0), 16.0);

    float distance = length(s_position - world_pos);
    float attenuation = 1.0 / (k + distance_constant * distance * distance);

    vec3 diffuse = s_diffuse * diff * attenuation * intensity;
    vec3 specular = s_specular * spec * attenuation * intensity;

    return diffuse + specular;
}

void main() {
    vec3 lighting_color = directional_light_color(v_normal, v_position);
    lighting_color += spotlight_light_color(v_normal, v_world_position);

    vec4 tex_color = texture(tex, v_tex_coords);

    color = tex_color * vec4(lighting_color, 1.0);
}
