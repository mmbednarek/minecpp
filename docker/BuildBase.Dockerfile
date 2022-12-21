FROM minecpp/grpc:latest

# Copy the source code
COPY . /root/minecpp

# Install JQ that is nessecary to reconfigure the build system
RUN apt update -y
RUN apt install -y jq dnsutils

# Generate protos for C++
WORKDIR /root/minecpp

RUN make proto
RUN make cmake-files

# Run CMake
WORKDIR /root/minecpp/build-docker
RUN cmake .. -DCMAKE_BUILD_TYPE=Release -G Ninja

# Build game library as a test that everything works
WORKDIR /root/minecpp/build-docker
RUN cmake --build . -j $(nproc) -t minecpp_game  \
  -t minecpp_controller  \
  -t minecpp_event  \
  -t minecpp_engine_api  \
  -t minecpp_utils  \
  -t minecpp_game  \
  -t minecpp_api_proto  \
  -t minecpp_nbt  \
  -t minecpp_chat  \
  -t minecpp_format  \
  -t minecpp_network  \
  -t minecpp_repository  \
  -t minecpp_command  \
  -t minecpp_storage_api  \
  -t minecpp_lexer  \
  -t minecpp_crypto \
  -t yaml-cpp
