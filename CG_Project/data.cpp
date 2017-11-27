#include "data.h"
#include <cstdio>
#include <string>
#include <cstdlib>
#include <iostream>

VolumeData* initVolumeData(unsigned int sx, unsigned int sy, unsigned int sz)
{
    VolumeData* obj;
    char func[] = "initVolumeData()";
    obj = new VolumeData;
    obj->data = new unsigned char[sx*sy*sz];
    obj->XDim = sx;
    obj->YDim = sy;
    obj->ZDim = sz;
    obj->totalSize = sx * sy * sz;
	return (obj);
}

void loadVolumeData(VolumeData* vol, std::string fname)
{
    FILE* fp;
	fp = fopen(fname.c_str(), "r");
    fread(vol->data, sizeof(unsigned char), vol->totalSize, fp);
    fclose(fp);
}

void showVolumeData(VolumeData* vol, std::string fname)
{
    FILE* fp;
    fp = fopen(fname.c_str(), "w");
    for (int k = 0; k < vol->ZDim; k++)
    {
        for (int i = 0; i < vol->XDim; i++)
        {
            for (int j = 0; j < vol->YDim; j++)
                fprintf(fp, "%d ", volumePixel(vol, i, j, k));
            fprintf(fp, "\n");
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
}

void deleteVolume(VolumeData* vol)
{
    std::string func = "freeVolume()";
    if(vol==NULL)
    {
    	std::cout<<"error in deleteVolume"<<std::endl;
    }
    if (vol->data)
    {
        delete[] vol->data;
    }
    delete vol;
}