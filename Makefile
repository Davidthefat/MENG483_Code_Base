all: main.o GaussianQuad.o
	g++ -g -o2 main.o GaussianQuad.o -o main 

main.o: main.cpp
	g++ -c -o2 main.cpp -o main.o 

GaussianQuad.o: GaussianQuad.h
	g++ -c -o2 GaussianQuad.cpp -o GaussianQuad.o
clean:
	rm *.o
