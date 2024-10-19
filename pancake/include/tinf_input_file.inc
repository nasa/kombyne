
interface
  function tinf_input_file_create(problem, fname, namelen, comm)               &
  result(ierr) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_size_t, c_int32_t
    implicit none
    type(c_ptr),                                      intent(out)   :: problem
    integer(c_size_t),                         value, intent(in)    :: namelen
    type(c_ptr),                               value, intent(in)    :: fname
    type(c_ptr),                               value, intent(in)    :: comm
    integer(c_int32_t)                                              :: ierr
  end function tinf_input_file_create
end interface

interface
  function tinf_input_file_destroy(problem) result(ierr) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int32_t
    implicit none
    type(c_ptr),                                      intent(inout) :: problem
    integer(c_int32_t)                                              :: ierr
  end function tinf_input_file_destroy
end interface

