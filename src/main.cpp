//
//  main.cpp
//  obj2stl
//
//  Created by Peter Saghelyi on 2019. 11. 27..
//  Copyright © 2019. psaghelyi. All rights reserved.
//


#include "../include/obj2stl/ObjReader.h"
#include "../include/obj2stl/StlWriter.h"

#include <iostream>
#include <exception>

int main(int argc, const char * argv[]) {
  
    ObjModel objModel;
    StlModel stlModel;
    ObjReader reader(objModel);
    StlWriter writer(stlModel);
  
    try {
        //reader.ReadFromFile("/Users/psaghelyi/Project/obj2stl/data/teapot.obj");
        reader.ReadFromFile("c:\\Project\\obj2stl\\data\\teapot.obj");
        writer.WriteToFile("c:\\Project\\obj2stl\\data\\teapot.stl");
    }
    catch (std::exception & e)
    {
        std::cout << e.what() << "\n";
        return -1;
    }
    
    return 0;
}
