#include <stdio.h>
#include <math.h>
#include <omp.h>
#include <stdlib.h>


double f(double x)
{
    return 4*sqrt(1-x*x);
}

int main(int argc, char * argv[])
{
    int N = 50000000;
    int size = 4;
    if (argc > 1) N = atoi(argv[1]);
    if (argc > 2) size = atoi(argv[2]);

    double h = 1.0 / N;
    double result = 0.0;
    double start = omp_get_wtime();
    printf("threads (1): %d\n", omp_get_num_threads());
    omp_set_num_threads(size);

#pragma omp parallel shared(N, size) reduction(+: result)
    {
        printf("threads (2): %d\n", omp_get_num_threads());
        int i = omp_get_thread_num();
        for (; i < N; i+= size)
        {
            result += (f(i*h) + f(i*h + h))*h/2;
        }
    }

    //result -= (f(0) + f(1))*h/2;
    double end = omp_get_wtime();

    printf("%.10lf,%d,%.5lf\n", result, size, end - start);


    return 0;
}
