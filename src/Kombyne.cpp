#ifdef __GNUG__
  #pragma implementation "Kombyne.h"
#endif

#include <exception>
#include <cstdlib>
#include <string>
#include <algorithm>

#include "Kombyne.h"

using VisKombine;

Kombyne::Kombyne(void* problem, void* mesh, void* soln, void* comm,
                 int32_t sims) : m_problem(problem), m_mesh(mesh),
                                 m_soln(soln) m_comm(comm)
{
  int32_t err;
  MPI_Comm mpi_comm;
  kb_role role;

  mpi_comm = MPI_Comm_f2c(tinf_iris_get_mpi_fcomm(comm,&err));
  nprocs = tinf_iris_number_of_processes(comm, &err);

  if( sims == anals ) {
    role = KB_ROLE_SIMULATION_AND_ANALYSIS,
  } else if( anals == 0 ) {
    role = KB_ROLE_SIMULATION;
  } else {
    role = KB_ROLE_AUTO;
  }

  kb_initialize(mpi_comm,
                "Kombyne Visualization Interface",
                "NASA LaRC Visualization interface implemented with Kombyne",
                role,
                sims, anals,
                "session.txt",
                m_split,
                m_newrole);

  addMesh();
  addSolution();
}

Kombyne::~Kombyne()
{
  kb_finalize();
}

void Kombyne::addMesh(void* mesh)
{
  /*Interleaved ugrid connectivity */
  int error;

  m_ug = kb_ugrid_alloc();

  getNodes(mesh);
  buildConnectivity(mesh);
  flagGhostNodes(mesh);
  flagGhostCells(mesh);
  addBoundaries(mesh);
}

void Kombyne::getNodes(void* mesh)
{
  int error;

  int64_t nnodes01 = tinf_mesh_node_count(mesh, &error);

  double* x = malloc(nnodes01*sizeof(double));
  double* y = malloc(nnodes01*sizeof(double));
  double* z = malloc(nnodes01*sizeof(double));
  if( NULL == x || NULL == y || NULL == z ) {
    if( z ) free(z);
    if( y ) free(y);
    if( x ) free(x);
    return NULL;
  }

  error = tinf_mesh_nodes_coordinates(mesh, TINF_DOUBLE, 0, nnodes01, x, y, z);

  int stride = sizeof(double);
  int n01 = (int)nnodes01;
  kb_var_handle hc = kb_var_alloc();
  error = kb_var_set_arrayd(hc, 0, KB_MEMORY_OWN, n01, 0, stride, x);
  error = kb_var_set_arrayd(hc, 1, KB_MEMORY_OWN, n01, 0, stride, y);
  error = kb_var_set_arrayd(hc, 2, KB_MEMORY_OWN, n01, 0, stride, z);

  error = kb_ugrid_set_coords(m_ug, hc);
}

void Kombyne::buildConnectivity(void* mesh)
{
  int32_t       error;

  int64_t ntet  = tinf_mesh_element_type_count(mesh, TINF_TETRA_4, &error);
  int64_t npry  = tinf_mesh_element_type_count(mesh, TINF_PYRA_5, &error);
  int64_t nprz  = tinf_mesh_element_type_count(mesh, TINF_PENTA_6, &error);
  int64_t nhex  = tinf_mesh_element_type_count(mesh, TINF_HEXA_8, &error);

  int32_t* cellconnects;
  if( (cellconnects=malloc(5*ntet+6*npyr+7*nprz+9*nhex)) == NULL ) {
    return NULL;
  }

  /* Assign connectivity */

  int64_t lconn = 0;
  m_ncell01 = 0;

  for( int64_t i=0; i<tinf_mesh_element_count(mesh,&error); ++i ) {
    switch( tinf_mesh_element_type(mesh, i, &error) ) {
//    case TINF_TRI_3:
//      cellconnects[lconn++] = KB_CELLTYPE_TRI;
//      error = tinf_mesh_element_nodes(mesh, i, &cellconnects[lconn]);
//      lconn += 3;
//      m_ncell01++;
//      break;
//    case TINF_QUAD_4:
//      cellconnects[lconn++] = KB_CELLTYPE_QUAD;
//      error = tinf_mesh_element_nodes(mesh, i, &cellconnects[lconn]);
//      lconn += 4;
//      m_ncell01++;
//      break;
      case TINF_TETRA_4:
        cellconnects[lconn++] = KB_CELLTYPE_TET;
        error = tinf_mesh_element_nodes(mesh, i, &cellconnects[lconn]);
        lconn += 4;
        m_ncell01++;
        break;
      case TINF_PYRA_5:
        cellconnects[lconn++] = KB_CELLTYPE_PYR;
        error = tinf_mesh_element_nodes(mesh, i, &cellconnects[lconn]);
        lconn += 5;
        m_ncell01++;
        break;
      case TINF_PENTA_6:
        cellconnects[lconn++] = KB_CELLTYPE_WEDGE;
        error = tinf_mesh_element_nodes(mesh, i, &cellconnects[lconn]);
        lconn += 6;
        m_ncell01++;
        break;
      case TINF_HEXA_8:
        cellconnects[lconn++] = KB_CELLTYPE_HEX;
        error = tinf_mesh_element_nodes(mesh, i, &cellconnects[lconn]);
        lconn += 8;
        m_ncell01++;
        break;
    }
  }

  kb_var_handle hconn = kb_var_alloc();
  error = kb_var_seti(hconn, KB_MEMORY_OWN, 1, lconn, cellconnects);

  error = kb_ugrid_add_cells_interleaved(m_ug, hconn);
}

