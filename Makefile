all: obj2stl

obj2stl: main.o libobj2stl.a
	g++ -std=c++14 -o obj2stl main.o libobj2stl.a -lm

main.o: src/main.cpp
	g++ -std=c++14 -O2 -c src/main.cpp

ObjModel.o: src/ObjModel.cpp include/obj2stl/ObjModel.h
	g++ -std=c++14 -O2 -c src/ObjModel.cpp 

ObjReader.o: src/ObjReader.cpp include/obj2stl/ObjReader.h
	g++ -std=c++14 -O2 -c src/ObjReader.cpp

StlModel.o: src/StlModel.cpp include/obj2stl/StlModel.h
	g++ -std=c++14 -O2 -c src/StlModel.cpp

StlWriter.o: src/StlWriter.cpp include/obj2stl/StlWriter.h
	g++ -std=c++14 -O2 -c src/StlWriter.cpp
	
Converter.o: src/Converter.cpp include/obj2stl/Converter.h
	g++ -std=c++14 -O2 -c src/Converter.cpp	

libobj2stl.a: ObjModel.o ObjReader.o StlModel.o StlWriter.o Converter.o
	ar rcs libobj2stl.a ObjModel.o ObjReader.o StlModel.o StlWriter.o Converter.o

libs: libobj2stl.a

clean:
	rm -f obj2stl *.o *.a
