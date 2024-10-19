
interface
  function tinf_mesh_boundary_tag_list_create(list, problem, mesh, comm)       &
  result(error) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int32_t
    implicit none
    type(c_ptr),                         intent(out)   :: list
    type(c_ptr),         value,          intent(in)    :: problem
    type(c_ptr),         value,          intent(in)    :: mesh
    type(c_ptr),         value,          intent(in)    :: comm
    integer(c_int32_t)                                 :: error
  end function tinf_mesh_boundary_tag_list_create
end interface

interface
  function tinf_mesh_boundary_tag_list_count(list, error) result(count)        &
  bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int32_t, c_int64_t
    implicit none
    type(c_ptr),         value,          intent(in)    :: list
    integer(c_int32_t),                  intent(out)   :: error
    integer(c_int64_t)                                 :: count
  end function tinf_mesh_boundary_tag_list_count
end interface

interface
  function tinf_mesh_boundary_tag_list_get(list, tags) result(error)           &
  bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int32_t
    implicit none
    type(c_ptr),        value,           intent(in)    :: list
    type(c_ptr),        dimension(*),    intent(out)   :: tags
    integer(c_int32_t)                                 :: error
  end function tinf_mesh_boundary_tag_list_get
end interface

interface
  function tinf_mesh_boundary_tag_flag_count(tag, error) result(count)         &
  bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int32_t, c_int64_t
    implicit none
    type(c_ptr),         value,          intent(in)    :: tag
    integer(c_int32_t),                  intent(out)   :: error
    integer(c_int64_t)                                 :: count
  end function tinf_mesh_boundary_tag_flag_count
end interface

interface
  function tinf_mesh_boundary_tag_flags(tag, flags) result(error)              &
  bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int64_t, c_int32_t
    implicit none
    type(c_ptr),        value,           intent(in)    :: tag
    integer(c_int64_t), dimension(*),    intent(out)   :: flags
    integer(c_int32_t)                                 :: error
  end function tinf_mesh_boundary_tag_flags
end interface

interface
  function tinf_mesh_boundary_tag_index(tag, error) result(tindex)             &
  bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int64_t, c_int32_t
    implicit none
    type(c_ptr),        value,           intent(in)    :: tag
    integer(c_int32_t),                  intent(out)   :: error
    integer(c_int64_t)                                 :: tindex
  end function tinf_mesh_boundary_tag_index
end interface

interface
  function tinf_mesh_boundary_tag_code(tag, error) result(tcode)               &
  bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int64_t, c_int32_t
    implicit none
    type(c_ptr),        value,           intent(in)    :: tag
    integer(c_int32_t),                  intent(out)   :: error
    integer(c_int64_t)                                 :: tcode
  end function tinf_mesh_boundary_tag_code
end interface

interface
  function tinf_mesh_boundary_tag_family_len(tag, error) result(flen)          &
  bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_size_t, c_int32_t
    implicit none
    type(c_ptr),        value,           intent(in)    :: tag
    integer(c_int32_t),                  intent(out)   :: error
    integer(c_size_t)                                  :: flen
  end function tinf_mesh_boundary_tag_family_len
end interface

interface
  function tinf_mesh_boundary_tag_family(tag, family, family_len)              &
  result(error) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_size_t, c_char, c_int32_t
    implicit none
    type(c_ptr),                  value,        intent(in)  :: tag
    integer(c_size_t),                          intent(in)  :: family_len
    character(len=1,kind=c_char), dimension(*), intent(out) :: family    
    integer(c_int32_t)                                      :: error
  end function tinf_mesh_boundary_tag_family
end interface

interface
  function tinf_mesh_boundary_tag_list_destroy(list) result(error)             &
  bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int32_t
    implicit none
    type(c_ptr),                         intent(inout) :: list
    integer(c_int32_t)                                 :: error
  end function tinf_mesh_boundary_tag_list_destroy
end interface

interface
  function tinf_mesh_boundary_create(boundary, problem, mesh, comm, tag)       &
  result(error) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int32_t
    implicit none
    type(c_ptr),                         intent(out)   :: boundary
    type(c_ptr),         value,          intent(in)    :: problem
    type(c_ptr),         value,          intent(in)    :: mesh
    type(c_ptr),         value,          intent(in)    :: comm
    type(c_ptr),         value,          intent(in)    :: tag
    integer(c_int32_t)                                 :: error
  end function tinf_mesh_boundary_create
end interface

interface
  function tinf_mesh_boundary_destroy(boundary) result(error) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int32_t
    implicit none
    type(c_ptr),                         intent(inout) :: boundary
    integer(c_int32_t)                                 :: error
  end function tinf_mesh_boundary_destroy
end interface

interface
  function tinf_mesh_boundary_nodes(boundary, start, cnt, nodes) result(error) &
  bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int32_t, c_int64_t
    implicit none
    type(c_ptr),        value,           intent(in)    :: boundary
    integer(c_int64_t), value,           intent(in)    :: start
    integer(c_int64_t), value,           intent(in)    :: cnt
    integer(c_int64_t), dimension(*),    intent(out)   :: nodes
    integer(c_int32_t)                                 :: error
  end function tinf_mesh_boundary_nodes
end interface

interface
  function tinf_mesh_boundary_family_len(boundary, error) result(flen)         &
  bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_size_t, c_int32_t
    implicit none
    type(c_ptr),        value,           intent(in)    :: boundary
    integer(c_int32_t),                  intent(out)   :: error
    integer(c_size_t)                                  :: flen
  end function tinf_mesh_boundary_family_len
end interface

interface
  function tinf_mesh_boundary_family(boundary, family, fam_len)                &
  result(error) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_size_t, c_char, c_int32_t
    type(c_ptr),                  value,              intent(in)  :: boundary
    integer(c_size_t),            value,              intent(in)  :: fam_len
    character(len=1,kind=c_char), dimension(*),       intent(out) :: family    
    integer(c_int32_t) :: error
  end function tinf_mesh_boundary_family
end interface

interface
  function tinf_mesh_boundary_condition(boundary, error)                       &
  result(bc) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int64_t, c_int32_t
    implicit none
    type(c_ptr),         value,          intent(in)    :: boundary
    integer(c_int32_t),                  intent(out)   :: error
    integer(c_int64_t)                                 :: bc
  end function tinf_mesh_boundary_condition
end interface

interface
  function tinf_mesh_boundary_parent_cell(boundary, element, error)           &
  result(cell) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int64_t, c_int32_t
    implicit none
    type(c_ptr),         value,          intent(in)    :: boundary
    integer(c_int64_t),  value,          intent(in)    :: element
    integer(c_int32_t),                  intent(out)   :: error
    integer(c_int64_t)                                 :: cell
  end function tinf_mesh_boundary_parent_cell
end interface
