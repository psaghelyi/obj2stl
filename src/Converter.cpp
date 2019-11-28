#include "../include/obj2stl/Converter.h"


static StlTriangle GetTriangules()
{

}

void Converter::Convert(const ObjModel& objModel, StlModel& stlModel)
{
    // enumerate faces
    for (auto const& f : objModel.GetFaces())
    {
        // collect face vertices
        std::vector<Coord6> face;
        for (auto const& v : f)
        {
            const Coord3& vt = v.vIndex() ? objModel.GetVertices()[v.vIndex() - 1] : Coord3();
            const Coord3& vn = v.vnIndex() ? objModel.GetNorms()[v.vnIndex() - 1] : Coord3();

            face.push_back(Coord6(vt, vn));
        }
        faces_.push_back(face);

        // collect 
    }
}
