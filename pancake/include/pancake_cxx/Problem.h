#ifndef _PROBLEM_H_
#define _PROBLEM_H_

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <exception>
#include <stdexcept>
#include <cstdlib>
#include <cstring>
#include <string>
#include <sstream>
#include <complex>
#include <vector>

#include "tinf_problem.h"
#include "tinf_type.h"

#include <stdio.h>

namespace pancake
{
/**
 * A Class to encapsulate and facilitate the interrogation of a T-Infinity
 * Problem description.
 */
class Problem
{
public:
  /**
   * Construct a Problem object from an opaque problem pointer.
   *
   * @param prob  Opaque Problem pointer
   */
  Problem(void *prob) : problem(prob) {}

  /**
   * Destruct a Problem object.
   */
  virtual ~Problem() {}

  /**
   * Determine if a key/value pair is defined in the problem description.
   *
   * @param key  Variable key
   * @param datatype  Data type of the value
   * @param rank  Data rank of the value
   * @param dims  Dimensions of each @p rank
   * @returns true if key/value defined
   * @throws std::runtime_error
   **/
  inline virtual bool
  defined(const char *key, enum TINF_DATA_TYPE *datatype, int32_t *rank,
          size_t dims[TINF_PROBLEM_MAX_RANK])
  {
    int32_t err;
    bool ret = tinf_problem_defined(problem, key, strlen(key), datatype, rank,
                                    dims, &err);
    if (TINF_SUCCESS != err)
    {
      std::stringstream ss;
      ss << err;
      std::string message =
          std::string("tinf_problem_defined returned ") + ss.str();
      throw std::runtime_error(message.c_str());
    }
    return ret;
  }

  /**
   * Retrieve the value of a key/value pair defined in the problem
   * description.
   *
   * @param key  Variable key
   * @param data  Data pointer
   * @param rank  Data rank of the value
   * @param dims  Dimensions of each @p rank
   * @throws std::runtime_error
   **/
  inline virtual void
  value(const char *key, const void *data, int32_t rank, const size_t dims[])
  {
    int32_t err =
        tinf_problem_value(problem, key, strlen(key), data, rank, dims);

    if (TINF_SUCCESS != err)
    {
      std::stringstream ss;
      ss << err;
      std::string message =
          std::string("tinf_problem_value returned ") + ss.str();
      throw std::runtime_error(message.c_str());
    }
  }

  /**
   * Set the value of a key/value pair defined in the problem
   * description.
   *
   * @param key  Variable key
   * @param data  Data pointer
   * @param rank  Data rank of the value
   * @param dims  Dimensions of each @p rank
   * @throws std::runtime_error
   **/
  inline virtual void
  set_value(const char *key, const void *data, int32_t rank,
            const size_t dims[])
  {
    int32_t err =
        tinf_problem_set_value(problem, key, strlen(key), data, rank, dims);

    if (TINF_SUCCESS != err)
    {
      std::stringstream ss;
      ss << err;
      std::string message =
          std::string("tinf_problem_set_value returned ") + ss.str();
      throw std::runtime_error(message.c_str());
    }
  }

  // Overloads

  /**
   * Retrieve a scalar int32_t value for a key if it is defined in the
   * problem description.
   *
   * @param key  Variable key
   * @param val  Pointer to int32_t
   * @returns true if key/value defined as int32_t
   * @throws std::runtime_error
   **/
  inline virtual bool
  value(const char *key, int32_t *val)
  {
    enum TINF_DATA_TYPE type;
    int32_t rank;
    size_t dims[TINF_PROBLEM_MAX_RANK];
    try
    {
      if (defined(key, &type, &rank, dims))
      {
        if (TINF_INT32 == type && 0 == rank)
        {
          value(key, (const void *)val, rank, dims);
          return true;
        }
      }
    }
    catch (std::runtime_error e)
    {
      throw;
    }
    return false;
  }

