#pragma once

#include <vector>

#include "Coord3.h"
#include "FaceVertex.h"

class ObjModel
{
public:
    const std::vector<Coord3>& GetVertices() const { return vertices_; }
    const std::vector<Coord3>& GetNorms() const { return norms_; }

    void AddVertex(Coord3&& v);
    void AddNorm(Coord3&& n);
    void AddFace(const std::vector<FaceVertex>& face);

private:
    std::vector<Coord3> vertices_;
    std::vector<Coord3> norms_;

    std::vector<std::vector<FaceVertex>> faces_;
};
