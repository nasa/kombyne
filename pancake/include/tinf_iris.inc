!=============================================================================80
!
! This file defines the iris message passing interface
!
!=============================================================================80

!integer, parameter :: tinf_iris_mode_rdonly        = MPI_MODE_RDONLY
!integer, parameter :: tinf_iris_info_null          = MPI_INFO_NULL
!integer, parameter :: tinf_iris_byte               = MPI_BYTE

interface
 function tinf_iris_create(comm, communicator) result(err) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int32_t
    type(c_ptr),               intent(out) :: comm
    integer(c_int32_t), value, intent(in)  :: communicator
    integer(c_int32_t)                     :: err
  end function
end interface

interface
  function tinf_iris_get_mpi_fcomm(comm, err) result(fcom) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int32_t
    type(c_ptr),        value, intent(in)  :: comm
    integer(c_int32_t),        intent(out) :: err
    integer(c_int32_t)                     :: fcom
  end function
end interface

interface
  function tinf_iris_fcomm_free(comm) result(err) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int32_t
    type(c_ptr), value, intent(in)  :: comm
    integer(c_int32_t)              :: err
  end function
end interface

interface
  function tinf_iris_rank(comm, err) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int32_t
    type(c_ptr),        value, intent(in)  :: comm
    integer(c_int32_t),        intent(out) :: err
    integer(c_int32_t)                     :: tinf_iris_rank
  end function
end interface

interface
  function tinf_iris_number_of_processes(comm, err) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int32_t
    type(c_ptr),       value, intent(in)  :: comm
    integer(c_int32_t),       intent(out) :: err
    integer(c_int32_t)                    :: tinf_iris_number_of_processes
  end function
end interface

interface
  function tinf_iris_local_info(comm, local_rank, local_size, local_comm)      &
           result(err) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int32_t
    implicit none
    type(c_ptr),        value,                  intent(in)  :: comm
    integer(c_int32_t),                         intent(out) :: local_rank
    integer(c_int32_t),                         intent(out) :: local_size
    type(c_ptr),                                intent(out) :: local_comm
    integer(c_int32_t)                                      :: err
  end function
end interface

interface
  function tinf_iris_stop(comm, flag, msg, len) result(err) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int32_t, c_size_t, c_char
    type(c_ptr),                  value,          intent(in) :: comm
    integer(c_int32_t),           value,          intent(in) :: flag
    integer(c_size_t),            value,          intent(in) :: len
    character(len=1,kind=c_char), dimension(len), intent(in) :: msg
    integer(c_int32_t)                                       :: err
  end function
end interface

interface
  function tinf_iris_abort(comm) result(err) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int32_t
    type(c_ptr),        value, intent(in) :: comm
    integer(c_int32_t)                    :: err
  end function
end interface

interface
  function tinf_iris_destroy(comm) result(err) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int32_t
    type(c_ptr),        value, intent(in) :: comm
    integer(c_int32_t)                    :: err
  end function
end interface

interface
  function tinf_iris_barrier(comm) result(err) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int32_t
    type(c_ptr),        value, intent(in) :: comm
    integer(c_int32_t)                    :: err
  end function
end interface

interface
  function tinf_iris_waitall(comm,counts,array_of_requests) result(err) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_size_t, c_int32_t
    type(c_ptr),        value,             intent(in)    :: comm
    integer(c_size_t),  value,             intent(in)    :: counts
    type(c_ptr),        dimension(counts), intent(in)    :: array_of_requests
    integer(c_int32_t)                                   :: err
  end function
end interface

interface
  function tinf_iris_max_processor_name_length(comm, err) result(length) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int32_t, c_size_t
    type(c_ptr),        value,           intent(in)  :: comm
    integer(c_int32_t),                  intent(out) :: err
    integer(c_size_t)                                :: length
  end function
end interface

interface
  function tinf_iris_get_processor_name(comm,name,length) result(err) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_size_t, c_char, c_int32_t
    type(c_ptr),                  value,             intent(in)  :: comm
    integer(c_size_t),            value,             intent(in)  :: length
    character(len=1,kind=c_char), dimension(length), intent(out) :: name
    integer(c_int32_t)                                           :: err
  end function
end interface

