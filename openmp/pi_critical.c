#include <omp.h>
#include <stdio.h>

static long num_steps = 100000000;
double step;
#define NUM_THREADS 4

void main(){
    int i;
    double pi;
    step = 1.0 / (double) num_steps;
    omp_set_num_threads(NUM_THREADS);

    #pragma omp parallel
    {
        int i, id, nthrds;
        double x, sum;

        id = omp_get_thread_num();
        nthrds = omp_get_num_threads();
    
        for(i=id, sum=0.0; i<num_steps; i+= nthrds){
            x = (i+0.5)*step;
            sum += 4.0/(1.0 + x*x);
        }
        #pragma omp critical
        pi += sum * step;
    }
    printf("the result is: %lf", pi);
}
//gcc -o pi_critical -fopenmp pi_critical.c