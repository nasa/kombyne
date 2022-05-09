#ifdef __GNUG__
  #pragma implementation "Kombyne.h"
#endif

#include <exception>
#include <cstdlib>
#include <cstring>
#include <string>
#include <sstream>
#include <algorithm>
#include <new>

#include "Kombyne.h"
#include "tinf_iris.h"
#include "tinf_mesh.h"
#include "tinf_solution.h"

using namespace VisKombyne;

#define KB_CHECK_STATUS(error, msg) ({ \
  if( KB_RETURN_ERROR == error ) { \
    std::stringstream ss; \
    ss << error; \
    std::string message = "ERROR - " + std::string(msg) + ": " + ss.str(); \
    throw std::runtime_error(message.c_str()); \
  } \
})

#define TINF_CHECK_SUCCESS(error, msg) ({ \
  if( TINF_SUCCESS != error ) { \
    std::stringstream ss; \
    ss << error; \
    std::string message = std::string(msg) + ": " + ss.str(); \
    throw std::runtime_error(message.c_str()); \
  } \
})


Kombyne::Kombyne(void* problem, void* mesh, void* soln, void* comm,
                 int32_t anals) : m_problem(problem), m_mesh(mesh),
                                  m_soln(soln), m_comm(comm),
                                  m_hc(KB_HANDLE_NULL)
{
  int32_t error;
  MPI_Comm mpi_comm;
  kb_role role;

  mpi_comm = MPI_Comm_f2c(tinf_iris_get_mpi_fcomm(m_comm,&error));
  int32_t nprocs = tinf_iris_number_of_processes(m_comm, &error);
  int32_t sims;

  if( 0 == anals ) {
    role = KB_ROLE_SIMULATION;
    sims = nprocs;
  } else if( anals == nprocs ) {
    role = KB_ROLE_SIMULATION_AND_ANALYSIS;
    sims = nprocs;
  } else if( anals < nprocs ) {
    role = KB_ROLE_AUTO;
    sims = nprocs - anals;
  } else {
    throw std::runtime_error("Bad number of analysis ranks");
  }

  bool moving_grid = false;
  m_problem.value("global:moving_grid",&moving_grid);

  bool grid_motion_attribute = false;
//m_problem.value("grid_motion:grid_motion_attribute",&grid_motion_attribute);

  m_moving_mesh = (moving_grid || grid_motion_attribute);

  kb_initialize(mpi_comm,
                "Kombyne Visualization Interface",
                "NASA LaRC Visualization interface implemented with Kombyne",
                role,
                sims, anals,
                "session.txt",
                &m_split,
                &m_newrole);

std::cerr << "Adding Mesh" << std::endl;
  addMesh();
std::cerr << "Adding Fields" << std::endl;
  addFields();
std::cerr << "Adding Pipeline Collection" << std::endl;
  addPipelineCollection();
std::cerr << "Kombyne constructed" << std::endl;
}

Kombyne::~Kombyne()
{
  kb_fields_handle hfield;
std::cerr << "Get Fields from Mesh" << std::endl;
  kb_ugrid_get_fields(m_ug,&hfield);
std::cerr << "Free Fields " << hfield << std::endl;
  kb_fields_free(hfield);
std::cerr << "Free Mesh" << std::endl;
  kb_ugrid_free(m_ug);

std::cerr << "Clear Fields vector" << std::endl;
  m_fields.clear();
  for (std::vector<int32_t*>::iterator it=m_quads.begin();
       it != m_quads.end(); ++it) free(*it);
  for (std::vector<int32_t*>::iterator it=m_tris.begin();
       it != m_tris.end(); ++it) free(*it);
  free(m_ghost_cells);
  free(m_ghost_nodes);
  free(m_cellconnects);

std::cerr << "Free Pipeline Collection" << std::endl;
  kb_pipeline_collection_free(m_hp);
std::cerr << "kb_finalize()" << std::endl;
  kb_finalize();
}

