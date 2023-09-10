FROM minecpp/ubuntu:latest

# Copy the source code
COPY . /root/minecpp

# Run CMake
WORKDIR /root/minecpp/build-docker
RUN cmake .. -DCMAKE_BUILD_TYPE=Release -G Ninja

# Build game library as a test that everything works
WORKDIR /root/minecpp/build-docker
RUN cmake --build . -j $(nproc) -t minecpp_game  \
  -t minecpp_controller  \
  -t minecpp_engine_api  \
  -t minecpp_utils  \
  -t minecpp_game  \
  -t minecpp_api_schema  \
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