  /**
   * Retrieve a scalar int64_t value for a key if it is defined in the
   * problem description.
   *
   * @param key  Variable key
   * @param val  Pointer to int64_t
   * @returns true if key/value defined as int64_t
   * @throws std::runtime_error
   **/
  inline virtual bool
  value(const char *key, int64_t *val)
  {
    enum TINF_DATA_TYPE type;
    int32_t rank;
    size_t dims[TINF_PROBLEM_MAX_RANK];
    try
    {
      if (defined(key, &type, &rank, dims))
      {
        if (TINF_INT64 == type && 0 == rank)
        {
          value(key, (const void *)val, rank, dims);
          return true;
        }
      }
    }
    catch (std::runtime_error e)
    {
      throw;
    }
    return false;
  }

  /**
   * Retrieve a scalar float value for a key if it is defined in the
   * problem description.
   *
   * @param key  Variable key
   * @param val  Pointer to float
   * @returns true if key/value defined as float
   * @throws std::runtime_error
   **/
  inline virtual bool
  value(const char *key, float *val)
  {
    enum TINF_DATA_TYPE type;
    int32_t rank;
    size_t dims[TINF_PROBLEM_MAX_RANK];
    try
    {
      if (defined(key, &type, &rank, dims))
      {
        if (TINF_FLOAT == type && 0 == rank)
        {
          value(key, (const void *)val, rank, dims);
          return true;
        }
      }
    }
    catch (std::runtime_error e)
    {
      throw;
    }
    return false;
  }

  /**
   * Retrieve a scalar double value for a key if it is defined in the
   * problem description.
   *
   * @param key  Variable key
   * @param val  Pointer to double
   * @returns true if key/value defined as double
   * @throws std::runtime_error
   **/
  inline virtual bool
  value(const char *key, double *val)
  {
    enum TINF_DATA_TYPE type;
    int32_t rank;
    size_t dims[TINF_PROBLEM_MAX_RANK];
    try
    {
      if (defined(key, &type, &rank, dims))
      {
        if (TINF_DOUBLE == type && 0 == rank)
        {
          value(key, (const void *)val, rank, dims);
          return true;
        }
      }
    }
    catch (std::runtime_error e)
    {
      throw;
    }
    return false;
  }

  /**
   * Retrieve a scalar std::complex<double> value for a key if it is
   * defined in the problem description.
   *
   * @param key  Variable key
   * @param val  Pointer to std::complex<double>
   * @returns true if key/value defined as std::complex<double>
   * @throws std::runtime_error
   **/
  inline virtual bool
  value(const char *key, std::complex<double> *val)
  {
    enum TINF_DATA_TYPE type;
    int32_t rank;
    size_t dims[TINF_PROBLEM_MAX_RANK];
    try
    {
      if (defined(key, &type, &rank, dims))
      {
        if (TINF_CMPLX_DOUBLE == type && 0 == rank)
        {
          value(key, (const void *)val, rank, dims);
          return true;
        }
      }
    }
    catch (std::runtime_error e)
    {
      throw;
    }
    return false;
  }

  /**
   * Retrieve a scalar bool value for a key if it is defined in the
   * problem description.
   *
   * @param key  Variable key
   * @param val  Pointer to bool
   * @returns true if key/value defined as bool
   * @throws std::runtime_error
   **/
  inline virtual bool
  value(const char *key, bool *val)
  {
    enum TINF_DATA_TYPE type;
    int32_t rank;
    size_t dims[TINF_PROBLEM_MAX_RANK];
    try
    {
      if (defined(key, &type, &rank, dims))
      {
        if (TINF_BOOL == type && 0 == rank)
        {
          value(key, (const void *)val, rank, dims);
          return true;
        }
      }
    }
    catch (std::runtime_error e)
    {
      throw;
    }
    return false;
  }

  /**
   * Retrieve an array of int32_t values for a key if they are defined
   * in the problem description.
   *
   * @param key  Variable key
   * @param val  Pointer to int32_t*
   * @param len  Length of @p val
   * @returns true if key/value defined as int32_t*
   * @throws std::runtime_error
   **/
  inline virtual bool
  value(const char *key, int32_t **val, size_t *len)
  {
    enum TINF_DATA_TYPE type;
    int32_t rank;
    size_t dims[TINF_PROBLEM_MAX_RANK];
    int32_t *ptr;
    try
    {
      if (defined(key, &type, &rank, dims))
      {
        if (TINF_INT32 == type && 1 == rank)
        {
          if ((ptr = (int32_t *)malloc(dims[0] * sizeof(int32_t))) == NULL)
            throw std::runtime_error("tinf_problem_value: allocation error");
          *len = dims[0];
          value(key, (const void *)ptr, rank, dims);
          *val = ptr;
          return true;
        }
      }
    }
    catch (std::runtime_error e)
    {
      throw;
    }
    return false;
  }

