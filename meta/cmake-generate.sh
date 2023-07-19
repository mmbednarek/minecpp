#!/usr/bin/env bash

tmp_file=$(mktemp ./cmakegen_lock.XXXXX)
lock_file="./cmakegen-lock"

trap "rm $tmp_file" EXIT

if ln $tmp_file $lock_file; then
  trap "rm $tmp_file $lock_file" EXIT

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
else
  echo "cmake generator is locked">/dev/stderr
  exit 1
fi
