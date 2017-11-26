#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <GL/glut.h>
#include "./code/const.h"
#include "code/funcs.h"
#include "code/data.c"
#include "code/cube.h"
using namespace std;

#define ll long long int

/* static global variables for storing state information */
static int currentButton;  /* currently pressed mouse button */  
static int displayType = RGB_SLICE_DISPLAY;  /* current display setting, i.e., 
						whether RGB slices (color coded) are being viewed
						or whether the polygonal model is being viewed. */
static int currentVolumeDataSet = TORSO_256_DATA_SET;   /* current volume data set */
static int currentSliceRGB = 0;   /* current slice being displayed in RGB form */
static int currentScaleFactorRGB = LOBSTER_SCALE;   /* current scale factor for the data set being displayed */
static int numTotalVertices = 0;
static int currentFacetIndex = 0;

/* volume data set */
static Volume *volume;
static point *vlist;
static point *nlist;
static triangle *flist;
static triangle *fnlist;

/* slices, etc */
vector<short int> outsideSliceA, outsideSliceB, outsideSliceC;
vector<long> xedge, yedge, zedge, topyedge;
static long old6pt, old10pt;
static long vert_index = 0;
static long baseCase = 50;

/* chooseColor: Function to set the current drawing color of the screen.
                The input parameter 'color' is the value returned by GLUT 
	        for the color option selected by the user.
	        */
void chooseColor(int cind)
{
    switch(cind)
    {
    	case 0: glColor3f(1.0, 0.0, 0.0); break;
    	case 1: glColor3f(0.0, 1.0, 0.0); break;
    	case 2: glColor3f(0.0, 0.0, 1.0); break;
    	default: glColor3f(1.0, 1.0, 1.0); break;
    }
}

/* SELECT_DATA_SET: Function to handle the options in the data set submenu.
                 The input parameter 'option' is the value returned by GLUT 
		 for the option selected by the user.
		 */
void selectDataSet(int option,string fname)
{
	/*currentVolumeDataSet = option;
	currentSliceRGB = 0;*/
	if(volume)
	{
		freeVolume(volume);
		freeStructures();
	}

	/*switch (option)
	{
	case TORSO_128_DATA_SET: 
	  currentScaleFactorRGB = TORSO_128_SCALE;
	  if (volume)
	freeVolume(volume);
	  freeStructures();
	  volume = createVolume(TORSO_128_XDIM,TORSO_128_YDIM,TORSO_128_ZDIM);
	  volReadFile(volume,"../data/128.dat");
	  computePolygonalModel();
	  break;
	case TORSO_256_DATA_SET:
	  currentScaleFactorRGB = TORSO_256_SCALE;
	  if (volume)
	freeVolume(volume);
	  freeStructures();
	  volume = createVolume(TORSO_256_XDIM,TORSO_256_YDIM,TORSO_256_ZDIM);
	  volReadFile(volume,"../data/256.dat");
	  computePolygonalModel();
	  break;
	case TORSO_512_DATA_SET:
	  currentScaleFactorRGB = TORSO_512_SCALE;
	  if (volume)
	freeVolume(volume);
	  freeStructures();
	  volume = createVolume(TORSO_512_XDIM,TORSO_512_YDIM,TORSO_512_ZDIM);
	  volReadFile(volume,"../data/512.dat");
	  computePolygonalModel();
	  break;
	case LOBSTER_DATA_SET:
	  currentScaleFactorRGB = LOBSTER_SCALE;
	  if (volume)
	freeVolume(volume);
	  freeStructures();
	  volume = createVolume(LOBSTER_XDIM,LOBSTER_YDIM,LOBSTER_ZDIM);
	  volReadFile(volume,"../data/lobster.dat");
	  computePolygonalModel();
	  break;
	case HYDROGEN_DATA_SET:
	  currentScaleFactorRGB = HYDROGEN_SCALE;
	  if (volume)
	freeVolume(volume);
	  freeStructures();
	  volume = createVolume(HYDROGEN_XDIM,HYDROGEN_YDIM,HYDROGEN_ZDIM);
	  volReadFile(volume,"../data/hydrogen.dat");
	  computePolygonalModel();
	  break;
	case VOL_TESLA_DATA_SET:
	  currentScaleFactorRGB = VOL_TESLA_SCALE;
	  if (volume)
	freeVolume(volume);
	  freeStructures();
	  volume = createVolume(VOL_TESLA_XDIM,VOL_TESLA_YDIM,VOL_TESLA_ZDIM);
	  volReadFile(volume,"../data/vol_tesla.dat");
	  computePolygonalModel();
	  break;
	}
	display();*/

}

/* SELECTOPTION: Function to handle the options in the main pulldown menu.
                 The input parameter 'option' is the value returned by GLUT 
		 for the option selected by the user.
		 */
