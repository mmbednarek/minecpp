FROM ubuntu:22.04

# Install dependecies
RUN apt-get -y update && apt-get upgrade -y
RUN apt-get -y install \
  build-essential \
  ninja-build \
  cmake \
  clang \
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
  libssl-dev \
  libfl-dev \
  libbenchmark-dev \
  libenet-dev \
  libabsl-dev \
  unzip \
  jq \
  dnsutils \
  curl

ENV CC="/usr/bin/clang"
ENV CXX="/usr/bin/clang++"

WORKDIR /root

RUN curl -L -o fdb.deb https://github.com/apple/foundationdb/releases/download/7.1.23/foundationdb-clients_7.1.23-1_amd64.deb
RUN dpkg -i fdb.deb

RUN ldconfig
