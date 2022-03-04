# -*- Autoconf -*- to force emacs autoconf mode

# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.69)

AC_INIT([kombyne], [1.0.0], [fun3d-support@lists.nasa.gov])

AC_CONFIG_HEADERS(config.h)
AC_CONFIG_AUX_DIR(config)
AC_CONFIG_SRCDIR([src/tinf_visualizer.cpp])

#AM_INIT_AUTOMAKE([tar-pax])

AX_CONFIG_PKG_DIR
AX_BUILD_TOOLS_LOCATION
AC_CONFIG_MACRO_DIR([m4])

AC_SUBST([ACLOCAL_AMFLAGS], ["-I ./m4 -I ${ax_cv_path_build_tools}/aclocal \${ACLOCAL_FLAGS}"])

AM_INIT_AUTOMAKE([1.11 tar-ustar -Wno-portability])

LT_PREREQ([2.4.2])
LT_INIT([dlopen])

AC_PROG_CXX(icpc armclang++ g++)
AC_PROG_CC
AM_PROG_CC_C_O

AX_CXX_COMPILE_STDCXX([11])

# Check for pancake
AS_VAR_SET_IF([with_pancake],[],[AS_VAR_SET([with_pancake],["subpackage"])])
AX_PANCAKE_REQUIRED

AC_CONFIG_FILES( \
	Makefile \
	src/Makefile \
	)

AC_OUTPUT


AC_MSG_RESULT([

Configuration (Tinf Dynamic Loader):

      Source code location: ${srcdir}
      C++ Compiler:         ${CXX}
      C++ flags:            ${CXXFLAGS}
      Linker flags:         ${LDFLAGS}

])
