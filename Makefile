test: md5.o encrypt.o test.o
	g++ -o test md5.o encrypt.o test.o
md5.o: md5.h
	g++ -g -c -o md5.o md5.cpp
encrypt.o: encrypt.h 
	g++ -g -c -o encrypt.o encrypt.cpp
test.o: encrypt.h
	g++ -g -c -o test.o test.cpp
clean:
	rm *.o test.exe
