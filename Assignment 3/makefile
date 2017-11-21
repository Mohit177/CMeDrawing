GPP = g++ -std=c++11 -w
INCLUDE = -I/usr/include/libdrm
CFLAGS = -lglfw -lGL -lGLU
a.out: demo.cpp
	$(GPP) demo.cpp $(INCLUDE) $(CFLAGS)
	./a.out

clean:
	rm *.o *.out
