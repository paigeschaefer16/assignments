#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"

// TODO: Implement this function
// Feel free to change the function signature if you prefer to implement an 
// array of arrays
struct ppm_pixel* read_ppm(const char* filename, int* w, int* h) {
  FILE *fp;
  struct ppm_pixel *image;
  

  fp = fopen(filename,"rb");
  if(!fp){
    printf("Unable to open file\n");
    return NULL;

  }
  char buff[100];

	fgets(buff,100,fp);

	fgets(buff,100,fp);
	if(buff[0] == '#'){
		fgets(buff,100,fp);
		sscanf(buff, "%d %d",w,h);
	}
	else{
		sscanf(buff, "%d %d",w,h);
	}


	fgets(buff,100,fp);	

	image = malloc(sizeof(struct ppm_pixel) * *w  * *h);
	if(image == NULL){
		printf("Error. Allocation was unsuccessful");
		return NULL;
	}
  fread(image,sizeof(struct ppm_pixel),*w * *h,fp);
  fclose(fp);
  return image;
}

// TODO: Implement this function
// Feel free to change the function signature if you prefer to implement an 
// array of arrays
extern void write_ppm(const char* filename, struct ppm_pixel* pxs, int w, int h) {
  FILE *fp;
  fp = fopen(filename,"wb");

  if(!fp){
    printf("Unable to Open File\n");

  }
  char buffer[256];
  sprintf(buffer,"P6 \n%d %d \n255\n",w,h);
  fwrite(buffer,sizeof(char),strlen(buffer),fp);
  fwrite(pxs,sizeof(struct ppm_pixel),w * h,fp);
  
  fclose(fp);

}