  /**
   * Retrieve an std::vector of int32_t values for a key if they are defined
   * in the problem description.
   *
   * @param key  Variable key
   * @param val  Vector to hold values
   * @returns true if key/value defined as int32_t*
   * @throws std::runtime_error
   **/
  inline virtual bool
  value(const char *key, std::vector<int32_t>& val)
  {
    enum TINF_DATA_TYPE type;
    int32_t rank;
    size_t dims[TINF_PROBLEM_MAX_RANK];
    try
    {
      if (defined(key, &type, &rank, dims))
      {
        if (TINF_INT32 == type && 1 == rank)
        {
          val.resize(dims[0]);
          value(key, (const void *)val.data(), rank, dims);
          return true;
        }
      }
    }
    catch (std::runtime_error e)
    {
      throw;
    }
    return false;
  }

  /**
   * Retrieve an array of int64_t values for a key if they are defined
   * in the problem description.
   *
   * @param key  Variable key
   * @param val  Pointer to int64_t*
   * @param len  Length of @p val
   * @returns true if key/value defined as int64_t*
   * @throws std::runtime_error
   **/
  inline virtual bool
  value(const char *key, int64_t **val, size_t *len)
  {
    enum TINF_DATA_TYPE type;
    int32_t rank;
    size_t dims[TINF_PROBLEM_MAX_RANK];
    int64_t *ptr;
    try
    {
      if (defined(key, &type, &rank, dims))
      {
        if (TINF_INT64 == type && 1 == rank)
        {
          if ((ptr = (int64_t *)malloc(dims[0] * sizeof(int64_t))) == NULL)
            throw std::runtime_error("tinf_problem_value: allocation error");
          *len = dims[0];
          value(key, (const void *)ptr, rank, dims);
          *val = ptr;
          return true;
        }
      }
    }
    catch (std::runtime_error e)
    {
      throw;
    }
    return false;
  }

  /**
   * Retrieve an std::vector of int64_t values for a key if they are defined
   * in the problem description.
   *
   * @param key  Variable key
   * @param val  Vector to hold values
   * @returns true if key/value defined as int64_t*
   * @throws std::runtime_error
   **/
  inline virtual bool
  value(const char *key, std::vector<int64_t>& val)
  {
    enum TINF_DATA_TYPE type;
    int32_t rank;
    size_t dims[TINF_PROBLEM_MAX_RANK];
    try
    {
      if (defined(key, &type, &rank, dims))
      {
        if (TINF_INT64 == type && 1 == rank)
        {
          val.resize(dims[0]);
          value(key, (const void *)val.data(), rank, dims);
          return true;
        }
      }
    }
    catch (std::runtime_error e)
    {
      throw;
    }
    return false;
  }

  /**
   * Retrieve an array of float values for a key if they are defined
   * in the problem description.
   *
   * @param key  Variable key
   * @param val  Pointer to float*
   * @param len  Length of @p val
   * @returns true if key/value defined as float*
   * @throws std::runtime_error
   **/
  inline virtual bool
  value(const char *key, float **val, size_t *len)
  {
    enum TINF_DATA_TYPE type;
    int32_t rank;
    size_t dims[TINF_PROBLEM_MAX_RANK];
    float *ptr;
    try
    {
      if (defined(key, &type, &rank, dims))
      {
        if (TINF_FLOAT == type && 1 == rank)
        {
          if ((ptr = (float *)malloc(dims[0] * sizeof(float))) == NULL)
            throw std::runtime_error("tinf_problem_value: allocation error");
          *len = dims[0];
          value(key, (const void *)ptr, rank, dims);
          *val = ptr;
          return true;
        }
      }
    }
    catch (std::runtime_error e)
    {
      throw;
    }
    return false;
  }

