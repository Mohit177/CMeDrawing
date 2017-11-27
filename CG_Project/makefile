GPP         = g++ -std=c++11 -w 
32_FLAG    = -L. -L/usr/lib64 -L/usr/lib 
X_LIB      = -lXt -lXext -lSM -lICE 
GL_LIB     = -lglut -lGLU -lGL -LXi -lXext -lX11 -lm 
LIBS       = -lm $(XF_LIB) $(X_LIB) $(GL_LIB)
OBJECTS    =  data.o callbacks.o 

marching_cubes:	marching_cubes.cpp $(OBJECTS)
			$(GPP) $(32_FLAG) -o marching_cubes.o marching_cubes.cpp $(OBJECTS) $(LIBS)

data.o:			data.cpp
			$(GPP) $(32_FLAG) -c data.cpp -o data.o

callbacks.o:		callbacks.cpp
			$(GPP) $(32_FLAG) -c callbacks.cpp -o callbacks.o

clean: 			
			rm *.o
