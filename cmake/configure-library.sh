#!/usr/bin/env bash

libname=$1
libdir=$2
targettype=$3

targetname=$(jq -r '.name' < "$libdir/Build.json")
header_only=$(jq -r '.header_only' < "$libdir/Build.json")
api_library=$(jq -r '.api_library' < "$libdir/Build.json")

if ! include_path=$(jq -r '.include_path' < "$libdir/Build.json"); then
  include_path="minecpp/$libname"
fi

if [[ $include_path = "null" ]];  then
  include_path="minecpp/$libname"
fi

libname_underscore=${libname//\//_}

if [[ $header_only != "true" ]]; then
  mkdir -p "$libdir/src"
fi

if [[ $targettype == "library" ]]; then
  mkdir -p "$libdir/include/$include_path"
fi

function generate_cmake_target() {
  echo "set(MINECPP_${libname_underscore^^}_DIR \${CMAKE_CURRENT_SOURCE_DIR})"
  echo ""
  if [[ $targettype == "executable" ]]; then
    echo "add_executable($targetname)"
  elif [[ $header_only == "true" ]]; then
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

  if pubdeps=$(jq -r '.dependencies.public[]' < "$libdir/Build.json" 2>/dev/null); then
    echo "        LINK_PUBLIC"
    for dep in $pubdeps; do
      echo "        $dep"
    done
  fi

  if privdeps=$(jq -r '.dependencies.private[]' < "$libdir/Build.json" 2>/dev/null); then
    echo "        LINK_PRIVATE"
    for dep in $privdeps; do
      echo "        $dep"
    done
  fi

  if ifdeps=$(jq -r '.dependencies.interface[]' < "$libdir/Build.json" 2>/dev/null); then
    echo "        INTERFACE"
    for dep in $ifdeps; do
      echo "        $dep"
    done
  fi

  echo ")"

  if [[ $api_library == "true" ]]; then
    echo ""
    echo "add_subdirectory(\"api\")"
  fi
}

generate_cmake_target > "$libdir/CMakeLists.txt"

if [[ $header_only != "true" ]]; then
  ./cmake/generate-src.sh "$libname" "$libdir" "$targetname" "" $include_path > "$libdir/src/CMakeLists.txt" "$targettype"
fi

if [[ $api_library == "true" ]]; then
  ./cmake/configure-library.sh "$libname""_api" "$libdir/api" "library"
fi