all: gobang

gobang: gobang.o computer.o
	g++ gobang.o computer.o -o gobang

gobang.o: gobang.cpp gobang.h
	g++ -c gobang.cpp

computer.o: computer.cpp gobang.h
	g++ -c computer.cpp

clean:
	-@rm -rvf *.o 
