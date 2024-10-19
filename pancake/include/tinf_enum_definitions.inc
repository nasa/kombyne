! tinf_max_ranks
enum, bind(c)
  enumerator ::                                                                &
   TINF_PROBLEM_MAX_RANK = 5,                                                  &
   TINF_DATA_MAX_RANK = 2
end enum

! tinf_error_codes
enum, bind(c)
  enumerator ::                                                                &
   TINF_SUCCESS = 1,                                                           &
   TINF_FAILURE = 2,                                                           &
   TINF_FINISHED = 3
end enum

! tinf_element_type
enum, bind(c)
  enumerator ::                                                                &
      TINF_NODE = 2,                                                           &
      TINF_BAR_2 = 3,                                                          &
      TINF_BAR_3 = 4,                                                          &
      TINF_BAR_4 = 24,                                                         &
      TINF_BAR_5 = 40,                                                         &
      TINF_TRI_3 = 5,                                                          &
      TINF_TRI_6 = 6,                                                          &
      TINF_TRI_9 = 25,                                                         &
      TINF_TRI_10 = 26,                                                        &
      TINF_TRI_12 = 41,                                                        &
      TINF_TRI_15 = 42,                                                        &
      TINF_QUAD_4 = 7,                                                         &
      TINF_QUAD_8 = 8,                                                         &
      TINF_QUAD_9 = 9,                                                         &
      TINF_QUAD_12 = 27,                                                       &
      TINF_QUAD_16 = 28,                                                       &
      TINF_QUAD_P4_16 = 4,                                                     &
      TINF_QUAD_25 = 44,                                                       &
      TINF_TETRA_4 = 10,                                                       &
      TINF_TETRA_10 = 11,                                                      &
      TINF_TETRA_16 = 29,                                                      &
      TINF_TETRA_20 = 30,                                                      &
      TINF_TETRA_22 = 45,                                                      &
      TINF_TETRA_34 = 46,                                                      &
      TINF_TETRA_35 = 47,                                                      &
      TINF_PYRA_5 = 12,                                                        &
      TINF_PYRA_14 = 13,                                                       &
      TINF_PYRA_13 = 21,                                                       &
      TINF_PYRA_21 = 31,                                                       &
      TINF_PYRA_29 = 32,                                                       &
      TINF_PYRA_30 = 33,                                                       &
      TINF_PYRA_P4_29 = 4,                                                     &
      TINF_PYRA_50 = 49,                                                       &
      TINF_PYRA_55 = 50,                                                       &
      TINF_PENTA_6 = 14,                                                       &
      TINF_PENTA_15 = 15,                                                      &
      TINF_PENTA_18 = 16,                                                      &
      TINF_PENTA_24 = 34,                                                      &
      TINF_PENTA_38 = 35,                                                      &
      TINF_PENTA_40 = 36,                                                      &
      TINF_PENTA_33 = 51,                                                      &
      TINF_PENTA_66 = 52,                                                      &
      TINF_PENTA_75 = 53,                                                      &
      TINF_HEXA_8 = 17,                                                        &
      TINF_HEXA_20 = 18,                                                       &
      TINF_HEXA_27 = 19,                                                       &
      TINF_HEXA_32 = 37,                                                       &
      TINF_HEXA_56 = 38,                                                       &
      TINF_HEXA_64 = 39,                                                       &
      TINF_HEXA_44 = 54,                                                       &
      TINF_HEXA_98 = 55,                                                       &
      TINF_HEXA_125 = 56
end enum

! tinf_data_types
enum, bind(c)
  enumerator ::                                                                &
   TINF_INT32 = 1,                                                             &
   TINF_INT64 = 2,                                                             &
   TINF_FLOAT = 3,                                                             &
   TINF_DOUBLE = 4,                                                            &
   TINF_CHAR = 5,                                                              &
   TINF_BOOL = 6,                                                              &
   TINF_CMPLX_FLOAT = 7,                                                       &
   TINF_CMPLX_DOUBLE = 8
end enum

! tinf_matrix_type
enum, bind(c)
  enumerator ::                                                                &
      TINF_DENSE = 1,                                                          &
      TINF_COO = 2,                                                            &
      TINF_CSR = 3,                                                            &
      TINF_CSC = 4,                                                            &
      TINF_BSC = 5,                                                            &
      TINF_BSR = 6,                                                            &
      TINF_BSRC = 7,                                                           &
      TINF_BSRR = 8
end enum
