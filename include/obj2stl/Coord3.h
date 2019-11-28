#pragma once

class Coord3
{
public:
    Coord3(float x, float y, float z) : x_(x), y_(y), z_(z) {}
    Coord3() : Coord3(0., 0., 0.) {}

    static Coord3 GetNormalVect(const Coord3& p1, const Coord3& p2, const Coord3& p3);

private:
    float x_;
    float y_;
    float z_;
}; 