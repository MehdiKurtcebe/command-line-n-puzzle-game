program: 1801042667_main.o 1801042667_classes.o
	g++ 1801042667_main.o 1801042667_classes.o -o program
	
main.o: 1801042667_main.cpp 1801042667_classes.cpp
	g++ -c 1801042667_main.cpp 1801042667_classes.cpp
	
clean:
	rm *.o program
