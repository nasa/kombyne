
interface
  function tinf_solver_create(solver, problem, mesh, comm) result(ierr) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int32_t
    implicit none
    type(c_ptr),                        intent(out)    :: solver
    type(c_ptr),         value,         intent(in)     :: problem
    type(c_ptr),         value,         intent(in)     :: mesh
    type(c_ptr),         value,         intent(in)     :: comm
    integer(c_int32_t)                                 :: ierr
  end function tinf_solver_create
end interface

interface
  function tinf_solver_destroy(solver) result(ierr) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int32_t
    implicit none
    type(c_ptr),                        intent(inout)  :: solver
    integer(c_int32_t)                                 :: ierr
  end function tinf_solver_destroy
end interface

interface
  function tinf_solver_get_version(solver, version) result(ierr) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int32_t
    implicit none
    type(c_ptr),                        value, intent(in)     :: solver
    type(c_ptr),                               intent(out)    :: version
    integer(c_int32_t)                                        :: ierr
  end function tinf_solver_get_version
end interface

interface
  function tinf_solver_freeze_nodes(solver, freeze_ids, num_frozen)            &
  result(ierr) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int64_t, c_int32_t
    implicit none
    type(c_ptr),                               value,  intent(in)  :: solver
    integer(c_int64_t),                        value,  intent(in)  :: num_frozen
    integer(c_int64_t), dimension(num_frozen),         intent(in)  :: freeze_ids
    integer(c_int32_t)                                             :: ierr
  end function tinf_solver_freeze_nodes
end interface

interface
  function tinf_solver_step_pre(solver) result(ierr) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int32_t
    implicit none
    type(c_ptr),                       value,  intent(in)     :: solver
    integer(c_int32_t)                                        :: ierr
  end function tinf_solver_step_pre
end interface

interface
  function tinf_solver_step(solver, seconds_to_advance) result(ierr) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int32_t, c_double
    implicit none
    type(c_ptr),                    value,  intent(in)     :: solver
    real(c_double),                 value,  intent(in)     :: seconds_to_advance
    integer(c_int32_t)                                     :: ierr
  end function tinf_solver_step
end interface

interface
  function tinf_solver_step_post(solver) result(ierr) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int32_t
    implicit none
    type(c_ptr),                       value,  intent(in)     :: solver
    integer(c_int32_t)                                        :: ierr
  end function tinf_solver_step_post
end interface
