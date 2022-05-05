#ifdef __GNUG__
  #pragma implementation "Kombyne.h"
#endif

#include <exception>
#include <cstdlib>
#include <cstring>
#include <string>
#include <sstream>
#include <algorithm>

#include "Kombyne.h"
#include "tinf_iris.h"
#include "tinf_mesh.h"
#include "tinf_solution.h"
#include "pancake_cxx/Problem.h"

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

class Sample
{
  public:
    Sample(std::string label, double s) : m_label(label), m_sample(s) {}

    inline std::string label() { return m_label; }
    inline double sample() { return m_sample; }

  private:
    std::string m_label;
    double m_sample;
};

Kombyne::Kombyne(void* problem, void* mesh, void* soln, void* comm,
                 int32_t sims) : m_problem(problem), m_mesh(mesh),
                                 m_soln(soln), m_comm(comm),
                                 m_hc(KB_HANDLE_NULL)
{
  int32_t error;
  MPI_Comm mpi_comm;
  kb_role role;

  mpi_comm = MPI_Comm_f2c(tinf_iris_get_mpi_fcomm(comm,&error));
  int32_t nprocs = tinf_iris_number_of_processes(comm, &error);
  int32_t anals = nprocs - sims;

  if( sims == anals ) {
    role = KB_ROLE_SIMULATION_AND_ANALYSIS;
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
                &m_split,
                &m_newrole);

  int64_t nnodes01 = tinf_mesh_node_count(mesh, &error);
  TINF_CHECK_SUCCESS(error, "Failed to retrieve mesh size");

  addMesh(mesh);
  addPipeline(problem);
  addFields(soln, nnodes01);
}

Kombyne::~Kombyne()
{
  kb_finalize();
}

void Kombyne::execute()
{
  int error;

  error = kb_simulation_execute(m_hp, m_hpd, m_hc);
  KB_CHECK_STATUS(error, "Could not execute pipeline");
}

void Kombyne::addMesh(void* mesh)
{
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
  TINF_CHECK_SUCCESS(error, "Could not get number of mesh nodes");

  double* x = (double*)malloc(nnodes01*sizeof(double));
  double* y = (double*)malloc(nnodes01*sizeof(double));
  double* z = (double*)malloc(nnodes01*sizeof(double));
  if( NULL == x || NULL == y || NULL == z ) {
    if( z ) free(z);
    if( y ) free(y);
    if( x ) free(x);
    throw std::runtime_error("Could not allocate mesh coordinates");
  }

  error = tinf_mesh_nodes_coordinates(mesh, TINF_DOUBLE, 0, nnodes01, x, y, z);
  TINF_CHECK_SUCCESS(error, "Could not get mesh coordinates");

  int stride = sizeof(double);
  int n01 = (int)nnodes01;
  kb_var_handle hc = kb_var_alloc();
  error = kb_var_set_arrayd(hc, 0, KB_MEM_OWN, n01, 0, stride, x);
  KB_CHECK_STATUS(error, "Could not set mesh x array");
  error = kb_var_set_arrayd(hc, 1, KB_MEM_OWN, n01, 0, stride, y);
  KB_CHECK_STATUS(error, "Could not set mesh y array");
  error = kb_var_set_arrayd(hc, 2, KB_MEM_OWN, n01, 0, stride, z);
  KB_CHECK_STATUS(error, "Could not set mesh z array");

  error = kb_ugrid_set_coords(m_ug, hc);
  KB_CHECK_STATUS(error, "Could not set mesh coordinates");
}

void Kombyne::buildConnectivity(void* mesh)
{
  /*Interleaved ugrid connectivity */
  int32_t       error;

  int64_t ntet  = tinf_mesh_element_type_count(mesh, TINF_TETRA_4, &error);
  TINF_CHECK_SUCCESS(error, "Could not get number of Tets");
  int64_t npyr  = tinf_mesh_element_type_count(mesh, TINF_PYRA_5, &error);
  TINF_CHECK_SUCCESS(error, "Could not get number of Pyramids");
  int64_t nprz  = tinf_mesh_element_type_count(mesh, TINF_PENTA_6, &error);
  TINF_CHECK_SUCCESS(error, "Could not get number of Prisms");
  int64_t nhex  = tinf_mesh_element_type_count(mesh, TINF_HEXA_8, &error);
  TINF_CHECK_SUCCESS(error, "Could not get number of Hexes");

  int64_t* cellconnects;
  if( (cellconnects=(int64_t*)malloc(5*ntet+6*npyr+7*nprz+9*nhex)) == NULL ) {
    throw std::runtime_error("Could not allocate cell connectivity");
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
        TINF_CHECK_SUCCESS(error, "Could not get Tet connectivity");
        lconn += 4;
        m_ncell01++;
        break;
      case TINF_PYRA_5:
        cellconnects[lconn++] = KB_CELLTYPE_PYR;
        error = tinf_mesh_element_nodes(mesh, i, &cellconnects[lconn]);
        TINF_CHECK_SUCCESS(error, "Could not get Pyramid connectivity");
        lconn += 5;
        m_ncell01++;
        break;
      case TINF_PENTA_6:
        cellconnects[lconn++] = KB_CELLTYPE_WEDGE;
        error = tinf_mesh_element_nodes(mesh, i, &cellconnects[lconn]);
        TINF_CHECK_SUCCESS(error, "Could not get Prism connectivity");
        lconn += 6;
        m_ncell01++;
        break;
      case TINF_HEXA_8:
        cellconnects[lconn++] = KB_CELLTYPE_HEX;
        error = tinf_mesh_element_nodes(mesh, i, &cellconnects[lconn]);
        TINF_CHECK_SUCCESS(error, "Could not get Hex connectivity");
        lconn += 8;
        m_ncell01++;
        break;
    }
  }

  kb_var_handle hconn = kb_var_alloc();
  error = kb_var_setl(hconn, KB_MEM_OWN, 1, lconn, cellconnects);
  KB_CHECK_STATUS(error, "Could not create cell connectivity array");

  error = kb_ugrid_add_cells_interleaved(m_ug, hconn);
  KB_CHECK_STATUS(error, "Could not add mesh cells");
}

