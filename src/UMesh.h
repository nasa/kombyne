#pragma once

/*
 *  Notices:
 *  Copyright 2023 United States Government as represented by the
 *  Administrator of the National Aeronautics and Space Administration.
 *  No copyright is claimed in the United States under Title 17,
 *  U.S. Code. All Other Rights Reserved.
 *
 *  Disclaimers No Warranty: THE SUBJECT SOFTWARE IS PROVIDED "AS
 *  IS" WITHOUT ANY WARRANTY OF ANY KIND, EITHER EXPRESSED, IMPLIED,
 *  OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, ANY WARRANTY THAT
 *  THE SUBJECT SOFTWARE WILL CONFORM TO SPECIFICATIONS, ANY IMPLIED
 *  WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE,
 *  OR FREEDOM FROM INFRINGEMENT, ANY WARRANTY THAT THE SUBJECT
 *  SOFTWARE WILL BE ERROR FREE, OR ANY WARRANTY THAT DOCUMENTATION,
 *  IF PROVIDED, WILL CONFORM TO THE SUBJECT SOFTWARE. THIS AGREEMENT
 *  DOES NOT, IN ANY MANNER, CONSTITUTE AN ENDORSEMENT BY GOVERNMENT
 *  AGENCY OR ANY PRIOR RECIPIENT OF ANY RESULTS, RESULTING DESIGNS,
 *  HARDWARE, SOFTWARE PRODUCTS OR ANY OTHER APPLICATIONS RESULTING
 *  FROM USE OF THE SUBJECT SOFTWARE.  FURTHER, GOVERNMENT AGENCY
 *  DISCLAIMS ALL WARRANTIES AND LIABILITIES REGARDING THIRD-PARTY
 *  SOFTWARE, IF PRESENT IN THE ORIGINAL SOFTWARE, AND DISTRIBUTES
 *  IT "AS IS." 
 *
 *  Waiver and Indemnity:  RECIPIENT AGREES TO WAIVE ANY AND ALL
 *  CLAIMS AGAINST THE UNITED STATES GOVERNMENT, ITS CONTRACTORS
 *  AND SUBCONTRACTORS, AS WELL AS ANY PRIOR RECIPIENT.  IF RECIPIENT'S
 *  USE OF THE SUBJECT SOFTWARE RESULTS IN ANY LIABILITIES, DEMANDS,
 *  DAMAGES, EXPENSES OR LOSSES ARISING FROM SUCH USE, INCLUDING
 *  ANY DAMAGES FROM PRODUCTS BASED ON, OR RESULTING FROM, RECIPIENT'S
 *  USE OF THE SUBJECT SOFTWARE, RECIPIENT SHALL INDEMNIFY AND HOLD
 *  HARMLESS THE UNITED STATES GOVERNMENT, ITS CONTRACTORS AND
 *  SUBCONTRACTORS, AS WELL AS ANY PRIOR RECIPIENT, TO THE EXTENT
 *  PERMITTED BY LAW.  RECIPIENT'S SOLE REMEDY FOR ANY SUCH MATTER
 *  SHALL BE THE IMMEDIATE, UNILATERAL TERMINATION OF THIS AGREEMENT.
 */

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

    Boundary(int64_t tag, std::string& name) : m_tag(tag), m_name(name) {}

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
    UMesh(void* prob, void* mesh, void* comm);
    virtual ~UMesh();

    void getNodes();
    inline void moving(bool moving) { m_moving = moving; }
    inline bool moving() { return m_moving; }
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
    inline void addBoundaries(std::vector<std::string> families,
                              std::vector<int64_t> bc_tags);
    inline std::vector<int64_t> boundaryTags(int64_t ntri, int64_t nquad);
    inline void addBoundary(int64_t tag, std::string& family);

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
