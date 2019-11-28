#pragma once

#include <vector>

#include "StlTriangle.h"

class StlModel
{
public:
    const std::vector<StlTriangle>& GetTriangles() const { return triangles_; }

    void AddTriangle(StlTriangle&& triangle);

private:
    std::vector<StlTriangle> triangles_;
};

