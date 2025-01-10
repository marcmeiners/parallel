#include <omp.h>
#include <stdio.h>

static long num_steps = 100000000;
double step;

void main(){
    int i;
    double x, pi, sum = 0.0;
    step = 1.0 / (double) num_steps;

    #pragma omp parallel
    {
        double x;
        //creates local copy of sum, in the end reduced using "+"
        #pragma omp for reduction(+:sum)

        for(i=0; i<num_steps; i++){
            x = (i+0.5)*step;
            sum += 4.0/(1.0 + x*x);
        }
    }

    pi = sum * step;
    printf("the result is: %lf", pi);
}
//gcc -o pi_loop_reduction -fopenmp pi_loop_reduction.c