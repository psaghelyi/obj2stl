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
        // use the calculated normal vector or generate one which should be perpendicular to the triangle plane
        Coord3 nv = t.size() > 3 ? t[3] : Coord3::CrossProduct(t[1] - t[0], t[2] - t[0]).Normalize();

        StlTriangle triangle(t[0], t[1], t[2], nv);

        stlModel.AddTriangle(triangle);
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
    }
    if (poly.size() == 3)
    {
        auto p1 = Coord3(poly[0].vt.x, poly[0].vt.y, poly[0].vt.z);
        auto p2 = Coord3(poly[1].vt.x, poly[1].vt.y, poly[1].vt.z);
        auto p3 = Coord3(poly[2].vt.x, poly[2].vt.y, poly[2].vt.z);

        std::vector<Coord3> triangle {p1, p2 ,p3};

        // if OBJ contained normal vectors, then try to use an average
        auto vn = ((poly[0].vn + poly[1].vn + poly[2].vn) / 3.F).Normalize();
        if (vn.GetLength() > FLT_MIN)
        {
            triangle.push_back(vn);
        }

        triangles_.push_back(triangle);
        return;
    }


}