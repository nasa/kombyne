#include <iostream>

#include "tinf_visualizer.h"
#include "Kombyne.h"

#define TINF_CHECK_SUCCESS(error, msg) ({ \
  if( TINF_SUCCESS == error ) { \
    std::stringstream ss; \
    ss << error; \
    std::string message = std::string(msg) + ": " + ss.str(); \
    std::cerr << message << std::endl; \
  } \
})

int32_t
tinf_visualizer_create(void **visual, void *problem, void *mesh,
                       void *solution, void *comm)
{
  try {
    int32_t error;
    int32_t nproc = tinf_iris_number_of_processes(comm, &error);
    TINF_CHECK_STATUS(error, "Could not determine the number of processors");

    VisKombyne::Kombyne* vis = new VisKombyne::Kombyne(problem, mesh, solution,
                                                       comm, nproc);

    *visual = (void*)vis;

    return TINF_SUCCESS;
  } catch( std::runtime_exception& e) {
    std::cerr << e.what() << std::endl;
  }

  return TINF_FAILURE;
}

int32_t
tinf_visualizer_destroy(void **visual)
{
  VisKombyne::Kombyne* vis = (VisKombyne::Kombyne*)(*visual);
  delete vis;

  return TINF_SUCCESS;
}

int32_t
tinf_visualizer(void *visual, _BOOL_ final_call)
{
  try {
    VisKombyne::Kombyne* vis = (VisKombyne::Kombyne*)(visual);

    vis.execute();

    return TINF_SUCCESS;
  } catch( std::runtime_exception& e) {
    std::cerr << e.what() << std::endl;
  }

  return TINF_FAILURE;
}
