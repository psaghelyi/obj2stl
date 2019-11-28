#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>
#include <array>

#include "../include/obj2stl/ObjParser.h"

struct FaceVertex
{
    FaceVertex() : indices{ 0,0,0 } {}

    int& vIndex() { return indices[0]; }
    int& vtIndex() { return indices[1]; }
    int& vnIndex() { return indices[2]; }

    int* Indices() { return indices; }

private:
    int  indices[3];
};


void ObjParser::ParseFile(const std::string& fname)
{
    std::ifstream file(fname);
    if (file.is_open())
    {
        std::string line;
        while (getline(file, line))
        {
            ParseLine(line);
            //std::cout << line << "\n";
        }
        file.close();
    }
}

void ObjParser::ParseLine(const std::string& line)
{
    static const std::string rxCoordStr = "([-+]?[0-9]*.?[0-9]+(?:[eE][-+]?[0-9]+)?)";
    static const std::regex rxV = std::regex("^(?:\\s*)" + rxCoordStr + "(?:\\s+)" + rxCoordStr + "(?:\\s+)" + rxCoordStr + "(?:.*)");
    static const std::regex rxVT = std::regex("^(?:\\s*)" + rxCoordStr + "(?:\\s+)" + rxCoordStr + "(?:.*)");
    static const std::regex rxVN = std::regex("^(?:\\s*)" + rxCoordStr + "(?:\\s+)" + rxCoordStr + "(?:\\s+)" + rxCoordStr + "(?:.*)");
    static const std::regex rxF = std::regex("(?:\\s*)((?:[0-9]+)(?:/[0-9]*)*)");  // 'v_ind' or 'v_ind/vt_ind' or 'v_ind/vt_ind/vn_ind' or 'v_ind//vn_ind'
    static const std::regex rxPrefix = std::regex("^(?:((?:\\s*)(f|v(?:n|t)?))\\s.*)"); // g1:prefix, g2:f|v|vn|vt

    std::smatch sm;
    if (std::regex_match(line, sm, rxPrefix))
    {
        if (sm[2].str().compare("v") == 0 && std::regex_match(line.begin() + sm[1].length(), line.end(), sm, rxV))
        {
            AddVertex(std::stof(sm[1]), std::stof(sm[2]), std::stof(sm[3]));
        }
        else if (sm[2].str().compare("vt") == 0 && std::regex_match(line.begin() + sm[1].length(), line.end(), sm, rxVT))
        {
            AddVertexTexture(std::stof(sm[1]), std::stof(sm[2]));
        }
        else if (sm[2].str().compare("vn") == 0 && std::regex_match(line.begin() + sm[1].length(), line.end(), sm, rxVN))
        {
            AddVertexNorm(std::stof(sm[1]), std::stof(sm[2]), std::stof(sm[3]));
        }
        else if (sm[2].str().compare("f") == 0)
        {
            std::vector<FaceVertex> faceVertices;

            std::string s(line.begin() + sm[1].length(), line.end());
            while (std::regex_search(s, sm, rxF))
            {
                FaceVertex faceVertex;

                std::istringstream tokenStream(s);
                std::string token;
                int* vi = faceVertex.Indices(), * pvi = vi;
                while (std::getline(tokenStream, token, '/'))
                {
                    if (token.length() > 0)
                    {
                        *pvi = std::stoi(token);
                    }
                    if (++pvi - vi > 3) // check for overrun
                    {
                        break;
                    }
                }

                faceVertices.push_back(faceVertex);
                s = sm.suffix().str();
            }

            AddFace(faceVertices);
        }
    }
}

void ObjParser::AddVertex(float x, float y, float z)
{
    std::cout << "v " << x << " " << y << " " << z << "\n";
}

void ObjParser::AddVertexTexture(float u, float v)
{
    std::cout << "vt " << u << " " << v << "\n";
}

void ObjParser::AddVertexNorm(float i, float j, float k)
{
    std::cout << "vn " << i << " " << j << " " << k << "\n";
}

void ObjParser::AddFace(const std::vector<FaceVertex>& faceVertexIndices)
{
    std::cout << "f ";
    for (auto x : faceVertexIndices)
    {
        std::cout << x.vIndex() << "/" << x.vtIndex() << "/" << x.vnIndex() << " ";
    }
    std::cout << "\n";
}

