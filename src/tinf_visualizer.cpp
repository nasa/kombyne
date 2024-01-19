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

#include <iostream>
#include <stdexcept>

#include "tinf_iris.h"
#include "tinf_visualizer.h"
#include "Kombyne.h"

#define TINF_CHECK_SUCCESS(error, msg) ({ \
  if( TINF_SUCCESS != error ) { \
    std::stringstream ss; \
    ss << error; \
    std::string message = std::string(msg) + ": " + ss.str(); \
    throw std::runtime_error(message.c_str()); \
  } \
})

int32_t
tinf_visualizer_create(void **visual, void *problem, void *mesh,
                       void *solution, void *comm)
{
  try {
    int32_t error;
    int32_t nproc = tinf_iris_number_of_processes(comm, &error);
    TINF_CHECK_SUCCESS(error, "Could not determine the number of processors");

    VisKombyne::Kombyne* vis = new VisKombyne::Kombyne(problem, mesh, solution,
                                                       comm, nproc);

    *visual = (void*)vis;

    return TINF_SUCCESS;
  } catch( std::runtime_error& e) {
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

    if( vis->processTimestep() )
      vis->execute();

    return TINF_SUCCESS;
  } catch( std::runtime_error& e) {
    std::cerr << e.what() << std::endl;
  }

  return TINF_FAILURE;
}
