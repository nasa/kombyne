interface
  function tinf_solver_apply_nonlinear(solver) result(ierr) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int32_t
    type(c_ptr),                    value,  intent(in)     :: solver
    integer(c_int32_t)                                     :: ierr
  end function tinf_solver_apply_nonlinear
end interface

interface
  function tinf_solver_solve_linear(solver, transposed) result(ierr) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int32_t
    type(c_ptr),                    value,  intent(in)     :: solver
    integer(c_int32_t),             value,  intent(in)     :: transposed
    integer(c_int32_t)                                     :: ierr
  end function tinf_solver_solve_linear
end interface

interface
  function tinf_solver_apply_linear_problem_input(solver, n_vars,              &
                                                  var_names, values,           &
                                                  values_per_variable,         &
                                                  transposed)                  &
                                                  result(ierr) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int32_t, c_int64_t, c_char
    type(c_ptr), value, intent(in) :: solver
    integer(c_int64_t), intent(in) :: n_vars
    type(c_ptr),        intent(in) :: var_names
    type(c_ptr), value, intent(in) :: values
    integer(c_int64_t), intent(in) :: values_per_variable
    integer(c_int32_t), intent(in) :: transposed
    integer(c_int32_t)              :: ierr
  end function tinf_solver_apply_linear_problem_input
end interface

interface
  function tinf_solver_apply_linear_nodal_input(solver, transposed,            &
                                                variable_name, ierr)           &
                                                result(ierr) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int32_t, c_char
    type(c_ptr),                    value,  intent(in)       :: solver
    integer(c_int32_t),             value,  intent(in)       :: transposed
    character(kind=c_char, len=1), dimension(80), intent(in) :: variable_name
    integer(c_int32_t)                                       :: ierr
  end function tinf_solver_apply_linear_nodal_input
end interface
