#version 330 core
layout(location = 0) out vec3 color;

uniform vec2 screenSize;
uniform float scale;
uniform vec2 displacment;
uniform vec2 juliaPoint;
uniform float MAX_ITERS;

float map(float value, float in_min, float in_max, float out_min, float out_max)
{

    return ((value - in_min)*(out_max-out_min)/(in_max-in_min)+out_min);

}

void main()
{   

    vec2 screenCoords = gl_FragCoord.xy/screenSize.xy;

    float a = map(screenCoords.x, 0.0, 1.0, -2.0/scale, 2.0/scale) + (displacment.x);
    float b = map(screenCoords.y, 0.0, 1.0, -2.0/scale, 2.0/scale) + (displacment.y);

    vec2 c = vec2(a,b);

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

    if(iterations >= MAX_ITERS - 1)
    {
        color = vec3(0.954, 1, 0);
    }
    else
    {
        color = vec3(0,iterations/MAX_ITERS, iterations/MAX_ITERS);
    }


};