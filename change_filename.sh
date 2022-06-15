#!/usr/bin/env bash

file=$1

base=$(basename $file)
dir=$(dirname $file)

changed_base=$(./to_pascal.py $base)

source_directories=(
  api
  include
  library
  test
  service
  tool
)

mv "$dir/$base" "$dir/changed_base"

for dir in "${source_directories[@]}"; do
  while IFS= read -r file; do
    sed  -i "s/$base/$changed_base/g" $file
  done <  <(find $dir -regex '.+\.h' -or -regex '.+\.cpp' -or -regex '.+\.hpp' -or -regex '.+\.cc' -or -regex '.+\.proto' -or -regex '.+\.nbt' -or -name 'CMakeLists.txt')
done
