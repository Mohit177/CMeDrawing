#ifndef DATA_H
#define DATA_H

#include <errno.h>
#include <cstdio>
#include <string>
#define TORSO_256_DATA_SET 2
#define TORSO_256_SCALE 2
#define TORSO_256_XDIM 256
#define TORSO_256_YDIM 256
#define TORSO_256_ZDIM 114

/* class to represent the 3D volume data */
class VolumeData
{
public:
    unsigned int XDim, YDim, ZDim; // number of samples per dimension
    unsigned int totalSize; // total size of the data buffer = XDim*YDim*ZDim
    unsigned char* data; // data buffer
};

#define volumePixel(vol, x, y, z) vol->data[z * (vol->XDim * vol->YDim) + y * vol->XDim + x]

VolumeData* initVolumeData(unsigned int s1, unsigned int s2, unsigned int s3);
void deleteVolume(VolumeData* vol);
void loadVolumeData(VolumeData* vol, std::string fname);
void showVolumeData(VolumeData* vol, std::string fname);

#endif