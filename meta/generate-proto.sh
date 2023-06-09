#!/usr/bin/env bash

proto_sources=$(find . -path "./api/minecpp/proto/*.proto")

protoc --proto_path=./api --cpp_out=library/api $proto_sources

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

# move generated headers to include path
for header in $(find . -path "./library/api/minecpp/proto/src/*.pb.h"); do
  sed -i 's/#include \"minecpp\/proto\/\(.*\)\"/#include <minecpp\/proto\/\1>/' $header
  suffix=${header#"./library/api/minecpp/proto/src/"}
  mkdir -p ./library/api/minecpp/proto/include/minecpp/proto/${suffix%/*.pb.h}
  mv $header "./library/api/minecpp/proto/include/minecpp/proto/$suffix"
done