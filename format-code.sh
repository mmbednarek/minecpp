#!/usr/bin/env bash

source_directories=(
  include
  lib
  test
  service
  tool
)

for dir in "${source_directories[@]}"; do
  while IFS= read -r file; do
    echo "formatting $file"
    clang-format -i $file
  done <  <(find $dir -regex '.+\.h' -or -regex '.+\.cpp')
done
