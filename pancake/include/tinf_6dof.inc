
interface
  function tinf_6dof_create(sixdof, problem, mesh, solver, comm)               &
  result(ierr) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int32_t
    implicit none
    type(c_ptr),                                      intent(out)   :: sixdof
    type(c_ptr),                               value, intent(in)    :: problem
    type(c_ptr),                               value, intent(in)    :: mesh
    type(c_ptr),                               value, intent(in)    :: solver
    type(c_ptr),                               value, intent(in)    :: comm
    integer(c_int32_t)                                              :: ierr
  end function tinf_6dof_create
end interface

interface
  function tinf_6dof_destroy(sixdof) result(ierr) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int32_t
    implicit none
    type(c_ptr),                                      intent(inout) :: sixdof
    integer(c_int32_t)                                              :: ierr
  end function tinf_6dof_destroy
end interface

interface
  function tinf_6dof_set_condition(sixdof,body,sim_time,transfor,cg)           &
  result(ierr) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int32_t, c_double
    implicit none
    type(c_ptr),                               value, intent(in)    :: sixdof
    integer(c_int32_t),                        value, intent(in)    :: body
    real(c_double),                            value, intent(in)    :: sim_time
    real(c_double), dimension(16),                    intent(in)    :: transfor
    real(c_double), dimension(3),                     intent(in)    :: cg
    integer(c_int32_t)                                              :: ierr
  end function tinf_6dof_set_condition
end interface

interface
  function tinf_6dof_get_condition(sixdof,body,sim_time,transfor,cg)           &
  result(ierr) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int32_t, c_double
    implicit none
    type(c_ptr),                               value, intent(in)    :: sixdof
    integer(c_int32_t),                        value, intent(in)    :: body
    real(c_double),                            value, intent(in)    :: sim_time
    real(c_double), dimension(16),                    intent(out)   :: transfor
    real(c_double), dimension(3),                     intent(out)   :: cg
    integer(c_int32_t)                                              :: ierr
  end function tinf_6dof_get_condition
end interface

interface
  function tinf_6dof_set_loads(sixdof,body,frame,sim_time,force,moment)        &
  result(ierr) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int32_t, c_double
    implicit none
    type(c_ptr),                               value, intent(in)    :: sixdof
    integer(c_int32_t),                        value, intent(in)    :: body
    integer(c_int32_t),                        value, intent(in)    :: frame
    real(c_double),                            value, intent(in)    :: sim_time
    real(c_double), dimension(3),                     intent(in)    :: force
    real(c_double), dimension(3),                     intent(in)    :: moment
    integer(c_int32_t)                                              :: ierr
  end function tinf_6dof_set_loads
end interface

interface
  function tinf_6dof_get_loads(sixdof,body,frame,sim_time,force,moment)        &
  result(ierr) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int32_t, c_double
    implicit none
    type(c_ptr),                               value, intent(in)    :: sixdof
    integer(c_int32_t),                        value, intent(in)    :: body
    integer(c_int32_t),                        value, intent(in)    :: frame
    real(c_double),                            value, intent(in)    :: sim_time
    real(c_double), dimension(3),                     intent(out)   :: force
    real(c_double), dimension(3),                     intent(out)   :: moment
    integer(c_int32_t)                                              :: ierr
  end function tinf_6dof_get_loads
end interface
