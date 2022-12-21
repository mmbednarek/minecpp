#!/usr/bin/env bash

libraries=$(jq -r '.libraries[]' <Build.json)

for lib in $libraries; do
  echo "Configuring library $lib"
  ./meta/cmake-generate-target.sh $lib "library/$lib" "library"
done

services=$(jq -r '.services[]' <Build.json)

for serv in $services; do
  echo "Configuring service $serv"
  ./meta/cmake-generate-target.sh $serv "service/$serv" "executable"
done

tools=$(jq -r '.tools[]' <Build.json)

for tool in $tools; do
  echo "Configuring tool $tool"
  ./meta/cmake-generate-target.sh $tool "tool/$tool" "executable"
done
