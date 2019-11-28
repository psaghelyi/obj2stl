//
//  main.cpp
//  obj2stl
//
//  Created by Peter Saghelyi on 2019. 11. 27..
//  Copyright © 2019. psaghelyi. All rights reserved.
//


#include "../include/obj2stl/ObjReader.h"
#include "../include/obj2stl/StlWriter.h"
#include "../include/obj2stl/Converter.h"

#include <iostream>
#include <exception>

void read(ObjModel& model)
{
    ObjReader reader(model);
    reader.ReadFromFile("c:\\Project\\obj2stl\\data\\teapot.obj");
}

void write(const StlModel& model)
{
    StlWriter writer(model);
    writer.WriteToFile("c:\\Project\\obj2stl\\data\\box.stl");
}

void convert(const ObjModel& modelIn, StlModel& modelOut)
{
    Converter converter;
    converter.Convert(modelIn, modelOut);
}

int main(int argc, const char * argv[]) {
  
    ObjModel objModel;
    StlModel stlModel;    

    try {
        read(objModel);
        convert(objModel, stlModel);
        write(stlModel);
    }
    catch (std::exception & e)
    {
        std::cout << e.what() << "\n";
        return -1;
    }
    
    return 0;
}
