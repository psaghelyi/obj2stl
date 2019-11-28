#pragma once

struct Coord3
{
    Coord3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
    Coord3() : Coord3(0., 0., 0.) {}

    static Coord3 GetNormalVect(const Coord3& p1, const Coord3& p2, const Coord3& p3);

    float x;
    float y;
    float z;
}; 