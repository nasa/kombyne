#pragma once
#ifndef TINF_GEOM_H
#define TINF_GEOM_H

#include <stdlib.h>

#include "tinf_enum_definitions.h"
#include "tinf_device.h"

#ifdef __cplusplus
extern "C" {
#endif

    typedef int32_t (*tinf_geom_create_f)(void**, void* const, void* const);
    typedef int32_t (*tinf_geom_destroy_f)(void**);
    typedef void* (*tinf_geom_device_f)(void* const, int32_t*);
    typedef int64_t (*tinf_geom_num_bodies_f)(void* const, int32_t*);
    typedef void* (*tinf_geom_body_f)(void* const, int64_t, int32_t*);
    typedef enum TINF_GEOM_BODY_TYPE (*tinf_geom_body_type_f)(void* const, void* const, int32_t*);
    typedef int64_t (*tinf_geom_index_in_body_f)(void* const, void* const, void* const, int32_t*);
    typedef int64_t (*tinf_geom_num_shells_f)(void* const, void* const, int32_t*);
    typedef int64_t (*tinf_geom_num_faces_f)(void* const, void* const, int32_t*);
    typedef int64_t (*tinf_geom_num_loops_f)(void* const, void* const, int32_t*);
    typedef int64_t (*tinf_geom_num_edges_f)(void* const, void* const, int32_t*);
    typedef int64_t (*tinf_geom_num_nodes_f)(void* const, void* const, int32_t*);
    typedef void* (*tinf_geom_shell_f)(void* const, void* const, int64_t, int32_t*);
    typedef int32_t (*tinf_geom_shell_data_f)(void* const, void* const, int32_t*, int64_t*, void***);
    typedef void* (*tinf_geom_face_f)(void* const, void* const, int64_t, int32_t*);
    typedef int32_t (*tinf_geom_face_data_f)(void* const, void* const, double[], int32_t*, int64_t*, void***);
    typedef void* (*tinf_geom_loop_f)(void* const, void* const, int64_t, int32_t*);
    typedef int32_t (*tinf_geom_loop_data_f)(void* const, void* const, int32_t*, int64_t*, void***, int32_t**);
    typedef void* (*tinf_geom_edge_f)(void* const, void* const, int64_t, int32_t*);
    typedef int32_t (*tinf_geom_edge_data_f)(void* const, void* const, double[], int32_t*, int64_t*, void***);
    typedef void* (*tinf_geom_node_f)(void* const, void* const, int64_t, int32_t*);
    typedef int32_t (*tinf_geom_node_data_f)(void* const, void* const, double*, double*, double*);
    typedef enum TINF_ERROR_CODES (*tinf_geom_in_f)(void* const, void* const, double, double, double);
    typedef enum TINF_ERROR_CODES (*tinf_geom_in_face_f)(void* const, void* const, double, double);
    typedef int32_t (*tinf_geom_range_f)(void* const, void* const, double [], enum TINF_GEOM_PERIODIC_TYPE*);
    typedef int32_t (*tinf_geom_bbox_f)(void* const, void* const, double [6]);
    typedef double (*tinf_geom_length_f)(void* const, void* const, double, double, int32_t*);
    typedef int32_t (*tinf_geom_curv_f)(void* const, void* const, double [], double [], double[]);
    typedef int32_t (*tinf_geom_eval_f)(void* const, void* const, double [], double*, double*, double*, double []);
    typedef int32_t (*tinf_geom_nearest_f)(void* const, void* const, double, double, double, double [], double*, double*, double*);
    typedef int64_t (*tinf_geom_num_attributes_f)(void* const, void* const, int32_t*);
    typedef int32_t (*tinf_geom_attribute_f)(void* const, void* const, int64_t, const char**, int32_t*, int64_t*, void**);
    typedef int32_t (*tinf_geom_attribute_by_name_f)(void* const, void* const, const char*, int32_t*, int64_t*, void**);

    /**
     * @subsection geom_interface Geometry Interface
     **/

    /**
     * Constructor.
     *
     * @param model  Opaque geometry model pointer
     * @param problem_definition  Context defining the problem
     * @param iris_comm  Iris communications opaque pointer
     * @returns  Error code
     */
    __TINF_HOST_DEVICE__
    int32_t tinf_geom_create(void** model, void* const problem,
                             void* const comm);

    /**
     * Destructor.
     *
     * @param model  Opaque geometry model pointer
     * @returns  Error code
     */
    __TINF_HOST_DEVICE__
    int32_t tinf_geom_destroy(void** model);


    /**
     * Return the device pointer for the  model.
     *
     * @param model  Opaque geometry model pointer
     * @param error  Error code
     * @returns  Opaque geometry model device pointer
     */
    __TINF_HOST_DEVICE__
    void* tinf_geom_device(void* const model, int32_t* error);


    /**
     * Return the number of bodies in a model.
     *
     * @param model  Opaque geometry model pointer
     * @param error  Error code
     * @returns  Number of bodies in the model
     */
    __TINF_DEVICE__
    int64_t tinf_geom_num_bodies(void* const model, int32_t* error);

    /**
     * Return an opaque body pointer from a model.
     *
     * @param model  Opaque geometry model pointer
     * @param index  Body number (bias-0)
     * @param error  Error code
     * @returns  Opaque body pointer
     */
    __TINF_DEVICE__
    void* tinf_geom_body(void* const model, int64_t index, int32_t* error);

    /**
     * Retrieve data about the body topological size.
     *
     * @param model  Opaque geometry model pointer
     * @param body  Opaque geometric body pointer
     * @param error  Error code
     * @returns  Body type (one of @ref TINF_GEOM_BODY_TYPE)
     */
    __TINF_DEVICE__
    enum TINF_GEOM_BODY_TYPE tinf_geom_body_type(void* const model,
                                                 void* const body,
                                                 int32_t* error);

    /**
     * Retrieve number of shells in a geometry object.
     *
     * @param model  Opaque geometry model pointer
     * @param body  Opaque body pointer (@ref TINF_GEOM_BODY)
     * @param geom  Opaque geometry pointer
     * @param error  Error code
     * @returns  Index in the body of @p geom (bias-0)
     */
    __TINF_DEVICE__
    int64_t tinf_geom_index_in_body(void* const model, void* const body,
                                    void* const geom, int32_t* error);

    /**
     * Retrieve number of shells in a geometry object.
     *
     * @param model  Opaque geometry model pointer
     * @param geom  Opaque geometry pointer (@ref TINF_GEOM_BODY)
     * @param error  Error code
     * @returns  Number of shells
     */
    __TINF_DEVICE__
    int64_t tinf_geom_num_shells(void* const model, void* const geom,
                                 int32_t* error);

    /**
     * Retrieve number of faces in a geometry object.
     *
     * @param model  Opaque geometry model pointer
     * @param geom  Opaque geometry pointer (@ref TINF_GEOM_BODY or
                    @ref TINF_GEOM_SHELL)
     * @param error  Error code
     * @returns  Number of faces
     */
    __TINF_DEVICE__
    int64_t tinf_geom_num_faces(void* const model, void* const geom,
                                int32_t* error);

    /**
     * Retrieve number of loops in a geometry object.
     *
     * @param model  Opaque geometry model pointer
     * @param geom  Opaque geometry pointer (@ref TINF_GEOM_BODY or
                    @ref TINF_GEOM_FACE)
     * @param error  Error code
     * @returns  Number of loops
     */
    __TINF_DEVICE__
    int64_t tinf_geom_num_loops(void* const model, void* const geom,
                                int32_t* error);

    /**
     * Retrieve number of edges in a geometry object.
     *
     * @param model  Opaque geometry model pointer
     * @param geom  Opaque geometry pointer (@ref TINF_GEOM_BODY or
                    @ref TINF_GEOM_LOOP)
     * @param error  Error code
     * @returns  Number of edges
     */
    __TINF_DEVICE__
    int64_t tinf_geom_num_edges(void* const model, void* const geom,
                                int32_t* error);

    /**
     * Retrieve number of nodes in a geometry object.
     *
     * @param model  Opaque geometry model pointer
     * @param geom  Opaque geometry pointer (@ref TINF_GEOM_BODY or
                    @ref TINF_GEOM_EDGE)
     * @param error  Error code
     * @returns  Number of nodes
     */
    __TINF_DEVICE__
    int64_t tinf_geom_num_nodes(void* const model, void* const geom,
                                int32_t* error);

    /**
     * Return an opaque shell pointer from a body object.
     *
     * @param model  Opaque geometry model pointer
     * @param body  Opaque geometric body pointer
     * @param index  Shell number relative to @p geom (bias-0)
     * @param error  Error code
     * @returns  Opaque shell pointer
     */
    __TINF_DEVICE__
    void* tinf_geom_shell(void* const model, void* const body,
                          int64_t index, int32_t* error);

    /**
     * Return data about shell pointer from a geometry object.
     *
     * @param model  Opaque geometry model pointer
     * @param shell  Opaque geometry pointer (@ref TINF_GEOM_SHELL)
     * @param closed  Indicates if shell is closed (0 -> open, 1 -> closed)
     * @param nface  Number of faces bounding the shell
     * @param faces  Array of opaque face pointers
     * @returns  Error code
     */
    __TINF_DEVICE__
    int32_t tinf_geom_shell_data(void* const model, void* const shell,
                                 int32_t* closed, int64_t* nface,
                                 void*** faces);

    /**
     * Return an opaque face pointer from a geometry object.
     *
     * @param model  Opaque geometry model pointer
     * @param geom  Opaque geometry pointer (@ref TINF_GEOM_BODY or @ref TINF_GEOM_SHELL)
     * @param index  Face number relative to @p geom (bias-0)
     * @param error  Error code
     * @returns  Opaque face pointer
     */
    __TINF_DEVICE__
    void* tinf_geom_face(void* const model, void* const geom,
                         int64_t index, int32_t* error);

    /**
     * Return data about face pointer from a geometry object.
     *
     * @param model  Opaque geometry model pointer
     * @param face  Opaque geometry pointer (@ref TINF_GEOM_FACE)
     * @param uv  Parameter range of geometry (umin,umax,vmin,vmax)
     * @param sense  Orientation of face to unerlying geometry (-1 or +1)
     * @param nloop  Number of loops bounding the face
     * @param loops  Array of opaque loop pointers
     * @returns  Error code
     */
    __TINF_DEVICE__
    int32_t tinf_geom_face_data(void* const model, void* const face,
                                double uv[4], int32_t* sense, int64_t* nloop,
                                void*** loops);

    /**
     * Return an opaque loop pointer from a geometry object.
     *
     * @param model  Opaque geometry model pointer
     * @param geom  Opaque geometry pointer (@ref TINF_GEOM_BODY or @ref TINF_GEOM_FACE)
     * @param index  Loop number relative to @p geom (bias-0)
     * @param error  Error code
     * @returns  Opaque loop pointer
     */
    __TINF_DEVICE__
    void* tinf_geom_loop(void* const model, void* const geom,
                         int64_t index, int32_t* error);

    /**
     * Return data about loop pointer from a geometry object.
     *
     * @param model  Opaque geometry model pointer
     * @param loop  Opaque geometry pointer (@ref TINF_GEOM_LOOP)
     * @param closed  Indicates if loop is closed (0 -> open, 1 -> closed)
     * @param nedge  Number of edges defining the loop
     * @param edges  Array of opaque edge pointers
     * @param orients  Array of edge orientation in loop (+1 or -1)
     * @returns  Error code
     */
    __TINF_DEVICE__
    int32_t tinf_geom_loop_data(void* const model, void* const loop,
                                int32_t* closed, int64_t* nedge,
                                void*** edges, int32_t** orients);

    /**
     * Return an opaque edge pointer from a geometry object.
     *
     * @param model  Opaque geometry model pointer
     * @param geom  Opaque geometry pointer (@ref TINF_GEOM_BODY or @ref TINF_GEOM_LOOP)
     * @param index  Edge number relative to @p geom (bias-0)
     * @param error  Error code
     * @returns  Opaque edge pointer
     */
    __TINF_DEVICE__
    void* tinf_geom_edge(void* const model, void* const geom,
                         int64_t index, int32_t* error);

    /**
     * Return data about edge pointer from a geometry object.
     *
     * @param model  Opaque geometry model pointer
     * @param edge  Opaque geometry pointer (@ref TINF_GEOM_EDGE)
     * @param t  Parametric bounds of edge (tmin, tmax)
     * @param degenerate  Indicates if edge is degenerate (1 -> degenerate)
     * @param nnode  Number of nodes bounding the edge
     * @param nodes  Array of opaque node pointers
     * @returns  Error code
     */
    __TINF_DEVICE__
    int32_t tinf_geom_edge_data(void* const model, void* const edge,
                                double t[2], int32_t* degenerate,
                                int64_t* nnode, void*** nodes);

    /**
     * Return an opaque node pointer from a geometry object.
     *
     * @param model  Opaque geometry model pointer
     * @param geom  Opaque geometry pointer (@ref TINF_GEOM_BODY or @ref TINF_GEOM_EDGE)
     * @param index  Node number relative to @p geom (bias-0)
     * @param error  Error code
     * @returns  Opaque node pointer
     */
    __TINF_DEVICE__
    void* tinf_geom_node(void* const model, void* const geom,
                         int64_t index, int32_t* error);

    /**
     * Return data about node pointer from a geometry object.
     *
     * @param model  Opaque geometry model pointer
     * @param node  Opaque geometry pointer (@ref TINF_GEOM_NODE)
     * @param x  X coordinate of the node
     * @param y  Y coordinate of the node
     * @param z  Z coordinate of the node
     * @returns  Error code
     */
    __TINF_DEVICE__
    int32_t tinf_geom_node_data(void* const model, void* const node,
                                double* x, double* y, double* z);

    /**
     * Determine if point evaluates within the bounds of a geometry object.
     *
     * @param model  Opaque geometry model pointer
     * @param geom  Opaque geometry pointer
     * @param x  X coordinate of point
     * @param y  Y coordinate of point
     * @param z  Z coordinate of point
     * @returns @ref TINF_SUCCESS if in, @ref TINF_FINISHED evaluated but outside
     */
    __TINF_DEVICE__
    enum TINF_ERROR_CODES tinf_geom_in(void* const model, void* const geom,
                                       double x, double y, double z);

    /**
     * Determine if parameters are within the valid part of a face.
     *
     * @param model  Opaque geometry model pointer
     * @param face  Opaque face pointer
     * @param u  U parameter to check
     * @param v  V parameter to check
     * @returns @ref TINF_SUCCESS if in, @ref TINF_FINISHED evaluated but outside
     */
    __TINF_DEVICE__
    enum TINF_ERROR_CODES tinf_geom_in_face(void* const model, void* const face,
                                            double u, double v);

    /**
     * Return the parameter range of a geometry object.
     *
     * @param model  Opaque geometry model pointer
     * @param geom  Opaque geometry pointer (@ref TINF_GEOM_EDGE or
     *              @ref TINF_GEOM_FACE)
     * @param param  Parameter range of geometry
     * @param periodic  Type of periodicity
     * @returns  Error code
     */
    __TINF_DEVICE__
    int32_t tinf_geom_range(void* const model, void* const geom, double param[],
                            enum TINF_GEOM_PERIODIC_TYPE* periodic);

    /**
     * Return the Cartesian bounding of a geometry object.
     *
     * @param model  Opaque geometry model pointer
     * @param geom  Opaque geometry pointer
     * @param bbox  Cartesian bounding box
     * @returns  Error code
     */
    __TINF_DEVICE__
    int32_t tinf_geom_bbox(void* const model, void* const geom, double bbox[6]);

    /**
     * Return the arclength of an edge object.
     *
     * @param model  Opaque geometry model pointer
     * @param edge  Opaque edge pointer
     * @param t0  Starting parameter along edge
     * @param t1  Ending parameter along edge
     * @param error  Error code
     * @returns Arclength of the edge between @p t0 and @p t1
     */
    __TINF_DEVICE__
    double tinf_geom_length(void* const model, void* const edge,
                            double t0, double t1, int32_t* error);

    /**
     * Return the curvature of a geometry object.
     *
     * @param model  Opaque geometry model pointer
     * @param geom  Opaque geometry pointer (@ref TINF_GEOM_EDGE or
     *              @ref TINF_GEOM_FACE)
     * @param param  Parametric coordinates to evaluate curvature
     * @param curv  Curvature(s) of the object
     * @param dir  Curvature direction vector(s) of the object
     * @returns  Error code
     */
    __TINF_DEVICE__
    int32_t tinf_geom_curv(void* const model, void* const geom,
                           double param[], double curv[], double dir[]);

    /**
     * Evaluate a geometry object at a given parameteric coordinate.
     *
     * @param model  Opaque geometry model pointer
     * @param geom  Opaque geometry pointer (@ref TINF_GEOM_EDGE or
     *              @ref TINF_GEOM_FACE)
     * @param param  Parametric coordinate(s) to evaluate
     * @param x  X coordinate on geometry
     * @param y  Y coordinate on geometry
     * @param z  Z coordinate on geometry
     * @param der  First and second derivatives of coordinate with respect
                   to parameter(s). For an edge, there are two derivative
                   vectors (first and second derivatives).  For a face, there
                   are 5 (first, second, and mixed derivatives). Maximum of
                   15 values.
     * @returns  Error code
     */
    __TINF_DEVICE__
    int32_t tinf_geom_eval(void* const model, void* const geom,
                           double param[], double* x, double* y, double* z,
                           double der[]);

    /**
     * Determine the nearest point on a geometry object from a given point
     * (projection/inverse evaluation).
     *
     * @param model  Opaque geometry model pointer
     * @param geom  Opaque geometry pointer (@ref TINF_GEOM_EDGE or
     *              @ref TINF_GEOM_FACE)
     * @param x  X coordinate
     * @param y  Y coordinate
     * @param z  Z coordinate
     * @param param  Parametric coordinate(s). The input values may be used as
     *               an initial guess for the solution (e.g. periodic surfaces).
     *               On output, corresponds to the solution in @p xg, @p yg,
                     @p zg.
     * @param xg  Closest X coordinate on geometry
     * @param yg  Closest Y coordinate on geometry
     * @param zg  Closest Z coordinate on geometry
     * @returns  Error code
     */
    __TINF_DEVICE__
    int32_t tinf_geom_nearest(void* const model, void* const geom,
                              double x, double y, double z,
                              double param[], double* xg, double* yg,
                              double* zg);

    /**
     * Return the number of attributes assigned to a geometry object.
     *
     * @param model  Opaque geometry model pointer
     * @param geom  Opaque geometry pointer
     * @param error  Error code
     * @returns  Number of assigned attributes
     */
    __TINF_DEVICE__
    int64_t tinf_geom_num_attributes(void* const model, void* const geom,
                                     int32_t* error);

    /**
     * Return the number of attributes assigned to a geometry object.
     *
     * @param model  Opaque geometry model pointer
     * @param geom  Opaque geometry pointer
     * @param index  Attribute index @p geom (bias-0)
     * @param name  Returned attribute name
     * @param atype  Type of attribute: TINF_INT32, TINF_DOUBLE, TINF_CHAR
     * @param len  Number of values
     * @param attr  Attribute values
     * @returns  Error code
     */
    __TINF_DEVICE__
    int32_t tinf_geom_attribute(void* const model, void* const geom,
                                int64_t index, const char** name,
                                int32_t* atype, int64_t* len,
                                void** attr);

    /**
     * Return the values of a named attribute assigned to a geometry object.
     *
     * @param model  Opaque geometry model pointer
     * @param geom  Opaque geometry pointer
     * @param name  Name of the attribute
     * @param atype  Type of attribute: TINF_INT32, TINF_DOUBLE, TINF_CHAR
     * @param len  Number of values
     * @param attr  Attribute values
     * @returns  Error code
     */
    __TINF_DEVICE__
    int32_t tinf_geom_attribute_by_name(void* const model, void* const geom, 
                                        const char* name, int32_t* atype,
                                        int64_t* len, void** attr);

#ifdef __cplusplus
}
#endif

#endif
