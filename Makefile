program: main.o classes.o
	g++ main.o classes.o -o program
	
main.o: main.cpp classes.cpp
	g++ -c main.cpp classes.cpp
	
clean:
	rm *.o program
