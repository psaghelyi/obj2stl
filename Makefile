all: bin/obj2stl

bin/obj2stl: bin/main.o bin/libobj2stl.a
	g++ -std=c++14 -o bin/obj2stl bin/main.o bin/libobj2stl.a -lm

bin/main.o: src/main.cpp
	g++ -std=c++14 -O2 -c src/main.cpp -o bin/main.o

bin/ObjModel.o: src/ObjModel.cpp include/obj2stl/ObjModel.h
	g++ -std=c++14 -O2 -c src/ObjModel.cpp -o bin/ObjModel.o

bin/ObjReader.o: src/ObjReader.cpp include/obj2stl/ObjReader.h
	g++ -std=c++14 -O2 -c src/ObjReader.cpp -o bin/ObjReader.o

bin/StlModel.o: src/StlModel.cpp include/obj2stl/StlModel.h
	g++ -std=c++14 -O2 -c src/StlModel.cpp -o bin/StlModel.o

bin/StlWriter.o: src/StlWriter.cpp include/obj2stl/StlWriter.h
	g++ -std=c++14 -O2 -c src/StlWriter.cpp -o bin/StlWriter.o
	
bin/Converter.o: src/Converter.cpp include/obj2stl/Converter.h
	g++ -std=c++14 -O2 -c src/Converter.cpp	-o bin/Converter.o

bin/libobj2stl.a: bin/ObjModel.o bin/ObjReader.o bin/StlModel.o bin/StlWriter.o bin/Converter.o
	ar rcs bin/libobj2stl.a bin/ObjModel.o bin/ObjReader.o bin/StlModel.o bin/StlWriter.o bin/Converter.o

libs: bin/libobj2stl.a

clean:
	rm -f bin/obj2stl bin/*.o bin/*.a
