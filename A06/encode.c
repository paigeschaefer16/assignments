#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"

int main(int argc, char** argv) {
  const char * fileName = argv[1];
  int width = 0;
  int height = 0; 

  struct ppm_pixel* pixelArray = read_ppm(fileName, &width,&height);

  printf("Reading %s with %d and height %d\n",fileName,width,height);

  int maxNumber = ((width*height*3)/8) - 1;
  
  printf("Max number of characters in the image: %d\n",maxNumber);

  char* input = malloc(maxNumber * sizeof(char));

  printf("Enter a phrase: ");
  scanf(" %s",input);

  int n = strlen(input);

  char *binary = malloc(n*8 + 1); 
  binary[0] = '\0';
  for(int i = 0; i < n; ++i) {
    char ch = input[i];
    for(int j = 7; j >= 0; --j){
      if(ch & (1 << j)) {
        strcat(binary,"1");
      } 
      else{
        strcat(binary,"0");
      }
    }
  }

  const char * outputFile = argv[1];
  char result[100];

  strcpy(result,outputFile);
  for(int i = 0; i < strlen(outputFile) + 8;i++){
    if(result[i] == '.'){
      result[i] = '-';
      result[i+1] = 'e';
      result[i+2] = 'n';
      result[i+3] = 'c';
      result[i+4] = 'o';
      result[i+5] = 'd';
      result[i+6] = 'e';
      result[i+7] = 'd';
      result[i+8] = '.';
      result[i+9] = 'p';
      result[i+10] = 'p';
      result[i+11] = 'm';
      result[i+12] = '\0';
      break;
    } 
  }
  unsigned int mask1 = 11111111;
  unsigned int mask2 = 00000000;
  for(int i = 0; i < width * height *3; i++){
    if(binary[i] == '1'){
      pixelArray[i].red = pixelArray[i].red | mask2;
      pixelArray[i].green = pixelArray[i].green | mask2;
      pixelArray[i].blue = pixelArray[i].blue | mask2;
    }
    else{
      pixelArray[i].red = pixelArray[i].red & mask1;
      pixelArray[i].green = pixelArray[i].green & mask1;
      pixelArray[i].blue = pixelArray[i].blue & mask1;
    }
  }
  
  printf("Writing file %s\n",result);
  write_ppm(result,pixelArray,width,height);
  
  free(pixelArray);
  free(binary);

  return 0;
}

