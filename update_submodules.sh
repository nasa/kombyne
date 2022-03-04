#!/usr/bin/env bash

set -u
set -e

subpacks=${1:-"build-tools pancake"}

for i in $subpacks
do
  if test x"none" == x"$subpacks"; then break; fi

  git submodule update --init $i
  if test -x $i/update_submodules.sh
  then
    case $i in
      *)
        (cd $i; ./update_submodules.sh none)
        ;;
    esac
  fi
done
