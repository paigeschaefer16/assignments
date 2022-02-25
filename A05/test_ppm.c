#include <stdio.h>
#include <stdlib.h>
#include "read_ppm.h"

int main(int argc, char** argv) {
  int width = 0;
  int height = 0; 

  const char* fileName = "feep-raw.ppm";
 

  struct ppm_pixel* pixelArray = read_ppm(fileName, &width,&height);

  int count = 1;
  printf("Testing file %s: %d %d\n",fileName,width,height);

  for(int i = 0; i < width* height; i++){
		printf("(%d, %d, %d) ", pixelArray[i].red,pixelArray[i].green, 
                                pixelArray[i].blue);
    if(count % width == 0){
      printf("\n");
    }
    count = count + 1;
    
	}
  free(pixelArray);
  return 0;
}

