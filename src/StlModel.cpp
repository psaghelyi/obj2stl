#include "..\include\obj2stl\StlModel.h"

void StlModel::AddTriangle(StlTriangle&& triangle)
{
    triangles_.push_back(triangle);
}
