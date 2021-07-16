#!/bin/bash

NBT_SOURCES_PATH="lib/api/minecpp/nbt/api.cmake"

source_files=()

for scheme in $(find . -path "./api/minecpp/nbt/*.nbt"); do
  echo "generating $scheme"

  suff=${scheme#"./api/minecpp/nbt/"}
  path=${suff%/*.nbt}

  cc_path="lib/api/minecpp/nbt/$path"
  h_path="include/minecpp/nbt/$path"
  i_path="minecpp/nbt/$path"

  source_files+=($suff.cpp)

  mkdir -p $cc_path
  mkdir -p $h_path

  nbtc "$scheme" -s $cc_path -h $h_path -I $i_path
done

SOURCES_SCRIPT="set(nbt_api_sources \n"
for source in ${source_files[@]}; do
  SOURCES_SCRIPT+="   $source\n"
done
SOURCES_SCRIPT+=")"

echo -ne $SOURCES_SCRIPT >$NBT_SOURCES_PATH