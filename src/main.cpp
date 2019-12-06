#include "ObjReader.h"
#include "StlWriter.h"
#include "Converter.h"

#include <iostream>
#include <exception>
#include <sstream>
#include <vector>


void read(ObjModel& model, const std::string& fname)
{
    ObjReader reader(model);
    reader.ReadFromFile(fname);
}

void write(const StlModel& model, const std::string& fname)
{
    StlWriter writer(model);
    writer.WriteToFile(fname);
}

void convert(const ObjModel& modelIn, StlModel& modelOut, const Coord3TR& tr)
{
    Converter converter(tr);
    converter.Convert(modelIn, modelOut);
}

int parsearg(int argc, const char* argv[], std::string& fname, Coord3TR& tr)
{
    if (argc == 1)
    {
        std::cout << "\nUsage:\n";
        std::cout << argv[0] << " <OBJ file> [1,0,0;0,1,0;0,0,1]\n";
        return 1;
    }
    fname = argv[1];
    
    if (argc == 3)
    {
        float* tref[9] =
        {
            &tr.c1.x, &tr.c1.y, &tr.c1.z,
            &tr.c2.x, &tr.c2.y, &tr.c2.z,
            &tr.c3.x, &tr.c3.y, &tr.c3.z
        };
        float** ptref = tref;

        std::istringstream tokenStream1(argv[2]);
        std::string token1;
        while (std::getline(tokenStream1, token1, ';'))
        {
            std::istringstream tokenStream2(token1);
            std::string token2;
            while (std::getline(tokenStream2, token2, ','))
            {
                **ptref++ = std::stof(token2);
            }
        }
    }

    return 0;
}

int main(int argc, const char * argv[]) 
{
    Coord3TR tr;
    std::string filein;

    int ret = parsearg(argc, argv, filein, tr);
    if (ret != 0)
    {
        return ret;
    }
        
    std::string fileout = filein.substr(0, filein.find_last_of('.')) + ".stl";

    ObjModel objModel;
    StlModel stlModel;

    try {
        read(objModel, filein);
        convert(objModel, stlModel, tr);        
        write(stlModel, fileout);
    }
    catch (std::exception & e)
    {
        std::cout << e.what() << "\n";
        return -1;
    }
    
    return 0;
}
