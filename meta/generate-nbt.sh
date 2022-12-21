#!/bin/bash

source_files=()

for scheme in $(find . -path "./api/minecpp/nbt/*.nbt"); do
  echo "generating $scheme"

  suff=${scheme#"./api/minecpp/nbt/"}
  path=${suff%/*.nbt}

  cc_path="library/api/minecpp/nbt/src/$path"
  h_path="library/api/minecpp/nbt/include/minecpp/nbt/$path"
  i_path="minecpp/nbt/$path"

  source_files+=($suff.cpp)

  mkdir -p $cc_path
  mkdir -p $h_path

  nbtc "$scheme" -s $cc_path -h $h_path -I $i_path
done