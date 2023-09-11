.PHONY: docker-core docker-storage docker-engine docker-front docker docker-run clang-format nbt

.docker-ubuntu: docker/Ubuntu.Dockerfile
	docker build . --network=host --no-cache -t minecpp/ubuntu:latest -f ./docker/Ubuntu.Dockerfile
	echo "remove this file if you want to rebuild the ubuntu docker image" > .docker-ubuntu

docker-core: .docker-ubuntu docker/Core.Dockerfile
	docker build . --network=host -t minecpp/core:latest -f ./docker/Core.Dockerfile

docker-storage: docker-core docker/Storage.Dockerfile
	docker build . --network=host -t minecpp/storage:latest -f ./docker/Storage.Dockerfile

docker-engine: docker-core docker/Engine.Dockerfile
	docker build . --network=host -t minecpp/engine:latest -f ./docker/Engine.Dockerfile

docker-front: docker-core docker/Front.Dockerfile
	docker build . --network=host -t minecpp/front:latest -f ./docker/Front.Dockerfile

docker: docker-storage docker-engine docker-front

docker-run: docker
	docker-compose up

clang-format:
	./meta/run-clang-format.sh

schema:
	schema_compiler -i ./api/minecpp -s library/api/src -h library/api/include/minecpp -I minecpp

cmake-files:
	./meta/cmake-generate.sh
