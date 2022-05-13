#ifdef __GNUG__
  #pragma implementation "UMesh.h"
#endif

#include <exception>
#include <cstdlib>
#include <string>
#include <sstream>
#include <algorithm>
#include <iostream>

#include "UMesh.h"
#include "tinf_mesh.h"
#include "kombyne_data_celltype.h"

using namespace VisKombyne;

#define TINF_CHECK_SUCCESS(error, msg) ({ \
  if( TINF_SUCCESS != error ) { \
    std::stringstream ss; \
    ss << error; \
    std::string message = std::string(msg) + ": " + ss.str(); \
    throw std::runtime_error(message.c_str()); \
  } \
})


UMesh::UMesh(void* mesh, void* comm) :
  m_mesh(mesh), m_comm(comm), m_moving(false)
{
  int error;

  addNodes();
  buildConnectivity();
  flagGhostNodes();
  flagGhostCells();
  addBoundaries();
}

UMesh::~UMesh()
{
  free(m_ghost_cells);
  free(m_ghost_nodes);
  free(m_cellconnects);
  free(m_x);
  free(m_y);
  free(m_z);
}

void UMesh::addNodes()
{
  int error;

  m_nnodes01 = tinf_mesh_node_count(m_mesh, &error);
  TINF_CHECK_SUCCESS(error, "Could not get number of mesh nodes");

  m_x = (double*)malloc(m_nnodes01*sizeof(double));
  m_y = (double*)malloc(m_nnodes01*sizeof(double));
  m_z = (double*)malloc(m_nnodes01*sizeof(double));
  if( NULL == m_x || NULL == m_y || NULL == m_z ) {
    if( m_z ) free(m_z);
    if( m_y ) free(m_y);
    if( m_x ) free(m_x);
    throw std::runtime_error("Failed to allocate Node coordinates");
  }

  getNodes();
}

void UMesh::getNodes()
{
  int error;

  error = tinf_mesh_nodes_coordinates(m_mesh, TINF_DOUBLE, 0, m_nnodes01,
                                      m_x, m_y, m_z);
  TINF_CHECK_SUCCESS(error, "Could not get mesh coordinates");
}

void UMesh::buildConnectivity()
{
  int32_t       error;

  int64_t ntet  = tinf_mesh_element_type_count(m_mesh, TINF_TETRA_4, &error);
  TINF_CHECK_SUCCESS(error, "Could not get number of Tets");
  int64_t npyr  = tinf_mesh_element_type_count(m_mesh, TINF_PYRA_5, &error);
  TINF_CHECK_SUCCESS(error, "Could not get number of Pyramids");
  int64_t nprz  = tinf_mesh_element_type_count(m_mesh, TINF_PENTA_6, &error);
  TINF_CHECK_SUCCESS(error, "Could not get number of Prisms");
  int64_t nhex  = tinf_mesh_element_type_count(m_mesh, TINF_HEXA_8, &error);
  TINF_CHECK_SUCCESS(error, "Could not get number of Hexes");

  m_lconn = 5*ntet+6*npyr+7*nprz+9*nhex;
  if( (m_cellconnects=(int32_t*)malloc(m_lconn*sizeof(int32_t))) == NULL ) {
    throw std::runtime_error("Could not allocate cell connectivity");
  }
  int64_t cellconnect[8];

  /* Assign connectivity */

  int64_t lconn = 0;
  m_ncell01 = 0;

  for( int64_t i=0; i<tinf_mesh_element_count(m_mesh,&error); ++i ) {
    switch( tinf_mesh_element_type(m_mesh, i, &error) ) {
//    case TINF_TRI_3:
//      m_cellconnects[lconn++] = KB_CELLTYPE_TRI;
//      error = tinf_mesh_element_nodes(m_mesh, i, cellconnect);
//      std::copy(cellconnect, cellconnect+3, &m_cellconnects[lconn]);
//      lconn += 3;
//      m_ncell01++;
//      break;
//    case TINF_QUAD_4:
//      m_cellconnects[lconn++] = KB_CELLTYPE_QUAD;
//      error = tinf_mesh_element_nodes(m_mesh, i, cellconnect);
//      std::copy(cellconnect, cellconnect+4, &m_cellconnects[lconn]);
//      lconn += 4;
//      m_ncell01++;
//      break;
      case TINF_TETRA_4:
        m_cellconnects[lconn++] = KB_CELLTYPE_TET;
        error = tinf_mesh_element_nodes(m_mesh, i, cellconnect);
        TINF_CHECK_SUCCESS(error, "Could not get Tet connectivity");
        std::copy(cellconnect, cellconnect+4, &m_cellconnects[lconn]);
        lconn += 4;
        m_ncell01++;
        break;
      case TINF_PYRA_5:
        m_cellconnects[lconn++] = KB_CELLTYPE_PYR;
        error = tinf_mesh_element_nodes(m_mesh, i, cellconnect);
        TINF_CHECK_SUCCESS(error, "Could not get Pyramid connectivity");
        std::copy(cellconnect, cellconnect+5, &m_cellconnects[lconn]);
        lconn += 5;
        m_ncell01++;
        break;
      case TINF_PENTA_6:
        m_cellconnects[lconn++] = KB_CELLTYPE_WEDGE;
        error = tinf_mesh_element_nodes(m_mesh, i, cellconnect);
        TINF_CHECK_SUCCESS(error, "Could not get Prism connectivity");
        std::copy(cellconnect, cellconnect+6, &m_cellconnects[lconn]);
        lconn += 6;
        m_ncell01++;
        break;
      case TINF_HEXA_8:
        m_cellconnects[lconn++] = KB_CELLTYPE_HEX;
        error = tinf_mesh_element_nodes(m_mesh, i, cellconnect);
        TINF_CHECK_SUCCESS(error, "Could not get Hex connectivity");
        std::copy(cellconnect, cellconnect+8, &m_cellconnects[lconn]);
        lconn += 8;
        m_ncell01++;
        break;
    }
  }
  if( m_lconn != lconn )
    throw std::runtime_error("Missing Cells");
}

