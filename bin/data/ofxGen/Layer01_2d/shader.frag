#version 410

uniform float u_alpha;
uniform float u_time;
uniform float num;
uniform vec2 u_grid;
uniform int u_swap;
uniform sampler2D u_tex;

in vec2 v_texcoord;

out vec4 fragcolor;

float random (in float x) {
    return fract(sin(x)*1e4);
}

float random (in vec2 st) {
    return fract(sin(dot(st.xy, vec2(12.9898,78.233)))* 43758.5453123);
}

float pattern(vec2 st, vec2 v, float t) {
    vec2 p = floor(st+v);
    return step(t, random(100.+p*.001)+random(p.x)*0.5);
}


void main (void) {
    vec2 st = v_texcoord;
    vec2 grid = vec2(40.0, 50.);
    st *= u_grid;

    vec2 ipos = floor(st);  // integer
    vec2 fpos = fract(st);  // fraction

    vec2 vel = vec2(u_time * max(grid.x, grid.y)); // time
    vel *= vec2(0., 1.0) * random(1.0 + ipos.y); // direction

    // Assign a random value base on the integer coord
    vec2 offset = vec2(0.02,0.);

    vec3 color = vec3(0.);
    color.r = pattern(st+offset,vel,0.5+num);
    color.g = pattern(st,vel,0.5+num);
    color.b = pattern(st-offset,vel,0.5+num);

    // Margins
    color *= step(0.04, fpos.y);

    fragcolor = vec4(color, 1.0);
}