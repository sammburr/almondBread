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

    while (iterations <= MAX_ITERS && x2 + y2 <= 4.0)
    {

        y = 2 * x * y + c.y;
        x = x2 - y2 + c.x;
        x2 = x * x;
        y2 = y * y;

        iterations = iterations + 1.0;

    }

    if(juliaPoint.x + ( 0.01 * scale ) >= c.x && juliaPoint.y + ( 0.01 * scale ) >= c.y && juliaPoint.x - ( 0.01 * scale ) <= c.x && juliaPoint.y - ( 0.01 * scale ) <= c.y)
    {
        color = vec3(1.0, 0.0, 0.0);
    }   
    else
    {
        color = vec3(iterations/MAX_ITERS, 1.0, 1.0);
    }

};