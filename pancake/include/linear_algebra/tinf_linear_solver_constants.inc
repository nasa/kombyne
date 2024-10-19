enum, bind(c)
  enumerator ::                                                                &
    IPAR_LENGTH = 16,                                                          &
    DPAR_LENGTH = 16
end enum

! Indices to ipar
enum, bind(c)
  enumerator ::                                                                &
    RCI_INDEX = 0,                                                             &
    PRECOND_DIRECTION_INDEX = 1,                                               &
    STOPPING_CRITERIA_INDEX = 2,                                               &
    WORK_SPACE_SIZE_INDEX = 3,                                                 &
    KRYLOV_SUBSPACE_SIZE_INDEX = 4,                                            &
    MAX_MATVEC_INDEX = 5,                                                      &
    MATVEC_COUNT_INDEX = 6,                                                    &
    MATVEC_INPUT_INDEX = 7,                                                    &
    MATVEC_OUTPUT_INDEX = 8,                                                   &
    INTERNAL_INDEX = 9,                                                        &
    EXTERNAL_CONVERGENCE_TEST_INDEX = 10,                                      &
    ORTHOG_ERROR_INDEX = 11,                                                   &
    INIT_COUNT_INDEX = 12,                                                     &
    REORTH_INDEX = 13,                                                         &
    ORTHOG_SELECTION_INDEX = 14,                                               &
    C_FORTRAN_INDEXING = 15
end enum

// Indices to dpar
enum, bind(c)
  enumerator ::                                                                &
    RELATIVE_TOLERANCE_INDEX = 0,                                              &
    ABSOLUTE_TOLERANCE_INDEX = 1,                                              &
    INITIAL_RESIDUAL_INDEX = 2,                                                &
    TARGET_RESIDUAL_INDEX = 3,                                                 &
    CURRENT_RESIDUAL_INDEX = 4,                                                &
    CURRENT_RESIDUAL_ERROR_INDEX = 5,                                          &
    CONVERGENCE_RATE_INDEX = 6,                                                &
    SOLVER_TIMER_INDEX = 7,                                                    &
    FLOP_COUNT_INDEX = 10
end enum

// RCI flags
//   1 == request a matvec with A,
//   2 == request a matvec with A^T,
//   3 == request a left preconditioner solve (Ml^{-1}),
//   4 == request a left preconditioner transposed solve (Ml^{-T}),
//   5 == request a right preconditioner solve (Mr^{-1}),
//   6 == request a right preconditioner transposed solve (Mr^{-T}),
//   10 == request the caller to perform stopping test,
//   0 == normal termination of the solver, satisfied the stopping
//            criteria,
//  -1 == termination because iteration number is greater than the
//        preset limit,
//  -2 == return due to insufficient work space,
//  -3 == return due to anticipated break-down / divide by zero,
//        in the case where Arnoldi procedure is used, additional
//            error code can be found in ipar(12), where ipar(12) is
//            the error code of orthogonalization procedure MGSRO:
//           -1: zero input vector
//           -2: input vector contains abnormal numbers
//           -3: input vector is a linear combination of others
//           -4: triangular system in GMRES/FOM/etc. has nul rank
//  -4 == the values of fpar(1) and fpar(2) are both <= 0, the valid
//    ranges are 0 <= fpar(1) < 1, 0 <= fpar(2), and they can
//    not be zero at the same time
//  -9 == while trying to detect a break-down, an abnormal number is
//        detected.
// -10 == return due to some non-numerical reasons, e.g. invalid
//            floating-point numbers etc.
//
//   ipar(2) -- status of the preconditioning:
//   0 == no preconditioning
//   1 == left preconditioning only
//   2 == right preconditioning only
//   3 == both left and right preconditioning

enum, bind(c)
  enumerator ::                                                                &
    LINEAR_SOLVERCONVERGED = 0,
    LINEAR_SOLVERSTOPPED = -1,
    USER_MATRIX_VECTOR_PRODUCT = 1,
    USER_TRANS_MATRIX_VECTOR_PRODUCT = 2,
    USER_LEFT_PRECONDITIONER_APPLICATION = 3,
    USER_LEFT_TRANS_PRECONDITIONER_APPLICATION = 4,
    USER_RIGHT_PRECONDITIONER_APPLICATION = 5,
    USER_RIGHT_TRANS_PRECONDITIONER_APPLICATION = 6,
    USER_STOPPING_TEST = 10,
    USER_RESTART = 11,
end enum
