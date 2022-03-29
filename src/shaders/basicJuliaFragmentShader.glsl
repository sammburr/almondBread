#version 330 core
layout(location = 0) out vec3 color;

uniform vec2 screenSize;
uniform float scale;
uniform vec2 displacment;
uniform vec2 juliaPoint;
uniform float MAX_ITERS;

void main()
{   

    vec2 c = gl_FragCoord.xy/(screenSize.xy/scale)- (displacment * scale);

    float iterations = 0.0;
    
    float x = 0;
    float y = 0;

    float x2,y2;

    x = c.x;
    y = c.y;
    x2 = c.x * c.x;
    y2 = c.y * c.y;

    c = juliaPoint;

    while (iterations <= MAX_ITERS && x2 + y2 <= 4.0)
    {

        y = 2 * x * y + c.y;
        x = x2 - y2 + c.x;
        x2 = x * x;
        y2 = y * y;

        iterations = iterations + 1.0;

    }

    color = vec3(iterations/MAX_ITERS, 0.5, 1.0);

};