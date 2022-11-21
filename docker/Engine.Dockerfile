FROM minecpp/build-base:latest

ENV REPOSITORY_FILENAME=/root/minecpp_data/repository.bin

RUN mkdir /root/minecpp_data
RUN cp /root/minecpp/repository.bin /root/minecpp_data/repository.bin

WORKDIR /root/minecpp/build-docker
RUN cmake --build . -j $(nproc) --target minecpp_engine
RUN cp /root/minecpp/build-docker/bin/minecpp_engine /usr/bin/minecpp_engine
RUN rm -rf /root/minecpp

# No entypoint because we need to wait for storage connection first
