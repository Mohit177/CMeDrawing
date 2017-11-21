GPP = g++ -std=c++11 -w
INCLUDE = -I/usr/include/libdrm
CFLAGS = -lglfw -lGL -lGLU
a.out: main.cpp Point2.o
	$(GPP) main.cpp Point2.o $(INCLUDE) $(CFLAGS)
	./a.out
	
Point2.o: Point2.cpp
	$(GPP) -c -o Point2.o Point2.cpp $(INCLUDE) $(CFLAGS)

clean:
	rm *.o *.out
