#ifndef _EXECUTIONTIME_H_
#define _EXECUTIONTIME_H_

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <exception>
#include <stdexcept>
#include <cstdlib>
#include <cstring>
#include <string>
#include <sstream>
#include <complex>
#include <vector>
#include <chrono>

#include <stdio.h>

namespace pancake
{
/**
 * A Class to encapsulate and facilitate the interrogation of a T-Infinity
 * Problem description.
 */
class ExecutionTimer
{
public:
  /**
   * Construct an ExecutionTimer
   */
  ExecutionTimer() : m_start(std::chrono::steady_clock::now()) {}

  /**
   * Determine elapsed time of exection since construction/reset.
   *
   * @returns Number of seconds of execution
   **/
  double elapsed() const
  {
    std::chrono::steady_clock::time_point t = std::chrono::steady_clock::now();

    std::chrono::duration<double> time_span =
      std::chrono::duration_cast<std::chrono::duration<double>>(t - m_start);

    return time_span.count();
  }

  /**
   * Reset the execution timer.
   **/
  void reset()
  {
    m_start = std::chrono::steady_clock::now();
  }

private:
  std::chrono::steady_clock::time_point m_start;
};
} // namespace pancake

#endif