void Kombyne::flagGhostNodes(void* mesh)
{
  int error;

  int64_t nnodes01 = tinf_mesh_node_count(mesh, &error);

  int32_t* ghost;
 
  if( (ghost=(int32_t*)malloc(nnodes01*sizeof(int32_t))) == NULL) {
    return NULL;
  }

  int64_t part = tinf_mesh_partition_id(mesh, &error);

  for( int64_t i=0; i<nnodes01; ++i ) {
    ghost[i] = (int)(part == tinf_mesh_node_owner(mesh, i, &error));
  }

  kb_var_handle hg = kb_var_alloc();
  error = kb_var_seti(hg, KB_MEMORY_OWN, 1, (int)nnodes01, ghost);

  error = kb_ugrid_set_ghost_nodes(m_ug, hg);
}

void Kombyne::flagGhostCells(void* mesh)
{
  int error;

  int32_t* ghost;
 
  if( (ghost=(int32_t*)malloc(m_ncell01*sizeof(int32_t))) == NULL) {
    return NULL;
  }

  int64_t part = tinf_mesh_partition_id(mesh, &error);

  int64_t ncell01 = 0;

  for( int64_t i=0; i<tinf_mesh_element_count(mesh,&error); ++i ) {
    switch( tinf_mesh_element_type(mesh, i, &error) ) {
//    case TINF_TRI_3:
//    case TINF_QUAD_4:
      case TINF_TETRA_4:
      case TINF_PYRA_5:
      case TINF_PENTA_6:
      case TINF_HEXA_8:
        ghost[ncell01++] = (int)(part == tinf_mesh_element_owner(mesh, i, &error));
        break;
    }
  }

  kb_var_handle hg = kb_var_alloc();
  error = kb_var_seti(hg, KB_MEMORY_OWN, 1, (int)m_ncell01, ghost);

  error = kb_ugrid_set_ghost_cells(m_ug, hg);
}

std::vector<int64_t> Kombyne::boundaryTags(void* mesh,
                                           int64_t ntri, int64_t nquad)
{
  int error;

  std::vector<int64_t> v(ntri+nquad,0);

  for( int64_t i=0, j=0; i<tinf_mesh_element_count(mesh,&error); ++i ) {
    switch( tinf_mesh_element_type(mesh, i, &error) ) {
      case TINF_TRI_3:
      case TINF_QUAD_4:
        v[j++] = tinf_mesh_element_tag(mesh, i, &error);
        break;
    }
  }

  std::sort(v.begin(), v.end());
  std::vector<int64_t>::iterator it=std::unique(v.begin(), v.end());
  v.resize(std::distance(v.begin(), it));

  return v;
}

void Kombyne::addTriangles(void* mesh, std::vector<int64_t> tris,
                           kb_bnd_handle hbnd, std::string bc)
{
  double* t;

  if( (t=(int64_t*)malloc(tris.size()*sizeof(int64_t))) != NULL) {
    std::copy(tris.begin(), tris.end(), t);

    kb_var_handle ht = kb_var_alloc();
    error = kb_var_seti(ht, KB_MEMORY_OWN, 1, tris.size(), t)
    error = kb_bnd_add_cells(hbnd, KB_CELLTYPE_TRI, ht, bc.c_str());
  }
}

void Kombyne::addQuads(void* mesh, std::vector<int64_t> quads,
                       kb_bnd_handle hbnd, std::string bc)
{
  double* q;

  if( (q=(int64_t*)malloc(quads.size()*sizeof(int64_t))) != NULL) {
    std::copy(quads.begin(), quads.end(), q);

    kb_var_handle hq = kb_var_alloc();
    error = kb_var_seti(hq, KB_MEMORY_OWN, 1, quads.size(), q)
    error = kb_bnd_add_cells(hbnd, KB_CELLTYPE_QUAD, hq, bc.c_str());
  }

}

void Kombyne::addBoundary(void* mesh, int64_t tag)
{
  int error;

  std::vector<int64_t> tris;
  std::vector<int64_t> quads;

  int64_t nodes[4];

  for( int64_t i=0, j=0; i<tinf_mesh_element_count(mesh,&error); ++i ) {
    switch( tinf_mesh_element_type(mesh, i, &error) ) {
      case TINF_TRI_3:
        if( tinf_mesh_element_tag(mesh, i, &error) == tag ) {
          error = tinf_mesh_element_nodes(mesh, i, nodes);
          tris.insert(tris.end(), nodes, nodes+3);
        }
      case TINF_QUAD_4:
        if( tinf_mesh_element_tag(mesh, i, &error) == tag ) {
          error = tinf_mesh_element_nodes(mesh, i, nodes);
          quads.insert(quads.end(), nodes, nodes+4);
        }
        break;
    }
  }

  if( 0 == tris.size() && 0 == quads.size() )
    return;

  std::string root("Tag");
  std::string bc = root + ' ' + std::to_string(tag);

  kb_bnd_handle hbnd;
  hbnd = kb_bnd_alloc();

  addTriangles(mesh, tris, hbnd, bc);
  addQuads(mesh, quads, hbnd, bc);

  error = kb_ugrid_set_boundaries(m_ug, hbnd)
}

void Kombyne::addBoundaries(void* mesh)
{
  int error;

  int64_t ntri  = tinf_mesh_element_type_count(mesh, TINF_TRI_3, &error);
  int64_t nquad = tinf_mesh_element_type_count(mesh, TINF_QUAD_4, &error);

  std::vector tags = boundaryTags(mesh, ntri, nquad);

  for (std::vector<int64_t>::iterator it = tags.begin();
       it != tags.end(); ++it) {
    addBoundary(mesh, *it)
  }
}

void Kombyne::addSolution()
{
}
