varying lowp vec4 DestinationColor;
precision mediump float;

void main(void) {
    gl_FragColor = DestinationColor;// New
    float x = (gl_FragCoord.x - 0.5);
    float y = (gl_FragCoord.y - 0.5);
    float z = (gl_FragCoord.z - 0.5);
    float d = sqrt(x*x + y*y + z*z);
    if(d > 330.0) {
        discard;
    }
}
