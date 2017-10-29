extract: extract_key_words.o CharString.o
	g++ -o extract extract_key_words.o CharString.o

extract_key_words: extract_key_words.cpp CharString/CharString.h
	g++ -c extract_key_words.cpp

CharString.o: CharString/CharString.cpp CharString/CharString.h
	g++ -c CharString/CharString.cpp

clean:
	rm extract extract_key_words.o CharString.o