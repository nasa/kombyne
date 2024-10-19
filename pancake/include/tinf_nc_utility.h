/**
 * @subsection node_centered_utility Node Centered Utilities
 *
 * Implements the node-centered utiltity library.
 * Cell/Face windings follow FUN3D ordering.  All indices (for nodes, elements,
 * partitions) follow C-indexing.
 * Error codes are indicate TINF_SUCCESS or TINF_FAILURE.
 **/
#pragma once
#ifndef TINF_NC_UTILITY_H
#define TINF_NC_UTILTIY_H

#include <stdlib.h>

#include "tinf_enum_definitions.h"

#ifdef __cplusplus
#define _BOOL_ bool
#else
#define _BOOL_ _Bool
#endif

typedef int32_t c2n_t;
typedef int32_t eptr_t;

#ifdef __cplusplus
extern "C" {
#endif

  typedef int32_t (*tinf_nc_util_create_f)(void** nc, void* const problem,
                                           void* const mesh, void* const comm);
  typedef int32_t (*tinf_nc_util_destroy_f)(void** nc);

  typedef int64_t (*tinf_nc_util_num_global_cells_f)(void* const nc,
                                                     int32_t* error);
  typedef int32_t (*tinf_nc_util_num_elem_f)(void* const nc, int32_t* error);
  typedef int32_t (*tinf_nc_util_edge_counts_f)(void* const nc, int64_t* nedge,
                                                int64_t* nedgeloc);
  typedef int32_t (*tinf_nc_util_edge_data_f)(void* const nc, int64_t* nedgeg,
                                              int32_t* eptr, int64_t* el2g);
  typedef int32_t (*tinf_nc_util_cell_data_f)(void* const nc, int64_t cell,
                                              int32_t* elem, int64_t* ndx);

  typedef int32_t (*tinf_nc_util_element_f)(void* const nc, int32_t index,
                                            void** element);
  typedef int32_t (*tinf_nc_util_element_sizes_f)(void* const nc,
                                                  void* const element,
                                                  int64_t* ncell,
                                                  int64_t* ncellg,
                                                  int32_t* npc, int32_t* epc,
                                                  int32_t* fpc,
                                                  int32_t* face_2d,
                                                  int32_t* type);
  typedef int32_t (*tinf_nc_util_element_e2n_f)(void* const nc,
                                                void* const element,
                                                int32_t* local_e2n);
  typedef int32_t (*tinf_nc_util_element_e2n_2_f)(void* const nc,
                                                  void* const element,
                                                  int32_t* local_e2n_2);
  typedef int32_t (*tinf_nc_util_element_f2n_f)(void* const nc,
                                                void* const element,
                                                int32_t* local_f2n);
  typedef int32_t (*tinf_nc_util_element_check_norm_f)(void* const nc,
                                                       void* const element,
                                                       int32_t* chk_norm);
  typedef int32_t (*tinf_nc_util_element_f2e_f)(void* const nc,
                                                void* const element,
                                                int32_t* f2e);
  typedef int32_t (*tinf_nc_util_element_c2n_f)(void* nc, void* const element,
                                                int32_t* c2n);
  typedef int32_t (*tinf_nc_util_element_c2e_f)(void* const nc,
                                                void* const element,
                                                int32_t* c2e);
  typedef int32_t (*tinf_nc_util_element_l2g_f)(void* const nc,
                                                void* const element,
                                                int64_t* l2g);

  typedef int32_t (*tinf_nc_util_sendrecv_node_sizes_f)(void* const nc,
                                                        int64_t* size1,
                                                        int64_t* size2,
                                                        int64_t* size3);
  typedef int32_t (*tinf_nc_util_sendrecv_edge_sizes_f)(void* const nc,
                                                        int32_t* eptr,
                                                        int64_t* size1,
                                                        int64_t* size2,
                                                        int64_t* size3);
  typedef int32_t (*tinf_nc_util_sendrecv_node_f)(void* const nc,
                                                  int32_t* recvproc,
                                                  int32_t* recvindex,
                                                  int32_t* sendproc,
                                                  int32_t* sendindex);
  typedef int32_t (*tinf_nc_util_sendrecv_edge_f)(void* nc, int32_t* eptr,
                                                  int64_t* el2g,
                                                  int32_t* recvproc,
                                                  int32_t* recvindex,
                                                  int32_t* sendproc,
                                                  int32_t* sendindex);

  /**
   * Create a node-centered utility object for a given mesh.
   *
   * @param nc  Opaque node-centered utility pointer
   * @param problem  Opaque problem pointer
   * @param mesh  Opaque mesh pointer
   * @param comm  Opaque communicator pointer
   * @returns  Error code
   **/
  int32_t tinf_nc_util_create(void** nc, void* const problem, void* const mesh,
                              void* const comm);

  /**
   * Destroy a node-centered utility object.
   *
   * @param nc  Opaque node-centered utility pointer
   * @returns  Error code
   **/
  int32_t tinf_nc_util_destroy(void** nc);

  /**
   * Retrieve the global number cells (3D elements)
   *
   * @param nc  Opaque node-centered utility pointer
   * @param error  Error code
   * @returns  Number of global cells.
   **/
  int64_t tinf_nc_util_num_global_cells(void* const nc, int32_t* error);

  /**
   * Retrieve the number of canonical element types in a mesh.
   *
   * @param nc  Opaque node-centered utility pointer
   * @param error  Error code
   * @returns  Number of canonical element types.
   **/
  int32_t tinf_nc_util_num_elem(void* const nc, int32_t* error);

  /**
   * Retrieve edge counts in the mesh.
   *
   * @param nc  Opaque node-centered utility pointer
   * @param nedge  Number of edges in the mesh
   * @param nedgeloc  Number of local edges in the mesh
   * @returns  Error code
   **/
  int32_t tinf_nc_util_edge_counts(void* const nc, int64_t* nedge,
                                   int64_t* nedgeloc);
  /**
   * Retrieve edge data (number of global edges, edge pointers, and edge
   * local-to-global map.
   *
   * @param nc  Opaque node-centered utility pointer
   * @param nedgeg  Number of global edges
   * @param eptr  Array of edge pointers (2*nedge)
   * @param l2g  Array of edge local-to-global mapping (nedge)
   * @returns  Error code
   **/
  int32_t tinf_nc_util_edge_data(void* const nc, int64_t* nedgeg, int32_t* eptr,
                                 int64_t* el2g);
  /**
   * Retrieve elem data (type and index) of a local cell
   *
   * @param nc  Opaque node-centered utility pointer
   * @param cell  Local cell number
   * @param elem  Element type index
   * @param ndx  Element count of cell
   * @returns  Error code
   **/
  int32_t tinf_nc_util_cell_data(void* const nc, int64_t cell, int32_t* elem,
                                 int64_t* ndx);

  /**
   * Retrieve a canonical element object based on index.
   *
   * @param nc  Opaque node-centered utility pointer
   * @param index  Element index (1:nelem)
   * @param element  Opaque element pointer
   * @returns  Error code
   **/
  int32_t tinf_nc_util_element(void* const nc, int32_t index, void** element);

  /**
   * Retrieve element size information.
   *
   * @param element  Opaque element pointer
   * @param ncell  Number of cells of the element type
   * @param ncellg  Number of global cells of the element type
   * @param npc  Number of points-per-cell of the element type
   * @param epc  Number of edges-per-cell of the element type
   * @param fpc  Number of faces-per-cell of the element type
   * @param face_2d  Number of faces for 2D solution
   * @param type  Element type (TINF_ELEMENT_TYPE)
   * @returns  Error code
   **/
  int32_t tinf_nc_util_element_sizes(void* const nc, void* const element,
                                     int64_t* ncell, int64_t* ncellg,
                                     int32_t* npc, int32_t* epc, int32_t* fpc,
                                     int32_t* face_2d, int32_t* type);
  /**
   * Retrieve element relative edge-to-node pointers.
   *
   * @param element  Opaque element pointer
   * @param local_e2n  Edge-to-node pointers relative to cell nodes (6*epc)
   * @returns  Error code
   **/
  int32_t tinf_nc_util_element_e2n(void* const nc, void* const element,
                                   int32_t* local_e2n);

  /**
   * Retrieve element relative edge-to-node pointers.
   *
   * @param element  Opaque element pointer
   * @param local_e2n_2  Edge-to-node pointers relative to cell nodes (2*epc)
   * @returns  Error code
   **/
  int32_t tinf_nc_util_element_e2n_2(void* const nc, void* const element,
                                     int32_t* local_e2n_2);

  /**
   * Retrieve element relative face-to-node pointers.
   *
   * @param element  Opaque element pointer
   * @param local_f2n  Face-to-node pointers relative to cell nodes (4*fpc)
   * @returns  Error code
   **/
  int32_t tinf_nc_util_element_f2n(void* const nc, void* const element,
                                   int32_t* local_f2n);

  /**
   * Retrieve element indicators of faces that should have inner products
   * (i.e. the angle between them) computed.
   *
   * @param element  Opaque element pointer
   * @param chk_norm  Indicators (fpc*fpc)
   * @returns  Error code
   **/
  int32_t tinf_nc_util_element_check_norm(void* const nc, void* const element,
                                          int32_t* chk_norm);

  /**
   * Retrieve element relative face-to-element pointers.
   *
   * @param element  Opaque element pointer
   * @param f2e  Face-to-element pointers relative to cell nodes (4*fpc)
   * @returns  Error code
   **/
  int32_t tinf_nc_util_element_f2e(void* const nc, void* const element,
                                   int32_t* f2e);

  /**
   * Retrieve element relative cell-to-node pointers.
   *
   * @param nc  Opaque node-centered utility pointer
   * @param element  Opaque element pointer
   * @param c2n  All cell-to-node pointers for element (ncell*npc)
   * @returns  Error code
   **/
  int32_t tinf_nc_util_element_c2n(void* const nc, void* const element,
                                   int32_t* c2n);

  /**
   * Retrieve element relative cell-to-edge pointers.
   *
   * @param element  Opaque element pointer
   * @param c2e  All cell-to-edge pointers for element (ncell*epc)
   * @returns  Error code
   **/
  int32_t tinf_nc_util_element_c2e(void* const nc, void* const element,
                                   int32_t* c2e);

  /**
   * Retrieve element global Ids for cells.
   *
   * @param element  Opaque element pointer
   * @param l2g  Local-to-gloal map for cells of element type
   * @returns  Error code
   **/
  int32_t tinf_nc_util_element_l2g(void* const nc, void* const element,
                                   int64_t* l2g);

  /**
   * Retrieve send/recieve sizes for mesh nodes.
   *
   * @param nc  Opaque node-centered utility pointer
   * @param size1  Number of send/recieve processors
   * @param size2  Number of recieve indicies
   * @param size3  Number of send indicies
   * @returns  Error code
   **/
  int32_t tinf_nc_util_sendrecv_node_sizes(void* const nc, int64_t* size1,
                                           int64_t* size2, int64_t* size3);
  /**
   * Retrieve send/recieve sizes for mesh edges.
   *
   * @param nc  Opaque node-centered utility pointer
   * @param eptr  Array of computed edge pointers (input, 2*nedge)
   * @param size1  Number of send/recieve processors
   * @param size2  Number of recieve indicies
   * @param size3  Number of send indicies
   * @returns  Error code
   **/
  int32_t tinf_nc_util_sendrecv_edge_sizes(void* const nc, int32_t* eptr,
                                           int64_t* size1, int64_t* size2,
                                           int64_t* size3);

  /**
   * Retrieve send/recieve pairs for mesh nodes.
   *
   * @param nc  Opaque node-centered utility pointer
   * @param recvproc  Recieve processor Ids
   * @param recvindex  Recieve node indicies
   * @param sendproc  Send processor Ids
   * @param sendindex  Send node indicies
   * @returns  Error code
   **/
  int32_t tinf_nc_util_sendrecv_node(void* const nc, int32_t* recvproc,
                                     int32_t* recvindex, int32_t* sendproc,
                                     int32_t* sendindex);
  /**
   * Retrieve send/recieve pairs for mesh edges.
   *
   * @param nc  Opaque node-centered utility pointer
   * @param eptr  Array of computed edge pointers (input, 2*nedge)
   * @param recvproc  Recieve processor Ids
   * @param recvindex  Recieve edge indicies
   * @param sendproc  Send processor Ids
   * @param sendindex  Send edge indicies
   * @returns  Error code
   **/
  int32_t tinf_nc_util_sendrecv_edge(void* const nc, int32_t* eptr,
                                     int64_t* el2g,
                                     int32_t* recvproc, int32_t* recvindex,
                                     int32_t* sendproc, int32_t* sendindex);

#ifdef __cplusplus
}
#endif

#endif
