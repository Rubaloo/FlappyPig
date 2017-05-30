varying lowp vec4 DestinationColor;
precision highp float;

uniform float xPosition;
uniform float yPosition;
uniform float radius;

void main(void) {
    gl_FragColor = DestinationColor;
    float d2 = distance(gl_FragCoord.xy, vec2(xPosition, yPosition));
    if(d2 > radius) {
        discard;
    }
}
