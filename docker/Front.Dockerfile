FROM minecpp/build-base:latest

ENV REGISTRY_FILE=/root/minecpp_data/registry.bin
RUN mkdir /root/minecpp_data
RUN cp /root/minecpp/registry.bin /root/minecpp_data/registry.bin

WORKDIR /root/minecpp/build-docker

RUN cmake --build . -j $(nproc) --target minecpp_front
RUN cp /root/minecpp/build-docker/bin/minecpp_front /usr/bin/minecpp_front
RUN rm -rf /root/minecpp_front

# No entypoint because we need to wait for engine and storage connection first
