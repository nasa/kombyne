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
                 int32_t anals) : m_problem(problem), m_mesh(mesh,comm),
                                  m_soln(soln), m_comm(comm)
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

  m_mesh.moving(moving_grid || grid_motion_attribute);

  createFields();

  kb_initialize(mpi_comm,
                "Kombyne Visualization Interface",
                "NASA LaRC Visualization interface implemented with Kombyne",
                role,
                sims, anals,
                "session.txt",
                &m_split,
                &m_newrole);

std::cerr << "Adding Pipeline Collection" << std::endl;
  addPipelineCollection();
std::cerr << "Kombyne constructed" << std::endl;
}

Kombyne::~Kombyne()
{
  m_fields.clear();

  kb_pipeline_collection_free(m_hp);
  kb_finalize();
}

void Kombyne::execute()
{
  int error;
std::cerr << "Execute Pipeline" << std::endl;

std::cerr << "Add Mesh" << std::endl;
  kb_ugrid_handle ug = addMesh();
//std::cerr << "Get Fields" << std::endl;
//addFields(ug);
//std::cerr << "Add Samples" << std::endl;
//addSamples();
std::cerr << "Add Pipeline Data" << std::endl;
  kb_pipeline_data_handle hpd = addPipelineData(ug);

std::cerr << "Executing" << std::endl;
  kb_controls_handle hc = KB_HANDLE_NULL;
  error = kb_simulation_execute(m_hp, hpd, hc);
  KB_CHECK_STATUS(error, "Could not execute pipeline");
std::cerr << "Done" << std::endl;

  kb_pipeline_data_free(hpd);
}

void Kombyne::createFields()
{
  int error;

  int64_t n_outputs;
  const char** names;
  const enum TINF_DATA_TYPE* datatype;
  error = tinf_solution_get_nodal_output_names(m_soln, &n_outputs,
                                               &names, &datatype);
  TINF_CHECK_SUCCESS(error, "Failed to retrieve Solver outputs");

  m_fields.reserve(n_outputs);
  for( int i=0; i<n_outputs; ++i ) {
    m_fields.push_back(Field(names[i], datatype[i]));
  }

  for(std::vector<Field>::iterator it = m_fields.begin();
      it != m_fields.end(); ++it)
    it->size(m_mesh.nNodes01());
}

kb_ugrid_handle Kombyne::addMesh()
{
  kb_ugrid_handle ug = kb_ugrid_alloc();

std::cerr << "Add Nodes" << std::endl;
  addNodes(ug);
std::cerr << "Add Connectivity" << std::endl;
  addConnectivity(ug);
//addGhostNodes(ug);
//addGhostCells(ug);
//addBoundaries(ug);

  return ug;
}

void Kombyne::addNodes(kb_ugrid_handle ug)
{
  int error;

std::cerr << "Get Nodes" << std::endl;
  m_mesh.getNodes();

  int n01 = (int)m_mesh.nNodes01();
  int stride = sizeof(double);

  kb_var_handle hc = kb_var_alloc();

  error = kb_var_set_arrayd(hc, 0, KB_MEM_BORROW, n01, 0, stride, m_mesh.x());
  KB_CHECK_STATUS(error, "Could not set mesh x array");
  error = kb_var_set_arrayd(hc, 1, KB_MEM_BORROW, n01, 0, stride, m_mesh.y());
  KB_CHECK_STATUS(error, "Could not set mesh y array");
  error = kb_var_set_arrayd(hc, 2, KB_MEM_BORROW, n01, 0, stride, m_mesh.z());
  KB_CHECK_STATUS(error, "Could not set mesh z array");

  error = kb_ugrid_set_coords(ug, hc);
  KB_CHECK_STATUS(error, "Could not set mesh coordinates");
}

void Kombyne::addConnectivity(kb_ugrid_handle ug)
{
  /*Interleaved ugrid connectivity */
  int32_t       error;

  int lconn = (int)m_mesh.cellConnectsSize();

  kb_var_handle hconn = kb_var_alloc();
  error = kb_var_seti(hconn, KB_MEM_BORROW, 1, lconn, m_mesh.cellConnects());
  KB_CHECK_STATUS(error, "Could not create cell connectivity array");

  error = kb_ugrid_add_cells_interleaved(ug, hconn);
  KB_CHECK_STATUS(error, "Could not add mesh cells");
}

void Kombyne::addGhostNodes(kb_ugrid_handle ug)
{
  int error;

  int n01 = (int)m_mesh.nNodes01();

  kb_var_handle hg = kb_var_alloc();
  error = kb_var_seti(hg, KB_MEM_BORROW, 1, n01, m_mesh.ghostNodes());
  KB_CHECK_STATUS(error, "Could not create Ghost nodes array");

  error = kb_ugrid_set_ghost_nodes(ug, hg);
  KB_CHECK_STATUS(error, "Could not set Ghost nodes");
}

