#version 330 core

uniform float time;
uniform vec2 resolution;   
uniform sampler2D backgroundTex;
uniform float textureScale;

/*
* uv - horizontal texture coordinates
* frequency - number of waves
* amplitude - wave height
* speed - wave speed
* phase - wave phase 
*/
float wave(float x, float frequency, float amplitude, float speed, float phase) {
    return sin(x * frequency + time * speed + phase) * amplitude;
}

void main() {
    vec2 uv = gl_FragCoord.xy / resolution.xy; 

    uv.y = 1.0 - uv.y;

    uv.x *= resolution.x / resolution.y;

    //uv.x *= resolution.x;
    //uv.y *= resolution.y;
    
    float y = 0.0;
    y += wave(uv.x, 10.0, 0.015, 2.0, 0.0); 
    y += wave(uv.x, 15.0, 0.01, 3.0, 1.0);
    y += wave(uv.x, 20.0, 0.005, 1.5, 2.0);
    

    vec3 color = vec3(0.0, 0.3, 0.6);

    if (uv.y < 0.5 + y) {
        vec2 texCoord = uv * textureScale;
        color = texture(backgroundTex, texCoord).rgb;
    }

    if (uv.y > 0.5 + y) {
        vec3 waveColor = vec3(0.25, 0.75, 0.75) * 0.6;
        color = mix(color, waveColor, 0.6);
    }

    gl_FragColor = vec4(color, 1.0);
}