void selectOption(int option)
{
  switch(option)
    {
    case 'w':   /* switch between displays: RGB slices or polygonal model */
      displayType = 1-displayType;
      createMenus();
      initLighting();
      display();
      break;
    case 's':   /* Clear the screen */
      glClear(GL_COLOR_BUFFER_BIT|GL_STENCIL_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
      break;
    case 'e':   /* Exit the application */
      if (volume)
	freeVolume(volume);
      freeStructures();
      exit(0);
      break;
    }
}

/* INIT_STRUCTURES: Allocate memory for the data structures used in this program.
   */
void initStructures(void)
{
	int i;

	if (outsideSliceC.size()>0)
	{
		//outsideSliceC = (short int *)malloc(sizeof(short int) * volume->XDim * volume->YDim);
		outsideSliceC.clear();
		outsideSliceC.resize(volume->XDim * volume->YDim);
	}
	if (outsideSliceA.size()>0)
	{
		outsideSliceA.clear();
		outsideSliceA.resize(volume->XDim * volume->YDim);
	}
		//outsideSliceA = (short int *)malloc(sizeof(short int) * volume->XDim * volume->YDim);
	if (outsideSliceB.size()>0)
	{
		outsideSliceB.clear();
		outsideSliceB.resize(volume->XDim * volume->YDim);
	}
		//outsideSliceB = (short int *)malloc(sizeof(short int) * volume->XDim * volume->YDim);
	if (xedge.size()>0)
	{
		xedge.clear();
		xedge.resize(volume->XDim* volume->YDim);
	}
	if (yedge.size()>0)
	{
		yedge.clear();
		yedge.resize(volume->XDim* volume->YDim);
	}
	if (zedge.size()>0)
	{
		zedge.clear();
		zedge.resize(volume->YDim);
	}
	if (topyedge.size()>0)
	{
		topyedge.clear();
		topyedge.resize(volume->YDim);
	}
	/*if (!vlist)
		vlist = (point *)malloc(sizeof(point)*500000);
	if (!nlist)
		nlist = (point *)malloc(sizeof(point)*500000);*/
	if (!vlist)
		vlist = new point[500000];
	if (!nlist)
		nlist = new point[500000];
	/*if (!flist)
	{
	  	flist = (triangle *)malloc(sizeof(triangle)*500000);
		for (i=0; i<500000; i++)
		{
			(flist+i)->pt1 = (point *)malloc(sizeof(point));
			(flist+i)->pt2 = (point *)malloc(sizeof(point));
			(flist+i)->pt3 = (point *)malloc(sizeof(point));
		}
	}
	if (!fnlist)
	{
		fnlist = (triangle *)malloc(sizeof(triangle)*500000);
		for (i=0; i<500000; i++)
		{
		  (fnlist+i)->pt1 = (point *)malloc(sizeof(point));
		  (fnlist+i)->pt2 = (point *)malloc(sizeof(point));
		  (fnlist+i)->pt3 = (point *)malloc(sizeof(point));
		}
	}*/
	if (!flist)
	{
	  	flist  = new triangle[500000];
		for (i=0; i<500000; i++)
		{
			(flist+i)->pt1 = new point;
			(flist+i)->pt2 = new point;
			(flist+i)->pt3 = new point;
		}
	}
	if (!fnlist)
	{
		fnlist  = new triangle[500000];
		for (i=0; i<500000; i++)
		{
			(fnlist+i)->pt1 = new point;
			(fnlist+i)->pt2 = new point;
			(fnlist+i)->pt3 = new point;
		}
	}
}

/* FREE_STRUCTURES: Free the memory allocated to the data structures used in this program.
   */
void freeStructures(void)
{
	int i;
	if (outsideSliceA.size()>0)
		outsideSliceA.clear();
	if (outsideSliceB.size()>0)
		outsideSliceB.clear();
	if (outsideSliceC.size()>0)
		outsideSliceC.clear();
	if (xedge.size()>0)
		xedge.clear();
	if (yedge.size()>0)
		yedge.clear();
	if (zedge.size()>0)
		zedge.clear();
	if (topyedge.size()>0)
		topyedge.clear();
	if (vlist)
		delete[] vlist;
	if (nlist)
		delete[] nlist;
	if (flist)
    {
		for (i=(500000-1); i>0; i--)
		{
			delete((flist+i)->pt1);
			delete((flist+i)->pt2);
			delete((flist+i)->pt3);
		}
		delete[] (flist);
    }
	if (fnlist)
	{
		for (i=(500000-1); i>0; i--)
		{
			delete((fnlist+i)->pt1);
			delete((fnlist+i)->pt2);
			delete((fnlist+i)->pt3);
		}
		delete[] (fnlist);
	}
}

/* GENERATE_FACET_DATA: This function generates the 'facet_data' array for all 
                        possible permutations of a marching cube.
			*/
void generateFacetData(void)
{
	int i,j,k,l,cube_index;

	for (i=0; i<NUM_CUBE_PERMS; i++) 
	{				/* i is the targeted cube_index */
		for (j=0; j<NUM_BASIS_CUBES; j++) 
		{			/* scan each of the NUM_BASIS_CUBES possible basis cubes */
			for (k=0; k<NUM_CUBE_ROTATIONS; k++) 
			{			/* and every possible rotation for those cubes */
			/* first determine if we have a matching cube_index */
				cube_index=0;
				for (l=0; l<NUM_CUBE_VERTICES; l++) 
				{
					if (init_facet_index[j][l]) 
						cube_index |= (1 << corner_rotation[k][l]);
				}
				if (cube_index==i) 
				{
					for (l=0; l<NUM_CUBE_EDGES; l++) 
					{
						if (init_facet_data[j][l]>=0) 
						{
							facet_data[i][l] = edge_rotation[k][init_facet_data[j][l]];
							facet_data[0xFF-i][l] = edge_rotation[k][init_facet_data[j][l]];
						}
						else 
						{
							facet_data[i][l] = (-1);
							facet_data[0xFF-i][l] = (-1);
						}
					}
				}
			}
		}
	}
}

/* PRINT_FACET_DATA_FILE: Print facet data array to a file. This function is useful for
                          debugging purposes.
			  */
void printFacetDataFile(void)
{
	FILE *FACET_DATA_FILE;
	int i,j;

	printf("Writing facet data to file ... ");
	FACET_DATA_FILE = fopen("facet_data.tmp","w");

	fprintf(FACET_DATA_FILE,"\n\nFacet data = \n");
	for (i=0; i<NUM_CUBE_PERMS; i++)
	{
		fprintf(FACET_DATA_FILE,"%d : ",i);
		for (j=0; j<NUM_CUBE_EDGES; j++)
		fprintf(FACET_DATA_FILE,"%d ",facet_data[i][j]);
		fprintf(FACET_DATA_FILE,"\n");
	}
	fprintf(FACET_DATA_FILE,"\n");
	fclose(FACET_DATA_FILE);
	printf("done!\n");
}

/* GENERATE_EDGE_DATA: This function generates the 'edge_data' array for all 
                       possible permutations of a marching cube.
		       */
void generateEdgeData(void)
{
	int found_edge[NUM_CUBE_EDGES]={FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE};
	int i,j,k;

	for (i=0; i<NUM_CUBE_PERMS; i++) 
	{				/* i is the index for facet_data and edge_data */
		for (j=0; j<NUM_CUBE_EDGES; j++) 
		{				/* j counts through edge_list[] */
			for (k=0; k<NUM_CUBE_EDGES; k++) 
			{				/* k counts through facet_data[i][] */
			if (edge_list[j]==facet_data[i][k]) 
			found_edge[j]=TRUE;
			}
		}
		k = 0;			/* k is now a position counter in the edge_data[][] table */
		for (j=0; j<NUM_CUBE_EDGES; j++) 
		{ /* again, j counts through edge_list[] */
			if (found_edge[j])
			{
				edge_data[i][k] = edge_list[j];
				k++;
			}
		}
		while (k < NUM_CUBE_EDGES) 
		{
			edge_data[i][k] = (-1);	/* fill up remaining space */
			k++;
		}
		for (k=0; k<NUM_CUBE_EDGES; k++) /* restore found_edge[] to initial state */
		found_edge[k] = FALSE; 
	}
}

/* PRINT_EDGE_DATA_FILE: Print edge data array to a file. This function is useful for
                         debugging purposes.
			 */
void printEdgeDataFile(void)
{
	FILE *EDGE_DATA_FILE;
	int i,j;
	EDGE_DATA_FILE = fopen("edge_data.tmp","w");

	fprintf(EDGE_DATA_FILE,"\n\nEdge data = \n");
	for (i=0; i<NUM_CUBE_PERMS; i++)
	{
		fprintf(EDGE_DATA_FILE,"%d : ",i);
		for (j=0; j<NUM_CUBE_EDGES; j++)
		fprintf(EDGE_DATA_FILE,"%d ",edge_data[i][j]);
		fprintf(EDGE_DATA_FILE,"\n");
	}
	fprintf(EDGE_DATA_FILE,"\n");
	fclose(EDGE_DATA_FILE);
	printf("done!\n");
}

/* GET_CORNER: This function returns the density value for a particular corner 
               of a cube in marching space.
	       */
short int getCorner(int corner, int imarch, int jmarch)
{
	short int result;
	switch (corner)
	{
		case 0: 
			result = outsideSliceA[imarch*volume->YDim + jmarch];
			break;
		case 1: 
			result = outsideSliceA[(imarch+1)*volume->YDim + jmarch];
			break;
		case 2: 
			result = outsideSliceA[(imarch+1)*volume->YDim + jmarch+1];
			break;
		case 3: 
			result = outsideSliceA[imarch*volume->YDim + jmarch+1];
			break;
		case 4: 
			result = outsideSliceB[imarch*volume->YDim + jmarch];
			break;
		case 5: 
			result = outsideSliceB[(imarch+1)*volume->YDim + jmarch];
			break;
		case 6: 
			result = outsideSliceB[(imarch+1)*volume->YDim + jmarch+1];
			break;
		case 7: 
			result = outsideSliceB[imarch*volume->YDim + jmarch+1];
			break;
	}
	return(result);
}

/* CONTOUR_INTERSECT: Find the intersection point of the contour with the edge of the cube.
                      The current cube is the one at (imarch,jmarch,kmarch).
		      The edge of the cube to find the intersection for is 'edge_name'.
		      The resulting point is stored in 'pt'.
		      */
void contour_intersect(int edge_name, int imarch, int jmarch, int kmarch, point *pt)
{
	short int A=0, B=0, C=0;
	double dist = 0.5;

	A = getCorner(6,imarch,jmarch);
	switch (edge_name)
	{
		case 5:
		C = getCorner(5,imarch,jmarch);
		break;
		case 6:
		C = getCorner(7,imarch,jmarch);
		break;
		case 10:
		C = getCorner(2,imarch,jmarch);
		break;
	}

	if (((A < baseCase) && (C > baseCase)) || ((A > baseCase) && (C < baseCase)))
	{
		dist = (((double)(baseCase - A))/((double)(C - A)));
		switch (edge_name)
		{
			case 5:
				pt->x = (double)imarch + 1;
				pt->y = (double)jmarch + 1 - dist; 
				pt->z = (double)kmarch + 1;
				break;
			case 6:
				pt->x = (double)imarch + 1 - dist;
				pt->y = (double)jmarch + 1;
				pt->z = (double)kmarch + 1;
				break;
			case 10:
				pt->x = (double)imarch + 1;
				pt->y = (double)jmarch + 1;
				pt->z = (double)kmarch + 1 - dist;
				break;
		}
	}
}

/* ADD_VERTEX: This function adds the vertex pointed to by 'pt' into the list 
               of total vertices for the volumetric polygonal model. The index
	       into which the vertex is written is given by 'vert_index'.
	       */
void add_vertex(point *pt)
{
	int sindex;
	double sumSquares;

	if ((pt->x > 0.01) || (pt->y > 0.01) || (pt->z > 0.01))
	{
		vert_index++;
		(vlist+vert_index)->x = pt->x;
		(vlist+vert_index)->y = pt->y;
		(vlist+vert_index)->z = pt->z;
		sindex = (int)rint(pt->x)*volume->YDim + (int)rint(pt->y);
		if (sindex >= volume->YDim)
		{
			(nlist+vert_index)->x = (double)(outsideSliceA[sindex + volume->YDim] - outsideSliceA[sindex - volume->YDim]);
			(nlist+vert_index)->y = (double)(outsideSliceA[sindex + 1] - outsideSliceA[sindex - 1]);
			(nlist+vert_index)->z = (double)(outsideSliceB[sindex] - outsideSliceC[sindex]);

			/* normalize the normals */
			sumSquares = sqrt(((nlist+vert_index)->x * (nlist+vert_index)->x)
				    + ((nlist+vert_index)->y * (nlist+vert_index)->y)
				    + ((nlist+vert_index)->z * (nlist+vert_index)->z));
			if (sumSquares > 0.01)
			{
				(nlist+vert_index)->x = (nlist+vert_index)->x / sumSquares;
				(nlist+vert_index)->y = (nlist+vert_index)->y / sumSquares;
				(nlist+vert_index)->z = (nlist+vert_index)->z / sumSquares;
			}
		}
		else
		{
			(nlist+vert_index)->x = 0.0;
			(nlist+vert_index)->y = 0.0;
			(nlist+vert_index)->z = -1.0;
		}
		numTotalVertices++;
	}
}

/* ADD_FACET: This function adds a facet with 'num_verts' vertices given by
              'vertex_list' into the facet table.
	      */
void add_facet(int num_verts, long vertex_list[])
{
	int i;
	point *pt1,*pt2,*pt3, *npt1, *npt2, *npt3;

	/* allocate memory */
	pt1 = new point;
	pt2 = new point;
	pt3 = new point;
	npt1 = new point;
	npt2 = new point;
	npt3 = new point;

	pt1 = (vlist+vertex_list[0]);
	pt2 = (vlist+vertex_list[1]);
	pt3 = (vlist+vertex_list[2]);
	npt1 = (nlist+vertex_list[0]);
	npt2 = (nlist+vertex_list[1]);
	npt3 = (nlist+vertex_list[2]);
	if (((pt1->x > 0.01) && (pt1->y > 0.01)) && ((pt2->x > 0.01) && (pt2->y > 0.01)) && ((pt3->x > 0.01) && (pt3->y > 0.01)))
	{
		(flist+currentFacetIndex)->pt1 = pt1;
		(flist+currentFacetIndex)->pt2 = pt2;
		(flist+currentFacetIndex)->pt3 = pt3;
		(fnlist+currentFacetIndex)->pt1 = npt1;
		(fnlist+currentFacetIndex)->pt2 = npt2;
		(fnlist+currentFacetIndex)->pt3 = npt3;
		currentFacetIndex++;
	}
}

/* PRINT_VERTICES_FILE: Print the data structure 'vlist' to a file.
   */
void printVerticesFile(void)
{
	FILE *VERTICES_FILE;
	int i;
	VERTICES_FILE = fopen("vertices.tmp","w");

	fprintf(VERTICES_FILE,"\nvlist = \n\n");
	for (i=0; i<numTotalVertices; i++)
	fprintf(VERTICES_FILE,"%d : {%2.2f,%2.2f,%2.2f}\n",i,(vlist+i)->x,(vlist+i)->y,(vlist+i)->z);

	fclose(VERTICES_FILE);
	printf("done!\n");
}

/* PRINT_FACETS_FILE: Print the data structure 'flist' to a file.
   */
void printFacetsFile(void)
{
	FILE *FACETS_FILE;
	int i;
	FACETS_FILE = fopen("facets.tmp","w");

	fprintf(FACETS_FILE,"\nflist = \n\n");
	for (i=0; i<currentFacetIndex; i++)
	{
		fprintf(FACETS_FILE,"%d : {%2.2f,%2.2f,%2.2f}\t{%2.2f,%2.2f,%2.2f}\t{%2.2f,%2.2f,%2.2f}\n",i,
		(flist+i)->pt1->x,(flist+i)->pt1->y,(flist+i)->pt1->z,
		(flist+i)->pt2->x,(flist+i)->pt2->y,(flist+i)->pt2->z,
		(flist+i)->pt3->x,(flist+i)->pt3->y,(flist+i)->pt3->z);
	}
	fclose(FACETS_FILE);
	printf("done!\n");
}

/* CUBE_INDEX: This function analyses a given voxel (from outsideSliceA and 
               outsideSliceB) and returns the cube index of that voxel using
	       the current baseCase values.
	       */
int cube_index(int imarch, int jmarch)
{
	short int corner;
	int i, result = 0;

	for (i=0; i<NUM_CUBE_VERTICES; i++)
	{
		corner = getCorner(i,imarch,jmarch);
		switch (i)
		{
			case 0:
				if (corner > baseCase)
					result += 1;
					break;
			case 1:
				if (corner > baseCase)
					result += 2;
					break;
			case 2:
				if (corner > baseCase)
					result += 4;
					break;
			case 3:
				if (corner > baseCase)
					result += 8;
					break;
			case 4:
				if (corner > baseCase)
					result += 16;
					break;
			case 5:
				if (corner > baseCase)
					result += 32;
					break;
			case 6:
				if (corner > baseCase)
					result += 64;
					break;
			case 7:
				if (corner > baseCase)
					result += 128;
					break;
		}
	}
	return(result);
}

void load_facet(int cube_index, int imarch, int jmarch, int kmarch)
{
	long edge_table[NUM_CUBE_EDGES] = {-99,-99,-99, -99,-99,-99, -99,-99,-99, -99,-99,-99};
	long edge, vertex_list[3];
	long vert_offset;
	long i,j, debugindex;
	long offset;
	point pt;

	static long nrow, ncol;

	nrow = volume->XDim;
	ncol = volume->YDim;

	i=0;
	while (edge_data[cube_index][i] != (-1))
	{
		edge = edge_data[cube_index][i];
		switch (edge)
		{
			case 0:
				offset = ncol*imarch+jmarch;
				vert_offset = xedge[offset];
				break;
			case 1:
				offset = ncol*(imarch+1)+jmarch;
				vert_offset = yedge[offset];
				break;
			case 2:
				offset = ncol*imarch+jmarch+1;
				vert_offset = xedge[offset];
				break;
			case 3:
				offset = ncol*imarch+jmarch;
				vert_offset = yedge[offset];
				break;
			case 4:
				vert_offset = old6pt;
				offset = ncol*imarch+jmarch;
				xedge[offset] = vert_offset;
				break;
			case 5:
				contour_intersect(5,imarch,jmarch,kmarch,&pt);
				add_vertex(&pt);
				topyedge[jmarch] = vert_index;
				vert_offset = vert_index;
				if (imarch == (nrow-2))
				{
				  offset = ncol*(nrow-1)+jmarch;
				  yedge[offset] = vert_index;
				}
				break;
			case 6:
				contour_intersect(6,imarch,jmarch,kmarch,&pt);
				add_vertex(&pt);
				old6pt = vert_index;
				vert_offset = vert_index;
				if (jmarch == (ncol-2))
				{
				  offset = ncol*imarch+ncol-1;
				  xedge[offset] = vert_index;
				}
				break;
			case 7:
				vert_offset = topyedge[jmarch];
				offset = ncol*imarch+jmarch;
				yedge[offset] = vert_offset;
				break;
			case 8:
				vert_offset = zedge[jmarch];
				break;
			case 9:
				vert_offset = old10pt;
				zedge[jmarch] = vert_offset;
				break;
			case 10:
				contour_intersect(10,imarch,jmarch,kmarch,&pt);
				add_vertex(&pt);
				old10pt = vert_index;
				vert_offset = vert_index;
				if (jmarch == (ncol-2))
				{
				  zedge[ncol-1] = vert_offset;
				}
				break;
			case 11:
				vert_offset = zedge[jmarch+1];
				break;
		}
		edge_table[edge] = vert_offset;
		i++;
	}

	/* now add the new facets to the facet table */
	i=0;
	while ((facet_data[cube_index][i] != -1) && (i != NUM_CUBE_EDGES))
	{
		for (j=0; j<3; j++)
		vertex_list[j] = edge_table[facet_data[cube_index][i+j]];
		add_facet(3,vertex_list);
		i += 3;
	}
}

/* DRAW_VOLUME_RBG: Draws the volume data slice by slice in RGB shading form.
   */
void drawVolumeRGB(Volume *vol, int slice)
{
	int i,j;
	double colorval;
	for (i=0; i<vol->XDim; i++)
	{
		for (j=0; j<vol->YDim; j++)
		{
			colorval = ((double)(volumePixel(vol,i,j,slice)))/256.0;
			glColor3f(colorval,colorval,colorval);
			glBegin(GL_POLYGON);
			glVertex3f(i*currentScaleFactorRGB,j*currentScaleFactorRGB,slice);
			glVertex3f((i+1)*currentScaleFactorRGB,j*currentScaleFactorRGB,slice);
			glVertex3f((i+1)*currentScaleFactorRGB,(j+1)*currentScaleFactorRGB,slice);
			glVertex3f(i*currentScaleFactorRGB,(j+1)*currentScaleFactorRGB,slice);
			glEnd();
		}
	}
}

/* DRAW_POLYGONAL_MODEL: This function draws the polygonal model computed
                         by the marching cubes algorithm.
			 */
void drawPolygonalModel(void)
{
	int i;

	/*glTranslatef(-256.0,-256.0,0.0);
	glRotatef(45.0,0.0,1.0,0.0);
	glTranslatef(256.0,256.0,0.0);*/

	chooseColor(WHITE);
	for (i=0; i<currentFacetIndex; i++)
	{
		glBegin(GL_POLYGON);
		glVertex3f(currentScaleFactorRGB*(flist+i)->pt1->x,
		 currentScaleFactorRGB*(flist+i)->pt1->y,
		 currentScaleFactorRGB*(flist+i)->pt1->z);
		glNormal3f((fnlist+i)->pt1->x,(fnlist+i)->pt1->y,(fnlist+i)->pt1->z);
		glVertex3f(currentScaleFactorRGB*(flist+i)->pt2->x,
		 currentScaleFactorRGB*(flist+i)->pt2->y,
		 currentScaleFactorRGB*(flist+i)->pt2->z);
		glNormal3f((fnlist+i)->pt2->x,(fnlist+i)->pt2->y,(fnlist+i)->pt2->z);
		glVertex3f(currentScaleFactorRGB*(flist+i)->pt3->x,
		 currentScaleFactorRGB*(flist+i)->pt3->y,
		 currentScaleFactorRGB*(flist+i)->pt3->z);
		glNormal3f((fnlist+i)->pt3->x,(fnlist+i)->pt3->y,(fnlist+i)->pt3->z);
		glEnd();
	}
}

/* COMPUTE_POLYGONAL_MODEL: This functions computes the polygonal model 
                            for a given data set using the marching cubes 
			    algorithm.
			    */
void computePolygonalModel(void)
{
	int i,j,sliceNum,l;
	int nrow,ncol,NK,NCI,NCJ,NCK;
	int cubeIndex;
	int pt_ij, pt_i1j, pt_ij1, pt_ijk, pt_ijk1, pt_i1jk, pt_i1jk1, pt_ij1k1, pt_k, pt_k1;
	double dist;
	point *pt;

	printf("Computing the polygonal model ... \n");

	generateFacetData();
	generateEdgeData();
	initStructures();

	nrow = volume->XDim;   /* no of density points along the x-direction */
	ncol = volume->YDim;   /* no of density points along the y-direction */
	NK = volume->ZDim;   /* no of density points along the z-direction */
	NCI = nrow-1;  /* no of cubes along the x-direction */
	NCJ = ncol-1;  /* no of cubes along the y-direction */
	NCK = NK-1;  /* no of cubes along the z-direction */

	pt = (point *)malloc(sizeof(point));

	for (sliceNum = 0; sliceNum < (NK-1); sliceNum++)
	{
		if (sliceNum == 0)
		{
			/* read in the first two slices */
			for (i=0; i<nrow; i++)
			for (j=0; j<ncol; j++)
			  {
			outsideSliceA[i*ncol + j] = volumePixel(volume,i,j,0);
			outsideSliceB[i*ncol + j] = volumePixel(volume,i,j,1);
			outsideSliceC[i*ncol + j] = outsideSliceA[i*ncol + j];
			  }

			/* compute xedge for the first slice */
			for (i=0; i<(nrow-1); i++)
			for (j=0; j<ncol; j++)
			  {
			pt_ij = outsideSliceA[i*ncol + j];
			pt_i1j = outsideSliceA[(i+1)*ncol + j];
			if (((pt_ij <= baseCase) && (pt_i1j > baseCase))
			    || ((pt_ij > baseCase) && (pt_i1j <= baseCase)))
			  {
			    dist = (((double)(baseCase - pt_ij))/((double)(pt_i1j - pt_ij)));
			    pt->x = i+dist;
			    pt->y = j;
			    pt->z = 0;
			    add_vertex(pt);
			    xedge[i*ncol + j] = vert_index;
			  }
			else
			  xedge[i*ncol + j] = 0;
			  }

			/* compute yedge for the first slice */
			for (i=0; i<nrow; i++)
			for (j=0; j<(ncol-1); j++)
			  {
			pt_ij = outsideSliceA[i*ncol + j];
			pt_ij1 = outsideSliceA[i*ncol + (j+1)];
			if (((pt_ij <= baseCase) && (pt_ij1 > baseCase))
			    || ((pt_ij > baseCase) && (pt_ij1 <= baseCase)))
			  {
			    dist = (((double)(baseCase - pt_ij))/((double)(pt_ij1 - pt_ij)));
			    pt->x = i;
			    pt->y = j+dist;
			    pt->z = 0;
			    add_vertex(pt);
			    yedge[i*ncol + j] = vert_index;
			  }
			else
			  yedge[i*ncol + j] = 0;
			  }
		}
		else
		{
		/* copy 'outsideSliceB' into 'outsideSliceA' and read in slice (sliceNum+1)
		 into 'outsideSliceB'. Also, transfer 'outsideSliceA' to 'outsideSliceC' */
		for (i=0; i<nrow; i++)
		for (j=0; j<ncol; j++)
		  outsideSliceC[i*ncol + j] = outsideSliceA[i*ncol + j];
		for (i=0; i<nrow; i++)
		for (j=0; j<ncol; j++)
		  outsideSliceA[i*ncol + j] = outsideSliceB[i*ncol + j];
		for (i=0; i<nrow; i++)
		for (j=0; j<ncol; j++)
		  outsideSliceB[i*ncol + j] = volumePixel(volume,i,j,(sliceNum+1));
		}

		/* for each row (i.e., i = constant) */
		for (i=0; i<(nrow-1); i++)
		{
		/* load zedge and topyedge for the first row of each slice */
			if (i==0)
			{
			  	/* compute zedge */
				for (j=0; j<ncol; j++)
				{
					pt_k = outsideSliceA[i*ncol + j];
					pt_k1 = outsideSliceB[i*ncol + j];
					if (((pt_k <= baseCase) && (pt_k1 > baseCase))
					  || ((pt_k > baseCase) && (pt_k1 <= baseCase)))
					{
						dist = (((double)(baseCase - pt_k))/((double)(pt_k1 - pt_k)));
						pt->x = i;
						pt->y = j;
						pt->z = sliceNum+dist;
						add_vertex(pt);
						zedge[j] = vert_index;
					}
					else
						zedge[j] = 0;
				}
			  
			  	/* compute topyedge */
				for (j=0; j<(ncol-1); j++)
				{
					pt_ijk1 = outsideSliceB[i*ncol + j];
					pt_ij1k1 = outsideSliceB[i*ncol + (j+1)];
					if (((pt_ijk1 <= baseCase) && (pt_ij1k1 > baseCase))
					  || ((pt_ijk1 > baseCase) && (pt_ij1k1 <= baseCase)))
					{
						dist = (((double)(baseCase - pt_ijk1))/((double)(pt_ij1k1 - pt_ijk1)));
						pt->x = i;
						pt->y = j+dist;
						pt->z = sliceNum+1;
						add_vertex(pt);
						topyedge[j] = vert_index;
					}
					else
						topyedge[j] = 0;
				}
			}

		/* for each cube in the row */
		for (j=0; j<(ncol-1); j++)
		{
		  /* load old6pt and old10pt for the first cube of each row in each slice */
		  if (j==0)
		{
		  /* compute old6pt */
		  pt_ijk1 = outsideSliceB[i*ncol + j];
		  pt_i1jk1 = outsideSliceB[(i+1)*ncol + j];
		  if (((pt_ijk1 < baseCase) && (pt_i1jk1 > baseCase))
		      || ((pt_ijk1 > baseCase) && (pt_i1jk1 < baseCase)))
		    {
		      dist = (((double)(baseCase - pt_ijk1))/((double)(pt_i1jk1 - pt_ijk1)));
		      pt->x = i+dist;
		      pt->y = j;
		      pt->z = sliceNum+1;
		      add_vertex(pt);
		      old6pt = vert_index;
		    }
		  else
		    old6pt = -1;

		  /* compute old10pt */
		  pt_i1jk1 = outsideSliceB[(i+1)*ncol + j];
		  pt_i1jk = outsideSliceA[(i+1)*ncol + j];
		  if (((pt_i1jk1 < baseCase) && (pt_i1jk > baseCase))
		      || ((pt_i1jk1 > baseCase) && (pt_i1jk < baseCase)))
		    {
		      dist = (((double)(baseCase - pt_i1jk1))/((double)(pt_i1jk - pt_i1jk1)));
		      pt->x = i+1;
		      pt->y = j;
		      pt->z = sliceNum+dist;
		      add_vertex(pt);
		      old10pt = vert_index;
		    }
		  else
		    old10pt = -1;
		}

		  cubeIndex = cube_index(i,j);
		  if ((cubeIndex != 0) && (cubeIndex != 255))
		load_facet(cubeIndex,i,j,sliceNum);
		}
		}
	}
	printf("done!\n");
}

/* RESHAPE: Callback function for a reshape event inrowtiated by the user
	    The input parameters 'width' and 'height' specify the current 
	    width and height of the window.
	    */
void reshape(int width, int height)
{
  /* change viewport dimensions */
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, width, 0, height, 1000, -1000);
  glMatrixMode(GL_MODELVIEW);
}

