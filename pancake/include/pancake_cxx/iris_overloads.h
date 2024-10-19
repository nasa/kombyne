#pragma once

#include "tinf_enum_definitions.h"
#include "tinf_iris.h"
#include "tinf_type.h"

inline int32_t
iris_rank(void *handle)
{
  int32_t err;
  int32_t rank = tinf_iris_rank(handle, &err);
  // handle error
  return rank;
}

inline void
iris_abort(void *handle)
{
  int32_t err = tinf_iris_abort(handle);
  // handle error
}

inline void
iris_barrier(void *handle)
{
  int32_t err = tinf_iris_barrier(handle);
}

inline void *
iris_build_sync_pattern(void *handle, int64_t *global_ids, size_t global_cnt,
                        int64_t *have, size_t have_cnt, int64_t *need,
                        size_t need_cnt)
{
  int32_t err = TINF_SUCCESS;
  void *sync_pattern = tinf_iris_build_sync_pattern(
      handle, global_ids, global_cnt, have, have_cnt, need, need_cnt, &err);
  // handle error
  return sync_pattern;
}

inline void
iris_delete_sync_pattern(void *handle, void *sync_pattern)
{
  int32_t err = tinf_iris_delete_sync_pattern(handle, sync_pattern);
  // handle error
}

template <typename Type>
inline int32_t
iris_rank_of_max(void *handle, Type x)
{
  enum TINF_DATA_TYPE data_type;
  int32_t err = tinf_type<Type>(data_type);

  int32_t data_rank = 0;
  size_t dims[TINF_DATA_MAX_RANK] = {0};
  int32_t rank{-1};
  err = tinf_iris_rank_of_max(handle, data_type, data_rank, dims,
                              static_cast<void *>(&x), &rank);
  return rank;
}

inline int32_t
iris_number_of_processes(void *handle)
{
  int32_t err;
  return tinf_iris_number_of_processes(handle, &err);
}

template <typename Type>
inline void
iris_broadcast(void *handle, Type *x, int32_t rank)
{
  enum TINF_DATA_TYPE data_type;
  int32_t err = tinf_type<Type>(data_type);

  int32_t data_rank = 0;
  size_t dims[TINF_DATA_MAX_RANK] = {0};
  err = tinf_iris_broadcast(handle, data_type, data_rank, dims, x, rank);
}

template <typename Type>
inline void
iris_broadcast(void *handle, Type *x, size_t n, int32_t rank)
{
  enum TINF_DATA_TYPE data_type;
  int32_t err = tinf_type<Type>(data_type);

  int32_t data_rank = 1;
  size_t dims[TINF_DATA_MAX_RANK] = {0};
  dims[0] = n;
  err = tinf_iris_broadcast(handle, data_type, data_rank, dims,
                            static_cast<void *>(x), rank);
}

template <typename Type>
inline void
iris_send(void *handle, Type *x, int32_t dest, int32_t tag)
{
  enum TINF_DATA_TYPE data_type;
  int32_t err = tinf_type<Type>(data_type);

  int32_t data_rank = 0;
  size_t dims[TINF_DATA_MAX_RANK] = {0};
  err = tinf_iris_send(handle, data_type, data_rank, dims,
                       static_cast<void *>(x), dest, tag);
}

template <typename Type>
inline void
iris_send(void *handle, Type *x, size_t n, int32_t dest, int32_t tag)
{
  enum TINF_DATA_TYPE data_type;
  int32_t err = tinf_type<Type>(data_type);

  int32_t data_rank = 1;
  size_t dims[TINF_DATA_MAX_RANK] = {0};
  dims[0] = n;
  err = tinf_iris_send(handle, data_type, data_rank, dims,
                       static_cast<void *>(x), dest, tag);
}

