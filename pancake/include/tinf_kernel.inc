
interface
  function tinf_kernel_create(kernel, problem, geom, mesh, soln, comm)         &
           result(ierr) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int32_t
    implicit none
    type(c_ptr),                        intent(out)    :: kernel
    type(c_ptr),         value,         intent(in)     :: problem
    type(c_ptr),         value,         intent(in)     :: geom
    type(c_ptr),         value,         intent(in)     :: mesh
    type(c_ptr),         value,         intent(in)     :: soln
    type(c_ptr),         value,         intent(in)     :: comm
    integer(c_int32_t)                                 :: ierr
  end function tinf_kernel_create
end interface

interface
  function tinf_kernel_destroy(kernel) result(ierr) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int32_t
    implicit none
    type(c_ptr),                        intent(inout)  :: kernel
    integer(c_int32_t)                                 :: ierr
  end function tinf_kernel_destroy
end interface

interface
  function tinf_kernel_launch(kernel, nblock, nthread) result(ierr) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int32_t
    implicit none
    type(c_ptr),                        intent(in)     :: kernel
    integer(c_int32_t),                 intent(in)     :: nblock
    integer(c_int32_t),                 intent(in)     :: nthread
    integer(c_int32_t)                                 :: ierr
  end function tinf_kernel_launch
end interface