/* DISPLAY: Callback function for a redisplay event initiated by the user or
            by the application itself.
	    */
void display(void)
{
  /* clear the display */
  glClear(GL_COLOR_BUFFER_BIT|GL_STENCIL_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

  if (!volume)
    selectDataSet(currentVolumeDataSet);

  if (displayType == RGB_SLICE_DISPLAY)
    drawVolumeRGB(volume,currentSliceRGB);
  else if (displayType == POLYGONAL_DISPLAY)
    drawPolygonalModel();

  /* swap the double buffers */
  glutSwapBuffers();  
}

void keyboard(int key, int x, int y)
{
}

/* KEYBOARDSPECIAL: Callback function to handle special key keyboard operations (arrow keys).
                    The input parameter 'key' specifies the key pressed by the user.
		    The parameters 'x' and 'y' specify the current mouse position.
		    */
void keyboardHandler(int key, int x, int y)
{
  switch (key)
    {
    case GLUT_KEY_UP:
      if (volume)
	{
	  currentSliceRGB++;
	  if (currentSliceRGB >= volume->ZDim)
	    currentSliceRGB = 0;
	}
      display();
      break;
    case GLUT_KEY_DOWN:
      if (volume)
	{
	  currentSliceRGB--;
	  if (currentSliceRGB < 0)
	    currentSliceRGB = volume->ZDim-1;
	}
      display();
      break;
    }
}

/* CREATEMENUS: function to create pulldown menus for the curve editing window.void createMenus(void)
{
  int dataSetMenu;

  dataSetMenu = glutCreateMenu(selectDataSet);
  glutAddMenuEntry("Torso: 128x128",TORSO_128_DATA_SET);
  glutAddMenuEntry("Torso: 256x256",TORSO_256_DATA_SET);
  glutAddMenuEntry("Torso: 512x512",TORSO_512_DATA_SET);
  glutAddMenuEntry("Lobster",LOBSTER_DATA_SET);
  glutAddMenuEntry("Hydrogen",HYDROGEN_DATA_SET);
  glutAddMenuEntry("Vol_Tesla",VOL_TESLA_DATA_SET);

  glutCreateMenu(selectOption);
  glutAddSubMenu("Choose data set",dataSetMenu);
  if (displayType == RGB_SLICE_DISPLAY)
    glutAddMenuEntry("Switch to polygonal model",'w');
  else if (displayType == POLYGONAL_DISPLAY)
    glutAddMenuEntry("Switch to RGB slices",'w');
  glutAddMenuEntry("Clear screen", 's');
  glutAddMenuEntry("Exit", 'e');

  /* attach all menus to the right mouse button/
  glutAttachMenu(GLUT_RIGHT_BUTTON);
}*/

/* INIT_LIGHTING: Initialize light sources' attributes and positions for the scene.
 */

/*void initLighting(void)
{
  GLfloat lightPosition[] = {0.0,0.0,1.0,0.0};
  GLfloat lightAmbient[] = {0.0,0.0,0.0,1.0};
  GLfloat lightDiffuse[] = {1.0,1.0,1.0,1.0};

  /* define properties of the lighting model 
  glShadeModel(GL_SMOOTH);

  /* define the properties of Light Source 0 
  glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
  glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);

  /* enable required lights and depth testing 
  if (displayType == POLYGONAL_DISPLAY)
    {
      glEnable(GL_LIGHTING);
      glEnable(GL_LIGHT0);
      glEnable(GL_DEPTH_TEST);
      glEnable(GL_NORMALIZE);
    }
  else if (displayType == RGB_SLICE_DISPLAY)
    {
      glDisable(GL_LIGHTING);
      glDisable(GL_LIGHT0);
      glDisable(GL_DEPTH_TEST);      
      glDisable(GL_NORMALIZE);
    }
}*/