interface
  function tinf_iris_broadcast(comm,data_type,data_rank,data_dims,buf,root)    &
           result(err) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int32_t, c_size_t
    type(c_ptr),        value,        intent(in)    :: comm
    integer(c_int32_t), value,        intent(in)    :: data_type
    integer(c_int32_t), value,        intent(in)    :: data_rank
    integer(c_size_t),  dimension(*), intent(in)    :: data_dims
    type(c_ptr),        value,        intent(in)    :: buf
    integer(c_int32_t), value,        intent(in)    :: root
    integer(c_int32_t)                              :: err
  end function
end interface

interface
  function tinf_iris_sum(comm, data_type, data_rank, data_dims, buf, suma)     &
           bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int32_t, c_size_t
    type(c_ptr),        value,        intent(in)    :: comm
    integer(c_int32_t), value,        intent(in)    :: data_type
    integer(c_int32_t), value,        intent(in)    :: data_rank
    integer(c_size_t),  dimension(*), intent(in)    :: data_dims
    type(c_ptr),        value,        intent(in)    :: buf
    type(c_ptr),        value,        intent(in)    :: suma
    integer(c_int32_t)                              :: tinf_iris_sum
  end function
end interface

interface
  function tinf_iris_min(comm, data_type, data_rank, data_dims, buf, mini)     &
           bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int32_t, c_size_t
    type(c_ptr),        value,        intent(in)    :: comm
    integer(c_int32_t), value,        intent(in)    :: data_type
    integer(c_int32_t), value,        intent(in)    :: data_rank
    integer(c_size_t),  dimension(*), intent(in)    :: data_dims
    type(c_ptr),        value,        intent(in)    :: buf
    type(c_ptr),        value,        intent(in)    :: mini
    integer(c_int32_t)                              :: tinf_iris_min
  end function
end interface

interface
  function tinf_iris_max(comm, data_type, data_rank, data_dims, buf, maxi)     &
           bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int32_t, c_size_t
    type(c_ptr),        value,        intent(in)    :: comm
    integer(c_int32_t), value,        intent(in)    :: data_type
    integer(c_int32_t), value,        intent(in)    :: data_rank
    integer(c_size_t),  dimension(*), intent(in)    :: data_dims
    type(c_ptr),        value,        intent(in)    :: buf
    type(c_ptr),        value,        intent(in)    :: maxi
    integer(c_int32_t)                              :: tinf_iris_max
  end function
end interface

interface
  function tinf_iris_rank_of_max(comm, data_type, data_rank, data_dims, buf,   &
                                 rank) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int32_t, c_size_t
    type(c_ptr),        value,        intent(in)    :: comm
    integer(c_int32_t), value,        intent(in)    :: data_type
    integer(c_int32_t), value,        intent(in)    :: data_rank
    integer(c_size_t),  dimension(*), intent(in)    :: data_dims
    type(c_ptr),        value,        intent(in)    :: buf
    integer(c_int32_t),               intent(out)   :: rank
    integer(c_int32_t)                              :: tinf_iris_rank_of_max
  end function
end interface

interface
  function tinf_iris_build_sync_pattern(comm, global_ids, gbl_cnt, have,       &
                                        have_cnt, need, need_cnt, err) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_size_t, c_int64_t,        &
                                            c_int32_t
    type(c_ptr),                             value,  intent(in)    :: comm
    integer(c_size_t),                       value,  intent(in)    :: gbl_cnt
    integer(c_int64_t), dimension(gbl_cnt),  target, intent(inout) :: global_ids
    integer(c_size_t),                       value,  intent(in)    :: have_cnt
    integer(c_int64_t), dimension(have_cnt), target, intent(inout) :: have
    integer(c_size_t),                       value,  intent(in)    :: need_cnt
    integer(c_int64_t), dimension(need_cnt), target, intent(inout) :: need
    integer(c_int32_t),                              intent(out)   :: err
    type(c_ptr)                            :: tinf_iris_build_sync_pattern
  end function
end interface

interface
  function tinf_iris_delete_sync_pattern(comm, sync_pattern) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int32_t
    type(c_ptr),        value,     intent(in) :: comm
    type(c_ptr),        value,     intent(in) :: sync_pattern
    integer(c_int32_t)                        :: tinf_iris_delete_sync_pattern
  end function