void Kombyne::addGhostCells(kb_ugrid_handle ug)
{
  int error;

  int lconn = (int)m_mesh.nCell01();

  kb_var_handle hg = kb_var_alloc();
  error = kb_var_seti(hg, KB_MEM_BORROW, 1, lconn, m_mesh.ghostCells());
  KB_CHECK_STATUS(error, "Could not create Ghost cells array");

  error = kb_ugrid_set_ghost_cells(ug, hg);
  KB_CHECK_STATUS(error, "Could not set Ghost cells");
}

void Kombyne::addBoundaries(kb_ugrid_handle ug)
{
  int error;

  const std::vector<Boundary>& boundary = m_mesh.boundary();

  kb_bnd_handle hbnd;
  hbnd = kb_bnd_alloc();

  for (std::vector<Boundary>::const_iterator it = boundary.begin();
       it != boundary.end(); ++it) {
    addBoundary(*it, hbnd);
  }

  error = kb_ugrid_set_boundaries(ug, hbnd);
  KB_CHECK_STATUS(error, "Could not set boundaries");
}

void Kombyne::addBoundary(Boundary bound, kb_bnd_handle hbnd)
{
  int error;

  const std::vector<int32_t>& tris = bound.tris();
  const std::vector<int32_t>& quads = bound.quads();

  if( 0 == tris.size() && 0 == quads.size() )
    throw std::runtime_error("Empty boundary");

  std::string root("Tag");
  std::string bc = root + ' ' + std::to_string(bound.tag());

  addTriangles(tris, hbnd, bc);
  addQuads(quads, hbnd, bc);
}

void Kombyne::addTriangles(std::vector<int32_t> tris,
                           kb_bnd_handle hbnd, std::string bc)
{
  int error;

  kb_var_handle ht = kb_var_alloc();
  error = kb_var_seti(ht, KB_MEM_BORROW, 1, tris.size(), tris.data());
  KB_CHECK_STATUS(error, "Could not set Triangle cell array");
std::cerr << "Add Triangles to " << bc << std::endl;
  error = kb_bnd_add_cells(hbnd, KB_CELLTYPE_TRI, ht, bc.c_str());
  KB_CHECK_STATUS(error, "Could not set Triangle cells");
}

void Kombyne::addQuads(std::vector<int32_t> quads,
                       kb_bnd_handle hbnd, std::string bc)
{
  int error;

  kb_var_handle hq = kb_var_alloc();
  error = kb_var_seti(hq, KB_MEM_BORROW, 1, quads.size(), quads.data());
  KB_CHECK_STATUS(error, "Could not set Quad cell array");
  error = kb_bnd_add_cells(hbnd, KB_CELLTYPE_QUAD, hq, bc.c_str());
  KB_CHECK_STATUS(error, "Could not add Quad cells");
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

kb_pipeline_data_handle Kombyne::addPipelineData(kb_ugrid_handle ug)
{
  int error;

  int32_t domain = tinf_iris_rank(m_comm, &error);
  int32_t ndomains = tinf_iris_number_of_processes(m_comm, &error);

  int64_t timestep=0;
  m_problem.value("info:step",&timestep);
  double time=0.0;
  m_problem.value("info:timestep",&time);
std::cerr << "Timestep " << timestep << " Time " << time << std::endl;

  kb_mesh_handle hmesh = (kb_mesh_handle)ug;

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

void Kombyne::addFields(kb_ugrid_handle ug)
{
  int error;

  kb_fields_handle hfield = kb_fields_alloc();

  for(std::vector<Field>::iterator it = m_fields.begin(); 
      it != m_fields.end(); ++it) {
    const char* name = it->name();
    error = tinf_solution_get_outputs_at_nodes(m_soln, it->type(), 0,
                                               m_mesh.nNodes01(), 1, &name,
                                               it->values());
    TINF_CHECK_SUCCESS(error, "Failed to retrieve Solver output values");

    kb_var_handle hvar = kb_var_alloc();
    error = kb_var_setd(hvar, KB_MEM_BORROW, 1, m_mesh.nNodes01(),it->values());
    KB_CHECK_STATUS(error, "Could not create field data variable");
    error = kb_fields_add_var(hfield, it->name(), KB_CENTERING_POINTS, hvar);
    KB_CHECK_STATUS(error, "Could not add field data");
  }

  error = kb_ugrid_set_fields(ug, hfield);
  KB_CHECK_STATUS(error, "Could not add fields to mesh");
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

void Kombyne::addSamples()
{
  int error;

  for(std::vector<Field>::iterator it = m_fields.begin(); 
      it != m_fields.end(); ++it) {
    if( strncmp(it->name(),"Residual",8) ) {
      double sample = l2norm(m_mesh.nNodes01(), it->values());
      error = kb_add_sample(it->name(), sample);
      KB_CHECK_STATUS(error, "Could not add sample");
    }
  }
}