void UMesh::flagGhostNodes()
{
  int error;

  if( (m_ghost_nodes=(int32_t*)malloc(m_nnodes01*sizeof(int32_t))) == NULL)
    throw std::runtime_error("Could not allocate ghost nodes");

  int64_t part = tinf_mesh_partition_id(m_mesh, &error);
  TINF_CHECK_SUCCESS(error, "Could not get mesh partition Id");

  for( int64_t i=0; i<m_nnodes01; ++i ) {
    m_ghost_nodes[i] = (int)(part == tinf_mesh_node_owner(m_mesh, i, &error));
    TINF_CHECK_SUCCESS(error, "Could not get node owner");
  }
}

void UMesh::flagGhostCells()
{
  int error;

  if( (m_ghost_cells=(int32_t*)malloc(m_ncell01*sizeof(int32_t))) == NULL) {
    throw std::runtime_error("Could not allocate ghost cells");
  }

  int64_t part = tinf_mesh_partition_id(m_mesh, &error);
  TINF_CHECK_SUCCESS(error, "Could not get mesh partition Id");

  int64_t ncell01 = 0;

  for( int64_t i=0; i<tinf_mesh_element_count(m_mesh,&error); ++i ) {
    switch( tinf_mesh_element_type(m_mesh, i, &error) ) {
//    case TINF_TRI_3:
//    case TINF_QUAD_4:
      case TINF_TETRA_4:
      case TINF_PYRA_5:
      case TINF_PENTA_6:
      case TINF_HEXA_8:
        m_ghost_cells[ncell01++] = (int)(part == tinf_mesh_element_owner(m_mesh,
                                                                       i,
                                                                       &error));
        TINF_CHECK_SUCCESS(error, "Could not get cell owner");
        break;
    }
  }
}

void UMesh::addBoundaries()
{
  int error;

  int64_t ntri  = tinf_mesh_element_type_count(m_mesh, TINF_TRI_3, &error);
  TINF_CHECK_SUCCESS(error, "Could not get Triangle element count");
  int64_t nquad = tinf_mesh_element_type_count(m_mesh, TINF_QUAD_4, &error);
  TINF_CHECK_SUCCESS(error, "Could not get Quad element count");

  std::vector<int64_t> tags = boundaryTags(ntri, nquad);

  m_bound.reserve(tags.size());

  for (std::vector<int64_t>::iterator it = tags.begin();
       it != tags.end(); ++it) {
    addBoundary(*it);
  }
}

std::vector<int64_t> UMesh::boundaryTags(int64_t ntri, int64_t nquad)
{
  int error;

  std::vector<int64_t> v(ntri+nquad,0);

  for( int64_t i=0, j=0; i<tinf_mesh_element_count(m_mesh,&error); ++i ) {
    switch( tinf_mesh_element_type(m_mesh, i, &error) ) {
      case TINF_TRI_3:
      case TINF_QUAD_4:
        v[j++] = tinf_mesh_element_tag(m_mesh, i, &error);
        TINF_CHECK_SUCCESS(error, "Could not get boundary tag");
        break;
    }
  }

  std::sort(v.begin(), v.end());
  std::vector<int64_t>::iterator it=std::unique(v.begin(), v.end());
  v.resize(std::distance(v.begin(), it));

  return v;
}

void UMesh::addBoundary(int64_t tag)
{
  int error;

  std::string root("Tag");
  std::string bc = root + ' ' + std::to_string(tag);

  m_bound.push_back(Boundary(tag,bc));
  Boundary& bound = m_bound.back();

  int64_t nodes[4];

  for( int64_t i=0; i<tinf_mesh_element_count(m_mesh,&error); ++i ) {
    switch( tinf_mesh_element_type(m_mesh, i, &error) ) {
      case TINF_TRI_3:
        if( tinf_mesh_element_tag(m_mesh, i, &error) == tag ) {
          error = tinf_mesh_element_nodes(m_mesh, i, nodes);
          TINF_CHECK_SUCCESS(error, "Could not get Triangle element nodes");
          bound.addTri(nodes);
        }
        break;
      case TINF_QUAD_4:
        if( tinf_mesh_element_tag(m_mesh, i, &error) == tag ) {
          error = tinf_mesh_element_nodes(m_mesh, i, nodes);
          TINF_CHECK_SUCCESS(error, "Could not get Quad element nodes");
          bound.addQuad(nodes);
        }
        break;
    }
  }
}