end interface

interface
  function tinf_iris_sync(comm, sync_pattern, data_type, data_rank, data_dims, &
                          buf) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_size_t, c_int32_t
    type(c_ptr),                      value, intent(in)    :: comm
    type(c_ptr),                      value, intent(in)    :: sync_pattern
    integer(c_int32_t),               value, intent(in)    :: data_type
    integer(c_int32_t),               value, intent(in)    :: data_rank
    integer(c_size_t),  dimension(*),        intent(in)    :: data_dims
    type(c_ptr),                      value, intent(in)    :: buf
    integer(c_int32_t)                                     :: tinf_iris_sync
  end function
end interface

interface
  function tinf_iris_send(comm, data_type, data_rank, data_dims, buf,          &
                          dest, tag) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int32_t, c_size_t
    type(c_ptr),                      value, intent(in)    :: comm
    integer(c_int32_t),               value, intent(in)    :: data_type
    integer(c_int32_t),               value, intent(in)    :: data_rank
    integer(c_size_t),  dimension(*),        intent(in)    :: data_dims
    type(c_ptr),                      value, intent(in)    :: buf
    integer(c_int32_t),               value, intent(in)    :: dest
    integer(c_int32_t),               value, intent(in)    :: tag
    integer(c_int32_t)                                     :: tinf_iris_send
  end function
end interface

interface
  function tinf_iris_recv(comm, data_type, data_rank, data_dims, buf,          &
                          src, tag, recv_tag) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int32_t, c_size_t
    type(c_ptr),                      value, intent(in)    :: comm
    integer(c_int32_t),               value, intent(in)    :: data_type
    integer(c_int32_t),               value, intent(in)    :: data_rank
    integer(c_size_t),  dimension(*),        intent(in)    :: data_dims
    type(c_ptr),                      value, intent(in)    :: buf
    integer(c_int32_t),               value, intent(in)    :: src
    integer(c_int32_t),               value, intent(in)    :: tag
    integer(c_int32_t),                      intent(out)   :: recv_tag
    integer(c_int32_t)                                     :: tinf_iris_recv
  end function
end interface

interface
  function tinf_iris_isend(comm, data_type, data_rank, data_dims, buf,         &
                          dest, tag, request, offs, dev_addr) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int32_t, c_size_t
    type(c_ptr),                      value, intent(in)    :: comm
    integer(c_int32_t),               value, intent(in)    :: data_type
    integer(c_int32_t),               value, intent(in)    :: data_rank
    integer(c_size_t),  dimension(*),        intent(in)    :: data_dims
    type(c_ptr),                      value, intent(in)    :: buf
    integer(c_int32_t),               value, intent(in)    :: dest
    integer(c_int32_t),               value, intent(in)    :: tag
    type(c_ptr),                             intent(out)   :: request
    integer(c_size_t),  dimension(*),        intent(in)    :: offs
    type(c_ptr),                      value, intent(in)    :: dev_addr
    integer(c_int32_t)                                     :: tinf_iris_isend
  end function
end interface

interface
  function tinf_iris_irecv(comm, data_type, data_rank, data_dims, buf,         &
                          src, tag, request, offs, dev_addr) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int32_t, c_size_t
    type(c_ptr),                      value, intent(in)    :: comm
    integer(c_int32_t),               value, intent(in)    :: data_type
    integer(c_int32_t),               value, intent(in)    :: data_rank
    integer(c_size_t),  dimension(*),        intent(in)    :: data_dims
    type(c_ptr),                      value, intent(in)    :: buf
    integer(c_int32_t),               value, intent(in)    :: src
    integer(c_int32_t),               value, intent(in)    :: tag
    type(c_ptr),                             intent(out)   :: request
    integer(c_size_t),  dimension(*),        intent(in)    :: offs
    type(c_ptr),                      value, intent(in)    :: dev_addr
    integer(c_int32_t)                                     :: tinf_iris_irecv
  end function
end interface

