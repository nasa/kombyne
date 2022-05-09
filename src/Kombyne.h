#pragma once

#include <vector>
#include <string>
#include <mpi.h>
#include <kombyne_execution.h>
#include <kombyne_data.h>
#include <kombyne_core_types.h>
#include "tinf_enum_definitions.h"
#include "pancake_cxx/Problem.h"

namespace VisKombyne
{

class Nodes
{
  public:
    Nodes() : m_npoints(0), m_x(NULL), m_y(NULL), m_z(NULL) {}

    virtual ~Nodes() { if(0 != m_npoints) { free(m_x); free(m_y); free(m_z); } }

    void size(int64_t npoints)
    {
      m_x = (double*)malloc(npoints*sizeof(double));
      m_y = (double*)malloc(npoints*sizeof(double));
      m_z = (double*)malloc(npoints*sizeof(double));
      if( NULL == m_x || NULL == m_y || NULL == m_z ) {
        if( m_z ) free(m_z);
        if( m_y ) free(m_y);
        if( m_x ) free(m_x);
        throw std::runtime_error("Failed to allocate Node coordinates");
      }
      m_npoints = npoints;
    }

    inline int64_t size() const { return m_npoints; }
    inline double* x() const { return m_x; }
    inline double* y() const { return m_y; }
    inline double* z() const { return m_z; }

  private:
    int64_t m_npoints;
    double* m_x;
    double* m_y;
    double* m_z;
};


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
     * Execute the Kombyne pipeline.
     */
    void execute();

  private:
    inline void addMesh();
    inline void getNodes();
    inline void addNodes();
    inline void buildConnectivity();
    inline void flagGhostNodes();
    inline void flagGhostCells();
    inline std::vector<int64_t> boundaryTags(int64_t ntri, int64_t nquad);
    inline void addTriangles(std::vector<int64_t> tris,
                             kb_bnd_handle hbnd, std::string bc);
    inline void addQuads(std::vector<int64_t> quads,
                         kb_bnd_handle hbnd, std::string bc);
    inline void addBoundary(int64_t tag, kb_bnd_handle hbnd);
    inline void addBoundaries();
    inline void addPipelineCollection();
    inline kb_pipeline_data_handle addPipelineData();
    inline double l2norm(int64_t npoints, double* values);
    inline void getFields();
    inline void addFields();
    inline void addSamples();

  private:
    pancake::Problem m_problem;
    void* m_mesh;
    void* m_soln;
    void* m_comm;
    MPI_Comm m_split;
    kb_role m_newrole;

    bool m_moving_mesh;
    Nodes m_nodes;
    int64_t m_ncell01;
    std::vector<Field> m_fields;

    kb_ugrid_handle m_ug;
    kb_pipeline_collection_handle m_hp;
    kb_controls_handle m_hc;

    int32_t* m_cellconnects;
    int32_t* m_ghost_nodes;
    int32_t* m_ghost_cells;
    std::vector<int32_t*> m_tris;
    std::vector<int32_t*> m_quads;
};

} // namespace VisKombyne
