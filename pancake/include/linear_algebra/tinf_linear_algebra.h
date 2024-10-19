#ifndef TINF_LINEAR_ALGEBRA_H
#define TINF_LINEAR_ALGEBRA_H
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
* Calculate the l2 norm of an array and store the value in a scalar, result,
* using sequential operations.
*
* @param select_tinf_data_type  identify the data type of the x array and result
           using the TINF_DATA_TYPE enum
* @param n  number of scalar values in x
* @param x  dense input array of size n
* @param incx  spacing between scalar values in x
* @param result  l2 norm of x
* @returns  Error code
**/
int32_t
tinf_nrm2(const int32_t select_tinf_data_type, const int64_t n,
          const void * const x, const int64_t incx, void * const result);

/**
* Calculate the l2 norm of an array and store the value in a scalar, result,
* using concurent operations.
*
* @param select_tinf_data_type  identify the data type of the x array and result
           using the TINF_DATA_TYPE enum
* @param select_tinf_execution_type  identify the concurrency execution type
           using the TINF_EXECUTION_TYPE enum
* @param n  number of scalar values in x
* @param x  dense input array of minimum size n*incx
* @param incx  spacing between scalar values in x
* @param iris_handle  IRIS communications context
* @param iris_sync_pattern  IRIS communications syncronization pattern
* @param result  l2 norm of x
* @returns  Error code
**/
int32_t
tinf_norm2(const int32_t select_tinf_data_type,
           const int32_t select_tinf_execution_type, const int64_t n,
           const void *const x, const int64_t incx, void *iris_context,
           void *iris_sync_pattern, void *const result);

/**
* Calculate the dot product of two arrays and store the value in a scalar,
* result using concurent operations.
*
* @param select_tinf_data_type  identify the data type of the x and y arrays and
           result using the TINF_DATA_TYPE enum
* @param select_tinf_execution_type  identify the concurrency execution type
           using the TINF_EXECUTION_TYPE enum
* @param n  number of scalar values in x and y
* @param x  dense input array of minimum size n*incx
* @param incx  spacing between scalar values in x
* @param y  dense input array of minimum size n*incy
* @param incy  spacing between scalar values in y
* @param iris_handle  IRIS communications context
* @param iris_sync_pattern  IRIS communications syncronization pattern
* @param result  l2 norm of x
* @returns  Error code
**/
int32_t
tinf_dot(const int32_t select_tinf_data_type,
         const int32_t select_tinf_execution_type, const int64_t n,
         const void *const x, const int64_t incx, const void *const y,
         const int64_t incy, void *iris_context, void *iris_sync_pattern,
         void *const result);

/**
* Perform a sparse matrix-vector product operation, y = A*x, with a
* block-sparse row-major matrix, A, and dense column vector, x, and
* store the result as a dense column vector, y using sequential operations.
*
* @param select_tinf_data_type  identify the data type of the A, x, and y arrays
           using the TINF_DATA_TYPE enum
* @param num_rows  number of block rows in A mtrix
* @param block_size number of scalar rows in each block
* @param a_num_blocks number of non-zero blocks
* @param a_val  contiguous array of matrix values
* @param row  stores the locations in the A vector that start a row
* @param col  stores the column indexes of the blocks in the A array
* @param x  dense input array of size num_rows*blocksize
* @param y  dense output array of size num_rows*blocksize
* @returns  Error code
**/
int32_t
tinf_bsrmv(const int32_t select_tinf_data_type,
           const int64_t num_rows, const int32_t blocksize,
           const int64_t a_num_blocks, const void * const a,
           const int64_t * const row, const int64_t * const col,
           const void * const x, void * const y);


/**
* Perform a sparse matrix-vector product operation, y = A*x, with a
* block-sparse row-major matrix, A, and dense column vector, x, and
* store the result as a dense column vector, y using concurent operations.
*
* @param select_tinf_data_type  identify the data type of the A, x, and y arrays
           using the TINF_DATA_TYPE enum
* @param select_tinf_execution_type  identify the concurrency execution type
           using the TINF_EXECUTION_TYPE enum
* @param select_tinf_matrix_type  identify the matrix format type using
           the TINF_MATRIX_TYPE enum
* @param num_rows  number of block rows in A mtrix
* @param block_size number of scalar rows in each block
* @param a_num_blocks number of non-zero blocks
* @param a_val  contiguous array of matrix values
* @param row  stores the locations in the A vector that start a row
* @param col  stores the column indexes of the blocks in the A array
* @param x  dense input array of size num_rows*blocksize
* @param iris_handle  IRIS communications context
* @param iris_sync_pattern  IRIS communications syncronization pattern
* @param y  dense output array of size num_rows*blocksize
* @returns  Error code
**/
int32_t
tinf_matvec(const int32_t select_tinf_data_type,
            const int32_t select_tinf_execution_type,
            const int32_t select_tinf_matrix_type,
            const int64_t num_rows, const int32_t blocksize,
            const int64_t a_num_blocks, const void * const a_val,
            const int64_t * const row, const int64_t * const col,
            const void * const x, void *iris_context, void *iris_sync_pattern,
            void * const y);

#ifdef __cplusplus
}
#endif

#endif 
