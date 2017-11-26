CC         = cc -w 
32_FLAG    = -L. -L/usr/lib64 -L/usr/lib 
X_LIB      = -lXmu -lXt -lXext -lSM -lICE 
GL_LIB     = -lglut -lGLU -lGL -lXmu -LXi -lXext -lX11 -lm 
XF_LIB     = -lforms
LIBS       = -lm $(XF_LIB) $(X_LIB) $(GL_LIB)
OBJECTS    = marching_cubes.o data.o callbacks.o 

marching_cubes:		$(OBJECTS)
			$(CC) $(32_FLAG) -o marching_cubes $(OBJECTS) $(LIBS)

marching_cubes.o:	marching_cubes.c
			$(CC) $(32_FLAG) -c marching_cubes.c -o marching_cubes.o

data.o:			data.c
			$(CC) $(32_FLAG) -c data.c -o data.o

callbacks.o:		callbacks.c
			$(CC) $(32_FLAG) -c callbacks.c -o callbacks.o

clean: 			
			rm *.o