  /**
   * Retrieve an std::vector of float values for a key if they are defined
   * in the problem description.
   *
   * @param key  Variable key
   * @param val  Vector to hold values
   * @returns true if key/value defined as float*
   * @throws std::runtime_error
   **/
  inline virtual bool
  value(const char *key, std::vector<float>& val)
  {
    enum TINF_DATA_TYPE type;
    int32_t rank;
    size_t dims[TINF_PROBLEM_MAX_RANK];
    try
    {
      if (defined(key, &type, &rank, dims))
      {
        if (TINF_FLOAT == type && 1 == rank)
        {
          val.resize(dims[0]);
          value(key, (const void *)val.data(), rank, dims);
          return true;
        }
      }
    }
    catch (std::runtime_error e)
    {
      throw;
    }
    return false;
  }

  /**
   * Retrieve an array of double values for a key if they are defined
   * in the problem description.
   *
   * @param key  Variable key
   * @param val  Pointer to double*
   * @param len  Length of @p val
   * @returns true if key/value defined as double*
   * @throws std::runtime_error
   **/
  inline virtual bool
  value(const char *key, double **val, size_t *len)
  {
    enum TINF_DATA_TYPE type;
    int32_t rank;
    size_t dims[TINF_PROBLEM_MAX_RANK];
    double *ptr;
    try
    {
      if (defined(key, &type, &rank, dims))
      {
        if (TINF_DOUBLE == type && 1 == rank)
        {
          if ((ptr = (double *)malloc(dims[0] * sizeof(double))) == NULL)
            throw std::runtime_error("tinf_problem_value: allocation error");
          *len = dims[0];
          value(key, (const void *)ptr, rank, dims);
          *val = ptr;
          return true;
        }
      }
    }
    catch (std::runtime_error e)
    {
      throw;
    }
    return false;
  }

  /**
   * Retrieve an std::vector of double values for a key if they are defined
   * in the problem description.
   *
   * @param key  Variable key
   * @param val  Vector to hold values
   * @returns true if key/value defined as double*
   * @throws std::runtime_error
   **/
  inline virtual bool
  value(const char *key, std::vector<double>& val)
  {
    enum TINF_DATA_TYPE type;
    int32_t rank;
    size_t dims[TINF_PROBLEM_MAX_RANK];
    try
    {
      if (defined(key, &type, &rank, dims))
      {
        if (TINF_DOUBLE == type && 1 == rank)
        {
          val.resize(dims[0]);
          value(key, (const void *)val.data(), rank, dims);
          return true;
        }
      }
    }
    catch (std::runtime_error e)
    {
      throw;
    }
    return false;
  }

  /**
   * Retrieve an array of std::complex<double> values for a key if they
   * are defined in the problem description.
   *
   * @param key  Variable key
   * @param val  Pointer to std::complex<double>*
   * @param len  Length of @p val
   * @returns true if key/value defined as std::complex<double>*
   * @throws std::runtime_error
   **/
  inline virtual bool
  value(const char *key, std::complex<double> **val, size_t *len)
  {
    enum TINF_DATA_TYPE type;
    int32_t rank;
    size_t dims[TINF_PROBLEM_MAX_RANK];
    std::complex<double> *ptr;
    try
    {
      if (defined(key, &type, &rank, dims))
      {
        if (TINF_CMPLX_DOUBLE == type && 1 == rank)
        {
          if ((ptr = (std::complex<double> *)malloc(
                   dims[0] * sizeof(std::complex<double>))) == NULL)
            throw std::runtime_error("tinf_problem_value: allocation error");
          *len = dims[0];
          value(key, (const void *)ptr, rank, dims);
          *val = ptr;
          return true;
        }
      }
    }
    catch (std::runtime_error e)
    {
      throw;
    }
    return false;
  }

  /**
   * Retrieve an std::vector of std::complex<double> values for a key if they
   * are defined in the problem description.
   *
   * @param key  Variable key
   * @param val  Vector to hold values
   * @returns true if key/value defined as std::complex<double>*
   * @throws std::runtime_error
   **/
  inline virtual bool
  value(const char *key, std::vector<std::complex<double> >& val)
  {
    enum TINF_DATA_TYPE type;
    int32_t rank;
    size_t dims[TINF_PROBLEM_MAX_RANK];
    try
    {
      if (defined(key, &type, &rank, dims))
      {
        if (TINF_CMPLX_DOUBLE == type && 1 == rank)
        {
          val.resize(dims[0]);
          value(key, (const void *)val.data(), rank, dims);
          return true;
        }
      }
    }
    catch (std::runtime_error e)
    {
      throw;
    }
    return false;
  }

