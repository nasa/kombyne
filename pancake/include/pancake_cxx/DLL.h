#ifndef _DLL_
#define _DLL_

#include <exception>
#include <stdexcept>
#include <iostream>
#include <string>
#include <ltdl.h>

namespace pancake {
  /**
   * A Class to encapsulate the loading and manipulation of Dlopen(3)
   * Dynamically Loadable Libraries (plugins) via Libtool's libltdl
   * functionality.
   */
  class DLL
  {
    public:
      typedef void* (*symbol_f)();

     /**
      * Initialize and load a Dynamically Loadable Library (DLL) via
      * Libtool's libltdl.
      *
      * @param name  Name of the DLL to load
      * @param path  Search path for @p name
      * @throws std::runtime_error
      **/
      DLL(const char* name, const char* path=NULL) : m_name(name), dll(NULL)
      {
        /* Initialize libltdl. */
        if( lt_dlinit() != 0 ) {
          std::string message = std::string("Initialization ") +
                                std::string(lt_dlerror());
          throw std::runtime_error(message);
        }

        if( path ) {
          if( lt_dlsetsearchpath(path) != 0 ) {
            std::string message = std::string("Search path ") +
                                  std::string(lt_dlerror());
            throw std::runtime_error(message);
          }
          m_path = std::string(path);
        }

//std::cout << "Loading " << std::string(name) << std::endl;
        if( (dll=lt_dlopenext(name)) == NULL ) {
//std::cout << "Failed Loading" << std::endl;
            std::string message = std::string("Loading ") +
                                  std::string(name) + std::string(", ") +
                                  std::string(lt_dlerror());
//std::cout << "  Msg: " << message << std::endl;
            throw std::runtime_error(message);
        }
//std::cout << "Loaded " << std::string(name) << std::endl;
      }

     /**
      * Destructor that closes the DLL and exits Libtool's libltdl.
      */
      virtual ~DLL()
      {
        if( dll )
          close();

        int num;
        if( (num=lt_dlexit()) != 0 ) {
          std::string message = std::string("lt_dlexit with error(s): ") +
                                std::string(lt_dlerror());
          std::cerr << message;
        }
      }

     /**
      * Retrieve a given symbol from the DLL.
      *
      * @param name  Name of the symbol to retrieve
      * @returns A pointer to the symbol
      * @throws std::runtime_error
      **/
      symbol_f symbol(const char* name) const
      {
        symbol_f sym;

        if( (sym=(symbol_f)lt_dlsym(dll,name)) == NULL) {
          std::string message = std::string("Library does NOT contain symbol ") +
                                std::string(name) + std::string(": ") +
                                std::string(lt_dlerror());
          throw std::runtime_error(message);
        }

        return sym;
      }

     /**
      * Close the DLL.
      *
      * @throws std::runtime_error
      **/
      void close()
      {
        if( lt_dlclose(dll) != 0 ) {
          std::string message = std::string("DLL close error: ") +
                                std::string(lt_dlerror());
          throw std::runtime_error(message);
        }

        dll = NULL;
      }

     /**
      * Return the name of the DLL.
      **/
      inline const char* dll_name() const { return m_name.c_str(); }

     /**
      * Return the path of the DLL.
      **/
      inline const char* path_name() const { return m_path.c_str(); }

    private:
      std::string m_name;
      std::string m_path;
      lt_dlhandle dll;
  };
}
#endif
