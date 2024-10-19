
interface
  function tinf_solution_get_nodal_input_names(solution, cnt, names, dtype,    &
                                               rank, dims)                     &
                                               result(ierr) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int64_t, c_int32_t
    implicit none
    type(c_ptr),                        value, intent(in)     :: solution
    integer(c_int64_t),                        intent(out)    :: cnt
    type(c_ptr),                               intent(out)    :: names
    type(c_ptr),                               intent(out)    :: dtype
    type(c_ptr),                               intent(out)    :: rank
    type(c_ptr),                               intent(out)    :: dims
    integer(c_int32_t)                                        :: ierr
  end function tinf_solution_get_nodal_input_names
end interface

interface
  function tinf_solution_set_inputs_at_nodes(solution, dtype, start_node,      &
                                             node_cnt, val_cnt, names, rank,   &
                                             dims, values) result(ierr) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int64_t, c_int32_t
    implicit none
    type(c_ptr),                              value,  intent(in)  :: solution
    integer(c_int64_t),                       value,  intent(in)  :: start_node
    integer(c_int64_t),                       value,  intent(in)  :: node_cnt
    integer(c_int64_t),                       value,  intent(in)  :: val_cnt
    type(c_ptr),        dimension(val_cnt),           intent(in)  :: names
    integer(c_int32_t),                       value,  intent(in)  :: dtype
    integer(c_int32_t),                       value,  intent(in)  :: rank
    integer(c_int64_t), dimension(*),                 intent(in)  :: dims
    type(c_ptr),                              value,  intent(in)  :: values
    integer(c_int32_t)                                            :: ierr
  end function tinf_solution_set_inputs_at_nodes
end interface

interface
  function tinf_solution_get_nodal_output_names(solution, cnt, names,          &
                                                dtype) result(ierr) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int64_t, c_int32_t
    implicit none
    type(c_ptr),                        value, intent(in)     :: solution
    integer(c_int64_t),                        intent(out)    :: cnt
    type(c_ptr),                               intent(out)    :: names
    type(c_ptr),                               intent(out)    :: dtype
    integer(c_int32_t)                                        :: ierr
  end function tinf_solution_get_nodal_output_names
end interface

interface
  function tinf_solution_get_outputs_at_nodes(solution, dtype, start_node,     &
                                          node_cnt, value_cnt, names, values)  &
                                          result(ierr) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int64_t, c_int32_t
    implicit none
    type(c_ptr),                              value,  intent(in)  :: solution
    integer(c_int32_t),                       value,  intent(in)  :: dtype
    integer(c_int64_t),                       value,  intent(in)  :: start_node
    integer(c_int64_t),                       value,  intent(in)  :: node_cnt
    integer(c_int64_t),                       value,  intent(in)  :: value_cnt
    type(c_ptr),        dimension(value_cnt),         intent(in)  :: names
    type(c_ptr),                              value,  intent(in)  :: values
    integer(c_int32_t)                                            :: ierr
  end function tinf_solution_get_outputs_at_nodes
end interface

interface
  function tinf_solution_get_outputs_in_cell(solution, xyztype, dtype,         &
                                             x, y, z, cell_id, name, rank,     &
                                             dims, values)                     &
                                             result(ierr) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int64_t, c_int32_t,       &
                                            c_size_t
    implicit none
    type(c_ptr),                              value,  intent(in)  :: solution
    integer(c_int32_t),                       value,  intent(in)  :: xyztype
    integer(c_int32_t),                       value,  intent(in)  :: dtype
    type(c_ptr),                              value,  intent(in)  :: x, y, z
    integer(c_int64_t),                       value,  intent(in)  :: cell_id
    type(c_ptr),                                      intent(in)  :: name
    integer(c_int32_t),                       value,  intent(in)  :: rank
    integer(c_size_t),dimension(*),                   intent(in)  :: dims
    type(c_ptr),                              value,  intent(in)  :: values
    integer(c_int32_t)                                            :: ierr
  end function tinf_solution_get_outputs_in_cell
end interface
