FROM minecpp/grpc:latest

# Copy the source code
COPY . /root/minecpp

# Install JQ that is nessecary to reconfigure the build system
RUN apt install -y jq

# Generate protos for C++
WORKDIR /root/minecpp
RUN bash protogen.sh

RUN bash cmake/configure.sh

# Run CMake
WORKDIR /root/minecpp/build-docker
RUN cmake .. -DCMAKE_BUILD_TYPE=Release -G Ninja

# Build game library as a test that everything works
WORKDIR /root/minecpp/build-docker
RUN cmake --build . -j $(nproc) --target minecpp_game
