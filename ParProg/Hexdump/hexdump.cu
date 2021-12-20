#include <stdio.h>
//#include <unistd.h>
//#include <stdlib.h>

const long N = 1 << 28;
char x[N];
char y[4*N];

__global__
void hexdump(char *y, char *x, size_t n)
{
  int i = blockIdx.x*blockDim.x + threadIdx.x;
  if (i < n)
  {
    char lowest = x[i] & 15;
    char highest = x[i] >> 4;
    y[4*i] = '\\';
    y[4*i+1] = 'x';
    y[4*i+2] = highest + (highest > 10 ? 'a' - 10 : '0');
    y[4*i+3] = lowest + (lowest > 10 ? 'a' - 10 : '0');
  }
}

int main(int argc, char * argv[])
{
  if (argc < 2)
  {
    printf("Usage: %s <filename>\n", argv[0]);
    return 1;
  }
  char *d_x, *d_y;
  FILE * binaryFile = fopen(argv[1], "rb");
  //x = (char*)calloc(N, sizeof(char));
  //y = (char*)calloc(4*N, sizeof(char));
  long n = fread(x, sizeof(char), N, binaryFile);
  cudaMalloc(&d_x, n*sizeof(char));
  cudaMalloc(&d_y, 4*n*sizeof(char));


  cudaMemcpy(d_x, x, n*sizeof(char), cudaMemcpyHostToDevice);
  cudaMemcpy(d_y, y, 4*n*sizeof(char), cudaMemcpyHostToDevice);

  // Perform SAXPY on 1M elements
  //saxpy<<<(N+255)/256, 256>>>(N, 2.0f, d_x, d_y);
  //sleep(20);
  hexdump<<<(N+255)/256, 256>>>(d_y, d_x, n);
  cudaMemcpy(y, d_y, 4*n*sizeof(char), cudaMemcpyDeviceToHost);
  //sleep(30);
  y[4*n-1] = 0;
  printf("%s", y);
  cudaFree(d_x);
  cudaFree(d_y);
  //free(x);
  //free(y);
 }
