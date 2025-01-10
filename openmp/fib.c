#include <stdio.h>
#include <omp.h>

void fillFibonacci(int fib[], int N) {
    fib[0] = 0;
    fib[1] = 1;

    #pragma omp parallel
    #pragma omp single
    for (int i = 2; i < N; i++) {
        #pragma omp task depend(in: fib[i-1], fib[i-2]) depend(out: fib[i])
        fib[i] = fib[i-1] + fib[i-2];
    }
}

int main() {
    const int N = 15;
    int fib[N];

    fillFibonacci(fib, N);

    // Ensuring all tasks are completed
    #pragma omp taskwait

    printf("The first %d numbers of the Fibonacci sequence are:\n", N);
    for (int i = 0; i < N; i++) {
        printf("%d ", fib[i]);
    }
    printf("\n");

    return 0;
}
