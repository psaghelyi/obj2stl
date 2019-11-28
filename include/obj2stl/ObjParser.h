#pragma once

#include <string>
#include <vector>

struct FaceVertex;

class ObjParser
{
public:
    void ParseFile(const std::string& fname);

private:
    void ParseLine(const std::string& line);

    void AddVertex(float x, float y, float z);
    void AddVertexTexture(float u, float v);
    void AddVertexNorm(float i, float j, float k);
    void AddFace(const std::vector<FaceVertex>& faceVertexIndices);
};