void Kombyne::execute()
{
  int error;
std::cerr << "Execute Pipeline" << std::endl;

std::cerr << "Get Mesh" << std::endl;
  if( m_moving_mesh ) getNodes();
std::cerr << "Get Fields" << std::endl;
  getFields();
std::cerr << "Add Samples" << std::endl;
  addSamples();
std::cerr << "Add Pipeline Data" << std::endl;
  kb_pipeline_data_handle hpd = addPipelineData();

std::cerr << "Executing" << std::endl;
  error = kb_simulation_execute(m_hp, hpd, m_hc);
  KB_CHECK_STATUS(error, "Could not execute pipeline");
std::cerr << "Done" << std::endl;

  kb_pipeline_data_free(hpd);
}

void Kombyne::addMesh()
{
  m_ug = kb_ugrid_alloc();

std::cerr << "Add Nodes" << std::endl;
  addNodes();
std::cerr << "build Connectivity" << std::endl;
  buildConnectivity();
  flagGhostNodes();
  flagGhostCells();
  addBoundaries();
}

void Kombyne::getNodes()
{
  int error;

  error = tinf_mesh_nodes_coordinates(m_mesh, TINF_DOUBLE, 0, m_nodes.size(),
                                      m_nodes.x(), m_nodes.y(), m_nodes.z());
  TINF_CHECK_SUCCESS(error, "Could not get mesh coordinates");
}

void Kombyne::addNodes()
{
  int error;

  int64_t nnodes01 = tinf_mesh_node_count(m_mesh, &error);
  TINF_CHECK_SUCCESS(error, "Could not get number of mesh nodes");

  m_nodes.size(nnodes01);

  getNodes();

  int stride = sizeof(double);
  int n01 = (int)nnodes01;
  kb_var_handle hc = kb_var_alloc();
  error = kb_var_set_arrayd(hc, 0, KB_MEM_BORROW, n01, 0, stride, m_nodes.x());
  KB_CHECK_STATUS(error, "Could not set mesh x array");
  error = kb_var_set_arrayd(hc, 1, KB_MEM_BORROW, n01, 0, stride, m_nodes.y());
  KB_CHECK_STATUS(error, "Could not set mesh y array");
  error = kb_var_set_arrayd(hc, 2, KB_MEM_BORROW, n01, 0, stride, m_nodes.z());
  KB_CHECK_STATUS(error, "Could not set mesh z array");

  error = kb_ugrid_set_coords(m_ug, hc);
  KB_CHECK_STATUS(error, "Could not set mesh coordinates");
}

