#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <string>
#include <fstream>
#include <GL/glut.h>
#include "const.h"
#include "callbacks.h"
#include "data.h"
#include "cube.h"
using namespace std;


static int currentButton;
static int displayType = 1;
static int currentVolumeDataSet = TORSO_256_DATA_SET;
static int currentSliceRGB = 0;
static int currentScaleFactorRGB = TORSO_256_SCALE;
static int numTotalVertices = 0;
static int currentFacetIndex = 0;

/* volume data set */
static VolumeData* volume;
static Point3* vertices_list;
static Point3* normals_list;
static Triangle* facet_list;
static Triangle* facet_normals_list;


static short int *outsideSliceA, *outsideSliceB, *outsideSliceC;
static long *xedge, *yedge, *zedge, *topyedge;
static long old6pt, old10pt;
static long vert_index = 0;
static long Threshold = 50;


void select_data_layer(int option)
{
    switch (option)
    {
        case 'w':
            displayType = 1 - displayType;
            display();
            break;
        case 's':
            glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            break;
        case 'e':
            if (volume)
                deleteVolume(volume);
            delete_Structure_Data();
            exit(0);
            break;
    }
}

void initialize_Structure_Data(void)
{
    int i;

    if (!outsideSliceC)
        outsideSliceC = new short int[volume->XDim * volume->YDim];
    if (!outsideSliceA)
        outsideSliceA = new short int[volume->XDim * volume->YDim];
    if (!outsideSliceB)
        outsideSliceB = new short int[volume->XDim * volume->YDim];
    if (!xedge)
        xedge = new long[volume->XDim * volume->YDim];
    if (!yedge)
        yedge = new long[volume->XDim * volume->YDim];
    if (!zedge)
        zedge = new long[volume->YDim];
    if (!topyedge)
        topyedge = new long[volume->YDim];
    if (!vertices_list)
        vertices_list = new Point3[500000];
    if (!normals_list)
        normals_list = new Point3[500000];
    if (!facet_list)
    {

        facet_list = (Triangle*)malloc(sizeof(Triangle) * 500000);
        for (i = 0; i < 500000; i++)
        {
            (facet_list + i)->pt1 = new Point3;
            (facet_list + i)->pt2 = new Point3;
            (facet_list + i)->pt3 = new Point3;
        }
    }
    if (!facet_normals_list)
    {
        facet_normals_list = (Triangle*)malloc(sizeof(Triangle) * 500000);
        for (i = 0; i < 500000; i++)
        {
            (facet_normals_list + i)->pt1 = new Point3;
            (facet_normals_list + i)->pt2 = new Point3;
            (facet_normals_list + i)->pt3 = new Point3;
        }
    }
}

void delete_Structure_Data(void)
{
    int i;

    if (outsideSliceA)
        delete(outsideSliceA);
    if (outsideSliceB)
        delete(outsideSliceB);
    if (outsideSliceC)
        delete(outsideSliceC);
    if (xedge)
        delete(xedge);
    if (yedge)
        delete(yedge);
    if (zedge)
        delete(zedge);
    if (topyedge)
        delete(topyedge);
    if (vertices_list)
        delete(vertices_list);
    if (normals_list)
        delete(normals_list);
    if (facet_list)
    {
        for (i = (500000 - 1); i > 0; i--)
        {
            delete((facet_list + i)->pt1);
            delete((facet_list + i)->pt2);
            delete((facet_list + i)->pt3);
        }
        delete(facet_list);
    }
    if (facet_normals_list)
    {
        for (i = (500000 - 1); i > 0; i--)
        {
            delete((facet_normals_list + i)->pt1);
            delete((facet_normals_list + i)->pt2);
            delete((facet_normals_list + i)->pt3);
        }
        delete(facet_normals_list);
    }
}

