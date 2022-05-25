FROM minecpp/build-base:latest

WORKDIR /root/minecpp/build-docker
RUN cmake --build . -j $(nproc) --target minecpp_front
RUN cp /root/minecpp/build-docker/bin/minecpp_front /usr/bin/minecpp_front
RUN rm -rf /root/minecpp_front
ENTRYPOINT ["/usr/bin/minecpp_front"]
