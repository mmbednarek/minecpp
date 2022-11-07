FROM minecpp/build-base:latest

WORKDIR /root/minecpp/build-docker
RUN cmake --build . -j $(nproc) --target minecpp_storage
RUN cp /root/minecpp/build-docker/bin/minecpp_storage /usr/bin/minecpp_storage
RUN rm -rf /root/minecpp

# No entypoint because we need to configure FDB before starting the service