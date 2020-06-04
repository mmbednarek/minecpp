proto:
	protoc -I services/protos --cpp_out=services/protos/include/minepb services/protos/engine.proto services/protos/chunk.proto services/protos/chunk_storage.proto
	protoc -I services/protos --grpc_out=services/protos/include/minepb --plugin=protoc-gen-grpc=${HOME}/.local/bin/grpc_cpp_plugin services/protos/engine.proto services/protos/chunk_storage.proto
