#include "../include/obj2stl/StlModel.h"

void StlModel::AddTriangle(const StlTriangle& triangle)
{
    triangles_.push_back(triangle);
}