void Kombyne::buildConnectivity()
{
  /*Interleaved ugrid connectivity */
  int32_t       error;

  int64_t ntet  = tinf_mesh_element_type_count(m_mesh, TINF_TETRA_4, &error);
  TINF_CHECK_SUCCESS(error, "Could not get number of Tets");
  int64_t npyr  = tinf_mesh_element_type_count(m_mesh, TINF_PYRA_5, &error);
  TINF_CHECK_SUCCESS(error, "Could not get number of Pyramids");
  int64_t nprz  = tinf_mesh_element_type_count(m_mesh, TINF_PENTA_6, &error);
  TINF_CHECK_SUCCESS(error, "Could not get number of Prisms");
  int64_t nhex  = tinf_mesh_element_type_count(m_mesh, TINF_HEXA_8, &error);
  TINF_CHECK_SUCCESS(error, "Could not get number of Hexes");

  int64_t ncell01 = 5*ntet+6*npyr+7*nprz+9*nhex;
  if( (m_cellconnects=(int32_t*)malloc(ncell01*sizeof(int32_t))) == NULL ) {
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
//      for( int32_t j=0; j<3; ++j ) m_cellconnects[lconn+j] = cellconnect[j];
//      lconn += 3;
//      m_ncell01++;
//      break;
//    case TINF_QUAD_4:
//      m_cellconnects[lconn++] = KB_CELLTYPE_QUAD;
//      error = tinf_mesh_element_nodes(m_mesh, i, cellconnect);
//      for( int32_t j=0; j<4; ++j ) m_cellconnects[lconn+j] = cellconnect[j];
//      lconn += 4;
//      m_ncell01++;
//      break;
      case TINF_TETRA_4:
        m_cellconnects[lconn++] = KB_CELLTYPE_TET;
        error = tinf_mesh_element_nodes(m_mesh, i, cellconnect);
        TINF_CHECK_SUCCESS(error, "Could not get Tet connectivity");
        for( int32_t j=0; j<4; ++j ) m_cellconnects[lconn+j] = cellconnect[j];
        lconn += 4;
        m_ncell01++;
        break;
      case TINF_PYRA_5:
        m_cellconnects[lconn++] = KB_CELLTYPE_PYR;
        error = tinf_mesh_element_nodes(m_mesh, i, cellconnect);
        TINF_CHECK_SUCCESS(error, "Could not get Pyramid connectivity");
        for( int32_t j=0; j<5; ++j ) m_cellconnects[lconn+j] = cellconnect[j];
        lconn += 5;
        m_ncell01++;
        break;
      case TINF_PENTA_6:
        m_cellconnects[lconn++] = KB_CELLTYPE_WEDGE;
        error = tinf_mesh_element_nodes(m_mesh, i, cellconnect);
        TINF_CHECK_SUCCESS(error, "Could not get Prism connectivity");
        for( int32_t j=0; j<6; ++j ) m_cellconnects[lconn+j] = cellconnect[j];
        lconn += 6;
        m_ncell01++;
        break;
      case TINF_HEXA_8:
        m_cellconnects[lconn++] = KB_CELLTYPE_HEX;
        error = tinf_mesh_element_nodes(m_mesh, i, cellconnect);
        TINF_CHECK_SUCCESS(error, "Could not get Hex connectivity");
        for( int32_t j=0; j<8; ++j ) m_cellconnects[lconn+j] = cellconnect[j];
        lconn += 8;
        m_ncell01++;
        break;
    }
  }

  kb_var_handle hconn = kb_var_alloc();
  error = kb_var_seti(hconn, KB_MEM_BORROW, 1, lconn, m_cellconnects);
  KB_CHECK_STATUS(error, "Could not create cell connectivity array");

  error = kb_ugrid_add_cells_interleaved(m_ug, hconn);
  KB_CHECK_STATUS(error, "Could not add mesh cells");
}

void Kombyne::flagGhostNodes()
{
  int error;

  if( (m_ghost_nodes=(int32_t*)malloc(m_nodes.size()*sizeof(int32_t))) == NULL)
    throw std::runtime_error("Could not allocate ghost nodes");

  int64_t part = tinf_mesh_partition_id(m_mesh, &error);
  TINF_CHECK_SUCCESS(error, "Could not get mesh partition Id");

  for( int64_t i=0; i<m_nodes.size(); ++i ) {
    m_ghost_nodes[i] = (int)(part == tinf_mesh_node_owner(m_mesh, i, &error));
    TINF_CHECK_SUCCESS(error, "Could not get node owner");
  }

  kb_var_handle hg = kb_var_alloc();
  error = kb_var_seti(hg, KB_MEM_BORROW, 1, (int)m_nodes.size(), m_ghost_nodes);
  KB_CHECK_STATUS(error, "Could not create Ghost nodes array");

  error = kb_ugrid_set_ghost_nodes(m_ug, hg);
  KB_CHECK_STATUS(error, "Could not set Ghost nodes");
}

void Kombyne::flagGhostCells()
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

  kb_var_handle hg = kb_var_alloc();
  error = kb_var_seti(hg, KB_MEM_BORROW, 1, (int)m_ncell01, m_ghost_cells);
  KB_CHECK_STATUS(error, "Could not create Ghost cells array");

  error = kb_ugrid_set_ghost_cells(m_ug, hg);
  KB_CHECK_STATUS(error, "Could not set Ghost cells");
}

std::vector<int64_t> Kombyne::boundaryTags(int64_t ntri, int64_t nquad)
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

