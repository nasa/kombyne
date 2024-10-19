# -*- Autoconf -*-
# autoconf macro to define package configuration options
#
# Assigned Shell Variables:
#   $ax_path_abs_pkg_srcdir   Location of the package top level source directory
#   $ax_path_abs_pkg_builddir Location of the package top level build directory
#
# Assigned Output Variables:
#
# Assigned Macros:
#
# Assigned AM_CONDITIONALS:
#
AC_DEFUN([AX_CONFIG_PKG_DIR], [
  AS_VAR_SET_IF([ax_cv_path_abs_pkg_srcdir],[],
    [AS_VAR_PUSHDEF([ax_path_abs_pkg_srcdir], [ax_cv_path_abs_pkg_srcdir])dnl
      ax_path_abs_pkg_srcdir=$( cd $srcdir; pwd )
      AC_CACHE_CHECK([for top level package directory],
                     [ax_path_abs_pkg_srcdir],
                     [AS_VAR_SET([ax_path_abs_pkg_srcdir],
                                 [$ax_path_abs_pkg_srcdir])])
      AS_VAR_SET([ac_configure_args],
                 ["$ac_configure_args ax_path_abs_pkg_srcdir=$ax_path_abs_pkg_srcdir"])dnl
     AS_VAR_POPDEF([ax_path_abs_pkg_srcdir])dnl

     AS_VAR_PUSHDEF([ax_path_abs_pkg_builddir],
                    [ax_cv_path_abs_pkg_builddir])dnl
      ax_path_abs_pkg_builddir=$( pwd )
      AC_CACHE_CHECK([for top level package build directory],
                     [ax_path_abs_pkg_builddir],
                     [AS_VAR_SET([ax_path_abs_pkg_builddir],
                                 [$ac_abs_builddir])])
      AS_VAR_SET([ac_configure_args],
                 ["$ac_configure_args ax_path_abs_pkg_builddir=$ax_path_abs_pkg_builddir"])dnl
     AS_VAR_POPDEF([ax_path_abs_pkg_builddir])dnl
    ]
  )
])


# autoconf macro to check that package directory was given
#
# Assigned Shell Variables:
#
# Assigned Output Variables:
#
# Assigned Macros:
#
# Assigned AM_CONDITIONALS:
#
AC_DEFUN([AX_CHECK_PKG_DIR], [
  AS_VAR_SET_IF(ax_cv_path_abs_pkg_srcdir,
                [AS_VAR_SET_IF(ax_cv_path_abs_pkg_builddir,[],
                               [AC_MSG_ERROR([Configuring $1 as a "package" requires having called [AX_CONFIG_PKG_DIR]])])],
                [AC_MSG_ERROR([Configuring $1 as a "package" requires having called [AX_CONFIG_PKG_DIR]])])
])


# _AX_PATH_FILE(VARIABLE, FILE-TO-CHECK-FOR, PATH, [VALUE-IF-NOT-FOUND])
# ------------------------------------------------------------------------
AC_DEFUN([_AX_PATH_FILE], [
  # Extract the first word of "$2", so it can be a file name with args.
  set dummy $2; ac_word=$[2]
  AC_MSG_CHECKING([for $ac_word])
  AC_CACHE_VAL([ac_cv_path_$1],
  [case $$1 in
    [[\\/]]* | ?:[[\\/]]*)
    ac_cv_path_$1="$$1" # Let the user override the test with a path.
    ;;
    *)
    _AS_PATH_WALK([$3],
                  [AC_CHECK_FILE(["$as_dir/$ac_word"],
                                 [AS_IF([test -f "$as_dir/$ac_word"],
                                        [ac_cv_path_$1="$as_dir/$ac_word"
                                         _AS_ECHO_LOG([found $as_dir/$ac_word])
                                         break],
                                        [test -d "$as_dir/$ac_word"],
                                        [AS_IF([test -n "$(ls -l $as_dir/$ac_word)"],
                                               [ac_cv_path_$1="$as_dir/$ac_word"
                                                _AS_ECHO_LOG([found $as_dir/$ac_word])
                                                break])])])])
dnl If no 4th arg is given, leave the cache variable unset,
dnl so AX_PATH_FILES will keep looking.
    m4_ifvaln([$4],[  test -z "$ac_cv_path_$1" && ac_cv_path_$1="$4"])dnl
    ;;
   esac])dnl
  $1=$ac_cv_path_$1
  if test -n "$$1"; then
    AC_MSG_RESULT([$$1])
  else
    AC_MSG_RESULT([no])
  fi
])# _AX_PATH_FILE