void generate_facet_Data(void)
{
    int i, j, k, l, cube_index;

    for (i = 0; i < NUM_CUBE_PERMS; i++)
    {
        for (j = 0; j < NUM_BASIS_CUBES; j++)
        {
            for (k = 0; k < NUM_CUBE_ROTATIONS; k++)
            {
                cube_index = 0;
                for (l = 0; l < NUM_CUBE_VERTICES; l++)
                {
                    if (init_facet_index[j][l])
                        cube_index |= (1 << corner_rotation[k][l]);
                }

                if (cube_index == i)
                {
                    for (l = 0; l < NUM_CUBE_EDGES; l++)
                    {
                        if (init_facet_data[j][l] >= 0)
                        {
                            facet_data[i][l] = edge_rotation[k][init_facet_data[j][l]];
                            facet_data[0xFF - i][l] = edge_rotation[k][init_facet_data[j][l]];
                        }
                        else
                        {
                            facet_data[i][l] = (-1);
                            facet_data[0xFF - i][l] = (-1);
                        }
                    }
                }
            }
        }
    }
}


void printFacetDataFile(void)
{
    FILE* FACET_DATA_FILE;
    int i, j;

    printf("Writing facet data to file ... ");
    FACET_DATA_FILE = fopen("facet_data.tmp", "w");

    fprintf(FACET_DATA_FILE, "\n\nFacet data = \n");
    for (i = 0; i < NUM_CUBE_PERMS; i++)
    {
        fprintf(FACET_DATA_FILE, "%d : ", i);
        for (j = 0; j < NUM_CUBE_EDGES; j++)
            fprintf(FACET_DATA_FILE, "%d ", facet_data[i][j]);
        fprintf(FACET_DATA_FILE, "\n");
    }
    fprintf(FACET_DATA_FILE, "\n");

    fclose(FACET_DATA_FILE);
    printf("done!\n");
}


void generateEdgeData(void)
{
    int found_edge[NUM_CUBE_EDGES]
        = { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE };
    int i, j, k;

    for (i = 0; i < NUM_CUBE_PERMS; i++)
    {
        for (j = 0; j < NUM_CUBE_EDGES; j++)
        {
            for (k = 0; k < NUM_CUBE_EDGES; k++)
            {
                if (edge_list[j] == facet_data[i][k])
                    found_edge[j] = TRUE;
            }
        }

        k = 0;
        for (j = 0; j < NUM_CUBE_EDGES; j++)
        {
            if (found_edge[j])
            {
                edge_data[i][k] = edge_list[j];
                k++;
            }
        }

        while (k < NUM_CUBE_EDGES)
        {
            edge_data[i][k] = (-1);
            k++;
        }

        for (k = 0; k < NUM_CUBE_EDGES; k++)
            found_edge[k] = FALSE;
    }
}


void printEdgeDataFile(void)
{
    FILE* EDGE_DATA_FILE;
    int i, j;

    printf("Writing edge data to file ... ");
    EDGE_DATA_FILE = fopen("edge_data.tmp", "w");

    fprintf(EDGE_DATA_FILE, "\n\nEdge data = \n");
    for (i = 0; i < NUM_CUBE_PERMS; i++)
    {
        fprintf(EDGE_DATA_FILE, "%d : ", i);
        for (j = 0; j < NUM_CUBE_EDGES; j++)
            fprintf(EDGE_DATA_FILE, "%d ", edge_data[i][j]);
        fprintf(EDGE_DATA_FILE, "\n");
    }
    fprintf(EDGE_DATA_FILE, "\n");

    fclose(EDGE_DATA_FILE);
    printf("done!\n");
}


short int getCorner(int corner, int imarch, int jmarch)
{
    short int result;

    switch (corner)
    {
        case 0:
            result = outsideSliceA[imarch * volume->YDim + jmarch];
            break;
        case 1:
            result = outsideSliceA[(imarch + 1) * volume->YDim + jmarch];
            break;
        case 2:
            result = outsideSliceA[(imarch + 1) * volume->YDim + jmarch + 1];
            break;
        case 3:
            result = outsideSliceA[imarch * volume->YDim + jmarch + 1];
            break;
        case 4:
            result = outsideSliceB[imarch * volume->YDim + jmarch];
            break;
        case 5:
            result = outsideSliceB[(imarch + 1) * volume->YDim + jmarch];
            break;
        case 6:
            result = outsideSliceB[(imarch + 1) * volume->YDim + jmarch + 1];
            break;
        case 7:
            result = outsideSliceB[imarch * volume->YDim + jmarch + 1];
            break;
    }

    return (result);
}


