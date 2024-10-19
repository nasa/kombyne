#pragma once
#ifndef TINF_DEVICE_H
#define TINF_DEVICE_H

#ifndef __TINF_HOST__
#if defined(__NVCC__) && defined(CUDART_DEVICE)
  #define __TINF_HOST__ __host__
#elif defined(__HIP__)
  #define __TINF_HOST__ __host__
#elif defined(SYCL_LANGUAGE_VERSION)
  #define __TINF_HOST__
#else
  #define __TINF_HOST__
#endif
#endif

#ifndef __TINF_DEVICE__
#if defined(__NVCC__) && defined(CUDART_DEVICE)
  #define __TINF_DEVICE__ CUDART_DEVICE
#elif defined(__HIP__)
  #define __TINF_DEVICE__ __device__
#elif defined(SYCL_LANGUAGE_VERSION)
  #define __TINF_DEVICE__
#else
  #define __TINF_DEVICE__
#endif
#endif

#ifndef __TINF_HOST_DEVICE__
#if defined(__NVCC__) && defined(CUDART_DEVICE)
  #define __TINF_HOST_DEVICE__ __host__ CUDART_DEVICE
#elif defined(__HIP__)
  #define __TINF_HOST_DEVICE__ __host__ __device__
#elif defined(SYCL_LANGUAGE_VERSION)
  #define __TINF_HOST_DEVICE__
#else
  #define __TINF_HOST_DEVICE__
#endif
#endif

#endif
