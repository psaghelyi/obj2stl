//
//  main.cpp
//  obj2stl
//
//  Created by Peter Saghelyi on 2019. 11. 27..
//  Copyright © 2019. psaghelyi. All rights reserved.
//


#include "../include/obj2stl/ObjReader.h"

int main(int argc, const char * argv[]) {
  
    Model model;
    ObjReader reader(model);
  
    //reader.ReadFromFile("/Users/psaghelyi/Project/obj2stl/data/teapot.obj");
    reader.ReadFromFile("c:\\Project\\obj2stl\\data\\teapot.obj");
    
    return 0;
}
