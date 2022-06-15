#!/usr/bin/env bash

source_directories=(
  include
  library
  test
  service
  tool
)

for dir in "${source_directories[@]}"; do
  while IFS= read -r file; do
    sed  -i "s/set_Hand\.h/set_hand\.h/g" $file
  done <  <(find $dir -regex '.+\.h' -or -regex '.+\.cpp' -or -regex '.+\.hpp' -or -regex '.+\.cc')
done
