
interface
  function tinf_visualizer_create(vis, problem, mesh, solution, comm)           &
    result(ierr) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int32_t
    implicit none
    type(c_ptr),                        intent(out)    :: vis
    type(c_ptr),         value,         intent(in)     :: problem
    type(c_ptr),         value,         intent(in)     :: mesh
    type(c_ptr),         value,         intent(in)     :: solution
    type(c_ptr),         value,         intent(in)     :: comm
    integer(c_int32_t)                                 :: ierr
  end function tinf_visualizer_create
end interface

interface
  function tinf_visualizer_destroy(vis) result(ierr) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int32_t
    implicit none
    type(c_ptr),                        intent(inout)  :: vis
    integer(c_int32_t)                                 :: ierr
  end function tinf_visualizer_destroy
end interface

interface
  function tinf_visualizer(vis, final_call) result(ierr) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int32_t, c_bool
    implicit none
    type(c_ptr),         value,         intent(in)     :: vis
    logical(c_bool),     value,         intent(in)     :: final_call
    integer(c_int32_t)                                 :: ierr
  end function tinf_visualizer
end interface
