#version 410

uniform sampler2D u_src;
uniform vec4 u_col;
uniform float u_alpha;

in vec2 v_texcoord;
in vec4 v_world;

layout(location = 0) out vec4 fragColor;
layout(location = 1) out vec4 fragColor_world;

void main() {
    vec2 st = v_texcoord;
    vec3 col = texture(u_src, v_texcoord).rgb;
    
    fragColor = vec4(u_col.rgb * col.rgb, u_alpha);
    fragColor_world = vec4(v_world.xyz, 1);
}