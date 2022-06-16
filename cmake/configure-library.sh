#!/usr/bin/env bash

libname=$1
pubdeps=$(jq -r '.dependencies.public[]' < "library/$libname/Build.json")
targetname=$(jq -r '.name' < "library/$libname/Build.json")

function generate_cmake_target() {
  echo "add_library($targetname)"
  echo "add_subdirectory(\"src\")"
  echo ""
  echo "target_link_libraries($targetname"
  echo "        LINK_PUBLIC"
  for dep in $pubdeps; do
  echo "        $dep"
  done
  echo ")"
}

generate_cmake_target > "library/$libname/CMakeLists.txt"
./cmake/generate-src.sh "$libname" "$targetname" "" > "library/$libname/src/CMakeLists.txt"