void Kombyne::addTriangles(std::vector<int64_t> tris,
                           kb_bnd_handle hbnd, std::string bc)
{
  int error;
  int32_t* t;

  if( (t=(int32_t*)malloc(tris.size()*sizeof(int32_t))) != NULL) {
    std::copy(tris.begin(), tris.end(), t);
    m_tris.push_back(t);

    kb_var_handle ht = kb_var_alloc();
    error = kb_var_seti(ht, KB_MEM_BORROW, 1, tris.size(), t);
    KB_CHECK_STATUS(error, "Could not set Triangle cell array");
std::cerr << "Add Triangles to " << bc << std::endl;
    error = kb_bnd_add_cells(hbnd, KB_CELLTYPE_TRI, ht, bc.c_str());
    KB_CHECK_STATUS(error, "Could not set Triangle cells");
  }
}

void Kombyne::addQuads(std::vector<int64_t> quads,
                       kb_bnd_handle hbnd, std::string bc)
{
  int error;
  int32_t* q;

  if( (q=(int32_t*)malloc(quads.size()*sizeof(int32_t))) != NULL) {
    std::copy(quads.begin(), quads.end(), q);
    m_quads.push_back(q);

    kb_var_handle hq = kb_var_alloc();
    error = kb_var_seti(hq, KB_MEM_BORROW, 1, quads.size(), q);
    KB_CHECK_STATUS(error, "Could not set Quad cell array");
    error = kb_bnd_add_cells(hbnd, KB_CELLTYPE_QUAD, hq, bc.c_str());
    KB_CHECK_STATUS(error, "Could not add Quad cells");
  }
}

void Kombyne::addBoundary(int64_t tag, kb_bnd_handle hbnd)
{
  int error;

  std::vector<int64_t> tris;
  std::vector<int64_t> quads;

  int64_t nodes[4];

  for( int64_t i=0, j=0; i<tinf_mesh_element_count(m_mesh,&error); ++i ) {
    switch( tinf_mesh_element_type(m_mesh, i, &error) ) {
      case TINF_TRI_3:
        if( tinf_mesh_element_tag(m_mesh, i, &error) == tag ) {
          error = tinf_mesh_element_nodes(m_mesh, i, nodes);
          TINF_CHECK_SUCCESS(error, "Could not get Triangle element nodes");
          tris.insert(tris.end(), nodes, nodes+3);
        }
      case TINF_QUAD_4:
        if( tinf_mesh_element_tag(m_mesh, i, &error) == tag ) {
          error = tinf_mesh_element_nodes(m_mesh, i, nodes);
          TINF_CHECK_SUCCESS(error, "Could not get Quad element nodes");
          quads.insert(quads.end(), nodes, nodes+4);
        }
        break;
    }
  }

  if( 0 == tris.size() && 0 == quads.size() )
    throw std::runtime_error("Empty boundary");

  std::string root("Tag");
  std::string bc = root + ' ' + std::to_string(tag);

  addTriangles(tris, hbnd, bc);
  addQuads(quads, hbnd, bc);
}

void Kombyne::addBoundaries()
{
  int error;

  int64_t ntri  = tinf_mesh_element_type_count(m_mesh, TINF_TRI_3, &error);
  TINF_CHECK_SUCCESS(error, "Could not get Triangle element count");
  int64_t nquad = tinf_mesh_element_type_count(m_mesh, TINF_QUAD_4, &error);
  TINF_CHECK_SUCCESS(error, "Could not get Quad element count");

  std::vector<int64_t> tags = boundaryTags(ntri, nquad);

  kb_bnd_handle hbnd;
  hbnd = kb_bnd_alloc();

  for (std::vector<int64_t>::iterator it = tags.begin();
       it != tags.end(); ++it) {
    addBoundary(*it, hbnd);
  }

  error = kb_ugrid_set_boundaries(m_ug, hbnd);
  KB_CHECK_STATUS(error, "Could not set boundaries");
}

void Kombyne::addPipelineCollection()
{
  int error;

  m_hp = kb_pipeline_collection_alloc();

  const char* filename = std::getenv("KOMBYNE_PIPELINE");
  if( filename ) {
    error = kb_pipeline_collection_set_filename(m_hp, filename);
  } else {
    error = kb_pipeline_collection_set_filename(m_hp, "kombyne.yaml");
  }
  
  error = kb_pipeline_collection_initialize(m_hp);
  KB_CHECK_STATUS(error, "Could not initialize pipeline");
}

