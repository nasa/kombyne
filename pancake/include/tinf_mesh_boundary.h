/**
 * @subsection mesh_boundary_interface Mesh Boundary Filter Interface
 *
 * Implements the mesh interface.
 * Face windings follow CGNS ordering.  All indices (for nodes, elements,
 * partitions) follow C-indexing.
 * Error codes are indicate TINF_SUCCESS or TINF_FAILURE.
 **/
#pragma once
#ifndef TINF_MESH_BOUNDARY_H
#define TINF_MESH_BOUNDARY_H

#include <stdlib.h>

#include "tinf_enum_definitions.h"

#ifdef __cplusplus
#define _BOOL_ bool
#else
#define _BOOL_ _Bool
#endif

#ifdef __cplusplus
extern "C" {
#endif

    typedef int32_t (*tinf_mesh_boundary_tag_list_create_f)(void** list, void* const problem, void* const mesh, void* const comm);
    typedef int64_t (*tinf_mesh_boundary_tag_list_count_f)(void* const list, int32_t* error);
    typedef int32_t (*tinf_mesh_boundary_tag_list_get_f)(void* const list, void*const tags[]);
    typedef int64_t (*tinf_mesh_boundary_tag_flag_count_f)(void* const tag, int32_t* error);
    typedef int32_t (*tinf_mesh_boundary_tag_flags_f)(void* const tag, int64_t* flags);
    typedef int64_t (*tinf_mesh_boundary_tag_index_f)(void* const tag, int32_t* error);
    typedef int64_t (*tinf_mesh_boundary_tag_code_f)(void* const tag, int32_t* error);
    typedef size_t  (*tinf_mesh_boundary_tag_family_len_f)(void* const tag, int32_t* error);
    typedef int32_t (*tinf_mesh_boundary_tag_family_f)(void* const tag, char* family, size_t family_len);
    typedef int32_t (*tinf_mesh_boundary_tag_list_destroy_f)(void** list);

    typedef int32_t (*tinf_mesh_boundary_create_f)(void** boundary, void* const problem, void* const mesh, void* const comm, void* const tag);
    typedef int32_t (*tinf_mesh_boundary_destroy_f)(void** boundary);
    typedef int32_t (*tinf_mesh_boundary_nodes_f)(void* const boundary, int64_t start, int64_t cnt, int64_t* const nodes);
    typedef size_t  (*tinf_mesh_boundary_family_len_f)(void* const boundary, int32_t* error);
    typedef int32_t (*tinf_mesh_boundary_family_f)(void* const boundary, char* const family, size_t family_len);
    typedef int64_t (*tinf_mesh_boundary_condition_f)(void* const boundary, int32_t* error);
    typedef int64_t (*tinf_mesh_boundary_parent_cell_f)(void* const boundary, int64_t element, int32_t* error);


    /**
     * Create a boundary tag list object for a given mesh.
     *
     * @param list  Opaque boundary tag list pointer
     * @param problem  Opaque problem defintion pointer
     * @param mesh  Opaque mesh pointer
     * @param comm  Opaque communications pointer
     * @returns  Error code
     **/
    int32_t tinf_mesh_boundary_tag_list_create(void** list, void* const problem,
                                               void* const mesh,
                                               void* const comm);


    /**
     * Return the number of unique boundary tags in the tag list.
     *
     * @param list  Opaque boundary tag list pointer
     * @param error  Error code
     * @returns  The number of unique boundary tags
     **/
    int64_t tinf_mesh_boundary_tag_list_count(void* const list, int32_t* error);


    /**
     * Retrieve the list of unique boundary tag objects.
     *
     * @param list  Opaque boundary tag list pointer
     * @param tags  List of unique boundary tag pointers
     * @returns  Error code
     **/
    int32_t tinf_mesh_boundary_tag_list_get(void* const list,
                                            void* const tags[]);


    /**
     * Return the number of boundary tag flags in the tag.
     *
     * @param tag  Opaque boundary tag pointer
     * @param error  Error code
     * @returns  The number of boundary tag flags
     **/
    int64_t tinf_mesh_boundary_tag_flag_count(void* const tag, int32_t* error);


    /**
     * Retrieve the list of boundary tag flags.
     *
     * @param tag  Opaque boundary tag pointer
     * @param flags  List of boundary tag flags
     * @returns  Error code
     **/
    int32_t tinf_mesh_boundary_tag_flags(void* const tag, int64_t flags[]);

    /**
     * Retrieve the boundary tag index.
     *
     * @param tag  Opaque boundary tag pointer
     * @param error  Error code
     * @returns  Boundary tag index
     **/
    int64_t tinf_mesh_boundary_tag_index(void* const tag, int32_t* error);


    /**
     * Retrieve the boundary tag code (boundary condition).
     *
     * @param tag  Opaque boundary tag pointer
     * @param error  Error code
     * @returns  Boundary tag code
     **/
    int64_t tinf_mesh_boundary_tag_code(void* const tag, int32_t* error);


    /**
     * Retrieve the boundary tag family name length.
     *
     * @param tag  Opaque boundary tag pointer
     * @param error  Error code
     * @returns  Boundary tag family name length
     **/
    size_t tinf_mesh_boundary_tag_family_len(void* const tag, int32_t* error);


    /**
     * Retrieve the boundary tag family name.
     *
     * @param tag  Opaque boundary tag pointer
     * @param family  Storage to hold family name
     * @param family_len  Maximum length of family name
     * @returns  Error code
     **/
    int32_t tinf_mesh_boundary_tag_family(void* const tag, char* family,
                                          size_t family_len);


    /**
     * Destroy a tag list object.
     *
     * @param list  Opaque boundary tag list pointer
     * @returns  Error code
     **/
    int32_t tinf_mesh_boundary_tag_list_destroy(void** list);


    /**
     * Create a boundary object for a given tag in the mesh.
     *
     * @param boundary  Opaque boundary pointer
     * @param problem  Opaque problem defintion pointer
     * @param mesh  Opaque mesh pointer
     * @param comm  Opaque communications pointer
     * @param tag  Target boundary tag
     * @returns  Error code
     **/
    int32_t tinf_mesh_boundary_create(void** boundary, void* const problem,
                                      void* const mesh, void* const comm,
                                      void* const tag);


    /**
     * Destroy a boundary object.
     *
     * @param boundary  Opaque boundary pointer
     * @returns  Error code
     **/
    int32_t tinf_mesh_boundary_destroy(void** boundary);


    /**
     * Return the local indicies of the boundary nodes in the boundary.
     *
     * @param boundary  Opaque boundary pointer
     * @param start  Starting local node identifier (bias 0)
     * @param cnt  Number of boundary nodes to retrieve
     * @param nodes  Local indicies for boundary (bias 0)
     * @returns  Error code
     **/
    int32_t tinf_mesh_boundary_nodes(void* const boundary,
                                     int64_t start, int64_t cnt,
                                     int64_t* nodes);


    /**
     * Retrieve the boundary family name length.
     *
     * @param boundary  Opaque boundary pointer
     * @param error  Error code
     * @returns  Boundary family name length
     **/
    size_t tinf_mesh_boundary_family_len(void* const boundary, int32_t* error);


    /**
     * Retrieve the family name associated with the boundary.
     *
     * @param boundary  Opaque boundary pointer
     * @param family  Name of the boundary family
     * @param family_len  Maximum length of family name
     * @returns  Error code
     **/
    int32_t tinf_mesh_boundary_family(void* const boundary, char* const family,
                                      size_t family_len);


    /**
     * Return the boundary condition for the boundary.
     *
     * @param boundary  Opaque boundary pointer
     * @param error  Error code
     * @returns  Boundary condition identifier for the boundary
     **/
    int64_t tinf_mesh_boundary_condition(void* const boundary, int32_t* error);


    /**
     * Return the parent cell index of the boundary face.
     *
     * @param boundary  Opaque boundary pointer
     * @param element  Boundary element for which parent is sought
     * @param error  Error code
     * @returns  Global index of parent cell
     **/
    int64_t tinf_mesh_boundary_parent_cell(void* const boundary, int64_t element, int32_t* error);


#ifdef __cplusplus
}
#endif

#endif
