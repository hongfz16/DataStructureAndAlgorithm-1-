testCharString: test_CharString.o CharString.o
	g++ -o testCharString test_CharString.o CharString.o

test_CharString.o: test_CharString.cpp ../CharString.h
	g++ -c test_CharString.cpp

CharString.o: ../CharString.cpp ../CharString.h
	g++ -c ../CharString.cpp

clean:
	rm testCharString test_CharString.o CharString.o