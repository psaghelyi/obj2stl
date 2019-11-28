#include "../include/obj2stl/Converter.h"
#include <stdexcept>


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

    // move triangles to stl
    for (const auto& t : triangles_)
    {
        Coord3 nv = Coord3::CrossProduct(t[1] - t[0], t[2] - t[0]).Normalize();
        StlTriangle triangle(t[0], t[1], t[2], nv);

        stlModel.AddTriangle(triangle);
    }
}

void Converter::CreatePolygonsWithNorms(const std::vector<FaceVertex>& faceVertices, const std::vector<Coord3>& objVertices, const std::vector<Coord3>& objNorms)
{
    // collect face vertices with norms
    std::vector<Coord6> face;
    for (auto const& v : faceVertices)
    {
        const Coord3& vt = v.vIndex() ? objVertices[v.vIndex() - 1] : Coord3();
        const Coord3& vn = v.vnIndex() ? objNorms[v.vnIndex() - 1] : Coord3();

        face.push_back({ vt, vn });
    }
    polygons_.push_back(face);
}

void Converter::CreateTrianglesWithNorms(const std::vector<Coord6>& poly)
{
    if (poly.size() < 3)
    {
        throw std::runtime_error("Polygon has less than 3 vertices");
    }
    if (poly.size() == 3)
    {
        auto p1 = Coord3(poly[0].vt.x, poly[0].vt.y, poly[0].vt.z);
        auto p2 = Coord3(poly[1].vt.x, poly[1].vt.y, poly[1].vt.z);
        auto p3 = Coord3(poly[2].vt.x, poly[2].vt.y, poly[2].vt.z);

        std::vector<Coord3> triangle {p1, p2 ,p3};
        triangles_.push_back(triangle);
        return;
    }


}