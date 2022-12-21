.PHONY: docker-build-base docker-chunk-storage docker-engine docker-front docker docker-run clang-format proto nbt

.docker-grpc: docker/UbuntuGrpc.Dockerfile
	docker build . --network=host --no-cache -t minecpp/grpc:latest -f ./docker/UbuntuGrpc.Dockerfile
	echo "remove this file if you want to rebuild the gRPC docker image" > .docker-grpc

docker-build-base: .docker-grpc docker/BuildBase.Dockerfile
	docker build . --network=host -t minecpp/build-base:latest -f ./docker/BuildBase.Dockerfile

docker-storage: docker-build-base docker/Storage.Dockerfile
	docker build . --network=host -t minecpp/storage:latest -f ./docker/Storage.Dockerfile

docker-engine: docker-build-base docker/Engine.Dockerfile
	docker build . --network=host -t minecpp/engine:latest -f ./docker/Engine.Dockerfile

docker-front: docker-build-base docker/Front.Dockerfile
	docker build . --network=host -t minecpp/front:latest -f ./docker/Front.Dockerfile

docker: docker-storage docker-engine docker-front

docker-run: docker
	docker-compose up

clang-format:
	./meta/run-clang-format.sh

proto:
	./meta/generate-proto.sh

nbt:
	./meta/generate-proto.sh

cmake-files:
	./meta/cmake-generate.sh
