#include <stdio.h>
#include <omp.h>

int main() {
    int num_threads=2;
    omp_set_num_threads(num_threads);
    #pragma omp parallel
    {
        int thread_ID = omp_get_thread_num();
        printf(" hello world %d\n", thread_ID);
    }
}