void contour_intersect(
    int edge_name, int imarch, int jmarch, int kmarch, Point3* pt) // linear interpolation wala
{
    short int A = 0, B = 0, C = 0;
    double dist = 0.5;

    A = getCorner(6, imarch, jmarch);
    switch (edge_name)
    {
        case 5:
            C = getCorner(5, imarch, jmarch);
            break;
        case 6:
            C = getCorner(7, imarch, jmarch);
            break;
        case 10:
            C = getCorner(2, imarch, jmarch);
            break;
    }

    if (((A < Threshold) && (C > Threshold)) || ((A > Threshold) && (C < Threshold)))
    {
        dist = (((double)(Threshold - A)) / ((double)(C - A)));

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


void add_vertex(Point3* pt)
{
    int sindex;
    double sumSquares;

    if ((pt->x > 0.01) || (pt->y > 0.01) || (pt->z > 0.01))
    {
        vert_index++;

        (vertices_list + vert_index)->x = pt->x;
        (vertices_list + vert_index)->y = pt->y;
        (vertices_list + vert_index)->z = pt->z;

        /* calculate the surface normals at each vertex */
        sindex = (int)rint(pt->x) * volume->YDim + (int)rint(pt->y);
        if (sindex >= volume->YDim)
        {
            (normals_list + vert_index)->x = (double)(outsideSliceA[sindex + volume->YDim]
                - outsideSliceA[sindex - volume->YDim]);
            (normals_list + vert_index)->y
                = (double)(outsideSliceA[sindex + 1] - outsideSliceA[sindex - 1]);
            (normals_list + vert_index)->z
                = (double)(outsideSliceB[sindex] - outsideSliceC[sindex]);

            /* normalize the normals */
            sumSquares = sqrt(((normals_list + vert_index)->x * (normals_list + vert_index)->x)
                + ((normals_list + vert_index)->y * (normals_list + vert_index)->y)
                + ((normals_list + vert_index)->z * (normals_list + vert_index)->z));
            if (sumSquares > 0.01)
            {
                (normals_list + vert_index)->x = (normals_list + vert_index)->x / sumSquares;
                (normals_list + vert_index)->y = (normals_list + vert_index)->y / sumSquares;
                (normals_list + vert_index)->z = (normals_list + vert_index)->z / sumSquares;
            }
        }
        else
        {
            (normals_list + vert_index)->x = 0.0;
            (normals_list + vert_index)->y = 0.0;
            (normals_list + vert_index)->z = -1.0;
        }

        numTotalVertices++;
    }
}


void add_facet(int num_verts, long vertex_list[])
{
    int i;
    Point3 *pt1, *pt2, *pt3, *npt1, *npt2, *npt3;

    /* allocate memory */
    pt1 = (Point3*)malloc(sizeof(Point3));
    pt2 = (Point3*)malloc(sizeof(Point3));
    pt3 = (Point3*)malloc(sizeof(Point3));
    npt1 = (Point3*)malloc(sizeof(Point3));
    npt2 = (Point3*)malloc(sizeof(Point3));
    npt3 = (Point3*)malloc(sizeof(Point3));

    pt1 = (vertices_list + vertex_list[0]);
    pt2 = (vertices_list + vertex_list[1]);
    pt3 = (vertices_list + vertex_list[2]);
    npt1 = (normals_list + vertex_list[0]);
    npt2 = (normals_list + vertex_list[1]);
    npt3 = (normals_list + vertex_list[2]);
    if (((pt1->x > 0.01) && (pt1->y > 0.01)) && ((pt2->x > 0.01) && (pt2->y > 0.01))
        && ((pt3->x > 0.01) && (pt3->y > 0.01)))
    {
        (facet_list + currentFacetIndex)->pt1 = pt1;
        (facet_list + currentFacetIndex)->pt2 = pt2;
        (facet_list + currentFacetIndex)->pt3 = pt3;
        (facet_normals_list + currentFacetIndex)->pt1 = npt1;
        (facet_normals_list + currentFacetIndex)->pt2 = npt2;
        (facet_normals_list + currentFacetIndex)->pt3 = npt3;
        currentFacetIndex++;
    }
}


void printVerticesFile(void)
{
    FILE* VERTICES_FILE;
    int i;

    printf("Writing vertex data to file ... ");
    VERTICES_FILE = fopen("vertices.tmp", "w");

    fprintf(VERTICES_FILE, "\nvertices_list = \n\n");
    for (i = 0; i < numTotalVertices; i++)
        fprintf(VERTICES_FILE, "%d : {%2.2f,%2.2f,%2.2f}\n", i, (vertices_list + i)->x,
            (vertices_list + i)->y, (vertices_list + i)->z);

    fclose(VERTICES_FILE);
    printf("done!\n");
}


void printFacetsFile(void)
{
    FILE* FACETS_FILE;
    int i;

    printf("Writing facets list to file ... ");
    FACETS_FILE = fopen("facets.tmp", "w");

    fprintf(FACETS_FILE, "\nfacet_list = \n\n");
    for (i = 0; i < currentFacetIndex; i++)
        fprintf(FACETS_FILE, "%d : {%2.2f,%2.2f,%2.2f}\t{%2.2f,%2.2f,%2.2f}\t{%2.2f,%2.2f,%2.2f}\n",
            i, (facet_list + i)->pt1->x, (facet_list + i)->pt1->y, (facet_list + i)->pt1->z,
            (facet_list + i)->pt2->x, (facet_list + i)->pt2->y, (facet_list + i)->pt2->z,
            (facet_list + i)->pt3->x, (facet_list + i)->pt3->y, (facet_list + i)->pt3->z);

    fclose(FACETS_FILE);
    printf("done!\n");
}


int cube_index(int imarch, int jmarch)
{
    short int corner;
    int i, result = 0;

    for (i = 0; i < NUM_CUBE_VERTICES; i++)
    {
        corner = getCorner(i, imarch, jmarch);
        switch (i)
        {
            case 0:
                if (corner > Threshold)
                    result += 1;
                break;
            case 1:
                if (corner > Threshold)
                    result += 2;
                break;
            case 2:
                if (corner > Threshold)
                    result += 4;
                break;
            case 3:
                if (corner > Threshold)
                    result += 8;
                break;
            case 4:
                if (corner > Threshold)
                    result += 16;
                break;
            case 5:
                if (corner > Threshold)
                    result += 32;
                break;
            case 6:
                if (corner > Threshold)
                    result += 64;
                break;
            case 7:
                if (corner > Threshold)
                    result += 128;
                break;
        }
    }

    return (result);
}

void load_facet(int cube_index, int imarch, int jmarch, int kmarch)
{
    long edge_table[NUM_CUBE_EDGES]
        = { -99, -99, -99, -99, -99, -99, -99, -99, -99, -99, -99, -99 };
    long edge, vertex_list[3];
    long vert_offset;
    long i, j, debugindex;
    long offset;
    Point3 pt;

    static long NI, NJ;

    NI = volume->XDim;
    NJ = volume->YDim;

    i = 0;
    while (edge_data[cube_index][i] != (-1))
    {
        edge = edge_data[cube_index][i];
        switch (edge)
        {
            case 0:
                offset = NJ * imarch + jmarch;
                vert_offset = *(xedge + offset);
                break;
            case 1:
                offset = NJ * (imarch + 1) + jmarch;
                vert_offset = *(yedge + offset);
                break;
            case 2:
                offset = NJ * imarch + jmarch + 1;
                vert_offset = *(xedge + offset);
                break;
            case 3:
                offset = NJ * imarch + jmarch;
                vert_offset = *(yedge + offset);
                break;
            case 4:
                vert_offset = old6pt;
                offset = NJ * imarch + jmarch;
                *(xedge + offset) = vert_offset;
                break;
            case 5:
                contour_intersect(5, imarch, jmarch, kmarch, &pt);
                add_vertex(&pt);
                *(topyedge + jmarch) = vert_index;
                vert_offset = vert_index;
                if (imarch == (NI - 2))
                {
                    offset = NJ * (NI - 1) + jmarch;
                    *(yedge + offset) = vert_index;
                }
                break;
            case 6:
                contour_intersect(6, imarch, jmarch, kmarch, &pt);
                add_vertex(&pt);
                old6pt = vert_index;
                vert_offset = vert_index;
                if (jmarch == (NJ - 2))
                {
                    offset = NJ * imarch + NJ - 1;
                    *(xedge + offset) = vert_index;
                }
                break;
            case 7:
                vert_offset = *(topyedge + jmarch);
                offset = NJ * imarch + jmarch;
                *(yedge + offset) = vert_offset;
                break;
            case 8:
                vert_offset = *(zedge + jmarch);
                break;
            case 9:
                vert_offset = old10pt;
                *(zedge + jmarch) = vert_offset;
                break;
            case 10:
                contour_intersect(10, imarch, jmarch, kmarch, &pt);
                add_vertex(&pt);
                old10pt = vert_index;
                vert_offset = vert_index;
                if (jmarch == (NJ - 2))
                {
                    *(zedge + NJ - 1) = vert_offset;
                }
                break;
            case 11:
                vert_offset = *(zedge + jmarch + 1);
                break;
        }
        edge_table[edge] = vert_offset;
        i++;
    }

    i = 0;
    while ((facet_data[cube_index][i] != -1) && (i != NUM_CUBE_EDGES))
    {
        for (j = 0; j < 3; j++)
            vertex_list[j] = edge_table[facet_data[cube_index][i + j]];
        add_facet(3, vertex_list);
        i += 3;
    }
}


void drawVolumeRGB(VolumeData* vol, int slice)
{
    int i, j;
    double colorval;

    printf("Z slice = %d\n", slice);

    for (i = 0; i < vol->XDim; i++)
        for (j = 0; j < vol->YDim; j++)
        {
            colorval = ((double)(volumePixel(vol, i, j, slice))) / 256.0;
            glColor3f(colorval, colorval, colorval);

            glBegin(GL_POLYGON);
            glVertex3f(i * currentScaleFactorRGB, j * currentScaleFactorRGB, slice);
            glVertex3f((i + 1) * currentScaleFactorRGB, j * currentScaleFactorRGB, slice);
            glVertex3f((i + 1) * currentScaleFactorRGB, (j + 1) * currentScaleFactorRGB, slice);
            glVertex3f(i * currentScaleFactorRGB, (j + 1) * currentScaleFactorRGB, slice);
            glEnd();
        }
}


void drawPolygonalModel(void)
{
    int i;
    ofstream ofil;
    ofil.open("tfile.mohit");
    glColor3f(1.0, 1.0, 1.0);
    for (i = 0; i < currentFacetIndex; i++)
    {
        ofil<<currentScaleFactorRGB *(facet_list + i)->pt1->x<<" "<<currentScaleFactorRGB *(facet_list + i)->pt1->y<<" "<<currentScaleFactorRGB *(facet_list + i)->pt1->z<<" ";
        ofil<<currentScaleFactorRGB *(facet_list + i)->pt2->x<<" "<<currentScaleFactorRGB *(facet_list + i)->pt2->y<<" "<<currentScaleFactorRGB *(facet_list + i)->pt2->z<<" ";
        ofil<<currentScaleFactorRGB *(facet_list + i)->pt3->x<<" "<<currentScaleFactorRGB *(facet_list + i)->pt3->y<<" "<<currentScaleFactorRGB *(facet_list + i)->pt3->z<<endl;

        glBegin(GL_POLYGON);
        glVertex3f(currentScaleFactorRGB * (facet_list + i)->pt1->x,
            currentScaleFactorRGB * (facet_list + i)->pt1->y,
            currentScaleFactorRGB * (facet_list + i)->pt1->z);
        glNormal3f((facet_normals_list + i)->pt1->x, (facet_normals_list + i)->pt1->y,
            (facet_normals_list + i)->pt1->z);
        glVertex3f(currentScaleFactorRGB * (facet_list + i)->pt2->x,
            currentScaleFactorRGB * (facet_list + i)->pt2->y,
            currentScaleFactorRGB * (facet_list + i)->pt2->z);
        glNormal3f((facet_normals_list + i)->pt2->x, (facet_normals_list + i)->pt2->y,
            (facet_normals_list + i)->pt2->z);
        glVertex3f(currentScaleFactorRGB * (facet_list + i)->pt3->x,
            currentScaleFactorRGB * (facet_list + i)->pt3->y,
            currentScaleFactorRGB * (facet_list + i)->pt3->z);
        glNormal3f((facet_normals_list + i)->pt3->x, (facet_normals_list + i)->pt3->y,
            (facet_normals_list + i)->pt3->z);
        glEnd();
    }
    ofil.close();
}


void computePolygonalModel(void)
{
    int i, j, sliceNum, l;
    int NI, NJ, NK, NCI, NCJ, NCK;
    int cubeIndex;
    int pt_ij, pt_i1j, pt_ij1, pt_ijk, pt_ijk1, pt_i1jk, pt_i1jk1, pt_ij1k1, pt_k, pt_k1;
    double dist;
    Point3* pt;
    generate_facet_Data();
    generateEdgeData();
    initialize_Structure_Data();

    NI = volume->XDim;
    NJ = volume->YDim;
    NK = volume->ZDim;
    NCI = NI - 1;
    NCJ = NJ - 1;
    NCK = NK - 1;

    pt = (Point3*)malloc(sizeof(Point3));

    for (sliceNum = 0; sliceNum < (NK - 1); sliceNum++)
    {
        if (sliceNum == 0)
        {
            for (i = 0; i < NI; i++)
                for (j = 0; j < NJ; j++)
                {
                    outsideSliceA[i * NJ + j] = volumePixel(volume, i, j, 0);
                    outsideSliceB[i * NJ + j] = volumePixel(volume, i, j, 1);
                    outsideSliceC[i * NJ + j] = outsideSliceA[i * NJ + j];
                }

            for (i = 0; i < (NI - 1); i++)
                for (j = 0; j < NJ; j++)
                {
                    pt_ij = outsideSliceA[i * NJ + j];
                    pt_i1j = outsideSliceA[(i + 1) * NJ + j];
                    if (((pt_ij <= Threshold) && (pt_i1j > Threshold))
                        || ((pt_ij > Threshold) && (pt_i1j <= Threshold)))
                    {
                        dist = (((double)(Threshold - pt_ij)) / ((double)(pt_i1j - pt_ij)));
                        pt->x = i + dist;
                        pt->y = j;
                        pt->z = 0;
                        add_vertex(pt);
                        xedge[i * NJ + j] = vert_index;
                    }
                    else
                        xedge[i * NJ + j] = 0;
                }

            for (i = 0; i < NI; i++)
                for (j = 0; j < (NJ - 1); j++)
                {
                    pt_ij = outsideSliceA[i * NJ + j];
                    pt_ij1 = outsideSliceA[i * NJ + (j + 1)];
                    if (((pt_ij <= Threshold) && (pt_ij1 > Threshold))
                        || ((pt_ij > Threshold) && (pt_ij1 <= Threshold)))
                    {
                        dist = (((double)(Threshold - pt_ij)) / ((double)(pt_ij1 - pt_ij)));
                        pt->x = i;
                        pt->y = j + dist;
                        pt->z = 0;
                        add_vertex(pt);
                        yedge[i * NJ + j] = vert_index;
                    }
                    else
                        yedge[i * NJ + j] = 0;
                }
        }
        else
        {
            for (i = 0; i < NI; i++)
                for (j = 0; j < NJ; j++)
                    outsideSliceC[i * NJ + j] = outsideSliceA[i * NJ + j];
            for (i = 0; i < NI; i++)
                for (j = 0; j < NJ; j++)
                    outsideSliceA[i * NJ + j] = outsideSliceB[i * NJ + j];
            for (i = 0; i < NI; i++)
                for (j = 0; j < NJ; j++)
                    outsideSliceB[i * NJ + j] = volumePixel(volume, i, j, (sliceNum + 1));
        }


        for (i = 0; i < (NI - 1); i++)
        {
            if (i == 0)
            {
                for (j = 0; j < NJ; j++)
                {
                    pt_k = outsideSliceA[i * NJ + j];
                    pt_k1 = outsideSliceB[i * NJ + j];
                    if (((pt_k <= Threshold) && (pt_k1 > Threshold))
                        || ((pt_k > Threshold) && (pt_k1 <= Threshold)))
                    {
                        dist = (((double)(Threshold - pt_k)) / ((double)(pt_k1 - pt_k)));
                        pt->x = i;
                        pt->y = j;
                        pt->z = sliceNum + dist;
                        add_vertex(pt);
                        zedge[j] = vert_index;
                    }
                    else
                        zedge[j] = 0;
                }

                for (j = 0; j < (NJ - 1); j++)
                {
                    pt_ijk1 = outsideSliceB[i * NJ + j];
                    pt_ij1k1 = outsideSliceB[i * NJ + (j + 1)];
                    if (((pt_ijk1 <= Threshold) && (pt_ij1k1 > Threshold))
                        || ((pt_ijk1 > Threshold) && (pt_ij1k1 <= Threshold)))
                    {
                        dist = (((double)(Threshold - pt_ijk1)) / ((double)(pt_ij1k1 - pt_ijk1)));
                        pt->x = i;
                        pt->y = j + dist;
                        pt->z = sliceNum + 1;
                        add_vertex(pt);
                        topyedge[j] = vert_index;
                    }
                    else
                        topyedge[j] = 0;
                }
            }

            for (j = 0; j < (NJ - 1); j++)
            {
                if (j == 0)
                {
                    pt_ijk1 = outsideSliceB[i * NJ + j];
                    pt_i1jk1 = outsideSliceB[(i + 1) * NJ + j];
                    if (((pt_ijk1 < Threshold) && (pt_i1jk1 > Threshold))
                        || ((pt_ijk1 > Threshold) && (pt_i1jk1 < Threshold)))
                    {
                        dist = (((double)(Threshold - pt_ijk1)) / ((double)(pt_i1jk1 - pt_ijk1)));
                        pt->x = i + dist;
                        pt->y = j;
                        pt->z = sliceNum + 1;
                        add_vertex(pt);
                        old6pt = vert_index;
                    }
                    else
                        old6pt = -1;

                    pt_i1jk1 = outsideSliceB[(i + 1) * NJ + j];
                    pt_i1jk = outsideSliceA[(i + 1) * NJ + j];
                    if (((pt_i1jk1 < Threshold) && (pt_i1jk > Threshold))
                        || ((pt_i1jk1 > Threshold) && (pt_i1jk < Threshold)))
                    {
                        dist = (((double)(Threshold - pt_i1jk1)) / ((double)(pt_i1jk - pt_i1jk1)));
                        pt->x = i + 1;
                        pt->y = j;
                        pt->z = sliceNum + dist;
                        add_vertex(pt);
                        old10pt = vert_index;
                    }
                    else
                        old10pt = -1;
                }

                cubeIndex = cube_index(i, j);
                if ((cubeIndex != 0) && (cubeIndex != 255))
                    load_facet(cubeIndex, i, j, sliceNum);
            }
        }
    }

    printf("done!\n");
}


void reshape(int width, int height)
{
    /* change viewport dimensions */
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, 0, height, 1000, -1000);
    glMatrixMode(GL_MODELVIEW);
}


void display(void)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (!volume){
	    currentSliceRGB = 0;

	    currentScaleFactorRGB = TORSO_256_SCALE;
	    if (volume)
	        deleteVolume(volume);
	    delete_Structure_Data();
	    volume = initVolumeData(TORSO_256_XDIM, TORSO_256_YDIM, TORSO_256_ZDIM);
	    loadVolumeData(volume, "../data/lobster.dat");
	    computePolygonalModel();
	   
	    display();
    }

    if (displayType == RGB_SLICE_DISPLAY)
        drawVolumeRGB(volume, currentSliceRGB);
    else if (displayType == POLYGONAL_DISPLAY)
        drawPolygonalModel();

    glutSwapBuffers();
}

void keyboardSpecial(int key, int x, int y)
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
                    currentSliceRGB = volume->ZDim - 1;
            }
            display();
            break;
    }
}