void Kombyne::flagGhostNodes(void* mesh)
{
  int error;

  int64_t nnodes01 = tinf_mesh_node_count(mesh, &error);
  TINF_CHECK_SUCCESS(error, "Could not get mesh node count");

  int32_t* ghost;
 
  if( (ghost=(int32_t*)malloc(nnodes01*sizeof(int32_t))) == NULL) {
    throw std::runtime_error("Could not allocate ghost nodes");
  }

  int64_t part = tinf_mesh_partition_id(mesh, &error);
  TINF_CHECK_SUCCESS(error, "Could not get mesh partition Id");

  for( int64_t i=0; i<nnodes01; ++i ) {
    ghost[i] = (int)(part == tinf_mesh_node_owner(mesh, i, &error));
    TINF_CHECK_SUCCESS(error, "Could not get node owner");
  }

  kb_var_handle hg = kb_var_alloc();
  error = kb_var_seti(hg, KB_MEM_OWN, 1, (int)nnodes01, ghost);
  KB_CHECK_STATUS(error, "Could not create Ghost nodes array");

  error = kb_ugrid_set_ghost_nodes(m_ug, hg);
  KB_CHECK_STATUS(error, "Could not set Ghost nodes");
}

void Kombyne::flagGhostCells(void* mesh)
{
  int error;

  int32_t* ghost;
 
  if( (ghost=(int32_t*)malloc(m_ncell01*sizeof(int32_t))) == NULL) {
    throw std::runtime_error("Could not allocate ghost cells");
  }

  int64_t part = tinf_mesh_partition_id(mesh, &error);
  TINF_CHECK_SUCCESS(error, "Could not get mesh partition Id");

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
        TINF_CHECK_SUCCESS(error, "Could not get cell owner");
        break;
    }
  }

  kb_var_handle hg = kb_var_alloc();
  error = kb_var_seti(hg, KB_MEM_OWN, 1, (int)m_ncell01, ghost);
  KB_CHECK_STATUS(error, "Could not create Ghost cells array");

  error = kb_ugrid_set_ghost_cells(m_ug, hg);
  KB_CHECK_STATUS(error, "Could not set Ghost cells");
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
        TINF_CHECK_SUCCESS(error, "Could not get boundary tag");
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
  int error;
  double* t;

  if( (t=(double*)malloc(tris.size()*sizeof(int64_t))) != NULL) {
    std::copy(tris.begin(), tris.end(), t);

    kb_var_handle ht = kb_var_alloc();
    error = kb_var_setd(ht, KB_MEM_OWN, 1, tris.size(), t);
    KB_CHECK_STATUS(error, "Could not set Triangle cell array");
    error = kb_bnd_add_cells(hbnd, KB_CELLTYPE_TRI, ht, bc.c_str());
    KB_CHECK_STATUS(error, "Could not set Triangle cells");
  }
}

