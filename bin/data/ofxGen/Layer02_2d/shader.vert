#version 330
in vec3 position;
in vec2 texcoord;

out vec2 v_texcoord;

void main() {
    v_texcoord = vec2(texcoord.x, texcoord.y);
    gl_Position = vec4(position, 1.0);
}