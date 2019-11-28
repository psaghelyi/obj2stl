#pragma once

#include "ObjModel.h"
#include "StlModel.h"

#include <vector>

struct Coord6
{
    Coord6(const Coord3& vt, const Coord3& vn) : vt(vt), vn(vn) {}

    Coord3 vt;
    Coord3 vn;
};

class Converter
{
public:
    void Convert(const ObjModel& objModel, StlModel& stlModel);

private:
    std::vector<std::vector<Coord6>> polygons_;    // list of faces -> list of coordinate pairs (vertex, norm)
    std::vector<std::vector<Coord3>> triangles_;

    void CreatePolygonsWithNorms(const std::vector<FaceVertex>& faceVertices, const std::vector<Coord3>& objVertices, const std::vector<Coord3>& objNorms);
    void CreateTrianglesWithNorms(const std::vector<Coord6>& poly);
};



