interface
  function tinf_distance_to_boundary(dcalc, wall_tags, n_wall_tags,            &
                                     start, cnt, node_distance)                &
  result(err) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int64_t, c_double,        &
                                            c_int32_t
    implicit none
    type(c_ptr),                      value,    intent(in)  :: dcalc
    integer(c_int64_t),               value,    intent(in)  :: n_wall_tags
    integer(c_int64_t), dimension(n_wall_tags), intent(in)  :: wall_tags
    integer(c_int64_t),               value,    intent(in)  :: start
    integer(c_int64_t),               value,    intent(in)  :: cnt
    real(c_double),     dimension(cnt),         intent(out) :: node_distance
    integer(c_int32_t)                                      :: err
  end function tinf_distance_to_boundary
end interface