inline void
iris_send(void *handle, std::string &str, int32_t dest, int32_t tag)
{
  enum TINF_DATA_TYPE data_type = TINF_INT32;

  int32_t data_rank = 0;
  size_t dims[TINF_DATA_MAX_RANK] = {0};
  int32_t any_tag = 1000;
  int32_t str_size = str.size();
  int32_t err = tinf_iris_send(handle, data_type, data_rank, dims,
                               static_cast<void *>(&str_size), dest, any_tag);
  char *str_chars = (char *)calloc(str_size, sizeof(char));
  for (int32_t i = 0; i < str_size; ++i)
  {
    str_chars[i] = str.c_str()[i];
  }
  data_type = TINF_CHAR;
  data_rank = 1;
  dims[0] = str_size;
  err = tinf_iris_send(handle, data_type, data_rank, dims,
                       static_cast<void *>(str_chars), dest, tag);
  free(str_chars);
}

template <typename Type>
inline void
iris_recv(void *handle, Type *x, int32_t source, int32_t tag, int32_t *recv_tag)
{
  enum TINF_DATA_TYPE data_type;
  int32_t err = tinf_type<Type>(data_type);

  int32_t data_rank = 0;
  size_t dims[TINF_DATA_MAX_RANK] = {0};
  err = tinf_iris_recv(handle, data_type, data_rank, dims,
                       static_cast<void *>(x), source, tag, recv_tag);
}

template <typename Type>
inline void
iris_recv(void *handle, Type *x, size_t n, int32_t source, int32_t tag,
          int32_t *recv_tag)
{
  enum TINF_DATA_TYPE data_type;
  int32_t err = tinf_type<Type>(data_type);

  int32_t data_rank = 1;
  size_t dims[TINF_DATA_MAX_RANK] = {0};
  dims[0] = n;
  err = tinf_iris_recv(handle, data_type, data_rank, dims,
                       static_cast<void *>(x), source, tag, recv_tag);
}

inline void
iris_recv(void *handle, std::string &str, int32_t source, int32_t tag,
          int32_t *recv_tag)
{
  enum TINF_DATA_TYPE data_type = TINF_INT32;

  int32_t data_rank = 0;
  size_t dims[TINF_DATA_MAX_RANK] = {0};
  int32_t any_tag = 1000;
  int32_t str_size;

  int32_t err =
      tinf_iris_recv(handle, data_type, data_rank, dims,
                     static_cast<void *>(&str_size), source, any_tag, recv_tag);
  char *str_chars = (char *)calloc(str_size, sizeof(char));
  data_type = TINF_CHAR;
  data_rank = 1;
  dims[0] = str_size;
  err = tinf_iris_recv(handle, data_type, data_rank, dims,
                       static_cast<void *>(str_chars), source, tag, recv_tag);
  str = str_chars;
  free(str_chars);
}

template <typename Type>
inline void
iris_sum(void *handle, Type x, Type *sum)
{
  enum TINF_DATA_TYPE data_type;
  int32_t err = tinf_type<Type>(data_type);

  int32_t data_rank = 0;
  size_t dims[TINF_DATA_MAX_RANK] = {0};
  err = tinf_iris_sum(handle, data_type, data_rank, dims,
                      static_cast<const void *>(&x), sum);
}

template <typename Type>
inline void
iris_sum(void *handle, Type *x, size_t n, Type *sum)
{
  enum TINF_DATA_TYPE data_type;
  int32_t err = tinf_type<Type>(data_type);

  int32_t data_rank = 1;
  size_t dims[TINF_DATA_MAX_RANK] = {0};
  dims[0] = n;
  err = tinf_iris_sum(handle, data_type, data_rank, dims, x, sum);
}

template <typename Type>
inline void
iris_sum(void *handle, Type *x, size_t m, size_t n, Type *sum)
{
  enum TINF_DATA_TYPE data_type;
  int32_t err = tinf_type<Type>(data_type);

  int32_t data_rank = 2;
  size_t dims[TINF_DATA_MAX_RANK] = {0};
  dims[0] = n;
  dims[1] = m; // TODO: check if m is rows, and n is cols?
  err = tinf_iris_sum(handle, data_type, data_rank, dims,
                      static_cast<void *>(&x), sum);
}