kb_pipeline_data_handle Kombyne::addPipelineData()
{
  int error;

  int32_t domain = tinf_iris_rank(m_comm, &error);
  int32_t ndomains = tinf_iris_number_of_processes(m_comm, &error);

  int64_t timestep=0;
  m_problem.value("info:step",&timestep);
  double time=0.0;
  m_problem.value("info:timestep",&time);
std::cerr << "Timestep " << timestep << " Time " << time << std::endl;

  kb_mesh_handle hmesh = (kb_mesh_handle)m_ug;

  kb_pipeline_data_handle hpd = kb_pipeline_data_alloc();

  error = kb_pipeline_data_add(hpd, domain, ndomains, timestep, time, hmesh);
  KB_CHECK_STATUS(error, "Could not add pipeline data");

#ifdef KOMBYNE
  int32_t promises = KB_PROMISE_STATIC_FIELDS; 

  if( !m_moving_mesh )
    promises |= KB_PROMISE_STATIC_GRID;

  error = kb_pipeline_data_set_promises(hpd, promises);
  KB_CHECK_STATUS(error, "Could not set pipeline promises");
#else
  error = kb_pipeline_data_promise_fields_same(hpd, true);
#endif

  return hpd;
}

double Kombyne::l2norm(int64_t npoints, double* values)
{
  double l2norm = 0.0;

  for( int i=0; i<npoints; ++i ) {
    l2norm += values[i] * values[i];
  }
  l2norm = sqrt(l2norm/(double)npoints);

  return l2norm;
}

void Kombyne::getFields()
{
  int error;

  for(std::vector<Field>::iterator it = m_fields.begin(); 
      it != m_fields.end(); ++it) {
    const char* name = it->name();
    error = tinf_solution_get_outputs_at_nodes(m_soln, it->type(), 0,
                                               m_nodes.size(), 1, &name,
                                               it->values());
    TINF_CHECK_SUCCESS(error, "Failed to retrieve Solver output values");
  }
}

void Kombyne::addFields()
{
  int error;

  int64_t n_outputs;
  const char** names;
  const enum TINF_DATA_TYPE* datatype;
  error = tinf_solution_get_nodal_output_names(m_soln, &n_outputs,
                                               &names, &datatype);
  TINF_CHECK_SUCCESS(error, "Failed to retrieve Solver outputs");

  kb_fields_handle hfield = kb_fields_alloc();

  m_fields.reserve(n_outputs);
  for( int i=0; i<n_outputs; ++i ) {
    m_fields.push_back(Field(names[i], datatype[i]));
  }

  for(std::vector<Field>::iterator it = m_fields.begin();
      it != m_fields.end(); ++it)
    it->size(m_nodes.size());

  getFields();

  for(std::vector<Field>::iterator it = m_fields.begin(); 
      it != m_fields.end(); ++it) {
    kb_var_handle hvar = kb_var_alloc();
    error = kb_var_setd(hvar, KB_MEM_BORROW, 1, m_nodes.size(), it->values());
    KB_CHECK_STATUS(error, "Could not create field data variable");
    error = kb_fields_add_var(hfield, it->name(), KB_CENTERING_POINTS, hvar);
    KB_CHECK_STATUS(error, "Could not add field data");
  }

  error = kb_ugrid_set_fields(m_ug, hfield);
  KB_CHECK_STATUS(error, "Could not add fields to mesh");
}

void Kombyne::addSamples()
{
  int error;

  for(std::vector<Field>::iterator it = m_fields.begin(); 
      it != m_fields.end(); ++it) {
    if( strncmp(it->name(),"Residual",8) ) {
      double sample = l2norm(m_nodes.size(), it->values());
      error = kb_add_sample(it->name(), sample);
      KB_CHECK_STATUS(error, "Could not add sample");
    }
  }
}

