#pragma once
#ifndef TINF_6DOF_H
#define TINF_6DOF_H

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

    typedef int32_t (*tinf_6dof_create_f)(void** sixdof,
                                          void* const problem,
                                          void* const mesh,
                                          void* const solver,
                                          void* const comm);
    typedef int32_t (*tinf_6dof_destroy_f)(void** sixdof);
    typedef int32_t (*tinf_6dof_set_condition_f)(void* sixdof, int32_t body,
                                                 double sim_time,
                                                 double transform[16],
                                                 double cg[3]);
    typedef int32_t (*tinf_6dof_get_condition_f)(void* sixdof, int32_t body,
                                                 double sim_time,
                                                 double transform[16],
                                                 double cg[3]);
    typedef int32_t (*tinf_6dof_set_loads_f)(void* sixdof, int32_t body,
                                             int32_t frame,
                                             double sim_time,
                                             double force[3], double moment[3]);
    typedef int32_t (*tinf_6dof_get_loads_f)(void* sixdof, int32_t body,
                                             int32_t frame,
                                             double sim_time,
                                             double force[3], double moment[3]);


    /**
     * Create an six degree of freedom object.
     *
     * @param sixdof  Opaque 6-DOF pointer
     * @param problem  Opaque problem description pointer
     * @param mesh  Opaque mesh pointer
     * @param solver  Opaque solver pointer
     * @param comm  Opaque Iris pointer
     * @returns  Error code
     **/
    int32_t tinf_6dof_create(void** sixdof,
                             void* const problem,
                             void* const mesh,
                             void* const solver,
                             void* const comm);

    /**
     * Destroy a six degree of freedom object.
     *
     * @param sixdof  Opaque 6-DOF pointer
     * @returns  Error code
     **/
    int32_t tinf_6dof_destroy(void** sixdof);

    /**
     * Set conditions for the six degree of freedom object.
     *
     * @param sixdof  Opaque 6-DOF pointer
     * @param body  Body ID for condition
     * @param sim_time  Simulation time for condition
     * @param transform  Transformation matrix (homogeneous coordinates)
     * @param cg  Center of gravity
     * @returns  Error code
     **/
    int32_t tinf_6dof_set_condition(const void* sixdof, int32_t body,
                                    double sim_time,
                                    double transform[16],
                                    double cg[3]);

    /**
     * Get conditions from the six degree of freedom object at a given
     * time.
     *
     * @param sixdof  Opaque 6-DOF pointer
     * @param body  Body ID for condition
     * @param sim_time  Simulation time for condition
     * @param transform  Transformation matrix (homogeneous coordinates)
     * @param cg  Center of gravity
     * @returns  Error code
     **/
    int32_t tinf_6dof_get_condition(const void* sixdof, int32_t body,
                                    double sim_time,
                                    double transform[16],
                                    double cg[3]);

    /**
     * Set aerodynamic loads for the six degree of freedom object at a given
     * time.
     *
     * @param sixdof  Opaque 6-DOF pointer
     * @param body  Body ID
     * @param frame  Reference frame (0 = inertial, or 1 = body)
     * @param sim_time  Simulation time for loads
     * @param force  Forces
     * @param moment  Moments
     * @returns  Error code
     **/
    int32_t tinf_6dof_set_loads(const void* sixdof, int32_t body, int32_t frame,
                                double sim_time,
                                double force[3], double moment[3]);

    /**
     * Get aerodynamic loads for the six degree of freedom object.
     *
     * @param sixdof  Opaque 6-DOF pointer
     * @param body  Body ID
     * @param frame  Reference frame (0 = inertial, or 1 = body)
     * @param sim_time  Simulation time for loads
     * @param force  Forces
     * @param moment  Moments
     * @returns  Error code
     **/
    int32_t tinf_6dof_get_loads(const void* sixdof, int32_t body, int32_t frame,
                                double sim_time,
                                double force[3], double moment[3]);

#ifdef __cplusplus
}
#endif

#endif
