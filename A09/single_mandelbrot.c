#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include "read_ppm.h"

int main(int argc, char* argv[]) {
  srand(time(0));

  int size = 480;
  float xmin = -2.0;
  float xmax = 0.47;
  float ymin = -1.12;
  float ymax = 1.12;
  int maxIterations = 1000;


  int opt;
  while ((opt = getopt(argc, argv, ":s:l:r:t:b:")) != -1) {
    switch (opt) {
      case 's': size = atoi(optarg); break;
      case 'l': xmin = atof(optarg); break;
      case 'r': xmax = atof(optarg); break;
      case 't': ymax = atof(optarg); break;
      case 'b': ymin = atof(optarg); break;
      case '?': printf("usage: %s -s <size> -l <xmin> -r <xmax> -b <ymin> -t <ymax>\n", argv[0]); break;
    }
  }
  printf("Generating mandelbrot with size %dx%d\n", size, size);
  printf("  X range = [%.4f,%.4f]\n", xmin, xmax);
  printf("  Y range = [%.4f,%.4f]\n", ymin, ymax);

  // todo: your work here
  // generate pallet
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
  
  int col = 0;
  int row = 0;

  for(int i = 0; i < size * size;i++){
    float xfrac = ((float)col)/size;
    float yfrac = ((float)row)/size;
    float x0 = xmin + xfrac * (xmax - xmin);
    float y0 = ymin + yfrac * (ymax - ymin);

    float x = 0; 
    float y = 0;
    int iter = 0;
    while(iter < maxIterations && (x*x + y*y) < 2*2){
      float xtmp = x*x - y*y + x0;
      y = 2*x*y + y0;
      x = xtmp; 
      iter = iter + 1;
    }
    if(iter < maxIterations){
      mandelbrot[i].red = palette[iter].red + rand() % 100 - 50;
      mandelbrot[i].green = palette[iter].green + rand() % 100 - 50;
      mandelbrot[i].blue = palette[iter].blue + rand() % 100 - 50;
    }
    else{
      mandelbrot[i].red = 0;
      mandelbrot[i].green = 0;
      mandelbrot[i].blue = 0;
    }

    col++;

    if(col == size){
      row++;
      col = 0;
    }
  }
  gettimeofday(&tend, NULL);
  timer = tend.tv_sec - tstart.tv_sec + (tend.tv_usec - tstart.tv_usec)/1.e6;
  printf("Computed mandelbrot set (%dx%d) in %f seconds\n",size,size,timer);

  char buffer[1000];
  int times = time(0);
  snprintf(buffer, sizeof(buffer), "mandelbrot-%d-%d.ppm", size,times);

  write_ppm(buffer,mandelbrot,size,size);
  printf("Writing file: %s\n",buffer);

  free(palette);
  free(mandelbrot);
}
