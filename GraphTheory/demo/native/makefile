main.dylib: EdgeInfo.o export.o VertexInfo.o
	g++ -dynamiclib -o main.dylib EdgeInfo.o export.o VertexInfo.o
export.o: export.cpp EdgeInfo.h siglobal.h sigraph.h VertexInfo.h
	g++ -c export.cpp
EdgeInfo.o: EdgeInfo.cpp EdgeInfo.h
	g++ -c EdgeInfo.cpp
VertexInfo.o: VertexInfo.cpp VertexInfo.h
	g++ -c VertexInfo.cpp

clean:
	rm main.dylib EdgeInfo.o export.o VertexInfo.o