void Kombyne::addQuads(void* mesh, std::vector<int64_t> quads,
                       kb_bnd_handle hbnd, std::string bc)
{
  int error;
  double* q;

  if( (q=(double*)malloc(quads.size()*sizeof(int64_t))) != NULL) {
    std::copy(quads.begin(), quads.end(), q);

    kb_var_handle hq = kb_var_alloc();
    error = kb_var_setd(hq, KB_MEM_OWN, 1, quads.size(), q);
    KB_CHECK_STATUS(error, "Could not set Quad cell array");
    error = kb_bnd_add_cells(hbnd, KB_CELLTYPE_QUAD, hq, bc.c_str());
    KB_CHECK_STATUS(error, "Could not add Quad cells");
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
          TINF_CHECK_SUCCESS(error, "Could not get Triangle element nodes");
          tris.insert(tris.end(), nodes, nodes+3);
        }
      case TINF_QUAD_4:
        if( tinf_mesh_element_tag(mesh, i, &error) == tag ) {
          error = tinf_mesh_element_nodes(mesh, i, nodes);
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

  kb_bnd_handle hbnd;
  hbnd = kb_bnd_alloc();

  addTriangles(mesh, tris, hbnd, bc);
  addQuads(mesh, quads, hbnd, bc);

  error = kb_ugrid_set_boundaries(m_ug, hbnd);
  KB_CHECK_STATUS(error, "Could not set boundaries");
}

void Kombyne::addBoundaries(void* mesh)
{
  int error;

  int64_t ntri  = tinf_mesh_element_type_count(mesh, TINF_TRI_3, &error);
  TINF_CHECK_SUCCESS(error, "Could not get Triangle element count");
  int64_t nquad = tinf_mesh_element_type_count(mesh, TINF_QUAD_4, &error);
  TINF_CHECK_SUCCESS(error, "Could not get Quad element count");

  std::vector<int64_t> tags = boundaryTags(mesh, ntri, nquad);

  for (std::vector<int64_t>::iterator it = tags.begin();
       it != tags.end(); ++it) {
    addBoundary(mesh, *it);
  }
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

void Kombyne::addPipelineData(void* prob)
{
  int error;

  kb_pipeline_data_handle m_hpd = kb_pipeline_data_alloc();

  int32_t domain = tinf_iris_rank(m_comm, &error);
  int32_t ndomains = tinf_iris_number_of_processes(m_comm, &error);

  pancake::Problem problem(prob);

  int32_t timestep;
  problem.value("info:step",&timestep);
  double time;
  problem.value("info:timestep",&time);

  error = kb_pipeline_data_add(m_hpd, domain, ndomains, timestep, time,
                               (kb_mesh_handle)m_ug);
  KB_CHECK_STATUS(error, "Could not add pipeline data");

  bool moving_grid = false;
  problem.value("global:moving_grid",&moving_grid);

  bool grid_motion_attribute = false;
//problem.value("grid_motion:grid_motion_attribute",&grid_motion_attribute);

#ifdef KOMBYNE
  int32_t promises = KB_PROMISE_STATIC_FIELDS; 

  if( !moving_grid && !grid_motion_attribute )
    promises |= KB_PROMISE_STATIC_GRID;

  error = kb_pipeline_data_set_promises(m_hpd, promises);
  KB_CHECK_STATUS(error, "Could not set pipeline promises");
#else
  error = kb_pipeline_data_promise_fields_same(m_hpd, true);
#endif
}

void Kombyne::addPipeline(void* prob)
{
  addPipelineCollection();
  addPipelineData(prob);
  execute();
}

double Kombyne::rms(int64_t npoints, double* values)
{
  double rms = 0.0;

  for( int i=0; i<npoints; ++i ) {
    rms += values[i] * values[i];
  }
  rms = sqrt(rms/(double)npoints);

  return rms;
}

void Kombyne::addFields(void* soln, int64_t npoints)
{
  int error;

  int64_t n_outputs;
  const char** names;
  const enum TINF_DATA_TYPE* datatype;
  error = tinf_solution_get_nodal_output_names(soln, &n_outputs,
                                               &names, &datatype);
  TINF_CHECK_SUCCESS(error, "Failed to retrieve Solver outputs");

  kb_fields_handle hfield = kb_fields_alloc();

  std::vector<Sample> sample;

  for( int i=0, j=0; i<n_outputs; ++i ) {
    double* values = (double*)malloc(npoints*sizeof(double));
    error = tinf_solution_get_outputs_at_nodes(soln, datatype[j], 0, npoints,
                                               1, &names[j], values);
    TINF_CHECK_SUCCESS(error, "Failed to retrieve Solver output values");

    if( strncmp(names[j],"Residual",8) ) {
      sample.push_back(Sample(names[j], rms(npoints, values)));
    }

    kb_var_handle hvar = kb_var_alloc();
    error = kb_var_setd(hvar, KB_MEM_OWN, 1, npoints, values);
    KB_CHECK_STATUS(error, "Could not create field data variable");
    error = kb_fields_add_var(hfield, names[j++], KB_CENTERING_POINTS, hvar);
    KB_CHECK_STATUS(error, "Could not add field data");
  }

  error = kb_ugrid_set_fields(m_ug, hfield);
  KB_CHECK_STATUS(error, "Could not add fields to mesh");

  for( int i=0; i<sample.size(); ++i ) {
    error = kb_add_sample(sample[i].label().c_str(), sample[i].sample());
    KB_CHECK_STATUS(error, "Could not add sample to mesh");
  }
}
