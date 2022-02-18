#include <stdio.h>
#include <stdlib.h>
#include "read_ppm.h"

int main() {
  int width = 0;
  int height = 0; 

  const char* fileName = malloc(100);
  fileName = "feep-ascii.ppm";
  

  struct ppm_pixel* pixelArray = read_ppm(fileName, &width,&height);

  int count = 1;
  printf("Testing file %s: %d %d\n",fileName,width,height);

  for(int i = 0; i < width* height; i++){
		printf("(%hhu, %hhu, %hhu) ", pixelArray[i].red,pixelArray[i].green, 
                                pixelArray[i].blue);
    if(count % width == 0){
      printf("\n");
    }
    count = count + 1;
    
	}
  free(pixelArray);
  return 0;
}

