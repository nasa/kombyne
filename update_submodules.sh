#!/usr/bin/env bash

set -u
set -e

subpacks=${1:-"ci_tools build-tools pancake libcore slat one-ring refine nfe sfe fun3d"}

for i in $subpacks
do
  if test x"none" == x"$subpacks"; then break; fi

  git submodule update --init $i
  if test -x $i/update_submodules.sh
  then
    case $i in
      nfe)
        (cd $i; ./update_submodules.sh "libgbu libmeshio libpartition libpreproc")
        ;;
      fun3d)
        (cd $i; ./update_submodules.sh "sparskit-interface fluda_binaries comploader")
        ;;
      vista)
        (cd $i; ./update_submodules.sh "plugins")
        ;;
      *)
        (cd $i; ./update_submodules.sh none)
        ;;
    esac
  fi
done
