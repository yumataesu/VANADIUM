#version 430

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

in vec4 position;
in vec2 texcoord;

out vec2 v_texcoord;
out vec4 v_world;

void main() {
    v_texcoord = texcoord;
    v_world = view * model * vec4(position.xyz, 1.0);
    gl_Position = projection * view * model * vec4(position.xyz, 1.0);
}