#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <pthread.h>
#include <math.h>
#include <sys/time.h>
#include "read_ppm.h"

pthread_mutex_t mutex;

struct thread_data {
  struct ppm_pixel* mandelbrot;
  int size;
  float xmin;
  float xmax;
  float ymin;
  float ymax;
  int maxIterations;
  int colStart;
  int colEnd;
  int rowStart;
  int rowEnd;
};
void *mandelbrotFunction(void *inputData){
  struct thread_data *data = (struct thread_data *) inputData;
  int col = data->colStart;
  int row = data->rowStart;


  char *setMembership[480][480];
  int counts[480][480];
  
  for(int i = 0; i < data->size; i++){
    for(int j = 0; j < data->size; j++){
      setMembership[i][j] = " ";
      counts[i][j] = 0;
    }
  }
  

  for(int i = 0; i < data->size * data->size;i++){
    float xfrac = ((float)col)/data->size;
    float yfrac = ((float)row)/data->size;
    float x0 = data->xmin + xfrac * (data->xmax - data->xmin);
    float y0 = data->ymin + yfrac * (data->ymax - data->ymin);

    float x = 0; 
    float y = 0;
    int iter = 0;
    while(iter < data->maxIterations && (x*x + y*y) < 2*2){
      float xtmp = x*x - y*y + x0;
      y = 2*x*y + y0;
      x = xtmp; 
      iter = iter + 1;
    }
    if(iter < data->maxIterations){
      setMembership[row][col] = "false";
      
    }
    else{
      setMembership[row][col] = "true";
    }

    col++;

    if(col == data->colEnd){
      row++;
      col = 0;
    }
  }

  col = data->colStart;
  row = data->rowStart;
  int maxCount = 0;

  for(int i = 0; i < data->size * data->size;i++){
    if((setMembership[row][col] = "true")){
      float xfrac = ((float)col)/data->size;
      float yfrac = ((float)row)/data->size;

      float x0 = data->xmin + xfrac * (data->xmax - data->xmin);
      float y0 = data->ymin + yfrac * (data->ymax - data->ymin);

      float x = 0; 
      float y = 0;
      
      while(x*x + y*y < 2*2){
        float xtmp = x*x - y*y + x0;
        y = 2*x*y + y0;
        x = xtmp; 

        int yrow = round(data->size * (y - data->ymin)/(data->ymax - data->ymax));
        int xcol = round(data->size * (x - data->xmin)/(data->xmax - data->xmax));
        
        if(yrow < 0 || yrow >= data->size){
          if(xcol < 0 || xcol >= data->size){
            counts[yrow][xcol] = counts[yrow][xcol] + 1;
            maxCount = maxCount + 1;
          }
        }
        
      }
      col++;

      if(col == data->colEnd){
        row++;
        col = 0;
      }
    }
  }

  col = data->colStart;
  row = data->rowStart;

  float gamma = 0.681;
  float factor = 1.0/gamma; 
  for(int i = 0; i < data->size * data->size;i++){
    int value = 0; 
    if(counts[row][col] > 0){
      value = log(counts[row][col])/log(maxCount);
      value = pow(value,factor);
    }
    data->mandelbrot[i].red = value * 255;
    data->mandelbrot[i].green = value * 255;
    data->mandelbrot[i].blue = value * 255;

    col++;

    if(col == data->colEnd){
      row++;
      col = 0;
    }
  }
  return (void*) NULL;
}

int main(int argc, char* argv[]) {
  int size = 480;
  float xmin = -2.0;
  float xmax = 0.47;
  float ymin = -1.12;
  float ymax = 1.12;
  int maxIterations = 1000;
  int numProcesses = 4;

  int opt;
  while ((opt = getopt(argc, argv, ":s:l:r:t:b:p:")) != -1) {
    switch (opt) {
      case 's': size = atoi(optarg); break;
      case 'l': xmin = atof(optarg); break;
      case 'r': xmax = atof(optarg); break;
      case 't': ymax = atof(optarg); break;
      case 'b': ymin = atof(optarg); break;
      case '?': printf("usage: %s -s <size> -l <xmin> -r <xmax> "
        "-b <ymin> -t <ymax> -p <numProcesses>\n", argv[0]); break;
    }
  }
  printf("Generating mandelbrot with size %dx%d\n", size, size);
  printf("  Num processes = %d\n", numProcesses);
  printf("  X range = [%.4f,%.4f]\n", xmin, xmax);
  printf("  Y range = [%.4f,%.4f]\n", ymin, ymax);

  // todo: your code here
  srand(time(0));
  struct timeval tstart, tend;
  double timer;

  gettimeofday(&tstart, NULL);
  struct ppm_pixel *mandelbrot = malloc(sizeof(struct ppm_pixel) *size*size);

  pthread_t threads[4];
  struct thread_data data[4];

  for(int i = 0; i < 4;i++){
    if(i == 0){
      data[i].colStart = 0; 
      data[i].colEnd = size/2; 
      data[i].rowStart = 0;
      data[i].rowEnd = size/2; 
    }
    if(i == 1){
      data[i].colStart = size/2; 
      data[i].colEnd = size; 
      data[i].rowStart = 0;
      data[i].rowEnd = size/2; 
    }
    if(i == 2){
      data[i].colStart = 0; 
      data[i].colEnd = size/2; 
      data[i].rowStart = size/2;
      data[i].rowEnd = size/2; 
    }
    if(i == 3){
      data[i].colStart = size/2; 
      data[i].colEnd = size; 
      data[i].rowStart = size/2;
      data[i].rowEnd = size; 
    }
    data[i].size = size;
    data[i].xmin = xmin;
    data[i].xmax = xmax;
    data[i].ymin = ymin;
    data[i].ymax = ymax;
    data[i].maxIterations = maxIterations;
    data[i].mandelbrot = mandelbrot;
    pthread_create(&threads[i],NULL,mandelbrotFunction,(void *) &data[i]);
  }

  for(int i = 0; i < 4;i++){
    pthread_join(threads[i],NULL);
  }
  
  gettimeofday(&tend, NULL);
  timer = tend.tv_sec - tstart.tv_sec + (tend.tv_usec - tstart.tv_usec)/1.e6;
  printf("Computed buddhabrot set (%dx%d) in %f seconds\n",size,size,timer);

  char buffer[1000];
  int times = time(0);
  snprintf(buffer, sizeof(buffer), "buddhabrot-%d-%d.ppm", size,times);

  write_ppm(buffer,data->mandelbrot,size,size);
  printf("Writing file: %s\n",buffer);
}
