#pragma once

#include <string>
#include <vector>
#include <istream>

#include "Model.h"

class ObjReader
{
public:
    ObjReader(Model& model) : model_(model) {}

    void ReadFromFile(const std::string& fname);
    void ReadFromStream(std::istream& is);

private:
    Model& model_;

    void ParseLine(const std::string& line);

    void AddVertex(float x, float y, float z);
    void AddVertexTexture(float u, float v);
    void AddVertexNorm(float i, float j, float k);
    void AddFace(const std::vector<FaceVertex>& faceVertexIndices);
};


