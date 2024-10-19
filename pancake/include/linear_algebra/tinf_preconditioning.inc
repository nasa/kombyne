interface
  function tinf_preconditioner_create(precond, method_name,                    &
                                      n, data_type, matrix_type, num_rows,     &
                                      block_size, ipar, ipar_length,           &
                                      dpar, dpar_length,                       &
                                      comm, sync_pattern, global_id)           &
           result(ierr) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_char, c_int32_t,          &
                                            c_int64_t
    implicit none
    type(c_ptr),                                intent(out)   :: precond
    integer(c_int32_t), value,                  intent(in)    :: n
    character(len=1,kind=c_char), dimension(n), intent(in)    :: method_name
    integer(c_int32_t), value,                  intent(in)    :: data_type
    integer(c_int32_t), value,                  intent(in)    :: matrix_type
    integer(c_int64_t), value,                  intent(in)    :: num_rows
    integer(c_int32_t), value,                  intent(in)    :: block_size
    integer(c_int32_t), value,                  intent(in)    :: ipar_length
    integer(c_int64_t), dimension(ipar_length), intent(inout) :: ipar
    integer(c_int32_t), value,                  intent(in)    :: dpar_length
    type(c_ptr),        value,                  intent(in)    :: dpar
    type(c_ptr),        value,                  intent(in)    :: comm
    type(c_ptr),        value,                  intent(in)    :: sync_pattern
    integer(c_int32_t), value,                  intent(in)    :: global_id
    integer(c_int32_t)                                        :: ierr
  end function tinf_preconditioner_create
end interface

interface
  function tinf_preconditioner_destroy(precond, block_size)                    &
           result(ierr) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int32_t
    implicit none
    type(c_ptr),                                intent(inout) :: precond
    integer(c_int32_t), value,                  intent(in)    :: block_size
    integer(c_int32_t)                                        :: ierr
  end function tinf_preconditioner_destroy
end interface

interface
  function tinf_preconditioner_generate_symbolic(precond, ipar, dpar,          &
                                                 num_rows, num_cols,           &
                                                 block_size, num_blocks,       &
                                                 a_val, a_row, a_col)          &
           result(ierr) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int64_t, c_int32_t
    implicit none
    type(c_ptr),        value,                  intent(in)    :: precond
    integer(c_int64_t), dimension(*),           intent(inout) :: ipar
    type(c_ptr),        value,                  intent(in)    :: dpar
    integer(c_int64_t), value,                  intent(in)    :: num_rows
    integer(c_int64_t), value,                  intent(in)    :: num_cols
    integer(c_int32_t), value,                  intent(in)    :: block_size
    integer(c_int64_t), value,                  intent(in)    :: num_blocks
    type(c_ptr),        value,                  intent(in)    :: a_val
    integer(c_int64_t), dimension(num_rows+1),  intent(inout) :: a_row
    integer(c_int64_t), dimension(num_blocks),  intent(inout) :: a_col
    integer(c_int32_t)                                        :: ierr
  end function tinf_preconditioner_generate_symbolic
end interface

interface
  function tinf_preconditioner_initialize_numeric(precond, ipar, dpar,         &
                                                  a_val)                       &
           result(ierr) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int64_t, c_int32_t
    implicit none
    type(c_ptr),        value,                  intent(in)    :: precond
    integer(c_int64_t), dimension(*),           intent(inout) :: ipar
    type(c_ptr),        value,                  intent(in)    :: dpar
    type(c_ptr),        value,                  intent(in)    :: a_val
    integer(c_int32_t)                                        :: ierr
  end function tinf_preconditioner_initialize_numeric
end interface

interface
  function tinf_preconditioner_update_numeric(precond, ipar, dpar,             &
                                              a_val)                           &
           result(ierr) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int64_t, c_int32_t
    implicit none
    type(c_ptr),        value,                  intent(in)    :: precond
    integer(c_int64_t), dimension(*),           intent(inout) :: ipar
    type(c_ptr),        value,                  intent(in)    :: dpar
    type(c_ptr),        value,                  intent(in)    :: a_val
    integer(c_int32_t)                                        :: ierr
  end function tinf_preconditioner_update_numeric
end interface

interface
  function tinf_preconditioner_apply(precond, ipar, dpar, num_rows,            &
                                     x, y)                                     &
           result(ierr) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int64_t, c_int32_t
    implicit none
    type(c_ptr),        value,                  intent(in)    :: precond
    integer(c_int64_t), dimension(*),           intent(inout) :: ipar
    type(c_ptr),        value,                  intent(in)    :: dpar
    integer(c_int64_t), value,                  intent(in)    :: num_rows
    type(c_ptr),        value,                  intent(in)    :: x
    type(c_ptr),                                intent(out)   :: y
    integer(c_int32_t)                                        :: ierr
  end function tinf_preconditioner_apply
end interface
