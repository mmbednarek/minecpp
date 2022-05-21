FROM minecpp/grpc:latest

# Copy the source code
COPY . /root/minecpp

# Generate protos for C++
WORKDIR /root/minecpp
RUN bash protogen.sh

# Run CMake
WORKDIR /root/minecpp/build-docker
RUN cmake .. -DCMAKE_BUILD_TYPE=Release -G Ninja

# Build game library as a test that everything works
WORKDIR /root/minecpp/build-docker
RUN cmake --build . -j $(nproc) --target minecpp_game