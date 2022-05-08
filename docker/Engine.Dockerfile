FROM minecpp/build-base:latest

ENV REPOSITORY_FILENAME=/root/minecpp/repository.bin

WORKDIR /root/minecpp/build-docker
RUN cmake --build . -j $(nproc) --target minecpp_engine
ENTRYPOINT ["/root/minecpp/build-docker/service/engine/minecpp_engine"]