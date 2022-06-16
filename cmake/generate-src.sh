#!/usr/bin/env bash

libname=$1
targetname=$2
sublib=$3

sublibs=$(find "library/$libname/src$sublib" -mindepth 1 -maxdepth 1 -type d | sort)
source_files=$(find "library/$libname/src$sublib" -maxdepth 1  -name "*.cpp" | sort)
include_files=$(find "include/minecpp/${libname}${sublib}" -maxdepth 1  -name "*.h" -or -name "*.hpp" | sort)

sublib2=${sublib//\//_}

echo "set(MINECPP_${libname^^}${sublib2^^}_INCLUDE_DIR \${MINECPP_INCLUDE_DIR}/$libname$sublib)"
echo ""
echo "target_sources($targetname PUBLIC"
echo "        # Source files"
for source_file in $source_files; do
echo "        \${CMAKE_CURRENT_SOURCE_DIR}/$(basename $source_file)"
done
echo ""
echo "        # Header files"
for include_file in $include_files; do
echo "        \${MINECPP_${libname^^}${sublib2^^}_INCLUDE_DIR}/$(basename $include_file)"
done
echo ")"
echo ""
echo "# Subdirectories"
for subsublib in $sublibs; do
    echo "add_subdirectory(\"$(basename $subsublib)\")"
done
echo ""

for subsublib in $sublibs; do
    ./cmake/generate-src.sh "$libname" "$targetname" "${sublib}/$(basename $subsublib)" > "library/$libname/src${sublib}/$(basename $subsublib)/CMakeLists.txt"
done