#include "../include/obj2stl/StlWriter.h"

#include <fstream>


void StlWriter::WriteToFile(const std::string& fname) const
{
    std::ofstream ofs(fname, std::ostream::binary);
    if (ofs.is_open())
    {
        WriteToStream(ofs);
        ofs.close();
        return;
    }
    throw new std::runtime_error("Cannot open file" + fname);
}

void StlWriter::WriteToStream(std::ostream& os) const
{
    WriteHeader(os);
    WriteBody(os);
}

void StlWriter::WriteHeader(std::ostream& os) const
{
    static const char header[80];
    os.write(header, sizeof(header));
}

static void WriteCoord(std::ostream& os, const Coord3& coord);

void StlWriter::WriteBody(std::ostream& os) const
{
    static const char attribute[2];

    for (auto tr : model_.GetTriangles())
    {
        WriteCoord(os, tr.norm_);
        WriteCoord(os, tr.v1_);
        WriteCoord(os, tr.v2_);
        WriteCoord(os, tr.v3_);
        os.write(attribute, sizeof(attribute));
    }
}

void WriteCoord(std::ostream& os, const Coord3& coord)
{
    os.write(reinterpret_cast<const char*>(&coord.x), sizeof(float));
    os.write(reinterpret_cast<const char*>(&coord.y), sizeof(float));
    os.write(reinterpret_cast<const char*>(&coord.z), sizeof(float));
}