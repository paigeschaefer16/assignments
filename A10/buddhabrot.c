#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <pthread.h>
#include <math.h>
#include <sys/time.h>
#include "read_ppm.h"

int maxCount = 0; 
pthread_mutex_t mutex;
pthread_barrier_t barrier;

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
  int **setMembership;
  int **counts;
  int id; 
};
void *mandelbrotFunction(void *inputData){
  struct thread_data *data = (struct thread_data *) inputData;
  

  for(int r = data->rowStart; r < data->rowEnd;r++){
    for(int c = data->colStart; c < data->colEnd;c++){
      int i = data -> size * r + c;
      float xfrac = ((float)c)/data->size;
      float yfrac = ((float)r)/data->size;
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
        data->setMembership[r][c] = 0;
      }
      else{
        data->setMembership[r][c] = 1;
      }
    }
  }

  for(int r = data->rowStart; r < data->rowEnd;r++){
    for(int c = data->colStart; c < data->colEnd;c++){
      int i = data->size * r + c;
      if((data->setMembership[r][c] == 0)){
        float xfrac = ((float)c)/data->size;
        float yfrac = ((float)r)/data->size;

        float x0 = data->xmin + xfrac * (data->xmax - data->xmin);
        float y0 = data->ymin + yfrac * (data->ymax - data->ymin);

        float x = 0; 
        float y = 0;
      
        while(x*x + y*y < 2*2){
          float xtmp = x*x - y*y + x0;
          y = 2*x*y + y0;
          x = xtmp; 

          int yrow = round(data->size * (y - data->ymin)/(data->ymax - data->ymin));
          int xcol = round(data->size * (x - data->xmin)/(data->xmax - data->xmin));
        
          if(yrow > 0 && yrow < data->size){
            if(xcol > 0 && xcol < data->size){
              pthread_mutex_lock(&mutex);
              data->counts[yrow][xcol] = data->counts[yrow][xcol] + 1;
              if(data->counts[yrow][xcol] > maxCount){
                maxCount = data->counts[yrow][xcol];
              }
              pthread_mutex_unlock(&mutex);
            }
          }
        }
      }
    }
  }

  //pthread_barrier_wait(&barrier);

  float gamma = 0.681;
  float factor = 1.0/gamma; 

  for(int r = data->rowStart; r < data->rowEnd;r++){
    for(int c = data->colStart; c < data->colEnd;c++){
      int i = data->size * r + c;
      int value = data->setMembership[r][c]; 
      if(data->counts[r][c] > 0){
        value = log(data->counts[r][c])/log(maxCount);
        value = pow(value,factor);
      }
      data->mandelbrot[i].red = value * 255;
      data->mandelbrot[i].green = value * 255;
      data->mandelbrot[i].blue = value * 255;
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

  int** setMembership = malloc(sizeof(int*) * size);
  for (int i = 0; i < size; i++) {
    setMembership[i] = malloc(sizeof(int) * size);
  }

  int** counts = malloc(sizeof(int*) * size);
  for (int i = 0; i < size; i++) {
    counts[i] = malloc(sizeof(int) * size);
  }

  for(int i = 0; i < size; i++){
    for(int j = 0; j < size;j++){
      counts[i][j] = 0;
    }
  }
  
  
  pthread_mutex_init(&mutex,NULL);
 
  //pthread_barrier_init(&barrier,NULL,maxCount);

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
      data[i].rowEnd = size; 
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
    data[i].setMembership = setMembership; 
    data[i].counts = counts; 
    pthread_create(&threads[i],NULL,mandelbrotFunction,(void *) &data[i]);
    printf("Thread %d) sub-image block: cols (%d, %d) to rows (%d,%d)\n",i,data[i].colStart,
                                                          data[i].colEnd,data[i].rowStart,data[i].rowEnd);
  }

  for(int i = 0; i < 4;i++){
    pthread_join(threads[i],NULL);
    printf("Thread %d) finished\n",i);
  }

  pthread_mutex_destroy(&mutex);
  //pthread_barrier_destroy(&barrier);

  
  gettimeofday(&tend, NULL);
  timer = tend.tv_sec - tstart.tv_sec + (tend.tv_usec - tstart.tv_usec)/1.e6;
  printf("Computed buddhabrot set (%dx%d) in %f seconds\n",size,size,timer);

  char buffer[1000];
  int times = time(0);
  snprintf(buffer, sizeof(buffer), "buddhabrot-%d-%d.ppm", size,times);

  write_ppm(buffer,data->mandelbrot,size,size);
  printf("Writing file: %s\n",buffer);

  for (int i = 0; i < size; i++) {
    free(setMembership[i]);
    free(counts[i]);
  }
  free(setMembership);
  free(counts);
  
}
