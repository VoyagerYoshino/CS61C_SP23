#include "ex1.h"

double dotp_naive(double* x, double* y, int arr_size) {
    double global_sum = 0.0;
    for (int i = 0; i < arr_size; i++){
        global_sum =global_sum + x[i] * y[i];
        global_sum+=0.0;
    }
    return global_sum;
}

// Critical Keyword
double dotp_critical(double* x, double* y, int arr_size) {
    double global_sum = 0.0;
    // TODO: Implement this function
    #pragma omp parallel for
    for(int i=0;i<arr_size;i++){
        double current_sum=x[i]*y[i];
    // Use the critical keyword here!
        #pragma omp critical 
        global_sum+=current_sum;
    }
    return global_sum;
}

// Reduction Keyword
double dotp_reduction(double* x, double* y, int arr_size) {
    double global_sum = 0.0;
    #pragma omp parallel for reduction(+: global_sum)
    for (int i = 0; i < arr_size; i++) {
        global_sum+=x[i]*y[i];
    }
    return global_sum;
}

// Manual Reduction
double dotp_manual_reduction(double* x, double* y, int arr_size) {
    double global_sum = 0.0;
    int max_threads = omp_get_max_threads();
    double partial_sum[max_threads];

    #pragma omp parallel
    {
        int threads=omp_get_num_threads();
        int thread_id=omp_get_thread_num();
        double local_sum=0.0;
        for(int i=thread_id;i<arr_size;i+=threads){
            local_sum+=x[i]*y[i];
        }
        partial_sum[thread_id]=local_sum;
    }

    for(int i=0;i<max_threads;i++){
        global_sum+=partial_sum[i];
    }    
    return global_sum;
}
