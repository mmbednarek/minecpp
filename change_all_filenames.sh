#!/usr/bin/env bash

source_directories=(
  api
  include
  lib
  test
  service
  tool
)

for dir in "${source_directories[@]}"; do
  while IFS= read -r file; do
    echo "changing $file"
    ./change_filename.sh $file
  done <  <(find $dir -regex '.+\.h' -or -regex '.+\.cpp' -or -regex '.+\.hpp' -or -regex '.+\.cc' -or -regex '.+\.proto' -or -regex '.+\.nbt' -regex )
done
