encodetest: encode_test.o CharString.o
	g++ -o encodetest encode_test.o CharString.o

encode_test.o: encode_test.cpp ./CharString/CharString.h
	g++ -c encode_test.cpp

CharString.o: CharString/CharString.cpp ./CharString/CharString.h
	g++ -c CharString/CharString.cpp

clean:
	rm encodetest encode_test.o CharString.o