  /**
   * Retrieve an array of char values for a key if they are defined
   * in the problem description.
   *
   * @param key  Variable key
   * @param val  Pointer to char*
   * @param len  Length of @p val
   * @returns true if key/value defined as char*
   * @throws std::runtime_error
   **/
  inline virtual bool
  value(const char *key, char **val, size_t *len)
  {
    enum TINF_DATA_TYPE type;
    int32_t rank;
    size_t dims[TINF_PROBLEM_MAX_RANK];
    char *ptr;
    try
    {
      if (defined(key, &type, &rank, dims))
      {
        if (TINF_CHAR == type && 1 == rank)
        {
          if ((ptr = (char *)malloc(dims[0] * sizeof(char))) == NULL)
            throw std::runtime_error("tinf_problem_value: allocation error");
          *len = dims[0];
          value(key, (const void *)ptr, rank, dims);
          *val = ptr;
          return true;
        }
      }
    }
    catch (std::runtime_error e)
    {
      throw;
    }
    return false;
  }

  /**
   * Retrieve a string value for a key if they are defined
   * in the problem description.
   *
   * @param key  Variable key
   * @param val  Reference to string
   * @returns true if key/value defined as char*
   * @throws std::runtime_error
   **/
  inline virtual bool
  value(const char *key, std::string& val)
  {
    enum TINF_DATA_TYPE type;
    int32_t rank;
    size_t dims[TINF_PROBLEM_MAX_RANK];
    char *ptr;
    try
    {
      if (defined(key, &type, &rank, dims))
      {
        if (TINF_CHAR == type && 1 == rank)
        {
          if ((ptr = (char *)malloc(dims[0] * sizeof(char))) == NULL)
            throw std::runtime_error("tinf_problem_value: allocation error");
          value(key, (const void *)ptr, rank, dims);
          val = std::string(ptr);
          free(ptr);
          return true;
        }
      }
    }
    catch (std::runtime_error e)
    {
      throw;
    }
    return false;
  }

  /**
   * Retrieve a string value for a key if they are defined
   * in the problem description.
   *
   * @param key  Variable key
   * @param val  Pointer to string
   * @param len  Length of @p val
   * @returns true if key/value defined as char*
   * @throws std::runtime_error
   **/
  inline virtual bool
  value(const char *key, std::vector<std::string>& val)
  {
    enum TINF_DATA_TYPE type;
    int32_t rank;
    size_t dims[TINF_PROBLEM_MAX_RANK];
    char* data;
    char* ptr;
    try
    {
      if (defined(key, &type, &rank, dims))
      {
        if (TINF_CHAR == type && 2 == rank)
        {
          if ((data = (char *)malloc(dims[0] * dims[1] * sizeof(char))) == NULL)
            throw std::runtime_error("tinf_problem_value: allocation error");

          value(key, (const void *)data, rank, dims);

          if ((ptr = (char *)malloc(dims[1] * sizeof(char))) == NULL)
            throw std::runtime_error("tinf_problem_value: allocation error");

          for (int i=0; i<dims[0]; ++i) {
            for (int j=0; j<dims[1]; ++j)
              ptr[j] = data[i+j*dims[0]];
            val.push_back(std::string(ptr));
          }
          free(ptr);
          free(data);
          return true;
        }
      }
    }
    catch (std::runtime_error e)
    {
      throw;
    }
    return false;
  }

  /**
   * Retrieve an array of bool values for a key if they are defined
   * in the problem description.
   *
   * @param key  Variable key
   * @param val  Pointer to bool*
   * @param len  Length of @p val
   * @returns true if key/value defined as bool*
   * @throws std::runtime_error
   **/
  inline virtual bool
  value(const char *key, bool **val, size_t *len)
  {
    enum TINF_DATA_TYPE type;
    int32_t rank;
    size_t dims[TINF_PROBLEM_MAX_RANK];
    bool *ptr;
    try
    {
      if (defined(key, &type, &rank, dims))
      {
        if (TINF_BOOL == type && 1 == rank)
        {
          if ((ptr = (bool *)malloc(dims[0] * sizeof(bool))) == NULL)
            throw std::runtime_error("tinf_problem_value: allocation error");
          *len = dims[0];
          value(key, (const void *)ptr, rank, dims);
          *val = ptr;
          return true;
        }
      }
    }
    catch (std::runtime_error e)
    {
      throw;
    }
    return false;
  }

