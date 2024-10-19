#ifndef _TINFSTATUS_H_
#define _TINFSTATUS_H_

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <exception>
#include <string>
#include <sstream>

#include "tinf_enum_definitions.h"

#define TINF_CHECK_STATUS(error, msg) \
({ \
  int32_t _error = (error); \
  if( TINF_SUCCESS != (_error) ) { \
    std::stringstream ss; \
    ss << (_error); \
    std::string message = std::string(msg) + ": " + ss.str(); \
    throw std::runtime_error(message.c_str()); \
  } \
})

#define TINF_CHECK_STATUS_ERROR(error, msg) \
({ \
  int32_t _error = (error); \
  if( TINF_SUCCESS != (_error) ) { \
    printf("%s: %d\n",msg,_error); \
    return _error; \
  } \
})

#endif