template <typename Type>
inline Type
iris_min(void *handle, Type x)
{
  Type min;
  enum TINF_DATA_TYPE data_type;
  int32_t err = tinf_type<Type>(data_type);

  int32_t data_rank = 0;
  size_t dims[TINF_DATA_MAX_RANK] = {0};
  err = tinf_iris_min(handle, data_type, data_rank, dims,
                      static_cast<const void *>(&x), &min);
  return min;
}

template <typename Type>
inline Type
iris_max(void *handle, Type x)
{
  Type max;
  enum TINF_DATA_TYPE data_type;
  int32_t err = tinf_type<Type>(data_type);

  int32_t data_rank = 0;
  size_t dims[TINF_DATA_MAX_RANK] = {0};
  err = tinf_iris_max(handle, data_type, data_rank, dims,
                      static_cast<void *>(&x), &max);
  return max;
}

template <typename Type>
inline void
iris_sync(void *handle, void *sync_pattern, Type *x, size_t count)
{

  enum TINF_DATA_TYPE data_type;
  int32_t err = tinf_type<Type>(data_type);

  int32_t data_rank = 1;
  size_t dims[TINF_DATA_MAX_RANK] = {0};
  dims[0] = count;
  err = tinf_iris_sync(handle, sync_pattern, data_type, data_rank, dims, x);
}

template <typename Type>
inline void
iris_sync(void *handle, void *sync_pattern, Type *x, size_t rows,
          size_t columns)
{

  enum TINF_DATA_TYPE data_type;
  int32_t err = tinf_type<Type>(data_type);

  int32_t data_rank = 1;
  size_t dims[TINF_DATA_MAX_RANK] = {0};
  dims[0] = columns;
  dims[1] = rows;
  err = tinf_iris_sync(handle, sync_pattern, data_type, data_rank, dims, x);
}

template <typename Type>
inline void
iris_gather(void *handle, Type *send, Type *recv, int32_t rank)
{
  enum TINF_DATA_TYPE data_type;
  int32_t err = tinf_type<Type>(data_type);

  int32_t data_rank = 0;
  size_t dims[TINF_DATA_MAX_RANK] = {0};
  err = tinf_iris_gather(handle, data_type, data_rank, dims, send, recv, rank);
}

template <typename Type>
inline void
iris_gatherv(void *handle, Type *send, int32_t count_send, Type *recv,
             int32_t *counts_recv, int32_t *displacements, int32_t rank)
{
  enum TINF_DATA_TYPE data_type;
  int32_t err = tinf_type<Type>(data_type);

  int32_t data_rank = 1;
  size_t dims[TINF_DATA_MAX_RANK] = {0};
  dims[0] = count_send;
  err = tinf_iris_gatherv(handle, data_type, data_rank, dims, send, recv,
                          counts_recv, displacements, rank);
}

template <typename Type>
inline void
iris_alltoall(void *handle, Type *send, Type *recv)
{
  enum TINF_DATA_TYPE data_type;
  int32_t err = tinf_type<Type>(data_type);

  int32_t data_rank = 0;
  size_t dims[TINF_DATA_MAX_RANK] = {0};
  err = tinf_iris_alltoall(handle, data_type, data_rank, dims, send, recv);
}

template <typename Type>
inline void
iris_alltoall(void *handle, Type *send, Type *recv, int32_t count)
{
  enum TINF_DATA_TYPE data_type;
  int32_t err = tinf_type<Type>(data_type);

  int32_t data_rank = 1;
  size_t dims[TINF_DATA_MAX_RANK] = {0};
  dims[0] = count;
  err = tinf_iris_alltoall(handle, data_type, data_rank, dims, send, recv);
}
