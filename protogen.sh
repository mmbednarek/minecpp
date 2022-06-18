#!/usr/bin/env bash

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

protoc --proto_path=./api --cpp_out=library/api $proto_sources
protoc --proto_path=./api --grpc_out=library/api --plugin=protoc-gen-grpc=$(which grpc_cpp_plugin) ${grpc_sources[@]}

# move generated headers to include path
for header in $(find . -path "./library/api/minecpp/proto/*.pb.h"); do
  sed -i 's/#include \"minecpp\/proto\/\(.*\)\"/#include <minecpp\/proto\/\1>/' $header
  suffix=${header#"./library/api/minecpp/proto/"}
  mkdir -p ./library/api/minecpp/proto/include/minecpp/proto/${suffix%/*.pb.h}
  mv $header "./library/api/minecpp/proto/include/minecpp/proto/$suffix"
done

# replace header include
for source in $(find . -path "./library/api/minecpp/proto/*.pb.cc"); do
  sed -i 's/#include \"minecpp\/proto\/\(.*\)\"/#include <minecpp\/proto\/\1>/' $source
done

# move source files
source_libs=$(find ./library/api/minecpp/proto/ -name "*.pb.cc"  | cut -d'/' -f6  | uniq)
for lib in $source_libs; do
  if [[ $lib == "src" ]]; then
    continue
  fi
  rm -rf ./library/api/minecpp/proto/src/$lib
  mv ./library/api/minecpp/proto/$lib ./library/api/minecpp/proto/src/$lib
done