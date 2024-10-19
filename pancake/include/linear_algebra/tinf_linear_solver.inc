interface
  function tinf_linear_solver_rci_create(linear_solver, method_name,           &
                                         n, data_type, num_rows, block_size,   &
                                         ipar, ipar_length, dpar, dpar_length, &
                                         comm, sync_pattern, work_space)       &
           result(ierr) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_char, c_int32_t,          &
                                            c_int64_t
    implicit none
    type(c_ptr),                                intent(out)   :: linear_solver
    integer(c_int32_t), value,                  intent(in)    :: n
    character(len=1,kind=c_char), dimension(n), intent(in)    :: method_name
    integer(c_int32_t), value,                  intent(in)    :: data_type
    integer(c_int64_t), value,                  intent(in)    :: num_rows
    integer(c_int32_t), value,                  intent(in)    :: block_size
    integer(c_int32_t), value,                  intent(in)    :: ipar_length
    integer(c_int64_t), dimension(ipar_length), intent(inout) :: ipar
    integer(c_int32_t), value,                  intent(in)    :: dpar_length
    type(c_ptr),        value,                  intent(in)    :: dpar
    type(c_ptr),        value,                  intent(in)    :: comm
    type(c_ptr),        value,                  intent(in)    :: sync_pattern
    type(c_ptr),                                intent(out)   :: work_space
    integer(c_int32_t)                                        :: ierr
  end function tinf_linear_solver_rci_create
end interface

interface
  function tinf_linear_solver_rci_destroy(linear_solver, work_space)           &
           result(ierr) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int32_t
    implicit none
    type(c_ptr),                                intent(inout) :: linear_solver
    type(c_ptr),                                intent(inout) :: work_space
    integer(c_int32_t)                                        :: ierr
  end function tinf_linear_solver_rci_destroy
end interface

interface
  function tinf_linear_solver_rci(linear_solver, num_rows, block_size,         &
                                  rhs, sol, ipar, dpar, work_space)            &
           result(ierr) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int64_t, c_int32_t
    implicit none
    type(c_ptr),        value,                  intent(in)    :: linear_solver
    integer(c_int64_t), value,                  intent(in)    :: num_rows
    integer(c_int32_t), value,                  intent(in)    :: block_size
    type(c_ptr),        value,                  intent(in)    :: rhs
    type(c_ptr),        value,                  intent(in)    :: sol
    integer(c_int64_t), dimension(*),           intent(inout) :: ipar
    type(c_ptr),        value,                  intent(in)    :: dpar
    type(c_ptr),        value,                  intent(in)    :: work_space
    integer(c_int32_t)                                        :: ierr
  end function tinf_linear_solver_rci
end interface
