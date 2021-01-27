#!/usr/bin/env bash
proto_files=(chunk.proto chunk_storage.proto engine.proto events.proto game.proto player.proto)

for file in "${proto_files[@]}"; do
  echo "generating proto impl for $file"
  docker run --rm -u="$(id -u)":"$(id -g)" -v "$(pwd)":/defs namely/protoc-all:1.34_2 -i services/protos -f $file -o services/protos/include/minepb -l cpp
done
