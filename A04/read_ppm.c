#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"

// TODO: Implement this function
// Feel free to change the function signature if you prefer to implement an 
// array of arrays
struct ppm_pixel* read_ppm(const char* filename, int* w, int* h) {
	FILE* fp; 
	unsigned char r,b,g;
	struct ppm_pixel *image; 

	fp = fopen(filename,"r");
	if(!fp){
		printf("Could not open %s\n",filename);
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
	fclose(fp);
	return image; 
}


