GPP = g++ -std=c++11
INCLUDE = -I/usr/include/libdrm
CFLAGS = -lglfw -lGL -lGLU
a.out: demo.cpp interaction.cpp
	$(GPP) demo.cpp interaction.cpp $(INCLUDE) $(CFLAGS)
	./a.out
	
interaction.o:	interaction.cpp
	$(GPP) -c -o interaction.o interaction.cpp $(INCLUDE) $(CFLAGS)

clean:
	rm *.o *.out
