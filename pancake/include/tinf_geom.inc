
interface
  function tinf_geom_create(geom_handle, problem, comm) result(ierr)   &
           bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int32_t
    implicit none
    type(c_ptr),                        intent(out)    :: geom_handle
    type(c_ptr),         value,         intent(in)     :: problem
    type(c_ptr),         value,         intent(in)     :: comm
    integer(c_int32_t)                                 :: ierr
  end function tinf_geom_create
end interface

interface
  function tinf_geom_destroy(geom_handle) result(ierr) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int32_t
    implicit none
    type(c_ptr),                        intent(inout)  :: geom_handle
    integer(c_int32_t)                                 :: ierr
  end function tinf_geom_destroy
end interface
