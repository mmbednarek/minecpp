FROM ubuntu:22.04

# Install dependecies
RUN apt-get -y update && apt-get upgrade -y
RUN apt-get -y install \
     build-essential \
     ninja-build \
     cmake \
     git \
     pkg-config \
     autoconf \
     libtool \
     libfmt-dev \
     libspdlog-dev \
     libgtest-dev \
     libboost-dev \
     libboost-iostreams-dev \
     libboost-system-dev \
     libboost-program-options-dev \
     libabsl-dev \
     libfl-dev \
     libbenchmark-dev \
     unzip \
     curl

WORKDIR /root

# Build gRPC (version 1.46.0)
# used only for protoc and grpc C++ protoc extension
# the gRPC as a library is specified a dependency in the CMake file.
RUN git clone --recurse-submodules -b v1.46.0 --depth 1 --shallow-submodules https://github.com/grpc/grpc
WORKDIR /root/grpc
RUN mkdir -p cmake/build
WORKDIR /root/grpc/cmake/build
RUN cmake -DgRPC_INSTALL=ON \
          -DgRPC_BUILD_TESTS=OFF \
          -DCMAKE_INSTALL_PREFIX=/usr \
          ../..
RUN make -j $(nproc)
RUN make install

# Copy the source code
COPY . /root/minecpp

# Generate protos for C++
WORKDIR /root/minecpp
RUN bash protogen.sh

# Run CMake
WORKDIR /root/minecpp/build-docker
RUN cmake .. -DCMAKE_BUILD_TYPE=Release -DUSE_LOCAL_GPRC=OFF -G Ninja

# Build game library as a test that everything works
WORKDIR /root/minecpp/build-docker
RUN cmake --build . -j $(nproc) --target minecpp_game