#include "data.h"
#include <stdio.h>
#include <stdlib.h>

/* Creates a data structure to store the volume data of size sx*sy*sz.
                  Allocates memory for this data structure.
		  */
void Volume::createVolume(unsigned int sx, unsigned int sy, unsigned int sz) {
  char func [] = "createVolume()";
  
  if (! (this->data = (unsigned char *)malloc(sizeof(unsigned char) * sx * sy * sz))){
      perror(func);
      this->~Volume();
      exit(1);
  }
  this->XDim = sx;
  this->YDim = sy;
  this->ZDim = sz;
  this->totalSize = sx * sy * sz;
}

/* FREE_VOLUME: Free the memory allocated to the volume data structure 'vol'.
   */
int Volume::freeVolume(){
  char func [] = "freeVolume()";
  
  if (this->data)
    free(this->data);
  this->~Volume();
  return 0;
}

/* VOL_READ_FILE: Function to read the volume data from the file pointed by 'fname'
                  and store it in the data structure 'vol'.
		  The inputs files are assumed to contain data in byte form.
		  */
int Volume::volReadFile(const char *fname){

  unsigned int i;
  char func [] = "volReadFile()";
  FILE *fp;

  printf("Reading volume data set from file %s   ...\n",fname);
  
  if (! (fp = fopen(fname, "r"))){
      perror(func);
      return 1;
  }

  if (! this->data){
      perror(func);
      return 1;
  }
  if (! this->totalSize){
      perror(func);
      return 1;
  }
  if ((i = fread(this->data, sizeof(unsigned char), this->totalSize, fp)) < this->totalSize){
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
int Volume::volPrintFile(const char *fname){
  FILE *fp;
  char func [] = "volPrintFile()";
  int i,j,k;

  printf("Writing volume data set to file %s   ...\n",fname);
  
  if (! (fp = fopen(fname, "w"))) {
      perror(func);
      return 1;
  }

  for(k=0; k<this->ZDim; k++){
      for (i=0; i<this->XDim; i++){
	       for (j=0; j<this->YDim; j++) 
	         fprintf(fp,"%d ",this->volumePixel(i, j, k));
         fprintf(fp,"\n");
	     }
    fprintf(fp,"\n");
  }  

  fclose(fp);
  printf("done!\n");
  return 0;
}

unsigned char Volume::volumePixel(unsigned int x, unsigned int y, unsigned int z){
  return this->data[z * (this->XDim * this->YDim) + y * this->XDim + x];
}