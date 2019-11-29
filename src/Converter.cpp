#include "../include/obj2stl/Converter.h"
#include <stdexcept>
#include <algorithm>


void Converter::Convert(const ObjModel& objModel, StlModel& stlModel)
{
    // collect coordinates for polygon faces
    for (const auto& f : objModel.GetFaces())
    {
        CreatePolygonsWithNorms(f, objModel.GetVertices(), objModel.GetNorms());        
    }

    // convert polygons to triangles
    for (const auto& poly : polygons_)
    {
        CreateTrianglesWithNorms(poly);
    }

    // sort triangles by z axis (not strictly enforced)
    std::sort(triangles_.begin(), triangles_.end(),
        [](const std::vector<Coord3>& a, const std::vector<Coord3>& b) -> bool
        {
            return std::min({ a[0].z, a[1].z, a[2].z }) > std::min({ b[0].z, b[1].z, b[2].z });
        });

    // move triangles to stl
    for (const auto& t : triangles_)
    {
        // use the calculated normal vector or generate one which should be perpendicular to the triangle plane
        Coord3 nv = t.size() > 3 ? t[3] : Coord3::CrossProduct(t[1] - t[0], t[2] - t[0]).Normalize();

        stlModel.AddTriangle({ t[0], t[1], t[2], nv });
    }
}

void Converter::CreatePolygonsWithNorms(const std::vector<FaceVertex>& faceVertices, const std::vector<Coord3>& objVertices, const std::vector<Coord3>& objNorms)
{
    // collect face vertices with norms
    std::vector<Coord3N> face;
    for (auto const& v : faceVertices)
    {
        const Coord3& vt = v.vIndex() ? objVertices[v.vIndex() - 1] : Coord3();
        const Coord3& vn = v.vnIndex() ? objNorms[v.vnIndex() - 1] : Coord3();

        face.push_back({ vt, vn });
    }
    polygons_.push_back(face);
}

void Converter::CreateTrianglesWithNorms(const std::vector<Coord3N>& poly)
{
    if (poly.size() < 3)
    {
        throw std::runtime_error("Polygon has less than 3 vertices");
    };   

    // traverse polygon and make triangles
    for (std::vector<Coord3N>::const_iterator it = poly.begin(); it+2 != poly.end(); ++it)
    {
        auto p1 = *(it+1);
        auto p2 = *(it+2);

        std::vector<Coord3> triangle{ poly.begin()->vt, p1.vt, p2.vt };

        // if OBJ contained normal vectors on vertices, then try to use an average
        auto vn = ((poly.begin()->vn + p1.vn + p2.vn) / 3.F);
        if (vn.GetLength() > FLT_MIN)
        {
            triangle.push_back(vn.Normalize());
        }

        triangles_.push_back(triangle);
    }
}
