//---------------------------------------------------------------------
// magic_square.c 
// CS223 - Spring 2022
// Identify whether a matrix is a magic square
// Name: Paige Schaefer 
//
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char **argv) {
    FILE *infile =  NULL;

    infile = fopen(argv[1], "r");


    int height;
    int width; 

    int m = 100; 
    int array[m][m];


    fscanf(infile, "%d%d", &height, &width);

    printf("height: %d width: %d\n",height,width);

    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            if(fscanf(infile,"%d", &array[i][j]) != 1){
                exit(1);
            }
        }
    }

    fclose(infile);
    
     for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            printf("%d ", array[i][j]);
        }
        printf("\n");
    }
    
    int check = 0; 

    int sumd1 = 0;
    int sumd2 = 0;

    while(check == 0){
        for(int i = 0; i < height; i++){
            sumd1 = sumd1 + array[i][i];
            sumd2 = sumd2 + array[i][height-1-i];
        }
        if(sumd1 != sumd2){
            check = 1;
            break;
        }

        for(int i = 0; i < height; i++){
            int rowSum = 0;
            int colSum = 0;
            for(int j = 0; j < height; j++){
                rowSum = rowSum + array[i][j];
                colSum = colSum + array[j][i];
            }   
            if(rowSum != colSum || colSum != sumd1){
                check = 1; 
                break;
            }
        }
        check = 2; 
    }
    if(check == 1){
        printf("M is NOT a magic square\n");
    }
    else{
        printf("M is a magic square (magic constant = %d)\n",sumd1);
    }
    
    return 0; 

}

