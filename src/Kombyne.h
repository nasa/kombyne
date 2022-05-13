#pragma once

#include <vector>
#include <string>
#include <mpi.h>
#include <kombyne_execution.h>
#include <kombyne_data.h>
#include <kombyne_core_types.h>
#include "tinf_enum_definitions.h"
#include "pancake_cxx/Problem.h"
#include "UMesh.h"

namespace VisKombyne
{

class Field
{
  public:
    Field(const char* name, TINF_DATA_TYPE datatype) :
      m_name(name), m_datatype(datatype), m_values(NULL) {}

    virtual ~Field() { if( m_values ) free(m_values); }

    inline void size(int64_t npoints)
    {
      m_values = (double*)malloc(npoints*sizeof(double));
      if( NULL == m_values )
        throw std::runtime_error("Failed to allocate field values");
    }

    inline const char* name() const { return m_name.c_str(); }
    inline enum TINF_DATA_TYPE type() const { return m_datatype; }
    inline double* values() const { return m_values; }

  private:
    std::string m_name;
    enum TINF_DATA_TYPE m_datatype;
    double* m_values;
};


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
     * @param anals  Number of analysis ranks (0 for in-situ)
     */
    Kombyne(void* problem, void* mesh, void* soln, void* comm, int32_t anals=0);

    /**
     * Destructor.
     */
    virtual ~Kombyne();

    /**
     * Check to see if need to process this timestep.
     *
     * @returns true if need to process this timestep.
     */
    bool processTimestep();

    /**
     * Execute the Kombyne pipeline.
     */
    void execute();

  private:
    inline void createFields();
    inline kb_ugrid_handle addMesh();
    inline void addNodes(kb_ugrid_handle ug);
    inline void addConnectivity(kb_ugrid_handle ug);
    inline void addGhostNodes(kb_ugrid_handle ug);
    inline void addGhostCells(kb_ugrid_handle ug);
    inline void addBoundaries(kb_ugrid_handle ug);
    inline void addBoundary(Boundary* bound, kb_bnd_handle hbnd);
    inline void addTriangles(std::vector<int32_t>& tris,
                             kb_bnd_handle hbnd, std::string bc);
    inline void addQuads(std::vector<int32_t>& quads,
                         kb_bnd_handle hbnd, std::string bc);
    inline void addPipelineCollection();
    inline kb_pipeline_data_handle addPipelineData(kb_ugrid_handle ug);
    inline void addFields(kb_ugrid_handle ug);
    inline double l2norm(int64_t npoints, double* values);
    inline void addSamples();

  private:
    pancake::Problem m_problem;
    UMesh m_mesh;
    void* m_soln;
    void* m_comm;
    MPI_Comm m_split;
    kb_role m_newrole;

    int64_t m_timestep;

    std::vector<Field> m_fields;

    kb_pipeline_collection_handle m_hp;
};

} // namespace VisKombyne
