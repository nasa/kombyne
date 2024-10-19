#pragma once
#ifndef TINF_MESH_FILTER_H
#define TINF_MESH_FILTER_H

#include <stdlib.h>

#include "tinf_mesh.h"

#ifdef __cplusplus
extern "C"
{
#endif

  typedef int32_t (*tinf_mesh_transform_create_f)(void **mesh, void *problem,
                                                  void *mesh_in, void *comm);
  typedef int32_t (*tinf_mesh_transform_destroy_f)(void **mesh);

  /**
   * Create a mesh transform that implements the mesh interface.
   *
   * @param mesh  The generated mesh transform object
   * @param problem  A problem description object
   * @param mesh_in  A base mesh object to transform
   * @param comm  A communications object
   * @returns  Error code
   **/
  int32_t
  tinf_mesh_transform_create(void **mesh, void *problem, void *mesh_in,
                             void *comm);

  /**
   * Destroy a mesh transform.
   *
   * @param mesh  Target mesh transform object
   * @returns  Error code
   **/
  int32_t
  tinf_mesh_transform_destroy(void **mesh);

#ifdef __cplusplus
}
#endif

#endif
