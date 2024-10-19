
interface
  function tinf_nc_util_create(nc, problem, mesh, comm) result(error)          &
  bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int32_t
    implicit none
    type(c_ptr),                         intent(out)   :: nc
    type(c_ptr),         value,          intent(in)    :: problem
    type(c_ptr),         value,          intent(in)    :: mesh
    type(c_ptr),         value,          intent(in)    :: comm
    integer(c_int32_t)                                 :: error
  end function tinf_nc_util_create
end interface

interface
  function tinf_nc_util_destroy(nc) result(error)                              &
  bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int32_t
    implicit none
    type(c_ptr),                         intent(inout) :: nc
    integer(c_int32_t)                                 :: error
  end function tinf_nc_util_destroy
end interface

interface
  function tinf_nc_util_num_global_cells(nc, error)                            &
  result(ncellg) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int64_t, c_int32_t
    implicit none
    type(c_ptr),         value,          intent(in)    :: nc
    integer(c_int32_t),                  intent(out)   :: error
    integer(c_int64_t)                                 :: ncellg
  end function tinf_nc_util_num_global_cells
end interface

interface
  function tinf_nc_util_num_elem(nc, error)                                    &
  result(nelem) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int64_t, c_int32_t
    implicit none
    type(c_ptr),         value,          intent(in)    :: nc
    integer(c_int32_t),                  intent(out)   :: error
    integer(c_int64_t)                                 :: nelem
  end function tinf_nc_util_num_elem
end interface

interface
  function tinf_nc_util_edge_counts(nc, nedge, nedgeloc) result(error)         &
  bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int32_t, c_int64_t
    implicit none
    type(c_ptr),        value,           intent(in)    :: nc
    integer(c_int64_t),                  intent(out)   :: nedge
    integer(c_int64_t),                  intent(out)   :: nedgeloc
    integer(c_int32_t)                                 :: error
  end function tinf_nc_util_edge_counts
end interface

interface
  function tinf_nc_util_edge_data(nc, nedgeg, eptr, el2g)                      &
  result(error) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int64_t, c_int32_t
    implicit none
    type(c_ptr),         value,          intent(in)    :: nc
    integer(c_int64_t),                  intent(out)   :: nedgeg
    integer(c_int32_t), dimension(*),    intent(out)   :: eptr
    integer(c_int64_t), dimension(*),    intent(out)   :: el2g
    integer(c_int32_t) :: error
  end function tinf_nc_util_edge_data
end interface

interface
  function tinf_nc_util_cell_data(nc, cell, elem, ndx)                         &
  result(error) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int64_t, c_int32_t
    implicit none
    type(c_ptr),         value,          intent(in)    :: nc
    integer(c_int64_t),  value,          intent(in)    :: cell
    integer(c_int32_t),                  intent(out)   :: elem
    integer(c_int64_t),                  intent(out)   :: ndx
    integer(c_int32_t) :: error
  end function tinf_nc_util_cell_data
end interface

interface
  function tinf_nc_util_element(nc, index, element)                            &
  result(error) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int32_t
    implicit none
    type(c_ptr),         value,          intent(in)    :: nc
    integer(c_int32_t),  value,          intent(in)    :: index
    type(c_ptr),                         intent(out)   :: element
    integer(c_int32_t) :: error
  end function tinf_nc_util_element
end interface

interface
  function tinf_nc_util_element_sizes(nc, element, ncell, ncellg, npc, epc,    &
                                      fpc, face_2d, etype) result(error) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int64_t, c_int32_t
    implicit none
    type(c_ptr),         value,          intent(in)    :: nc
    type(c_ptr),         value,          intent(in)    :: element
    integer(c_int64_t),                  intent(out)   :: ncell
    integer(c_int64_t),                  intent(out)   :: ncellg
    integer(c_int32_t),                  intent(out)   :: npc
    integer(c_int32_t),                  intent(out)   :: epc
    integer(c_int32_t),                  intent(out)   :: fpc
    integer(c_int32_t),                  intent(out)   :: face_2d
    integer(c_int32_t),                  intent(out)   :: etype
    integer(c_int32_t) :: error
  end function tinf_nc_util_element_sizes
end interface

interface
  function tinf_nc_util_element_e2n(nc, element, local_e2n)                    &
  result(error) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int32_t
    implicit none
    type(c_ptr),         value,          intent(in)    :: nc
    type(c_ptr),         value,          intent(in)    :: element
    integer(c_int32_t),  dimension(*),   intent(out)   :: local_e2n
    integer(c_int32_t) :: error
  end function tinf_nc_util_element_e2n
end interface

interface
  function tinf_nc_util_element_e2n_2(nc, element, local_e2n_2)                &
  result(error) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int32_t
    implicit none
    type(c_ptr),         value,          intent(in)    :: nc
    type(c_ptr),         value,          intent(in)    :: element
    integer(c_int32_t),  dimension(*),   intent(out)   :: local_e2n_2
    integer(c_int32_t) :: error
  end function tinf_nc_util_element_e2n_2
end interface

