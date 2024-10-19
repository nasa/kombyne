#ifndef _TINFSTREAM_H_
#define _TINFSTREAM_H_

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <cstring>
#include <exception>
#include <stdexcept>

#include "tinf_enum_definitions.h"

#ifndef __HOSTDEVICEOP__
#define __HOSTDEVICEOP__
#endif

namespace pancake
{
/**
 * A Class to encapsulate and reading from a byte stream with optional byte
 * swapping.
 */

  class Stream {
  public:
    /**
     * Construct a Problem object from an opaque problem pointer.
     *
     * @param prob  Opaque Problem pointer
     */
    __HOSTDEVICEOP__
    Stream(std::size_t size, const char* const buffer, bool swap=false)
      : m_size(size), m_buffer(buffer), m_swap(swap), m_pos(0) {}

    /**
     * Return if data is byteswapped.
     *
     * @returns  true if swap is needed.
     */
    __HOSTDEVICEOP__
    inline bool swap() { return m_swap; }

    /**
     * Perform byteswap on item.
     *
     * @param size  Size of item in bytes
     * @param x  Item to byteswap
     */
    __HOSTDEVICEOP__
    inline void swap(int size, char* x)
    {
#if ( ( (defined(__BYTE_ORDER) && (__BYTE_ORDER==__LITTLE_ENDIAN)) || \
        (defined(_BYTE_ORDER) && (_BYTE_ORDER==_LITTLE_ENDIAN)) ||    \
        (defined(BYTE_ORDER) && (BYTE_ORDER==LITTLE_ENDIAN)) ||       \
        (defined(WINNT)) ) &&                                         \
      !defined(NO_BYTE_SWAP) )
#endif
      int sz = size-1;
      if( size > sizeof(char) ) {
        for( int ii=0; ii<size/2; ++ii ) {
          *(x+ii)      ^= *(x+(sz-ii));
          *(x+(sz-ii)) ^= *(x+ii);
          *(x+ii)      ^= *(x+(sz-ii));
        }
      }
    }

    /**
     * Set swap flag based on comparison to a given value.
     *
     * @param val  Data value to compare
     * @param size  Data size in bytes
     * @param nmemb  Number of items of data
     * @throws std::runtime_error
     */
    template<typename T>
    __HOSTDEVICEOP__
    inline void swap(T key)
    {
      T val;

      if( 1 == peek(&val) ) {
        if( key != val ) { // try to byteswap
          swap(sizeof(T), (char*)(&val));
          if( key == val ) {
            m_swap = !m_swap;
          } else {
            throw std::runtime_error("Swap still didn't read expected value");
          }
        }
      } else {
        throw std::runtime_error("Could not peek to test byteswap");
      }
    }

    /**
     * Set swap flag based on comparison to a given value.
     *
     * @param val  Data value to compare
     * @param size  Data size in bytes
     * @param nmemb  Number of items of data
     * @returns #TINF_ERROR_CODES
     */
    template<typename T>
    __HOSTDEVICEOP__
    inline enum TINF_ERROR_CODES swap_noexcept(T key)
    {
      T val;

      if( 1 == peek(&val) ) {
        if( key != val ) { // try to byteswap
          swap(sizeof(T), (char*)(&val));
          if( key == val ) {
            m_swap = !m_swap;
          } else {
            printf("Swap still didn't read expected value\n");
            return TINF_FAILURE;
          }
        }
      } else {
        printf("Could not peek to test byteswap\n");
        return TINF_FAILURE;
      }
      return TINF_SUCCESS;
    }

    /**
     * Read a number of items from the stream.
     *
     * @param ptr  Data storage of item(s) read
     * @param size  Data size in bytes
     * @param nmemb  Number of items of data
     * @returns number of items read
     */
    __HOSTDEVICEOP__
    inline std::size_t fread(void *data, std::size_t size, std::size_t nmemb,
                             int32_t rank=-1)
    {
      char* buf = (char*)data;

//printf("fread(%ld): %ld %ld '",m_pos,size,nmemb);
//printf("%02hhx%02hhx",m_buffer[m_pos+1],m_buffer[m_pos+0]);
//for(size_t i=2,ii=3; i<size*nmemb; i+=2,++ii)
//printf(" %02hhx%02hhx",m_buffer[m_pos+ii],m_buffer[m_pos+i]);
//printf("' %d",m_swap);
//if( 0 <= rank )
//printf(" on rank %d\n",rank);
//else
//printf("\n");

      memcpy(data, &(m_buffer[m_pos]), size*nmemb);
      if( size > sizeof(char) && m_swap )
        for(int i=0; i<nmemb; ++i) swap(size,&buf[i*size]);
      m_pos += size*nmemb;

      return nmemb;
    }

    /**
     * Peek ahead in the stream for a value.
     *
     * @param val  Data storage of item(s) peek
     * @param nmemb  Number of items of data
     */
    template<typename T>
    __HOSTDEVICEOP__
    inline std::size_t peek(T* val, std::size_t nmemb=1)
    {
      if( nmemb == fread((void*)val,sizeof(T),nmemb) ) {
        m_pos -= sizeof(T)*nmemb;
      }
      return nmemb;
    }

    /**
     * Rewind the stream to position.
     *
     * @param pos  New position of the stream
     */
    inline void rewind(std::size_t pos=0) { m_pos = pos; }

  private:
    std::size_t m_size;
    const char* m_buffer;
    std::size_t m_pos;
    bool        m_swap;
  };
}

#endif
