#!/usr/bin/env bash

libname=$1
targetname=$(jq -r '.name' < "library/$libname/Build.json")

function generate_cmake_target() {
  echo "set(MINECPP_${libname^^}_DIR \${CMAKE_CURRENT_SOURCE_DIR})"
  echo ""
  echo "add_library($targetname)"
  echo ""
  echo "# Public include headers"
  echo "target_include_directories($targetname PUBLIC \${CMAKE_CURRENT_SOURCE_DIR}/include)"
  echo ""
  echo "# Source subdirectory"
  echo "add_subdirectory(\"src\")"
  echo ""
  echo "target_link_libraries($targetname"

  if pubdeps=$(jq -r '.dependencies.public[]' < "library/$libname/Build.json" 2>/dev/null); then
    echo "        LINK_PUBLIC"
    for dep in $pubdeps; do
      echo "        $dep"
    done
  fi

  if privdeps=$(jq -r '.dependencies.private[]' < "library/$libname/Build.json" 2>/dev/null); then
    echo "        LINK_PRIVATE"
    for dep in $privdeps; do
      echo "        $dep"
    done
  fi

  echo ")"
}

generate_cmake_target > "library/$libname/CMakeLists.txt"
./cmake/generate-src.sh "$libname" "$targetname" "" > "library/$libname/src/CMakeLists.txt"