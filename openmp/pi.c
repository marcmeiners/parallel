#include <omp.h>
#include <stdio.h>

static long num_steps = 100000;
double step;

#define NUM_THREADS 4
//padding so each sum value is on different cache line
#define PAD 8


void main(){
    int i, nthreads;
    double pi, sum[NUM_THREADS][PAD];
    step = 1.0 / (double) num_steps;
    omp_set_num_threads(NUM_THREADS);

    #pragma omp parallel
    {
       int i, id, nthrds;
       double x;
       id = omp_get_thread_num();
       nthrds = omp_get_num_threads();
       //the global number of thread variable can only be set once pragma omp parallel is initiated
       if(id == 0) nthreads = nthrds;
       
       for(i=id, sum[id][0] = 0.0; i<num_steps; i=i+nthrds){
            x = (i+0.5)*step;
            sum[id][0] += 4.0/(1.0 + x*x);
       }
    }

    for(i=0, pi=0.0; i<nthreads; i++){
        pi+=sum[i][0]*step;
    }
    printf("the result is: %lf", pi);
}
//gcc -o pi -fopenmp pi.c