  /**
   * Retrieve an std::vector of bool values for a key if they are defined
   * in the problem description.
   *
   * @param key  Variable key
   * @param val  Vector to hold values
   * @returns true if key/value defined as bool*
   * @throws std::runtime_error
   **/
  inline virtual bool
  value(const char *key, std::vector<bool>& val)
  {
    enum TINF_DATA_TYPE type;
    int32_t rank;
    size_t dims[TINF_PROBLEM_MAX_RANK];
    bool* ptr;
    try
    {
      if (defined(key, &type, &rank, dims))
      {
        if (TINF_BOOL == type && 1 == rank)
        {
          val.reserve(dims[0]);
          if ((ptr = (bool *)malloc(dims[0] * sizeof(bool))) == NULL)
            throw std::runtime_error("tinf_problem_value: allocation error");
          value(key, (const void *)ptr, rank, dims);
          for( int i=0; i<dims[0]; ++i )
            val.push_back(ptr[i]);
          free(ptr);
          return true;
        }
      }
    }
    catch (std::runtime_error e)
    {
      throw;
    }
    return false;
  }

  /**
   * Set a scalar value for a key if it is defined in the
   * problem description.
   *
   * @param key  Variable key
   * @param val  Pointer to typename T
   * @returns true if key/value defined
   * @throws std::runtime_error
   **/
  template <typename T>
  inline bool
  set_value(const char *key, const T val)
  {
    enum TINF_DATA_TYPE type;
    enum TINF_DATA_TYPE template_type;
    int32_t rank;
    size_t dims[TINF_PROBLEM_MAX_RANK];
    if( TINF_SUCCESS != tinf_type<T>(template_type) )
      return false;
    try
    {
      if (defined(key, &type, &rank, dims))
      {
        if (template_type == type && 0 == rank)
        {
          set_value(key, (const void *)&val, rank, dims);
          return true;
        }
      }
    }
    catch (std::runtime_error e)
    {
      throw;
    }
    return false;
  }

  /**
   * Set a dimensioned value for a key if it is defined in the
   * problem description.
   *
   * @param key  Variable key
   * @param val  Pointer to typename T
   * @param dim  Dimensions of @p val
   * @returns true if key/value defined
   * @throws std::runtime_error
   **/
  template <typename T>
  inline bool
  set_value(const char *key, const T *val, const size_t dim)
  {
    enum TINF_DATA_TYPE type;
    enum TINF_DATA_TYPE template_type;
    int32_t rank;
    size_t dims[TINF_PROBLEM_MAX_RANK];
    if( TINF_SUCCESS != tinf_type<T>(template_type) )
      return false;
    try
    {
      if (defined(key, &type, &rank, dims))
      {
        if (template_type == type && 1 == rank)
        {
          dims[0] = dim;
          set_value(key, (const void *)val, rank, dims);
          return true;
        }
      }
    }
    catch (std::runtime_error e)
    {
      throw;
    }
    return false;
  }

  /**
   * Set a dimensioned value for a key if it is defined in the
   * problem description.
   *
   * @param key  Variable key
   * @param val  Pointer to typename T
   * @param dim  Dimensions of @p val
   * @returns true if key/value defined
   * @throws std::runtime_error
   **/
  template <typename T>
  inline bool
  set_value(const char *key, const T **val,
            const size_t dims[TINF_PROBLEM_MAX_RANK])
  {
    enum TINF_DATA_TYPE type;
    enum TINF_DATA_TYPE template_type;
    int32_t rank;
    size_t dims_[TINF_PROBLEM_MAX_RANK];
    if( TINF_SUCCESS != tinf_type<T>(template_type) )
      return false;
    try
    {
      if (defined(key, &type, &rank, dims_))
      {
        if (template_type == type && 1 == rank)
        {
          set_value(key, (const void *)&val, rank, dims);
          return true;
        }
      }
    }
    catch (std::runtime_error e)
    {
      throw;
    }
    return false;
  }

private:
  void *problem;
};
} // namespace pancake

#endif