interface
  function tinf_iris_file_open(comm, file_name, nlen, mode, info, file_descr)  &
  bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_size_t, c_int32_t, c_char
    type(c_ptr),                  value,        intent(in)  :: comm
    integer(c_size_t),            value,        intent(in)  :: nlen
    character(len=1,kind=c_char), dimension(*), intent(in)  :: file_name
    integer(c_int32_t),           value,        intent(in)  :: mode
    type(c_ptr),                  value,        intent(in)  :: info
    integer(c_int32_t),                         intent(out) :: file_descr
    integer(c_int32_t)                                   :: tinf_iris_file_open
  end function
end interface

interface
  function tinf_iris_file_close(comm, file_descr) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int32_t
    type(c_ptr),                  value,        intent(in) :: comm
    integer(c_int32_t),           value,        intent(in) :: file_descr
    integer(c_int32_t)                                  :: tinf_iris_file_close
  end function
end interface

interface
  function tinf_iris_file_set_view(comm, file_descr, disp, etype, filetype,    &
                                   datarep, datarep_len, info) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int32_t, c_int64_t,       &
                                            c_size_t, c_char
    type(c_ptr),                  value,        intent(in) :: comm
    integer(c_int32_t),           value,        intent(in) :: file_descr
    integer(c_int64_t),           value,        intent(in) :: disp
    integer(c_int32_t),           value,        intent(in) :: etype
    integer(c_int32_t),           value,        intent(in) :: filetype
    integer(c_size_t),            value,        intent(in) :: datarep_len
    character(len=1,kind=c_char), dimension(*), intent(in) :: datarep
    type(c_ptr),                  value,        intent(in) :: info
    integer(c_int32_t)                               :: tinf_iris_file_set_view
  end function
end interface

interface
  function tinf_iris_create_from_ranks(comm, offs, cnt, rank_list, err)        &
           result(new_comm) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_size_t, c_int64_t,        &
                                            c_int32_t
    type(c_ptr),        value,                  intent(in)  :: comm
    integer(c_size_t),  value,                  intent(in)  :: offs
    integer(c_size_t),  value,                  intent(in)  :: cnt
    integer(c_int64_t), dimension(cnt),         intent(in)  :: rank_list
    integer(c_int32_t),                         intent(out) :: err
    type(c_ptr)                                             :: new_comm
  end function
end interface

interface
  function tinf_iris_file_read_at(comm, data_type, file_descr, offs, buf, cnt) &
           result(err) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int32_t, c_size_t
    type(c_ptr),               value,           intent(in)    :: comm
    integer(c_int32_t),        value,           intent(in)    :: data_type
    integer(c_int32_t),        value,           intent(in)    :: file_descr
    integer(c_size_t),         value,           intent(in)    :: offs
    type(c_ptr),               value,           intent(in)    :: buf
    integer(c_size_t),         value,           intent(in)    :: cnt
    integer(c_int32_t)                                        :: err
  end function
end interface

interface
  function tinf_iris_file_read_at_all(comm, data_type, file_descr, offs, buf,  &
                                      cnt) result(err) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int32_t, c_size_t
    type(c_ptr),               value,           intent(in)    :: comm
    integer(c_int32_t),        value,           intent(in)    :: data_type
    integer(c_int32_t),        value,           intent(in)    :: file_descr
    integer(c_size_t),         value,           intent(in)    :: offs
    type(c_ptr),               value,           intent(in)    :: buf
    integer(c_size_t),         value,           intent(in)    :: cnt
    integer(c_int32_t)                                        :: err
  end function
end interface

interface
  function tinf_iris_file_write_at(comm, data_type, file_descr, offs, buf, cnt)&
           result(err) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int32_t, c_size_t
    type(c_ptr),               value,           intent(in)    :: comm
    integer(c_int32_t),        value,           intent(in)    :: data_type
    integer(c_int32_t),        value,           intent(in)    :: file_descr
    integer(c_size_t),         value,           intent(in)    :: offs
    type(c_ptr),               value,           intent(in)    :: buf
    integer(c_size_t),         value,           intent(in)    :: cnt
    integer(c_int32_t)                                        :: err
  end function
end interface

