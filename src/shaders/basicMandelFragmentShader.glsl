#version 330 core
out vec4 FragColor;

float MAX_ITERS = 100.0;
vec2 RES = vec2(800,800);

void main()
{   

    vec2 c = gl_FragCoord.xy/RES.xy;

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

    FragColor = vec4(iterations/MAX_ITERS, 1.0, 0.0, 1.0);

};