interface
  function tinf_nc_util_element_f2n(nc, element, local_f2n)                    &
  result(error) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int32_t
    implicit none
    type(c_ptr),         value,          intent(in)    :: nc
    type(c_ptr),         value,          intent(in)    :: element
    integer(c_int32_t),  dimension(*),   intent(out)   :: local_f2n
    integer(c_int32_t) :: error
  end function tinf_nc_util_element_f2n
end interface

interface
  function tinf_nc_util_element_check_norm(nc, element, chk_norm)              &
  result(error) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int32_t
    implicit none
    type(c_ptr),         value,          intent(in)    :: nc
    type(c_ptr),         value,          intent(in)    :: element
    integer(c_int32_t),  dimension(*),   intent(out)   :: chk_norm
    integer(c_int32_t) :: error
  end function tinf_nc_util_element_check_norm
end interface

interface
  function tinf_nc_util_element_f2e(nc, element, f2e)                          &
  result(error) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int32_t
    implicit none
    type(c_ptr),         value,          intent(in)    :: nc
    type(c_ptr),         value,          intent(in)    :: element
    integer(c_int32_t),  dimension(*),   intent(out)   :: f2e
    integer(c_int32_t) :: error
  end function tinf_nc_util_element_f2e
end interface

interface
  function tinf_nc_util_element_c2n(nc, element, c2n)                          &
  result(error) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int32_t
    implicit none
    type(c_ptr),         value,          intent(in)    :: nc
    type(c_ptr),         value,          intent(in)    :: element
    integer(c_int32_t),  dimension(*),   intent(out)   :: c2n
    integer(c_int32_t) :: error
  end function tinf_nc_util_element_c2n
end interface

interface
  function tinf_nc_util_element_c2e(nc, element, c2e)                          &
  result(error) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int32_t
    implicit none
    type(c_ptr),         value,          intent(in)    :: nc
    type(c_ptr),         value,          intent(in)    :: element
    integer(c_int32_t),  dimension(*),   intent(out)   :: c2e
    integer(c_int32_t) :: error
  end function tinf_nc_util_element_c2e
end interface

interface
  function tinf_nc_util_element_l2g(nc, element, l2g)                          &
  result(error) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int64_t, c_int32_t
    implicit none
    type(c_ptr),         value,          intent(in)    :: nc
    type(c_ptr),         value,          intent(in)    :: element
    integer(c_int64_t),  dimension(*),   intent(out)   :: l2g
    integer(c_int32_t) :: error
  end function tinf_nc_util_element_l2g
end interface

interface
  function tinf_nc_util_sendrecv_node_sizes(nc, size1, size2, size3)           &
  result(error) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int64_t, c_int32_t
    implicit none
    type(c_ptr),         value,          intent(in)    :: nc
    integer(c_int64_t),                  intent(out)   :: size1
    integer(c_int64_t),                  intent(out)   :: size2
    integer(c_int64_t),                  intent(out)   :: size3
    integer(c_int32_t) :: error
  end function tinf_nc_util_sendrecv_node_sizes
end interface

interface
  function tinf_nc_util_sendrecv_edge_sizes(nc, eptr, size1, size2, size3)     &
  result(error) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int64_t, c_int32_t
    implicit none
    type(c_ptr),         value,          intent(in)    :: nc
    integer(c_int32_t), dimension(*),    intent(in)    :: eptr
    integer(c_int64_t),                  intent(out)   :: size1
    integer(c_int64_t),                  intent(out)   :: size2
    integer(c_int64_t),                  intent(out)   :: size3
    integer(c_int32_t) :: error
  end function tinf_nc_util_sendrecv_edge_sizes
end interface

interface
  function tinf_nc_util_sendrecv_node(nc, recvproc, recvindex, sendproc,       &
                                      sendindex) result(error) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int32_t
    implicit none
    type(c_ptr),         value,          intent(in)    :: nc
    integer(c_int32_t), dimension(*),    intent(out)   :: recvproc
    integer(c_int32_t), dimension(*),    intent(out)   :: recvindex
    integer(c_int32_t), dimension(*),    intent(out)   :: sendproc
    integer(c_int32_t), dimension(*),    intent(out)   :: sendindex
    integer(c_int32_t) :: error
  end function tinf_nc_util_sendrecv_node
end interface

interface
  function tinf_nc_util_sendrecv_edge(nc, eptr, el2g, recvproc, recvindex,     &
                                      sendproc, sendindex) result(error) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int64_t, c_int32_t
    implicit none
    type(c_ptr),         value,          intent(in)    :: nc
    integer(c_int32_t), dimension(*),    intent(in)    :: eptr
    integer(c_int64_t), dimension(*),    intent(in)    :: el2g
    integer(c_int32_t), dimension(*),    intent(out)   :: recvproc
    integer(c_int32_t), dimension(*),    intent(out)   :: recvindex
    integer(c_int32_t), dimension(*),    intent(out)   :: sendproc
    integer(c_int32_t), dimension(*),    intent(out)   :: sendindex
    integer(c_int32_t) :: error
  end function tinf_nc_util_sendrecv_edge
end interface

