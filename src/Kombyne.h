#pragma once

#include <mpi.h>
#include <kombyne_execution.h>
#include <kombyne_data.h>
#include <kombyne_core_types.h>

namespace VisKombyne
{

class Kombyne
{
  public:
    /**
     * Constructor.
     *
     * @param problem  Problem description object
     * @param mesh  Mesh object
     * @param soln  Solution object
     * @param comm  Communications object
     */
    Kombyne(void* problem, void* mesh, void* soln, void* comm, int32_t sims);

    /**
     * Destructor.
     */
    virtual ~Kombyne();

  private:
    void* m_problem;
    void* m_mesh;
    void* m_soln;
    void* m_comm;
    MPI_Comm m_split;
    kb_role m_newrole;
};

} // namespace VisKombyne