# AX_PATH_FILE(VARIABLE, FILE-TO-CHECK-FOR, PATH, [VALUE-IF-NOT-FOUND])
# -----------------------------------------------------------------------
AC_DEFUN([AX_PATH_FILE], [
  _AX_PATH_FILE($@)
  AC_SUBST([$1])dnl
])


# AX_PATH_FILES(VARIABLE, FILES-TO-CHECK-FOR, PATH, [VALUE-IF-NOT-FOUND])
# -----------------------------------------------------------------
AC_DEFUN([AX_PATH_FILES], [
  for ac_prog in $2
  do
    AX_PATH_FILE([$1], [$ac_prog], , [$4])
    test -n "$$1" && break
  done
  m4_ifvaln([$3], [test -n "$$1" || $1="$3"])dnl
])


# autoconf macro to find a given package beneath the package directory
#
# Assigned Shell Variables:
#   $ax_cv_path_abs_$1_srcdir   Location of the located package source directory
#   $ax_cv_path_abs_$1_builddir Location of the located package build directory
#
# Assigned Output Variables:
#
# Assigned Macros:
#
# Assigned AM_CONDITIONALS:
#
# AX_PATH_PACKAGE(PACKAGE-TO-CHECK-FOR)
# -----------------------------------------------------------------------
AC_DEFUN([AX_PATH_PACKAGE], [
  AX_CHECK_PKG_DIR([$1])
#echo "ax_cv_path_abs_pkg_srcdir $ax_cv_path_abs_pkg_srcdir"
#echo "ax_cv_path_abs_pkg_builddir $ax_cv_path_abs_pkg_builddir"
  AS_REQUIRE([_AS_PATH_SEPARATOR_PREPARE])
  AC_REQUIRE([AC_PROG_SED])

#echo "srcdir $srcdir"
  ax_abs_top_srcdir=$( cd $srcdir; pwd )
#echo "ax_abs_top_srcdir $ax_abs_top_srcdir"

  ax_search_path=$ax_abs_top_srcdir
  ax_dir=$ax_search_path
#echo "ax_dir $ax_dir"
  until test "$ax_dir" == "$ax_cv_path_abs_pkg_srcdir" -o -z "$ax_dir"
  do
    ax_dir=$(AS_DIRNAME(["$ax_dir"]))
#echo "ax_dir $ax_dir"
    ax_search_path="$ax_dir$PATH_SEPARATOR$ax_search_path"
#echo "Search $ax_search_path"
  done
#echo "Searching $ax_search_path"
#echo "To find $1"

  AS_VAR_PUSHDEF([ax_srcdir], [ax_cv_path_abs_$1_srcdir])dnl

    AC_CACHE_VAL([ax_srcdir],
                 [_AS_PATH_WALK([$ax_search_path],
#echo "as_dir: $as_dir"
                                [AC_CHECK_FILE(["${as_dir}/$1"],
                                               [AS_IF([test -d "${as_dir}/$1"],
                                                      [AS_IF([test -n "$(ls -l ${as_dir}/$1)"],
                                                             [AS_VAR_SET([ax_srcdir],["$as_dir"])
                                                              _AS_ECHO_LOG([found ${as_dir}/$1])
                                                              break])])])])])
    ax_srcdir=$(echo "$ax_srcdir" | $SED "s,\/$,,")
#echo "ax_srcdir: $ax_srcdir"

    AS_VAR_IF([ax_srcdir],[],
              [AC_MSG_ERROR([Could not find populated package directory for $1])])

    AS_VAR_PUSHDEF([ax_builddir], [ax_cv_path_abs_$1_builddir])dnl
      ax_rel_path=$(echo "$ax_srcdir" | $SED "s,$ax_cv_path_abs_pkg_srcdir,,")
#echo "ax_rel_path: $ax_rel_path"
      ax_builddir=$ax_cv_path_abs_pkg_builddir$ax_rel_path
#echo "ax_builddir: $ax_builddir"
    AS_VAR_POPDEF([ax_builddir])dnl
  AS_VAR_POPDEF([ax_srcdir])dnl

])# AX_PATH_PACKAGE
