#ifndef TINF_TYPE_H
#define TINF_TYPE_H

#include <type_traits>
#include "tinf_enum_definitions.h"

template <typename T>
int32_t
tinf_type(TINF_DATA_TYPE &datatype)
{
  int32_t error = TINF_SUCCESS;
  datatype = TINF_DOUBLE;
  if (std::is_same<T, int32_t>::value)
  {
    datatype = TINF_INT32;
  }
  else if (std::is_same<T, int64_t>::value)
  {
    datatype = TINF_INT64;
  }
  else if (std::is_same<T, float>::value)
  {
    datatype = TINF_FLOAT;
  }
  else if (std::is_same<T, double>::value)
  {
    datatype = TINF_DOUBLE;
  }
  else if (std::is_same<T, char>::value)
  {
    datatype = TINF_CHAR;
  }
  else if (std::is_same<T, bool>::value)
  {
    datatype = TINF_BOOL;
  }
  else if (std::is_same<T, std::complex<float>>::value)
  {
    datatype = TINF_CMPLX_FLOAT;
  }
  else if (std::is_same<T, std::complex<double>>::value)
  {
    datatype = TINF_CMPLX_DOUBLE;
  }
  else if (std::is_same<T, size_t>::value)
  {
    datatype = TINF_SIZE_T;
  }
  else
  {
    error = TINF_FAILURE;
  }
  return error;
}

inline int32_t
tinf_type_name(int32_t data_type, std::string &data_type_name)
{
  int32_t error = TINF_SUCCESS;
  switch (data_type)
  {
  case TINF_INT32:
  {
    data_type_name = "int32_t";
    break;
  }
  case TINF_INT64:
  {
    data_type_name = "int64_t";
    break;
  }
  case TINF_FLOAT:
  {
    data_type_name = "float";
    break;
  }
  case TINF_DOUBLE:
  {
    data_type_name = "double";
    break;
  }
  case TINF_CHAR:
  {
    data_type_name = "char";
    break;
  }
  case TINF_BOOL:
  {
    data_type_name = "bool";
    break;
  }
  case TINF_CMPLX_FLOAT:
  {
    data_type_name = "complex<float>";
    break;
  }
  case TINF_CMPLX_DOUBLE:
  {
    data_type_name = "complex<double>";
    break;
  }
  case TINF_SIZE_T:
  {
    data_type_name = "size_t";
    break;
  }
  default:
  {
    data_type_name = "unkown";
    error = TINF_FAILURE;
    break;
  }
  }
  return error;
}

template <typename T>
int32_t
tinf_type_name(std::string &data_type_name)
{
  int32_t error = TINF_SUCCESS;
  TINF_DATA_TYPE datatype = TINF_DOUBLE;
  error = tinf_type<T>(datatype);
  error = tinf_type_name(datatype, data_type_name);
  return error;
}

inline size_t
tinf_type_sizeof(const enum TINF_DATA_TYPE data_type, TINF_ERROR_CODES *error)
{
  *error = TINF_SUCCESS;
  switch (data_type)
  {
  case TINF_INT32:
  {
    return sizeof(int32_t);
  }
  case TINF_INT64:
  {
    return sizeof(int64_t);
  }
  case TINF_FLOAT:
  {
    return sizeof(float);
  }
  case TINF_DOUBLE:
  {
    return sizeof(double);
  }
  case TINF_CHAR:
  {
    return sizeof(char);
  }
  case TINF_BOOL:
  {
    return sizeof(bool);
  }
  case TINF_CMPLX_FLOAT:
  {
    return sizeof(std::complex<float>);
  }
  case TINF_CMPLX_DOUBLE:
  {
    return sizeof(std::complex<double>);
  }
  case TINF_SIZE_T:
  {
    return sizeof(size_t);
  }
  default:
  {
    *error = TINF_FAILURE;
    return 0;
  }
  }
}

template <typename T>
size_t
tinf_type_sizeof(TINF_ERROR_CODES *error)
{
  *error = TINF_SUCCESS;
  TINF_DATA_TYPE datatype = TINF_DOUBLE;
  *error = static_cast<TINF_ERROR_CODES>(tinf_type<T>(datatype));
  if (*error != TINF_SUCCESS)
    return 0;
  return tinf_type_sizeof(datatype, error);
}

#endif
