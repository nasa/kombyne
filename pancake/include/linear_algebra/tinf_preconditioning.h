#ifndef TINF_PRECONDITIONER_H
#define TINF_PRECONDITIONER_H
#include <stdlib.h>

#ifdef __cplusplus
extern "C"
{
#endif

  typedef int32_t (*tinf_preconditioner_create_f)(
      void **precond_context, const char *method_name,
      const int32_t method_name_length, const int32_t select_tinf_data_type,
      const int32_t select_tinf_matrix_type, int64_t *const ipar,
      const int32_t ipar_length, void *const dpar, const int32_t dpar_length,
      void *iris_context, void *iris_sync_pattern, const int32_t global_id);

  typedef int32_t (*tinf_preconditioner_destroy_f)(void **precond_context,
                                                   const int32_t block_size);

  typedef int32_t (*tinf_preconditioner_generate_symbolic_f)(
      void *precond_context, int64_t *ipar, void *dpar, const int64_t num_rows,
      const int64_t num_cols, const int32_t block_size,
      const int64_t a_num_blocks, void *a_val, int64_t *a_row, int64_t *a_col);

  typedef int32_t (*tinf_preconditioner_initialize_numeric_f)(
      void *precond_context, int64_t *ipar, void *dpar, void *a_val);

  typedef int32_t (*tinf_preconditioner_update_numeric_f)(void *precond_context,
                                                          int64_t *ipar,
                                                          void *dpar,
                                                          void *a_val);

  typedef int32_t (*tinf_preconditioner_apply_f)(void *precond_context,
                                                 int64_t *ipar, void *dpar,
                                                 int64_t num_rows, void *x,
                                                 void *y, void *rhs);

  /**
  * Create a preconditioner context for parition and store a pointer to it in
  * precond_context.
  *
  * @param method_name  preconditioner context
  * @param method_name  preconditioner name
  * @param method_name_length  preconditioner name length
  * @param select_tinf_data_type  identify the data type of the x array and
  result using the TINF_DATA_TYPE enum
  * @param select_tinf_matrix_type  identify the matrix format type using
             the TINF_MATRIX_TYPE enum
  * @param ipar  integer parameter array for the preconditioner method
  * @param ipar_length  integer length of ipar array (minimum IPAR_LENGTH)
  * @param dpar  data parameter array storing inputs and outputs from a
  *          preconditioner method
  * @param dpar_length  integer length of dpar array (minimum DPAR_LENGTH)
  * @param iris_handle  IRIS communications context
  * @param iris_sync_pattern  IRIS communications syncronization pattern
  * @param global_id  partition id
  * @returns  Error code
  **/
  int32_t
  tinf_preconditioner_create(void **precond_context, const char *method_name,
                             const int32_t method_name_length,
                             const int32_t select_tinf_data_type,
                             const int32_t select_tinf_matrix_type,
                             int64_t *const ipar, const int32_t ipar_length,
                             void *const dpar, const int32_t dpar_length,
                             void *iris_context, void *iris_sync_pattern,
                             const int32_t global_id);

  /**
   * Destroy a preconditioner context.
   *
   * @param method_name  preconditioner context
   * @returns  Error code
   **/
  int32_t
  tinf_preconditioner_destroy(void **precond_context, const int32_t block_size);

  /**
   * Generate the sparsity pattern for a preconditioning method.
   *
   * @param method_name  preconditioner context
   * @param ipar  integer parameter array for the preconditioner method
   * @param dpar  data parameter array storing inputs and outputs from a
   *          preconditioner method
   * @param num_rows  number of block rows in A matrix
   * @param num_rows number of rows in A matrix
   * @param num_rcol number of columns in A matrix
   * @param a_num_blocks number of non-zero blocks
   * @param block_size number of scalar rows in each block
   * @param a_val  contiguous array of matrix values
   * @param a_row  stores the locations in the A vector that start a row
   * @param a_col  stores the column indexes of the blocks in the A array
   * @returns  Error code
   **/
  int32_t
  tinf_preconditioner_generate_symbolic(void *precond_context, int64_t *ipar,
                                        void *dpar, const int64_t num_rows,
                                        const int64_t num_cols,
                                        const int32_t block_size,
                                        const int64_t a_num_blocks, void *a_val,
                                        int64_t *a_row, int64_t *a_col);

  /**
   * Initialize the preconditioning method with values from the A matrix.
   *
   * @param method_name  preconditioner context
   * @param ipar  integer parameter array for the preconditioner method
   * @param dpar  data parameter array storing inputs and outputs from a
   *          preconditioner method
   * @param a_val  contiguous array of matrix values
   * @returns  Error code
   **/
  int32_t
  tinf_preconditioner_initialize_numeric(void *precond_context, int64_t *ipar,
                                         void *dpar, void *a_val);

  /**
   * Update the numberic values of the preconditioning method.
   *
   * @param method_name  preconditioner context
   * @param ipar  integer parameter array for the preconditioner method
   * @param dpar  data parameter array storing inputs and outputs from a
   *          preconditioner method
   * @param a_val  contiguous array of matrix values
   * @returns  Error code
   **/
  int32_t
  tinf_preconditioner_update_numeric(void *precond_context, int64_t *ipar,
                                     void *dpar, void *a_val);

  /**
   * Apply preconditioning method to dense vector x and store the result in y.
   *
   * @param method_name  preconditioner context
   * @param ipar  integer parameter array for the preconditioner method
   * @param dpar  data parameter array storing inputs and outputs from a
   *          preconditioner method
   * @param num_rows  number of block rows in A matrix
   * @param x  dense array of minimum length num_rows*block_size
   * @param y  dense array of minimum length num_rows*block_size
   * @param rhs  dense array of minimum length num_rows*block_size
   * @returns  Error code
   **/
  int32_t
  tinf_preconditioner_apply(void *precond_context, int64_t *ipar, void *dpar,
                            int64_t num_rows, void *x, void *y, void *rhs);

#ifdef __cplusplus
}
#endif

#endif
