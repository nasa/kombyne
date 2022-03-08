#pragma once

#include <vector>
#include <string>
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
    inline void addMesh(void* mesh);
    inline void getNodes(void* mesh);
    inline void buildConnectivity(void* mesh);
    inline void flagGhostNodes(void* mesh);
    inline void flagGhostCells(void* mesh);
    inline std::vector<int64_t> boundaryTags(void* mesh);
    inline void addTriangles(void* mesh, std::vector<int64_t> tris,
                             kb_bnd_handle hbnd, std::string bc);
    inline void addQuads(void* mesh, std::vector<int64_t> quads,
                         kb_bnd_handle hbnd, std::string bc);
    inline void addBoundary(void* mesh, int64_t tag);
    inline void addBoundaries(void* mesh);
    inline void addPipelineCollection();
    inline void addPipelineData(void* prob);
    inline void execute();
    inline void addPipeline(void* prob);
    inline double rms(int64_t npoints, double* values);
    inline void addFields(void* soln, int64_t npoints);

  private:
    void* m_problem;
    void* m_mesh;
    void* m_soln;
    void* m_comm;
    MPI_Comm m_split;
    kb_role m_newrole;

    int64_t m_ncell01;
    kb_ugrid_handle m_ug;
    kb_pipeline_collection_handle m_hp;
    kb_pipeline_data_handle m_hpd;
    kb_controls_handle m_hpc;
};

} // namespace VisKombyne
