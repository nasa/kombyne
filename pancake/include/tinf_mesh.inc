
interface
  function tinf_mesh_node_count(mesh_handle, ierr) result(count) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int64_t, c_int32_t
    implicit none
    type(c_ptr),         value,          intent(in)    :: mesh_handle
    integer(c_int32_t),                  intent(out)   :: ierr
    integer(c_int64_t)                                 :: count
  end function tinf_mesh_node_count
end interface

interface
  function tinf_mesh_resident_node_count(mesh_handle, ierr) result(count)      &
           bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int64_t, c_int32_t
    implicit none
    type(c_ptr),         value,          intent(in)    :: mesh_handle
    integer(c_int32_t),                  intent(out)   :: ierr
    integer(c_int64_t)                                 :: count
  end function tinf_mesh_resident_node_count
end interface

interface
  function tinf_mesh_element_count(mesh_handle, ierr) result(count) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int64_t, c_int32_t
    implicit none
    type(c_ptr),         value,          intent(in)    :: mesh_handle
    integer(c_int32_t),                  intent(out)   :: ierr
    integer(c_int64_t)                                 :: count
  end function tinf_mesh_element_count
end interface

interface
  function tinf_mesh_element_type_count(mesh_handle, etype, ierr)              &
           result(count) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int64_t, c_int32_t
    implicit none
    type(c_ptr),         value,          intent(in)    :: mesh_handle
    integer(c_int32_t),  value,          intent(in)    :: etype
    integer(c_int32_t),                  intent(out)   :: ierr
    integer(c_int64_t)                                 :: count
  end function tinf_mesh_element_type_count
end interface

interface
  function tinf_mesh_nodes_coordinates(mesh_handle, dtype, start, cnt, x, y, z)&
           result(ierr) bind(c)
     use, intrinsic :: iso_c_binding, only : c_ptr, c_int64_t,                 &
                                             c_int32_t
     implicit none
     type(c_ptr),        value,          intent(in)    :: mesh_handle
     integer(c_int32_t), value,          intent(in)    :: dtype
     integer(c_int64_t), value,          intent(in)    :: start
     integer(c_int64_t), value,          intent(in)    :: cnt
     type(c_ptr),        value,          intent(in)    :: x, y, z
     integer(c_int32_t)                                :: ierr
  end function tinf_mesh_nodes_coordinates
end interface

interface
  function tinf_mesh_element_type(mesh_handle, eid, ierr)                      &
           result(etype) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int64_t, c_int32_t
    implicit none
    type(c_ptr),         value,          intent(in)    :: mesh_handle
    integer(c_int64_t),  value,          intent(in)    :: eid
    integer(c_int32_t),                  intent(out)   :: ierr
    integer(c_int32_t)                                 :: etype
  end function tinf_mesh_element_type
end interface

interface
  function tinf_mesh_element_nodes(mesh_handle, element_id, element_nodes)     &
           result(ierr) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int64_t, c_int32_t
    implicit none
    type(c_ptr),                      value, intent(in)    :: mesh_handle
    integer(c_int64_t),               value, intent(in)    :: element_id
    integer(c_int64_t), dimension(*),        intent(out)   :: element_nodes
    integer(c_int32_t)                                     :: ierr
  end function tinf_mesh_element_nodes
end interface

interface
  function tinf_mesh_global_node_id(mesh_handle, local_id, ierr)               &
           result(global_id) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int64_t, c_int32_t
    implicit none
    type(c_ptr),         value,          intent(in)    :: mesh_handle
    integer(c_int64_t),  value,          intent(in)    :: local_id
    integer(c_int32_t),                  intent(out)   :: ierr
    integer(c_int64_t)                                 :: global_id
  end function tinf_mesh_global_node_id
end interface

interface
  function tinf_mesh_global_element_id(mesh_handle, local_id, ierr)            &
           result(global_id) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int64_t, c_int32_t
    implicit none
    type(c_ptr),         value,          intent(in)    :: mesh_handle
    integer(c_int64_t),  value,          intent(in)    :: local_id
    integer(c_int32_t),                  intent(out)   :: ierr
    integer(c_int64_t)                                 :: global_id
  end function tinf_mesh_global_element_id
end interface

interface
  function tinf_mesh_element_tag(mesh_handle, element_id, ierr)                &
           result(tag) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int64_t, c_int32_t
    implicit none
    type(c_ptr),         value,          intent(in)    :: mesh_handle
    integer(c_int64_t),  value,          intent(in)    :: element_id
    integer(c_int32_t),                  intent(out)   :: ierr
    integer(c_int64_t)                                 :: tag
  end function tinf_mesh_element_tag
end interface

interface
  function tinf_mesh_element_owner(mesh_handle, element_id, ierr)              &
           result(partition) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int64_t, c_int32_t
    implicit none
    type(c_ptr),         value,          intent(in)    :: mesh_handle
    integer(c_int64_t),  value,          intent(in)    :: element_id
    integer(c_int32_t),                  intent(out)   :: ierr
    integer(c_int64_t)                                 :: partition
  end function tinf_mesh_element_owner
end interface

interface
  function tinf_mesh_node_owner(mesh_handle, node_id, ierr)                    &
           result(partition) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int64_t, c_int32_t
    implicit none
    type(c_ptr),         value,          intent(in)    :: mesh_handle
    integer(c_int64_t),  value,          intent(in)    :: node_id
    integer(c_int32_t),                  intent(out)   :: ierr
    integer(c_int64_t)                                 :: partition
  end function tinf_mesh_node_owner
end interface

interface
  function tinf_mesh_partition_id(mesh_handle, ierr)                           &
           result(partition) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int64_t, c_int32_t
    implicit none
    type(c_ptr),         value,          intent(in)    :: mesh_handle
    integer(c_int32_t),                  intent(out)   :: ierr
    integer(c_int64_t)                                 :: partition
  end function tinf_mesh_partition_id
end interface
