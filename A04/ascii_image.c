#include <stdio.h>
#include <stdlib.h>
#include "read_ppm.h"

int main(int argc, char** argv) {
  char* temp = argv[1]; 
  const char* fileName = temp;
  int width = 0;
  int height = 0; 
  
  struct ppm_pixel* pixelArray = read_ppm(fileName, &width,&height);

  printf("Reading %s with width %d and height %d\n",fileName,width,height);

  
  int pixelSize = width * height;
  unsigned char *intensity = malloc(sizeof((unsigned char)* &pixelSize));
  char *symbols = malloc(sizeof((char) * &pixelSize));

  int count = 1;
  
  for(int i = 0; i < pixelSize ; i++){
    const float frac = 1.0f/3.0f;
	  intensity[i] = frac * (pixelArray[i].red+pixelArray[i].green+pixelArray[i].blue);
    if(intensity[i]>= 0 && intensity[i] <= 25){
      symbols[i] = '@';
      printf("%c",symbols[i]);
    }
    if(intensity[i]>= 26 && intensity[i] <= 50){
      symbols[i] = '#';
      printf("%c",symbols[i]);
    }
    if(intensity[i]>= 51 && intensity[i] <= 75){
      symbols[i] = '%';
      printf("%c",symbols[i]);
    }
    if(intensity[i]>= 76 && intensity[i] <= 100){
      symbols[i] = '*';
      printf("%c",symbols[i]);
    }
    if(intensity[i]>= 101 && intensity[i] <= 125){
      symbols[i] = 'o';
      printf("%c",symbols[i]);
    }
    if(intensity[i]>= 126 && intensity[i] <= 150){
      symbols[i] = ';';
      printf("%c",symbols[i]);
    }
    if(intensity[i]>= 151 && intensity[i] <= 175){
      symbols[i] = ':';
      printf("%c",symbols[i]);
    }
    if(intensity[i]>= 176 && intensity[i] <= 200){
      symbols[i] = ',';
      printf("%c",symbols[i]);
    }
    if(intensity[i]>= 201 && intensity[i] <= 225){
      symbols[i] = '.';
      printf("%c",symbols[i]);
    }
    if(intensity[i]>= 226 && intensity[i] <= 255){
      symbols[i] = ' ';
      printf("%c",symbols[i]);
    } 
    if(count % width == 0){
      printf("\n");
    }
    count++;
	}
  
  free(symbols);
  free(intensity);
  free(pixelArray);
  return 0;
}

