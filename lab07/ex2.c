#include "ex2.h"

void v_add_naive(double* x, double* y, double* z) {
    #pragma omp parallel
    {
    for(int i=0; i<ARRAY_SIZE; i++)
        z[i] = x[i] + y[i];
    }
}

// Adjacent Method
void v_add_optimized_adjacent(double* x, double* y, double* z) {
    // TODO: Implement this function
     #pragma omp parallel
     {
        int thread_num=omp_get_num_threads();
        int thread_id=omp_get_thread_num();

        for(int i=thread_id;i<ARRAY_SIZE;i+=thread_num){
            z[i] = x[i] + y[i];
        }
     }
    // Do NOT use the `for` directive here!
}

// Chunks Method
void v_add_optimized_chunks(double* x, double* y, double* z) {
    #pragma omp parallel
    {
        // TODO: Implement this function
        int thread_num=omp_get_num_threads();
        int thread_id=omp_get_thread_num();
        int chunk=ARRAY_SIZE/thread_num;
        int start=thread_id*chunk;
        int end=(thread_id==thread_num-1)?ARRAY_SIZE:start+chunk;
        for(int i=start;i<end;i++){
            z[i]=x[i]+y[i];
        }
    }
    // Do NOT use the `for` directive here!
}
