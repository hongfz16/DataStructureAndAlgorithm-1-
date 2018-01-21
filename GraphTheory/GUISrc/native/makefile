main.dylib: EdgeInfo.o export.o VertexInfo.o unionfind.o persistence_unionfind.o
	g++ -O2 -dynamiclib -o main.dylib EdgeInfo.o export.o VertexInfo.o unionfind.o persistence_unionfind.o
export.o: export.cpp EdgeInfo.h siglobal.h sigraph.h VertexInfo.h
	g++ -c export.cpp
EdgeInfo.o: EdgeInfo.cpp EdgeInfo.h
	g++ -c EdgeInfo.cpp
VertexInfo.o: VertexInfo.cpp VertexInfo.h
	g++ -c VertexInfo.cpp
unionfind.o: unionfind.cpp unionfind.h siglobal.h
	g++ -c unionfind.cpp
persistence_unionfind.o: persistence_unionfind.cpp siglobal.h persistencearry.h
	g++ -c persistence_unionfind.cpp

clean:
	rm main.dylib EdgeInfo.o export.o VertexInfo.o persistence_unionfind.o unionfind.o