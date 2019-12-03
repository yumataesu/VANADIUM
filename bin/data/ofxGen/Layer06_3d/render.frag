#version 330

uniform sampler2D u_tex;
uniform float u_time;
uniform float u_scale;
uniform float u_sp;
uniform float u_seed;
uniform float u_alpha;
uniform vec4 u_col;

in vec2 v_texcoord;
in vec4 v_world;

//out vec4 FragColor;

layout(location = 0) out vec4 fragColor;
layout(location = 1) out vec4 fragColor_world;

vec2 random2( vec2 p ) {
    return fract(sin(vec2(dot(p,vec2(127.1,311.7)),dot(p,vec2(269.5,183.3))))*43758.5453);
}


void main() {
    vec2 st = v_texcoord;
    st.y -= u_sp + u_seed;
    //st.x *= 1280.0 / 720.0;
    vec3 color = vec3(0.);

    // Scale
    st *= u_scale;
    //vec3 c = voronoi(st);
    
    vec2 n = floor(st);
    vec2 f = fract(st);

    // first pass: regular voronoi
    vec2 mg, mr, g, o;
    vec2 point = vec2(0.0);
    float md = 8.0;
    for (int j= -1; j <= 1; j++) {
        for (int i= -1; i <= 1; i++) {
            g = vec2(float(i),float(j));
            o = random2( n + g );
            o = 0.5 + 0.5*sin( u_time + 6.2831*o );

            vec2 r = g + o - f;
            float d = dot(r, r);

            if( d<md ) {
                md = d;
                mr = r;
                mg = g;
                point = o;
            }
        }
    }

    // second pass: distance to borders
    md = 8.0;
    for (int j= -2; j <= 2; j++) {
        for (int i= -2; i <= 2; i++) {
            vec2 g = mg + vec2(float(i),float(j));
            vec2 o = random2( n + g );
            o = 0.5 + 0.5*sin( u_time + 6.2831*o );

            vec2 r = g + o - f;

            if ( dot(mr-r,mr-r)>0.00001 ) {
                md = min(md, dot( 0.5*(mr+r), normalize(r-mr) ));
            }
        }
    }
    vec3 c = vec3(md, mr);
    

    // isolines
    //color = vec3(1.0);
    
    //color += dot(o, vec2(.0, 1.0));
    float fill_col = dot(point, vec2(0.3, 0.7));
    if(fill_col > 0.8) color += vec3(1.0);
    //color += vec3(mr.r, mr.g, mr.r);
    
    // borders
    color = mix( vec3(1.000, 1.0, 1.0), color, smoothstep( 0.01, 0.02, c.x ) );

    mat3 rot = mat3(
        cos(u_time*2), -sin(u_time*2), 0,
        sin(u_time*2), cos(u_time*2), 0,
        0, 0, 1
    );

    vec3 r = rot * vec3(mr, 0.0);
    vec3 eye = vec3(1.0) - texture(u_tex, r.rg).rgb;
    if(color.r < 0.1) discard;
    
    fragColor = vec4(eye * u_col.rgb, u_alpha);
    fragColor_world = vec4(v_world.xyz, 1);
}