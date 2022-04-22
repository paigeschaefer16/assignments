#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"

struct ppm_pixel* read_ppm(const char* filename, int* w, int* h) {
  FILE *fp;
  struct ppm_pixel *image;
  unsigned char r,b,g;

  fp = fopen(filename,"rb");
  if(!fp){
    printf("Unable to open file\n");
    return NULL;

  }
  char buff[100];

  fgets(buff,100,fp);

  if(buff[1] == '6'){
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
  }
  else if(buff[0] == '3'){
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
		  printf("Eror. Allocation was unsuccessful");
		  return NULL;
	  }

	  for(int i =0; i < *h;i++){
		  for(int j = 0; j < *w; j++){
			  int index = i * *w + j;
			  fscanf(fp,"%hhu %hhu %hhu",&r, &g, &b);
			  image[index].red = r; 
			  image[index].green = g;
			  image[index].blue = b;
		  }
	  }
  }
  fclose(fp);
  return image;
  return NULL;
}

void write_ppm(const char* filename, struct ppm_pixel* pixels, int w, int h) {
  FILE *fp;
  fp = fopen(filename,"wb");

  if(!fp){
    printf("Unable to Open File\n");

  }
  char buffer[256];
  sprintf(buffer,"P6 \n%d %d \n255\n",w,h);
  fwrite(buffer,sizeof(char),strlen(buffer),fp);
  fwrite(pixels,sizeof(struct ppm_pixel),w * h,fp);

  fclose(fp);
}



