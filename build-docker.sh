#!/usr/bin/env bash

# docker build . --network=host -t minecpp/grpc:latest -f ./docker/UbuntuGrpc.Dockerfile
docker build . --network=host -t minecpp/build-base:latest -f ./docker/BuildBase.Dockerfile
docker build . --network=host -t minecpp/chunk-storage:latest -f ./docker/ChunkStorage.Dockerfile
docker build . --network=host -t minecpp/engine:latest -f ./docker/Engine.Dockerfile
docker build . --network=host -t minecpp/front:latest -f ./docker/Front.Dockerfile
