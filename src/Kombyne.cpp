#ifdef __GNUG__
  #pragma implementation "Kombyne.h"
#endif

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
}

Kombyne::~Kombyne()
{
  kb_finalize();
}
