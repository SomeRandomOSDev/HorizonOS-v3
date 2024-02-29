#pragma once

float floor(float x)
{
    int _x = (int)x;
    return (float)_x;
}

float ceil(float x)
{
    float floorX = floor(x);

    if(x == floorX)
        return x;

    return floorX + 1;
}