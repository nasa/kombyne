interface
  function tinf_reordering_create(reord, method_name,                          &
                                  n, data_type, matrix_type,                   &
                                  ipar, ipar_length, dpar, dpar_length,        &
                                  global_id)                                   &
           result(ierr) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_char, c_int32_t,          &
                                            c_int64_t
    implicit none
    type(c_ptr),                                intent(out)   :: reord
    integer(c_int32_t), value,                  intent(in)    :: n
    character(len=1,kind=c_char), dimension(n), intent(in)    :: method_name
    integer(c_int32_t), value,                  intent(in)    :: data_type
    integer(c_int32_t), value,                  intent(in)    :: matrix_type
    integer(c_int32_t), value,                  intent(in)    :: ipar_length
    integer(c_int64_t), dimension(ipar_length), intent(inout) :: ipar
    integer(c_int32_t), value,                  intent(in)    :: dpar_length
    type(c_ptr),        value,                  intent(in)    :: dpar
    integer(c_int32_t), value,                  intent(in)    :: global_id
    integer(c_int32_t)                                        :: ierr
  end function tinf_reordering_create
end interface

interface
  function tinf_reordering_destroy(reord)                                      &
           result(ierr) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int32_t
    implicit none
    type(c_ptr),                                intent(inout) :: reord
    integer(c_int32_t)                                        :: ierr
  end function tinf_reordering_destroy
end interface

interface
  function tinf_reordering_generate_symbolic(reord, num_rows, num_cols,        &
                                            block_size, num_blocks,            &
                                            a_row, a_col, a_diag,              &
                                            ipar, dpar, old_to_new, new_to_old)&
           result(ierr) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int64_t, c_int32_t
    implicit none
    type(c_ptr),        value,                  intent(in)    :: reord
    integer(c_int64_t), value,                  intent(in)    :: num_rows
    integer(c_int64_t), value,                  intent(in)    :: num_cols
    integer(c_int32_t), value,                  intent(in)    :: block_size
    integer(c_int64_t), value,                  intent(in)    :: num_blocks
    integer(c_int64_t), dimension(num_rows+1),  intent(in)    :: a_row
    integer(c_int64_t), dimension(num_blocks),  intent(in)    :: a_col
    integer(c_int64_t), dimension(num_rows),    intent(in)    :: a_diag
    integer(c_int64_t), dimension(*),           intent(inout) :: ipar
    type(c_ptr),        value,                  intent(in)    :: dpar
    type(c_ptr),                                intent(out)   :: old_to_new
    type(c_ptr),                                intent(out)   :: new_to_old
    integer(c_int32_t)                                        :: ierr
  end function tinf_reordering_generate_symbolic
end interface

interface
  function tinf_reordering_apply(reord, num_rows, block_size, num_blocks,      &
                                 ipar, dpar, old_to_new, new_to_old,           &
                                 a_row, a_col, a_diag, a_val,                  &
                                 ra_row, ra_col, ra_diag, ra_val)              &
           result(ierr) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int64_t, c_int32_t
    implicit none
    type(c_ptr),        value,                  intent(in)    :: reord
    integer(c_int64_t), value,                  intent(in)    :: num_rows
    integer(c_int32_t), value,                  intent(in)    :: block_size
    integer(c_int64_t), value,                  intent(in)    :: num_blocks
    integer(c_int64_t), dimension(*),           intent(inout) :: ipar
    type(c_ptr),        value,                  intent(in)    :: dpar
    integer(c_int64_t), dimension(num_rows+1),  intent(in)    :: a_row
    integer(c_int64_t), dimension(num_blocks),  intent(in)    :: a_col
    integer(c_int64_t), dimension(num_rows),    intent(in)    :: a_diag
    type(c_ptr),                                intent(in)    :: a_val
    type(c_ptr),                                intent(in)    :: old_to_new
    type(c_ptr),                                intent(in)    :: new_to_old
    integer(c_int64_t), dimension(num_rows+1),  intent(out)   :: ra_row
    integer(c_int64_t), dimension(num_blocks),  intent(out)   :: ra_col
    integer(c_int64_t), dimension(num_rows),    intent(out)   :: ra_diag
    type(c_ptr),                                intent(out)   :: ra_val
    integer(c_int32_t)                                        :: ierr
  end function tinf_reordering_apply
end interface
