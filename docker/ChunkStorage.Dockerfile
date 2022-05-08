FROM minecpp/build-base:latest

ENV REPOSITORY_FILENAME=/root/minecpp/repository.bin

WORKDIR /root/minecpp/build-docker
RUN cmake --build . -j $(nproc) --target minecpp_chunk_storage
ENTRYPOINT ["/root/minecpp/build-docker/service/chunk_storage/minecpp_chunk_storage"]