interface
  function tinf_bsrmv(data_type, num_rows, block_size, nnz, a, row, col,       &
                      x, y) result(ierr) bind(c)
    use, intrinsic :: iso_c_binding, only : c_int32_t, c_int64_t, c_ptr
    implicit none
    integer(c_int32_t), value,                  intent(in)    :: data_type
    integer(c_int64_t),  value,                 intent(in)    :: num_rows
    integer(c_int32_t),  value,                 intent(in)    :: block_size
    integer(c_int64_t),  value,                 intent(in)    :: nnz
    type(c_ptr),        value,                  intent(in)    :: a
    integer(c_int64_t),  dimension(num_rows+1), intent(in)    :: row
    integer(c_int64_t),  dimension(nnz),        intent(in)    :: col
    type(c_ptr),        value,                  intent(in)    :: x
    type(c_ptr),                                intent(inout) :: y
    integer(c_int32_t)                                        :: ierr
  end function tinf_bsrmv
end interface

interface
  function tinf_nrm2(data_type, n, x, incx, result) result(ierr) bind(c)
    use, intrinsic :: iso_c_binding, only : c_int32_t, c_int64_t, c_ptr
    implicit none
    integer(c_int32_t), value,                  intent(in)    :: data_type
    integer(c_int64_t),  value,                 intent(in)    :: n
    type(c_ptr),        value,                  intent(in)    :: x
    integer(c_int64_t),  value,                 intent(in)    :: incx
    type(c_ptr),                                intent(out)   :: result
    integer(c_int32_t)                                        :: ierr
  end function tinf_nrm2
end interface
