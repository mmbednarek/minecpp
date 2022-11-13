FROM ubuntu:22.04

# Install dependecies
RUN apt-get -y update --fix-missing && apt-get upgrade -y
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

RUN git clone -b openssl-3.0.7 git://git.openssl.org/openssl.git

WORKDIR /root/openssl
RUN ./Configure --prefix=/usr
RUN make -j$(nproc)
RUN make install

WORKDIR /root

# Build gRPC (version 1.50.1)
# used only for protoc and grpc C++ protoc extension
RUN git clone -b v1.50.1 https://github.com/grpc/grpc
WORKDIR /root/grpc
RUN git submodule update --init --recursive
WORKDIR /root/grpc/third_party/protobuf
RUN ./autogen.sh
RUN ./configure --prefix=/usr --enable-shared
RUN make -j$(nproc)
RUN make check -j$(nproc)
RUN make install
RUN ldconfig
WORKDIR /root/grpc
RUN mkdir -p cmake/build
WORKDIR /root/grpc/cmake/build
RUN cmake -DgRPC_INSTALL=ON \
          -DgRPC_BUILD_TESTS=OFF \
          -DCMAKE_INSTALL_PREFIX=/usr \
          -DCMAKE_BUILD_TYPE=Release \
          -DBUILD_SHARED_LIBS=ON \
        ../..
RUN make -j $(nproc)
RUN make install

RUN curl -L -o fdb.deb https://github.com/apple/foundationdb/releases/download/7.1.23/foundationdb-clients_7.1.23-1_amd64.deb
RUN dpkg -i fdb.deb

RUN ldconfig
