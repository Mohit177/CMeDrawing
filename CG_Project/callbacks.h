#ifndef CALLSBACK_H
#define CALLSBACK_H
#include "data.h"
#include "const.h"

void select_data_layer(int option);
void initialize_Structure_Data(void);
void delete_Structure_Data(void);
void generate_facet_Data(void);
void printFacetDataFile(void);
void generateEdgeData(void);
void printEdgeDataFile(void);
short int getCorner(int corner, int imarch, int jmarch);
void contour_intersect(int edge_name, int imarch, int jmarch, int kmarch, Point3* pt);
void add_vertex(Point3* pt);
void add_facet(int num_verts, long vertex_list[]);
void printVerticesFile(void);
void printFacetsFile(void);
int cube_index(int imarch, int jmarch);
void load_facet(int cube_index, int imarch, int jmarch, int kmarch);
void drawVolumeRGB(VolumeData* vol, int slice);
void drawPolygonalModel(void);
void computePolygonalModel(void);
void reshape(int width, int height);
void display(void);
void keyboardSpecial(int key, int x, int y);

#endif
