varying lowp vec4 DestinationColor;
precision mediump float;

uniform float ScreenWidth;
uniform float ScreenHeight;
uniform float radius;

void main(void) {
    gl_FragColor = DestinationColor;
    
    vec2 center = vec2(ScreenWidth/2.0, ScreenHeight/2.0);
    float x = (gl_FragCoord.x - center.x);
    float y = (gl_FragCoord.y - center.y);
    float d = sqrt(x*x + y*y);
    if(d > radius) {
        discard;
    }
}
