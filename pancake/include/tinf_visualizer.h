#pragma once
#ifndef TINF_VISUALIZER_H
#define TINF_VISUALIZER_H

#include <stdlib.h>

#include "tinf_enum_definitions.h"

#ifdef __cplusplus
#define _BOOL_ bool
#else
#define _BOOL_ _Bool
#endif

#ifdef __cplusplus
extern "C"
{
#endif
typedef int32_t (*tinf_visualizer_create_f)(void **vis, void *problem,
                                            void *tinf_mesh, void *solution,
                                            void *iris_comm);
typedef int32_t (*tinf_visualizer_destroy_f)(void **vis);
typedef int32_t (*tinf_visualizer_f)(void *vis, _BOOL_ final_call);

/**
 * Constructor for a visualization from a pair of mesh and solution objects.
 *
 * @param vis  Opaque visualization plugin pointer
 * @param problem  Opaque problem pointer
 * @param mesh  Opaque mesh pointer
 * @param solution  Opaque solution pointer
 * @param iris_comm  Iris communications opaque pointer
 * @returns Error code
 **/
int32_t
tinf_visualizer_create(void **vis, void *problem, void *mesh,
                       void *solution, void *iris_comm);

/**
 * Destructor.
 *
 * @param vis  Opaque visualization plugin pointer
 * @returns Error code
 **/
int32_t
tinf_visualizer_destroy(void **vis);

/**
 * Execute the visualization
 *
 * @param vis  Opaque visualization plugin pointer
 * @param final_call  whether this is a call during the simulation or at the end
 * @returns Error code
 **/
int32_t
tinf_visualizer(void *vis, _BOOL_ final_call);

#ifdef __cplusplus
}
#endif

#endif
