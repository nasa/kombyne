interface
  function tinf_distance_calculator_create(dcalc, problem, mesh, comm)         &
  result(err) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int32_t
    implicit none
    type(c_ptr),                                intent(out) :: dcalc
    type(c_ptr),        value,                  intent(in)  :: problem
    type(c_ptr),        value,                  intent(in)  :: mesh
    type(c_ptr),        value,                  intent(in)  :: comm
    integer(c_int32_t)                                      :: err
  end function tinf_distance_calculator_create
end interface

interface
  function tinf_distance_calculator_destroy(dcalc) result(ierr) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int32_t
    implicit none
    type(c_ptr),                        intent(inout)  :: dcalc
    integer(c_int32_t)                                 :: ierr
  end function tinf_distance_calculator_destroy
end interface
