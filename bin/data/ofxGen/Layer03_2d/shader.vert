#version 410

in vec3 position;
in vec2 texcoord;

out vec2 v_texcoord;

void main() {
    v_texcoord = texcoord;
    gl_Position = vec4(position, 1.0);
}