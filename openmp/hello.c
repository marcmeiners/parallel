#include <omp.h>
#include <stdio.h>

int main(){
    #pragma omp parallel num_threads(4)
    {
        int ID = omp_get_thread_num();
        printf("hello (%d)", ID);
    }
}
