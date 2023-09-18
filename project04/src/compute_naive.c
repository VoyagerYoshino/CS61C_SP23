#include "compute.h"

// Computes the dot product of vec1 and vec2, both of size n
int flip_dot(uint32_t n, int32_t *vec1, int32_t *vec2) {
  // TODO: implement dot product of vec1 and vec2, both of size n
  int result=0;
  for(uint32_t i=0;i<n;i++){
    result+=vec1[i]*vec2[n-i-1];
  }
  return result;
}

// Computes the convolution of two matrices
int convolve(matrix_t *a_matrix, matrix_t *b_matrix, matrix_t **output_matrix) {
  // TODO: convolve matrix a and matrix b, and store the resulting matrix in
  uint32_t row_output=a_matrix->rows-b_matrix->rows+1;
  uint32_t col_output=a_matrix->cols-b_matrix->cols+1;
  matrix_t *result=(matrix_t*)malloc(sizeof(matrix_t));
  if (result==NULL){
    return -1;
  }
  result->rows=row_output;
  result->cols=col_output;
  result->data=(int32_t*)malloc(row_output*col_output*sizeof(int32_t));
  if (result->data==NULL){
    return -1;
  }
  uint32_t index=0;

  for(int i=0;i<row_output;i++){
    for(int j=0;j<col_output;j++){
          for(int a_index=0;a_index<a_matrix->cols*b_matrix->rows;a_index+=a_matrix->cols){
            result->data[index]+=flip_dot(b_matrix->cols,(a_matrix->data)+sizeof(int32_t)*a_index,b_matrix->data);
          }
          index+=1;
    }
  }
  // output_matrix
  *output_matrix=result;
  return 0;
}

// Executes a task
int execute_task(task_t *task) {
  matrix_t *a_matrix, *b_matrix, *output_matrix;

  if (read_matrix(get_a_matrix_path(task), &a_matrix))
    return -1;
  if (read_matrix(get_b_matrix_path(task), &b_matrix))
    return -1;

  if (convolve(a_matrix, b_matrix, &output_matrix))
    return -1;

  if (write_matrix(get_output_matrix_path(task), output_matrix))
    return -1;

  free(a_matrix->data);
  free(b_matrix->data);
  free(output_matrix->data);
  free(a_matrix);
  free(b_matrix);
  free(output_matrix);
  return 0;
}
