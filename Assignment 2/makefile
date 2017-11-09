GPP = g++ -std=c++11 -w
INCLUDE = -I/usr/include/libdrm
CFLAGS = -lglfw -lGL -lGLU
a.out: demo.cpp Camera.o Scene.o Utility.o
	$(GPP) demo.cpp Camera.o Scene.o Utility.o $(INCLUDE) $(CFLAGS)
	./a.out
	
Camera.o: Camera.cpp
	$(GPP) -c -o Camera.o Camera.cpp $(INCLUDE) $(CFLAGS)
	
Scene.o: Scene.cpp
	$(GPP) -c -o Scene.o Scene.cpp $(INCLUDE) $(CFLAGS)	

Utility.o: Utility.cpp
	$(GPP) -c -o Utility.o Utility.cpp $(INCLUDE) $(CFLAGS)


clean:
	rm *.o *.out