interface
  function tinf_iris_file_write_at_all(comm, data_type, file_descr, offs, buf, &
                                      cnt) result(err) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int32_t, c_size_t
    type(c_ptr),               value,           intent(in)    :: comm
    integer(c_int32_t),        value,           intent(in)    :: data_type
    integer(c_int32_t),        value,           intent(in)    :: file_descr
    integer(c_size_t),         value,           intent(in)    :: offs
    type(c_ptr),               value,           intent(in)    :: buf
    integer(c_size_t),         value,           intent(in)    :: cnt
    integer(c_int32_t)                                        :: err
  end function
end interface

interface
  function tinf_iris_gather(comm, data_type, data_rank, data_dims, send, recv, &
                            rank) result(err) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int32_t, c_size_t
    type(c_ptr),                          value, intent(in)    :: comm
    integer(c_int32_t),                   value, intent(in)    :: data_type
    integer(c_int32_t),                   value, intent(in)    :: data_rank
    integer(c_size_t),  dimension(*),            intent(in)    :: data_dims
    type(c_ptr),                          value, intent(in)    :: send
    type(c_ptr),                          value, intent(in)    :: recv
    integer(c_int32_t),                   value, intent(in)    :: rank
    integer(c_int32_t)                                         :: err
  end function
end interface

interface
  function tinf_iris_gatherv(comm, data_type, data_rank, data_dims, send,      &
                             recv, counts_recv, displacements, rank)           &
                             result(err) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int32_t, c_size_t
    type(c_ptr),                          value, intent(in)    :: comm
    integer(c_int32_t),                   value, intent(in)    :: data_type
    integer(c_int32_t),                   value, intent(in)    :: data_rank
    integer(c_size_t),  dimension(*),            intent(in)    :: data_dims
    type(c_ptr),                          value, intent(in)    :: send
    type(c_ptr),                          value, intent(in)    :: recv
    integer(c_int32_t), dimension(*),            intent(in)    :: counts_recv
    integer(c_int32_t), dimension(*),            intent(in)    :: displacements
    integer(c_int32_t),                   value, intent(in)    :: rank
    integer(c_int32_t)                                         :: err
  end function
end interface

interface
  function tinf_iris_alltoall(comm, data_type, data_rank, data_dims, send,     &
                              recv) result(err) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int32_t, c_size_t
    type(c_ptr),                      value, intent(in)    :: comm
    integer(c_int32_t),               value, intent(in)    :: data_type
    integer(c_int32_t),               value, intent(in)    :: data_rank
    integer(c_size_t),  dimension(*),        intent(in)    :: data_dims
    type(c_ptr),                      value, intent(in)    :: send
    type(c_ptr),                      value, intent(in)    :: recv
    integer(c_int32_t)                                     :: err
  end function
end interface

interface
  function tinf_iris_alltoallv(comm, data_type, data_rank, data_dims, send,    &
                               nsend, recv, nrecv) result(err) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_int32_t, c_size_t
    type(c_ptr),                      value, intent(in)    :: comm
    integer(c_int32_t),               value, intent(in)    :: data_type
    integer(c_int32_t),               value, intent(in)    :: data_rank
    integer(c_size_t),  dimension(*),        intent(in)    :: data_dims
    type(c_ptr),                      value, intent(in)    :: send
    integer(c_int32_t), dimension(*),        intent(in)    :: nsend
    type(c_ptr),                      value, intent(in)    :: recv
    integer(c_int32_t), dimension(*),        intent(in)    :: nrecv
    integer(c_int32_t)                                     :: err
  end function
end interface

interface
  function tinf_iris_create_requests(comm, cnt, requests) result(err) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_size_t, c_int32_t
    type(c_ptr),                       value, intent(in)    :: comm
    integer(c_size_t),                 value, intent(in)    :: cnt
    type(c_ptr),       dimension(cnt),        intent(out)   :: requests
    integer(c_int32_t)                                      :: err
  end function
end interface

interface
  function tinf_iris_destroy_requests(comm, cnt, requests) result(err) bind(c)
    use, intrinsic :: iso_c_binding, only : c_ptr, c_size_t, c_int32_t
    type(c_ptr),                       value, intent(in)    :: comm
    integer(c_size_t),                 value, intent(in)    :: cnt
    type(c_ptr),       dimension(cnt),        intent(in)    :: requests
    integer(c_int32_t)                                      :: err
  end function
end interface
