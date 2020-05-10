proto:
	protoc -I src/api/proto --cpp_out=src/api/pbcpp src/api/proto/engine.proto
	protoc -I src/api/proto --grpc_out=src/api/pbcpp --plugin=protoc-gen-grpc=${HOME}/.local/bin/grpc_cpp_plugin src/api/proto/engine.proto
