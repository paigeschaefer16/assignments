#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include "read_ppm.h"

void mandelbrotFunction(struct ppm_pixel* palette,struct ppm_pixel* mandelbrot,int size,float xmin,
                                        float xmax,float ymin, float ymax,int maxIterations,
                                        int colStart,int colEnd,int rowStart,int rowEnd){
  

  for(int r = rowStart; r < rowEnd;r++){
    for(int c = colStart; c < colEnd;c++){
      int i = size * r + c;
      float xfrac = ((float)c)/size;
      float yfrac = ((float)r)/size;
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
    }
  }
}
int main(int argc, char* argv[]) {
  srand(time(0));
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
  struct timeval tstart, tend;
  double timer;

  gettimeofday(&tstart, NULL);
  struct ppm_pixel *palette = malloc(sizeof(struct ppm_pixel) *maxIterations);

  int shmid;
  shmid = shmget(IPC_PRIVATE, sizeof(struct ppm_pixel) *size*size, 0644 | IPC_CREAT);
  if (shmid == -1) {
    perror("Error: cannot initialize shared memory\n");
    exit(1);
  }

  struct ppm_pixel *fullMandelbrot = shmat(shmid, NULL, 0);
  if (fullMandelbrot == (void*) -1) {
    perror("Error: cannot access shared memory\n");
    exit(1);
  }


  for(int i = 0; i < maxIterations; i++){
    palette[i].red = rand() % 255;
    palette[i].green = rand() % 255;
    palette[i].blue = rand() % 255;
  }


  int child1_colsStart = 0; 
  int child1_colsEnd = size/2; 
  int child1_rowsStart = 0;
  int child1_rowsEnd = size/2; 

  int child2_colsStart = size/2; 
  int child2_colsEnd = size; 
  int child2_rowsStart = 0;
  int child2_rowsEnd = size/2; 

  int child3_colsStart = 0; 
  int child3_colsEnd = size/2; 
  int child3_rowsStart = size/2;
  int child3_rowsEnd = size; 

  int child4_colsStart = size/2; 
  int child4_colsEnd = size; 
  int child4_rowsStart = size/2;
  int child4_rowsEnd = size; 

  pid_t pid; 
 
  for(int count = 1; count <= 4;count++){
    pid = fork(); 
    if(pid == 0){
      if(count == 1){
        printf("Launched child process %d\n",getpid());
        mandelbrotFunction(palette,fullMandelbrot,size,xmin,xmax,ymin,ymax,maxIterations,child1_colsStart,
                            child1_colsEnd,child1_rowsStart,child1_rowsEnd);
        printf("%d) Sub-Image block: cols (%d,%d) to rows (%d,%d)\n",getpid(), child1_colsStart,
                                                              child1_colsEnd,child1_rowsStart,child1_rowsEnd);
        fflush(stdout);
        exit(0);
      }
      if(count == 2){
        printf("Launched child process %d\n",getpid());
        mandelbrotFunction(palette,fullMandelbrot,size,xmin,xmax,ymin,ymax,maxIterations,
                                            child2_colsStart,child2_colsEnd,child2_rowsStart,
                                            child2_rowsEnd);
        printf("%d) Sub-Image block: cols (%d,%d) to rows (%d,%d)\n",getpid(), child2_colsStart,
                                                              child2_colsEnd,child2_rowsStart,child2_rowsEnd);
        fflush(stdout);
        exit(0);
      }
      if(count == 3){
        printf("Launched child process %d\n",getpid());
        mandelbrotFunction(palette,fullMandelbrot,size,xmin,xmax,ymin,ymax,maxIterations,
                                            child3_colsStart,child3_colsEnd,child3_rowsStart,
                                            child3_rowsEnd);
        printf("%d) Sub-Image block: cols (%d,%d) to rows (%d,%d)\n",getpid(), child3_colsStart,
                                                              child3_colsEnd,child3_rowsStart,child3_rowsEnd);
        fflush(stdout);
        exit(0);

      }
      if(count == 4){
        printf("Launched child process %d\n",getpid());
        mandelbrotFunction(palette,fullMandelbrot,size,xmin,xmax,ymin,ymax,maxIterations,
                                            child4_colsStart,child4_colsEnd,child4_rowsStart,
                                            child4_rowsEnd);
        printf("%d) Sub-Image block: cols (%d,%d) to rows (%d,%d)\n",getpid(), child4_colsStart,
                                                              child4_colsEnd,child4_rowsStart,child4_rowsEnd);
        fflush(stdout);
        exit(0);

      }
      exit(0);
    }
    else{
      fflush(stdout);
    }
  }
  for(int i = 1; i <=4;i++){
    int status; 
    int pid = wait(&status);
    printf("Child process complete\n");
    fflush(stdout);
  } 

  gettimeofday(&tend, NULL);
  timer = tend.tv_sec - tstart.tv_sec + (tend.tv_usec - tstart.tv_usec)/1.e6;
  printf("Computed mandelbrot set (%dx%d) in %f seconds\n",size,size,timer);

  char buffer[1000];
  int times = time(0);
  snprintf(buffer, sizeof(buffer), "multi-mandelbrot-%d-%d.ppm", size,times);

  write_ppm(buffer,fullMandelbrot,size,size);
  printf("Writing file: %s\n",buffer);

  free(palette);
  if (shmdt(fullMandelbrot) == -1) {
    perror("Error: cannot detatch from shared memory\n");
    exit(1);
  }

  if (shmctl(shmid, IPC_RMID, 0) == -1) {
    perror("Error: cannot remove shared memory\n");
    exit(1);
  }

}
