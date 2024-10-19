#pragma once
#ifndef TINF_KERNEL_H
#define TINF_KERNEL_H

#include <stdlib.h>

#include "tinf_enum_definitions.h"

#ifdef __cplusplus
extern "C" {
#endif

    typedef int32_t (*tinf_kernel_create_f)(void**, void* const,
                                            void* const, void* const,
                                            void* const, void* const);
    typedef int32_t (*tinf_kernel_destroy_f)(void**);
    typedef int32_t (*tinf_kernel_launch_f)(void* const, int32_t, int32_t);

    /**
     * @subsection kernel_interface Device Kernel Interface
     **/

    /**
     * Constructor.
     *
     * @param kernel  Opaque device kernel pointer
     * @param problem  Context defining the problem
     * @param geom  Context defining the geometry
     * @param mesh  Context defining the mesh
     * @param soln  Context defining the solution
     * @param iris_comm  Iris communications opaque pointer
     * @returns  Error code
     */
    int32_t tinf_kernel_create(void** kernel, void* const problem,
                               void* const geom, void* const mesh,
                               void* const soln, void* const comm);

    /**
     * Destructor.
     *
     * @param kernel  Opaque device kernel pointer
     * @returns  Error code
     */
    int32_t tinf_kernel_destroy(void** kernel);


    /**
     * Return the number of bodies in a model.
     *
     * @param kernel  Opaque device kernel pointer
     * @param nb  Number of blocks
     * @param nt  Number of threads
     * @returns  Error code
     */
    int32_t tinf_kernel_launch(void* const kernel, int32_t nb, int32_t nt);

#ifdef __cplusplus
}
#endif

#endif
