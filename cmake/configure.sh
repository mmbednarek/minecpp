#!/usr/bin/env bash

libraries=$(jq -r '.libraries[]' <Build.json)

for lib in $libraries; do
  echo "Configuring library $lib"
  mkdir -p "library/$lib/src"
  mkdir -p "library/$lib/include/minecpp/$lib"
  ./cmake/configure-library.sh $lib
done
