GPP = g++ -std=c++11 -w
INCLUDE = -I/usr/include/libdrm
CFLAGS = -lglfw -lGL -lGLU
a.out: demo.cpp Scene.o
	$(GPP) demo.cpp Scene.o $(INCLUDE) $(CFLAGS)
	./a.out
	
Camera.o:	Camera.cpp
	$(GPP) -c -o Camera.o Camera.cpp $(INCLUDE) $(CFLAGS)
	
Scene.o:	Scene.cpp
	$(GPP) -c -o Scene.o Scene.cpp $(INCLUDE) $(CFLAGS)	

point3.o:	point3.cpp
	$(GPP) -c -o point3.o point3.cpp $(INCLUDE) $(CFLAGS)	

clean:
	rm *.o *.out
