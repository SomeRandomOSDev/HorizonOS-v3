#pragma once

double floor(double x)
{
    int _x = (int)x;
    return (double)_x;
}

double ceil(double x)
{
    double floorX = floor(x);

    if(x == floorX)
        return x;

    return floorX + 1;
}

double fabs(double x)
{
    return (x < 0) ? -x : x;
}

double fmod(double x, double y) // Unsure
{
    while(x >= y)
        x -= y;

    return x;
}