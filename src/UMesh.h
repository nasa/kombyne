#pragma once

#include <string>
#include <vector>

namespace VisKombyne
{

class Boundary
{
  public:
#ifdef TEST_CONSTRUCTION
    Boundary(const Boundary& copy) : m_tag(copy.m_tag), m_name(copy.m_name),
      m_tris(copy.m_tris), m_quads(copy.m_quads)
    { std::cerr << "Copy Construct Boundary " << copy.m_tag << std::endl; }
    Boundary(int64_t tag, std::string name) : m_tag(tag), m_name(name)
    { std::cerr << "Construct Boundary " << m_tag << std::endl; }
    virtual ~Boundary()
    { std::cerr << "Destroy Boundary " << m_tag << ", " << m_tris.size() <<
      std::endl; }
#endif

    Boundary(int64_t tag, std::string name) : m_tag(tag), m_name(name) {}

    inline void addTri(int64_t nodes[3])
      { m_tris.insert(m_tris.end(), nodes, nodes+3); }
    inline void addQuad(int64_t nodes[4])
      { m_quads.insert(m_quads.end(), nodes, nodes+4); }

    inline int64_t tag() const { return m_tag; }
    inline std::string name() const { return m_name; }
    inline std::vector<int32_t>& tris() { return m_tris; }
    inline std::vector<int32_t>& quads() { return m_quads; }

  private:
    int64_t m_tag;
    std::string m_name;
    std::vector<int32_t> m_tris;
    std::vector<int32_t> m_quads;
};


class UMesh
{
  public:
    UMesh(void* mesh, void* comm);
    virtual ~UMesh();

    void getNodes();
    inline void moving(bool moving) { m_moving = moving; }
    inline void updateCoordinates() { if( m_moving ) getNodes(); }

    inline int64_t nNodes01() const { return m_nnodes01; }
    inline double* x() { return m_x; }
    inline double* y() { return m_y; }
    inline double* z() { return m_z; }
    inline int64_t nCell01() const { return m_ncell01; }
    inline int64_t cellConnectsSize() const { return m_lconn; }
    inline int32_t* cellConnects() const { return m_cellconnects; }
    inline int32_t* ghostNodes() const { return m_ghost_nodes; }
    inline int32_t* ghostCells() const { return m_ghost_cells; }
    inline std::vector<Boundary>& boundaries() { return m_bound; }

  private:
    inline void addNodes();
    inline void buildConnectivity();
    inline void addGhostNodes();
    inline void addGhostCells();
    inline void flagGhostNodes();
    inline void flagGhostCells();
    inline void addBoundaries();
    inline std::vector<int64_t> boundaryTags(int64_t ntri, int64_t nquad);
    inline void addBoundary(int64_t tag);

  private:
    void* m_mesh;
    void* m_comm;
    bool m_moving;

    int64_t m_nnodes01;
    double* m_x;
    double* m_y;
    double* m_z;
    int64_t m_ncell01;
    int64_t m_lconn;
    int32_t* m_cellconnects;
    int32_t* m_ghost_nodes;
    int32_t* m_ghost_cells;
    std::vector<Boundary> m_bound;
};

} // namespace VisKombyne
