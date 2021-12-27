#!/usr/bin/env bash

PROTO_SOURCES_PATH="lib/api/minecpp/proto/api.cmake"

function contains_grpc_service() {
  grep "service" $1 &>/dev/null
}

proto_sources=$(find . -path "./api/minecpp/proto/*.proto")

grpc_sources=()
for proto_source in $proto_sources; do
  if contains_grpc_service $proto_source; then
    grpc_sources+=($proto_source)
  fi
done

protoc --proto_path=./api --cpp_out=lib/api $proto_sources
protoc --proto_path=./api --grpc_out=lib/api --plugin=protoc-gen-grpc=$(which grpc_cpp_plugin) ${grpc_sources[@]}

# move generated headers to include path
for header in $(find . -path "./lib/api/minecpp/proto/*.pb.h"); do
  sed -i 's/#include \"minecpp\/proto\/\(.*\)\"/#include <minecpp\/proto\/\1>/' $header
  suffix=${header#"./lib/api/minecpp/proto/"}
  mkdir -p ./include/minecpp/proto/${suffix%/*.pb.h}
  mv $header "./include/minecpp/proto/$suffix"
done

source_files=()
# replace header include
for source in $(find . -path "./lib/api/minecpp/proto/*.pb.cc"); do
  source_files+=(${source#"./lib/api/minecpp/proto/"})
  sed -i 's/#include \"minecpp\/proto\/\(.*\)\"/#include <minecpp\/proto\/\1>/' $source
done

SOURCES_SCRIPT="set(proto_api_sources \n"
for source in ${source_files[@]}; do
  SOURCES_SCRIPT+="   $source\n"
done
SOURCES_SCRIPT+=")"

echo -ne $SOURCES_SCRIPT >$PROTO_SOURCES_PATH
