FROM minecpp/build-base:latest

ENV CONFIG_FILE=/root/minecpp/config.yml

WORKDIR /root/minecpp/build-docker
RUN cmake --build . -j $(nproc) --target minecpp_front
ENTRYPOINT ["/root/minecpp/build-docker/service/front/minecpp_front"]
