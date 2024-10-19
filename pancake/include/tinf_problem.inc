interface
  function tinf_problem_defined(problem, key, keylen, datatype,                &
                                rank, dims, ierr) result(valu) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_size_t, c_char,           &
                                            c_int32_t, c_bool
    implicit none
    type(c_ptr),                               value, intent(in)    :: problem
    integer(c_size_t),                         value, intent(in)    :: keylen
    character(len=1,kind=c_char), dimension(keylen),  intent(in)    :: key
    integer(c_int32_t),                               intent(out)   :: datatype
    integer(c_int32_t),                               intent(out)   :: rank
    integer(c_size_t),            dimension(5),       intent(out)   :: dims
    integer(c_int32_t),                               intent(out)   :: ierr
    logical(c_bool)                                                 :: valu
  end function tinf_problem_defined
end interface


interface
  function tinf_problem_value(problem, key, keylen,                          &
                              vdata, rank, dims) result(ierr) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_size_t, c_char, c_int32_t
    implicit none
    type(c_ptr),                               value, intent(in)    :: problem
    integer(c_size_t),                         value, intent(in)    :: keylen
    character(len=1,kind=c_char), dimension(keylen),  intent(in)    :: key
    type(c_ptr),                               value, intent(in)    :: vdata
    integer(c_int32_t),                        value, intent(in)    :: rank
    integer(c_size_t),            dimension(rank),    intent(in)    :: dims
    integer(c_int32_t)                                              :: ierr
  end function tinf_problem_value
end interface


interface
  function tinf_problem_set_value(problem, key, keylen,                        &
                                vdata, rank, dims) result(ierr) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_size_t, c_char, c_int32_t
    implicit none
    type(c_ptr),                               value, intent(in)    :: problem
    integer(c_size_t),                         value, intent(in)    :: keylen
    character(len=1,kind=c_char), dimension(keylen),  intent(in)    :: key
    type(c_ptr),                               value, intent(in)    :: vdata
    integer(c_int32_t),                        value, intent(in)    :: rank
    integer(c_size_t),            dimension(rank),    intent(in)    :: dims
    integer(c_int32_t)                                              :: ierr
  end function tinf_problem_set_value
end interface
