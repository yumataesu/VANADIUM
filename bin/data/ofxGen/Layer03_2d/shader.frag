#version 330

// author: Genco Levi // sporadiclizard
// shadertoy: https://www.shadertoy.com/view/MtcBzH

uniform float u_time;
uniform float u_alpha;
uniform vec2 u_point;
uniform vec2 u_resolution;

in vec2 v_texcoord;

out vec4 fragcolor;

// ******** TOGGLES 0 / 1 **************** // 
const int SWIRL_OSC = 0;
const int ONE_OSC 	= 0;
// ******** TOGGLES 0 / 1 **************** // 

////////////////////////////////////////

// 2*pi
#define TAU 6.283185307179
 
vec2 cxmul(vec2 z, vec2 w) {
    return mat2(z, -z.y, z.x) * w; //vec2(z.x*w.x - z.y*w.y, z.x*w.y + z.y*w.x);
}

vec2 cxdiv(vec2 z, vec2 w) {
    return cxmul(z, vec2(w.x, -w.y)) / dot(w,w);
}

vec2 mobius(vec2 z, vec2 a, vec2 b, vec2 c, vec2 d) {
    return cxdiv(cxmul(a,z) + b, cxmul(c,z) + d); 
}

// mobius transformation described with which complex numbers 
// it sends zero, one and infinity to.
// 0 -> q, 1 -> r, inf -> s
vec2 mobi3(vec2 z, vec2 q, vec2 r, vec2 s) {
    return cxdiv(cxmul(z - q, r - s), cxmul(z - s, r - q));
}


void main (void) {

    //vec2 u_resolution = vec2(960, 540);

    vec2 mnuv = v_texcoord;
    vec2 mn = (2. * u_point.xy - u_resolution.xy) / u_resolution.y;
    
    vec2 pos = ( 2. * gl_FragCoord.xy - u_resolution.xy ) / u_resolution.y; 
    
    // mouse control! 
    vec2 inf = mn;
    vec2 zero = -inf;

    vec2 one = vec2(0.);
    if (ONE_OSC==1) {
    	float t = sin(u_time*0.912)*0.3 + 0.5;
    	one = t*inf + (1.-t)*zero;
    } else {
    	one =  (inf + zero) * 0.5;
    }
    
    // mobius transformed position - deforms the plane 
    vec2 posi = mobi3(pos, zero, one, inf);
    
    float logr = log(length(posi));
    
    float swirl = 0.;
    // 2 positive turns at infinity, 2 negative turns at zero  
    swirl = 2.*TAU*atan(logr);
    
    // add in the swirl
    float ang = atan(posi.y,posi.x) + swirl;
            
    // RGB offset
    const float offset = TAU*0.1;
    vec3 offsetv = vec3(-offset,0.,offset);
    
    vec3 colVal = sin(ang*2.+ u_time*5. + offsetv);

        // smooth colors mode
    vec3 smoothCol = colVal * 0.5 + 0.5;
    
    // antialiased solid colors mode 
    vec3 b = fwidth(colVal);
    vec3 col_aa = smoothstep(vec3(-b), vec3(b), colVal); 
    
    // switch modes
    vec3 col = mix(col_aa, smoothCol, 0.5);//floor(mod(u_time*0.5,2.)));

    fragcolor = vec4(col, 1);
}
