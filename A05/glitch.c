#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "read_ppm.h"

int main(int argc, char** argv) {
  const char * fileName = argv[1];
  int width = 0;
  int height = 0; 

  struct ppm_pixel* pixelArray = read_ppm(fileName, &width,&height);

  printf("Reading %s with %d and height %d\n",fileName,width,height);
  
  for(int i = 0; i < width* height; i++){
    pixelArray[i].red = pixelArray[i].red << (rand() % 2);
    pixelArray[i].green = pixelArray[i].green << (rand() % 4);
    pixelArray[i].blue = pixelArray[i].blue << (rand() % 6);
  }
  const char * outputFile = fileName;
  char result[100];

  strcpy(result,outputFile);
  for(int i = 0; i < strlen(outputFile) + 7;i++){
    if(result[i] == '.'){
      result[i] = '-';
      result[i+1] = 'g';
      result[i+2] = 'l';
      result[i+3] = 'i';
      result[i+4] = 't';
      result[i+5] = 'c';
      result[i+6] = 'h';
      result[i+7] = '.';
      result[i+8] = 'p';
      result[i+9] = 'p';
      result[i+10] = 'm';
      result[i+11] = '\0';
      break;
    } 
  }

  
  printf("Writing file %s\n",result);
  write_ppm(result,pixelArray,width,height);
  
  return 0;
}
