#pragma once

#include "ObjModel.h"
#include "StlModel.h"

#include <vector>

class Converter
{
public:
    void Convert(const ObjModel& objModel, StlModel& stlModel);

    Coord3TR& GetTrMatrix() { return trMatix_ ; }

private:
    std::vector<std::vector<Coord3N>> polygons_;    // list of faces -> list of coordinate pairs (vertex, norm)
    std::vector<std::vector<Coord3>> triangles_;  // list of faces -> 3 * coordinates + 1 optional normal vector

    Coord3TR trMatix_;

    void CreatePolygonsWithNorms(const std::vector<FaceVertex>& faceVertices, const std::vector<Coord3>& objVertices, const std::vector<Coord3>& objNorms);
    void CreateTrianglesWithNorms(const std::vector<Coord3N>& poly);
};



