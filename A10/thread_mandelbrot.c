#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <pthread.h>
#include <sys/time.h>
#include "read_ppm.h"

struct thread_data {
  struct ppm_pixel* palette;
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
      data->mandelbrot[i].red = data->palette[iter].red + rand() % 100 - 50;
      data->mandelbrot[i].green = data->palette[iter].green + rand() % 100 - 50;
      data->mandelbrot[i].blue = data->palette[iter].blue + rand() % 100 - 50;
      
    }
    else{
      data->mandelbrot[i].red = 0;
      data->mandelbrot[i].green = 0;
      data->mandelbrot[i].blue = 0;
    }

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

  struct ppm_pixel *palette = malloc(sizeof(struct ppm_pixel) *maxIterations);
  struct ppm_pixel *mandelbrot = malloc(sizeof(struct ppm_pixel) *size*size);

  for(int i = 0; i < maxIterations; i++){
    palette[i].red = rand() % 255;
    palette[i].green = rand() % 255;
    palette[i].blue = rand() % 255;
  }

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
    data[i].palette = palette;
    data[i].mandelbrot = mandelbrot;
    pthread_create(&threads[i],NULL,mandelbrotFunction,(void *) &data[i]);
    printf("Thread %d) sub-image block: cols (%d, %d) to rows (%d,%d)\n",i,data[i].colStart,
                                                          data[i].colEnd,data[i].rowStart,data[i].rowEnd);
  }

  for(int i = 0; i < 4;i++){
    pthread_join(threads[i],NULL);
    printf("Thread %d) finished\n",i);
  }
  
  gettimeofday(&tend, NULL);
  timer = tend.tv_sec - tstart.tv_sec + (tend.tv_usec - tstart.tv_usec)/1.e6;
  printf("Computed mandelbrot set (%dx%d) in %f seconds\n",size,size,timer);

  char buffer[1000];
  int times = time(0);
  snprintf(buffer, sizeof(buffer), "mandelbrot-%d-%d.ppm", size,times);

  write_ppm(buffer,data->mandelbrot,size,size);
  printf("Writing file: %s\n",buffer);


}
