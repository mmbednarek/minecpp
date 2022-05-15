#!/usr/bin/env bash

source_directories=(
  include
  lib
  test
  service
  tool
)

if [ -z "${CLANG_FORMAT}" ]; then
  CLANG_FORMAT=$(which clang-format)
fi

for dir in "${source_directories[@]}"; do
  while IFS= read -r file; do
    echo "formatting $file"
    $CLANG_FORMAT -i $file
  done <  <(find $dir -regex '.+\.h' -or -regex '.+\.cpp')
done
