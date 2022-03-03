#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"

unsigned long binaryToDecimal(char *binary, int length);
void binaryToText(char *binary, int binaryLength, char *text, int symbolCount);

void binaryToText(char *binary, int binaryLength, char *text, int symbolCount){
  for(int i = 0; i < binaryLength; i+=8){
    char *byte = binary;
    byte[8] = '\0';
    *text++ = binaryToDecimal(byte, 8);
    binary += 8;
  }
  text -= symbolCount;
}

unsigned long binaryToDecimal(char *binary, int length){
	unsigned long decimal = 0;
	unsigned long weight = 1;
	binary += length - 1;
	weight = 1;
	for(int i = 0; i < length; ++i){
		if(*binary == '1'){
			decimal += weight;
    }
		weight *= 2;
    --binary;
	}
	return decimal;
}


int main(int argc, char** argv) {
  const char * fileName = argv[1];
  int width = 0;
  int height = 0; 

  if(argv[1] == NULL){
    printf("Please enter a file to be read\n");
  }

  struct ppm_pixel* pixelArray = read_ppm(fileName, &width,&height);

  printf("Reading %s with %d and height %d\n",fileName,width,height);
  
  int maxNumber =  (width*height*3)/8;
  printf("Max number of characters in the image: %d\n",maxNumber);

  
  int **bitArray = (int **)malloc(maxNumber * sizeof(int *));
  for (int i = 0; i < maxNumber; i++){
    bitArray[i] = (int*)malloc(8 * sizeof(int));
  }

  int row = 0;
  int col = 0;
  int count = 0;

  for(int i = 0; i < width * height; i++){
		bitArray[row][col] = pixelArray[i].red;
    col = col + 1;
    count = count + 1;
    if(count % 8 == 0){
      row = row + 1;
      col = 0;
    }
    bitArray[row][col]= pixelArray[i].green;
    col = col + 1;
    count = count + 1;
    if(count % 8 == 0){
      row = row + 1;
      col = 0;
    }
    bitArray[row][col] = pixelArray[i].blue;
    col = col + 1;
    count = count + 1; 

    if(count % 8 == 0){
      row = row + 1;
      col = 0;
    }
    
	}


  int totalbits = width*height*3;
 
  int * array = malloc(totalbits * sizeof(int));
  

  int k = 0;
  for(int i = 0; i < maxNumber - 1; i++){
    for(int j = 0; j < 8; j++){
      array[k] = bitArray[i][j];
      k = k + 1;
    }
  }
  for(int i = 0; i < totalbits - 1; i++){
    if(array[i] % 2 == 0){
      array[i] = 0;
    }
    else{
      array[i] = 1;
    }
  }
  
  char * charArray = malloc(totalbits * sizeof(char));
  for(int i = 0; i < totalbits - 1; i++){
    charArray[i] = array[i] + '0';
  }
  charArray[totalbits] = '\0';
  
 
  int binaryLength = strlen(charArray);
  int symbolCount = binaryLength / 8 + 1;
  char *text = malloc(symbolCount + 1);


  binaryToText(charArray,binaryLength, text, symbolCount);
  printf("%s", text);
  
  free(text);
  free(charArray);
  free(array);
  for (int i = 0; i < maxNumber - 1; i++) {
    free(bitArray[i]);
  }
 
  free(bitArray);
  free(pixelArray);
  return 0;
}