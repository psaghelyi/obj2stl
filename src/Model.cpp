#include "../include/obj2stl/Model.h"
#include "../include/obj2stl/FaceVertex.h"

#include <stdexcept>


void Model::AddVertex(Coord3&& v)
{
    vertices_.push_back(v);
}

void Model::AddNorm(Coord3&& n)
{
    norms_.push_back(n);
}

void Model::AddFace(const std::vector<FaceVertex>& face)
{
    for (auto const& p : face)
    {
        if (p.vIndex() < 0 || p.vIndex() > vertices_.size())
        {
            throw std::runtime_error("Vertex index is out of bounds");
        }
        if (p.vnIndex() < 0 || p.vnIndex() > norms_.size())
        {
            throw std::runtime_error("Normal index is out of bounds");
        }
    }
    faces_.push_back(face);
}
