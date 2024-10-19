# -*- Autoconf -*-
# autoconf macro to define pancake configuration options
#
# Assigned Shell Variables:
#   $with_pancake        Location of the pancake installation
#
# Assigned Output Variables:
#   @pancake_fcflags@    Pancake Fortran compiler flags
#   @pancake_cflags@     Pancake C compiler flags
#   @pancake_cxxflags@   Pancake C++ compiler flags
#   @pancakedir@         Pancake directory
#
# Assigned Macros:
#   HAVE_PANCAKE
#
# Assigned AM_CONDITIONALS:
#   BUILD_PANCAKE
#
AC_DEFUN([AX_PANCAKE],[

  AC_ARG_WITH(pancake,
          [[  --with-pancake[=ARG]    use pancake interfaces [ARG=no]]],
          [with_pancake=${withval}],     [with_pancake="no"])

  if test "${with_pancake}" == 'subpackage'
  then

    ax_abs_top_srcdir=$( cd $srcdir; pwd )

    AX_PATH_PACKAGE([pancake])

    AC_CHECK_FILE([${ax_cv_path_abs_pancake_srcdir}/pancake/include/tinf_mesh.h],
      [pancake_fcflags="\$(FC_MODINC)${ax_cv_path_abs_pancake_srcdir}/pancake/include"
       pancake_cflags="-I${ax_cv_path_abs_pancake_srcdir}/pancake/include"
       pancake_cxxflags="-I${ax_cv_path_abs_pancake_srcdir}/pancake/include"
       pancakedir="${ax_cv_path_abs_pancake_srcdir}/pancake"
      ],
      [AC_MSG_ERROR([pancake sub-package not found in expected location ${ax_cv_path_abs_pancake_srcdir}/pancake, try using --with-pancake=...])
      ])

    AC_DEFINE([HAVE_PANCAKE],[1],[Pancake headers available])
    AM_CONDITIONAL(BUILD_PANCAKE,false)

  else

    if test "${with_pancake}" != 'no'
    then

      AC_CHECK_FILE([${with_pancake}/include/tinf_mesh.h],
        [pancake_cflags="-I${with_pancake}/include"
         pancake_cxxflags="-I${with_pancake}/include"
         pancake_fcflags='$(FC_MODINC)'"${with_pancake}/include"
         pancakedir="${with_pancake}"
        ],
        [AC_MSG_ERROR([pancake tinf_mesh.h not found in ${with_pancake}/include])])

      AC_DEFINE([HAVE_PANCAKE],[1],[Pancake headers available])

    fi

    AM_CONDITIONAL(BUILD_PANCAKE,false)

  fi

  AC_SUBST([pancake_cflags])
  AC_SUBST([pancake_cxxflags])
  AC_SUBST([pancake_fcflags])
  AC_SUBST([pancakedir])

  AM_COND_IF([BUILD_PANCAKE],[AC_CONFIG_SUBDIRS([pancake])])

])


# autoconf macro to require pancake configuration options be defined
#
# Assigned Shell Variables:
#   $with_pancake        Location of the pancake installation
#
# Assigned Output Variables:
#   @pancake_fcflags@    Pancake Fortran compiler flags
#   @pancake_cflags@     Pancake C compiler flags
#   @pancake_cxxflags@   Pancake C++ compiler flags
#
# Assigned Macros:
#   HAVE_PANCAKE
#
# Assigned AM_CONDITIONALS:
#   BUILD_PANCAKE
#
AC_DEFUN([AX_PANCAKE_REQUIRED],[

AX_PANCAKE

if test "${with_pancake}" == 'no'
then
  AC_MSG_ERROR([pancake is required to define interfaces])
fi

])
