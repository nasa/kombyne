
interface
  function tinf_mesh_filter_create(mesh_handle, problem, mesh_in, comm)        &
           result(ierr) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int32_t
    implicit none
    type(c_ptr),                        intent(out)    :: mesh_handle
    type(c_ptr),         value,         intent(in)     :: problem
    type(c_ptr),         value,         intent(in)     :: mesh_in
    type(c_ptr),         value,         intent(in)     :: comm
    integer(c_int32_t)                                 :: ierr
  end function tinf_mesh_filter_create
end interface

interface
  function tinf_mesh_filter_destroy(mesh_handle) result(ierr) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int32_t
    implicit none
    type(c_ptr),                        intent(inout)  :: mesh_handle
    integer(c_int32_t)                                 :: ierr
  end function tinf_mesh_filter_destroy
end interface
