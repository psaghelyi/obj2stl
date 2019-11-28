#pragma once

#include "ObjModel.h"
#include "StlModel.h"

#include <vector>

struct Coord6
{
    Coord6(const Coord3& vt, const Coord3& vn) 
        : x(vt.x), y(vt.y), z(vt.z), 
          i(vn.x), j(vn.y), k(vn.z) 
    {}

    float x, y, z;
    float i, j, k;
};

class Converter
{
public:
    void Convert(const ObjModel& objModel, StlModel& stlModel);

private:
    std::vector<std::vector<Coord6>> faces_;    // list of faces -> list of coordinate pairs (vertex, norm)

    std::vector<StlTriangle> triangles_;

};

