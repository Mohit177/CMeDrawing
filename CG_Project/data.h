#ifndef DATA_H
#define DATA_H

#include <errno.h>
#include <stdio.h>
#define TORSO_128_DATA_SET 1
#define TORSO_256_DATA_SET 2
#define TORSO_512_DATA_SET 3
#define LOBSTER_DATA_SET 4
#define HYDROGEN_DATA_SET 5
#define VOL_TESLA_DATA_SET 6
#define TORSO_128_SCALE 4
#define TORSO_256_SCALE 2
#define TORSO_512_SCALE 1
#define LOBSTER_SCALE 4
#define HYDROGEN_SCALE 8
#define VOL_TESLA_SCALE 20
#define TORSO_128_XDIM 128
#define TORSO_128_YDIM 128
#define TORSO_128_ZDIM 114
#define TORSO_256_XDIM 256
#define TORSO_256_YDIM 256
#define TORSO_256_ZDIM 114
#define TORSO_512_XDIM 512
#define TORSO_512_YDIM 512
#define TORSO_512_ZDIM 114
#define LOBSTER_XDIM 120
#define LOBSTER_YDIM 120
#define LOBSTER_ZDIM 34
#define HYDROGEN_XDIM 64
#define HYDROGEN_YDIM 64
#define HYDROGEN_ZDIM 64
#define VOL_TESLA_XDIM 10
#define VOL_TESLA_YDIM 10
#define VOL_TESLA_ZDIM 10

/* class to represent the 3D volume data */
class Volume
{
	public:
    unsigned int XDim, YDim, ZDim; // number of samples per dimension
    unsigned int totalSize; // total size of the data buffer = XDim*YDim*ZDim
    unsigned char* data; // data buffer
};

#define volumePixel(vol, x, y, z) vol->data[z * (vol->XDim * vol->YDim) + y * vol->XDim + x]

Volume* createVolume(unsigned int s1, unsigned int s2, unsigned int s3);
int freeVolume(Volume* vol);
int volReadFile(Volume* vol, char* fname);
int volPrintFile(Volume* vol, char* fname);

#endif