#pragma once
#ifndef TINF_LINEAR_SOLVER_H
#define TINF_LINEAR_SOLVER_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdlib.h>

#include "tinf_linear_solver_constants.h"

#ifdef __cplusplus
extern "C"
{
#endif

  typedef int32_t (*tinf_linear_solver_rci_create_f)(void** linear_solver,
                                               const char* const method_name,
                                               const int32_t method_name_length,
                                               const int32_t data_type,
                                               const int64_t rows,
                                               const int32_t block_size,
                                               int64_t* const ipar,
                                               const int32_t ipar_length,
                                               void* const dpar,
                                               const int32_t dpar_length,
                                               void* const comm,
                                               void* const sync_pattern,
                                               void** work_space);
  typedef int32_t (*tinf_linear_solver_rci_destroy_f)(void** linear_solver,
                                                      void** work_space);
  typedef int32_t (*tinf_linear_solver_rci_f)(void* const linear_solver,
                                              const int64_t rows,
                                              const int32_t block_size,
                                              void* const rhs, void* const sol,
                                              int64_t* const ipar,
                                              void* const dpar,
                                              void* const work_space);

/**f1
 * Create a linear system solver that implements the reverse-communication interface (RCI) to solve Ax = b.
 *
 * @param linear_solver  Opaque pointer to linear system solver
 * @param method_name  Linear system solver method name, eg. gmres, fgmres, or jacobi
 * @param method_name_length  Length of the method_name (including null terminator)
 * @param data_type  Data type of the dpar, work_space, b, and x arrays
 * @param rows  Number of block rows in the linear system
 * @param block_size Number of scalar rows in each block
 * @param ipar  Integer parameter array for the reverse-communication protocol
 * @param ipar_length  Length of ipar array (minimum IPAR_LENGTH)
 * @param dpar  Pointer to storage for data parameter array storing inputs and outputs
 * @param dpar_length  Length of dpar array (minimum DPAR_LENGTH)
 * @param comm  Iris communications context
 * @param sync_pattern  Iris communications syncronization pattern
 * @param work_space  Pointer to storage utilized by the linear solver for intermediate calculations
 * @returns  Error code
 **/
int32_t tinf_linear_solver_rci_create(void** linear_solver,
                                      const char* const method_name,
                                      const int32_t method_name_length,
                                      const int32_t data_type,
                                      const int64_t rows,
                                      const int32_t block_size,
                                      int64_t* const ipar,
                                      const int32_t ipar_length,
                                      void* const dpar,
                                      const int32_t dpar_length,
                                      void* const comm,
                                      void* const sync_pattern,
                                      void** work_space);

/**f2
 * Destroy a linear system solver that implements the reverse-communication interface (RCI) and free the workspace.
 *
 * @param linear_solver  Opaque pointer to linear system solver
 * @param work_space  Pointer to storage utilized by the linear solver for intermediate calculations
 * @returns  Error code
 **/
int32_t tinf_linear_solver_rci_destroy(void** linear_solver,
                                       void** work_space);


/**
 * Call a reverse-communication interface (RCI) linear system solver.
 *
 * @param linear_solver  Opaque pointer to linear system solver
 * @param rows  Number of block rows in linear system
 * @param block_size Number of scalar rows in each block
 * @param b  Pointer to storage for the Right-Hand-Side array
 * @param x  Pointer to storage for the solution array
 * @param ipar  Integer parameter array for the reverse-communication protocol
 * @param dpar  Pointer to storage for data parameter array storing inputs and outputs
 * @param work_space  Pointer to storage utilized by the linear solver for intermediate calculations
 * @returns  Error code
 **/
int32_t tinf_linear_solver_rci(void* const linear_solver,
                               const int64_t rows, const int32_t block_size,
                               void* const rhs, void* const sol,
                               int64_t* const ipar, void* const dpar,
                               void* const work_space);


#ifdef __cplusplus
}
#endif

#endif 
