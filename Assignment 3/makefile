GPP = g++ -std=c++11 -w
INCLUDE = -I/usr/include/libdrm
CFLAGS = -lglfw -lGL -lGLU
a.out: main.cpp Polymesh.o
	$(GPP) main.cpp Polymesh.o $(INCLUDE) $(CFLAGS)
	./a.out
	
Polymesh.o: Polymesh.cpp
	$(GPP) -c -o Polymesh.o Polymesh.cpp $(INCLUDE) $(CFLAGS)

clean:
	rm *.o *.out
