FROM minecpp/build-base:latest

ENV REPOSITORY_FILENAME=/root/minecpp_data/repository.bin

RUN mkdir /root/minecpp_data
RUN cp /root/minecpp/repository.bin /root/minecpp_data/repository.bin

WORKDIR /root/minecpp/build-docker
RUN cmake --build . -j $(nproc) --target minecpp_chunk_storage
RUN cp /root/minecpp/build-docker/bin/minecpp_chunk_storage /usr/bin/minecpp_chunk_storage
RUN rm -rf /root/minecpp
ENTRYPOINT ["/usr/bin/minecpp_chunk_storage"]