//
//  main.cpp
//  obj2stl
//
//  Created by Peter Saghelyi on 2019. 11. 27..
//  Copyright © 2019. psaghelyi. All rights reserved.
//


#include "../include/obj2stl/ObjParser.h"


int main(int argc, const char * argv[]) {
  
  ObjParser objParser;
  
  //objParser.ParseFile("/Users/psaghelyi/Project/obj2stl/data/teapot.obj");
  objParser.ParseFile("c:\\Project\\obj2stl\\data\\teapot.obj");
    
  return 0;
}
