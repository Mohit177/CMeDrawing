/********************************************************************
  Subroutines to read volume data from files: CS580 Assignment P5
*********************************************************************
   Authors: Joshua Richardson and Lavanya Viswanathan
      Date: December 01, 1997
********************************************************************/

#include "data.h"
#include <stdio.h>
#include <stdlib.h>

/* CREATE_VOLUME: Creates a data structure to store the volume data of size sx*sy*sz.
                  Allocates memory for this data structure.
		  */
Volume *createVolume(unsigned int sx, unsigned int sy, unsigned int sz) 
{
  Volume *volume;
  char func [] = "createVolume()";
  
  if (! (volume = (Volume *)calloc(1, sizeof(Volume)))) 
    {
      errno = ENOMEM;
      perror(func);
      return 0;
    }
  if (! (volume->data = (unsigned char *)malloc(sizeof(unsigned char) * sx * sy * sz))) 
    {
      errno = ENOMEM;
      perror(func);
      free (volume);
      return 0;
    }
  volume->XDim = sx;
  volume->YDim = sy;
  volume->ZDim = sz;
  volume->totalSize = sx * sy * sz;
  
  return(volume);
}

/* FREE_VOLUME: Free the memory allocated to the volume data structure 'vol'.
   */
int freeVolume(Volume *vol) 
{
  char func [] = "freeVolume()";
  
  if (! vol) 
    {
      errno = EINVAL;
      perror(func);
      return errno;
    }
  if (vol->data)
    free(vol->data);
  free(vol);
  
  return 0;
}

/* VOL_READ_FILE: Function to read the volume data from the file pointed by 'fname'
                  and store it in the data structure 'vol'.
		  The inputs files are assumed to contain data in byte form.
		  */
int volReadFile(Volume *vol, char *fname) 
{
  unsigned int i;
  char func [] = "volReadFile()";
  FILE *fp;

  printf("Reading volume data set from file %s   ...\n",fname);
  
  if (! (fp = fopen(fname, "r"))) 
    {
      perror(func);
      return 1;
    }
  if (! vol->data) 
    {
      errno = EINVAL;
      perror(func);
      return errno;
    }
  if (! vol->totalSize) 
    {
      errno = EINVAL;
      perror(func);
      return errno;
    }
  if ((i = fread(vol->data, sizeof(unsigned char), vol->totalSize, fp)) < vol->totalSize) 
    {
      fprintf(stderr, "%s: EOF reached after %d reads.\n", func, i);
      return 1;
    }

  fclose(fp);
  printf("done!\n");
  return 0;
}

/* VOL_PRINT_FILE: Print the volume data set from 'vol' to the file given by 'fname'.
                   The data is printed as formatted data, i.e., ASCII characters.
		   This function should be used only for debugging purposes as 
		   ASCII files take up a lot of memory.
		   */
int volPrintFile(Volume *vol, char *fname)
{
  FILE *fp;
  char func [] = "volPrintFile()";
  int i,j,k;

  printf("Writing volume data set to file %s   ...\n",fname);
  
  if (! (fp = fopen(fname, "w"))) 
    {
      perror(func);
      return 1;
    }

  if (! vol) 
    {
      perror(func);
      return 1;
    }

  for (k=0; k<vol->ZDim; k++)
    {
      for (i=0; i<vol->XDim; i++) 
	{
	  for (j=0; j<vol->YDim; j++) 
	    fprintf(fp,"%d ",volumePixel(vol, i, j, k));
	  fprintf(fp,"\n");
	}
      fprintf(fp,"\n");
    }  

  fclose(fp);
  printf("done!\n");
  return 0;
}