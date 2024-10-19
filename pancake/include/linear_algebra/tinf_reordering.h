#ifndef TINF_REORDERING_H
#define TINF_REORDERING_H
#include <stdlib.h>

#ifdef __cplusplus
extern "C"
{
#endif

  typedef int32_t (*tinf_reordering_create_f)(
      void **reord_context, const char *method_name,
      const int32_t method_name_length, const int32_t select_tinf_data_type,
      const int32_t select_tinf_matrix_type, int64_t *const ipar,
      const int32_t ipar_length, void *const dpar, const int32_t dpar_length,
      const int32_t global_id);

  typedef int32_t (*tinf_reordering_destroy_f)(void **reord_context);

  typedef int32_t (*tinf_reordering_generate_symbolic_f)(
      void *reord_context, const int64_t num_rows, const int32_t block_size,
      const int64_t a_num_blocks, int64_t *a_row, int64_t *a_col,
      int64_t *a_diag, int64_t *ipar, void *dpar, int64_t **old_to_new,
      int64_t **new_to_old);

  typedef int32_t (*tinf_reordering_apply_f)(
      void *reord_context, int64_t num_rows, const int32_t block_size,
      const int64_t a_num_blocks, int64_t *ipar, void *dpar,
      int64_t *old_to_new, int64_t *new_to_old, int64_t *a_row, int64_t *a_col,
      int64_t *a_diag, void *a_val, int64_t **ra_row, int64_t **ra_col,
      int64_t **ra_diag, void **ra_val);

  /**
  * Create a reordering context for parition and store a pointer to it in
  * reordering_context.
  *
  * @param method_name  reordering context
  * @param method_name  reordering name
  * @param method_name_length  reordering name length
  * @param select_tinf_data_type  identify the data type of the x array and
  result using the TINF_DATA_TYPE enum
  * @param select_tinf_matrix_type  identify the matrix format type using
             the TINF_MATRIX_TYPE enum
  * @param ipar  integer parameter array for the reordering method
  * @param ipar_length  integer length of ipar array (minimum IPAR_LENGTH)
  * @param dpar  data parameter array storing inputs and outputs from a
  reordering
  *          method
  * @param dpar_length  integer length of dpar array (minimum DPAR_LENGTH)
  * @param global_id  partition id
  * @returns  Error code
  **/
  int32_t
  tinf_reordering_create(void **reord_context, const char *method_name,
                         const int32_t method_name_length,
                         const int32_t select_tinf_data_type,
                         const int32_t select_tinf_matrix_type,
                         int64_t *const ipar, const int32_t ipar_length,
                         void *const dpar, const int32_t dpar_length,
                         const int32_t global_id);

  /**
   * Destroy a reordering context for parition and store a pointer to it in
   * reordering_context.
   *
   * @param method_name  reordering context
   * @returns  Error code
   **/
  int32_t
  tinf_reordering_destroy(void **reord_context);

  /**
   * Generate a reordering pattern for parition and store the permutations
   *arrays in old_to_new and new_to_old.
   *
   * @param method_name  reordering context
   * @param block_size number of scalar rows in each block
   * @param a_num_blocks number of non-zero blocks
   * @param a_row  stores the locations in the A vector that start a row
   * @param a_col  stores the column indexes of the blocks in the A array
   * @param a_diag  stores the diagonal indexes of the blocks in the A array
   * @param ipar  integer parameter array for the reordering method
   * @param dpar  data parameter array storing inputs and outputs from a
   *reordering
   * @param old_to_new  forward permutation array
   * @param new_to_old  backward permutation array
   *          method
   * @returns  Error code
   **/
  int32_t
  tinf_reordering_generate_symbolic(void *reord_context, const int64_t num_rows,
                                    const int32_t block_size,
                                    const int64_t a_num_blocks, int64_t *a_row,
                                    int64_t *a_col, int64_t *a_diag,
                                    int64_t *ipar, void *dpar,
                                    int64_t **old_to_new, int64_t **new_to_old);

  /**
   * Apply a reordering permutation and store the reordered sparsity matrix
   * in ra_row, ra_col, ra_diag, and ra_val.
   *
   * @param method_name  reordering context
   * @param block_size number of scalar rows in each block
   * @param a_num_blocks number of non-zero blocks
   * @param a_row  stores the locations in the A vector that start a row
   * @param a_col  stores the column indexes of the blocks in the A array
   * @param a_diag  stores the diagonal indexes of the blocks in the A array
   * @param ipar  integer parameter array for the reordering method
   * @param dpar  data parameter array storing inputs and outputs from a
   *reordering
   * @param old_to_new  forward permutation array
   * @param new_to_old  backward permutation array
   * @param ra_row  stores the locations in the RA vector that start a row
   * @param ra_col  stores the column indexes of the blocks in the RA array
   * @param ra_diag  stores the diagonal indexes of the blocks in the RA array
   * @returns  Error code
   **/
  int32_t
  tinf_reordering_apply(void *reord_context, int64_t num_rows,
                        const int32_t block_size, const int64_t a_num_blocks,
                        int64_t *ipar, void *dpar, int64_t *old_to_new,
                        int64_t *new_to_old, int64_t *a_row, int64_t *a_col,
                        int64_t *a_diag, void *a_val, int64_t **ra_row,
                        int64_t **ra_col, int64_t **ra_diag, void **ra_val);

#ifdef __cplusplus
}
#endif

#endif
