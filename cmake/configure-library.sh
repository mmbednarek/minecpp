#!/usr/bin/env bash

libname=$1
targetname=$(jq -r '.name' < "library/$libname/Build.json")
header_only=$(jq -r '.header_only' < "library/$libname/Build.json")

if ! include_path=$(jq -r '.include_path' < "library/$libname/Build.json"); then
  include_path="minecpp/$libname"
fi

if [[ $include_path = "null" ]];  then
  include_path="minecpp/$libname"
fi

libname_underscore=${libname//\//_}

if [[ $header_only != "true" ]]; then
  mkdir -p "library/$libname/src"
fi

mkdir -p "library/$libname/include/$include_path"

function generate_cmake_target() {
  echo "set(MINECPP_${libname_underscore^^}_DIR \${CMAKE_CURRENT_SOURCE_DIR})"
  echo ""
  if [[ $header_only == "true" ]]; then
    echo "add_library($targetname INTERFACE)"
  else
    echo "add_library($targetname STATIC)"
  fi
  echo ""
  echo "# Public include headers"
  if [[  $header_only == "true"  ]]; then
    echo "target_include_directories($targetname INTERFACE \${CMAKE_CURRENT_SOURCE_DIR}/include)"
  else
    echo "target_include_directories($targetname PUBLIC \${CMAKE_CURRENT_SOURCE_DIR}/include)"
    echo ""
    echo "# Source subdirectory"
    echo "add_subdirectory(\"src\")"
  fi
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

  if ifdeps=$(jq -r '.dependencies.interface[]' < "library/$libname/Build.json" 2>/dev/null); then
    echo "        INTERFACE"
    for dep in $ifdeps; do
      echo "        $dep"
    done
  fi

  echo ")"
}

generate_cmake_target > "library/$libname/CMakeLists.txt"

if [[  $header_only != "true"  ]]; then
  ./cmake/generate-src.sh "$libname" "$targetname" "" $include_path > "library/$libname/src/CMakeLists.txt"
fi