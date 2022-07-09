set(MINECPP_ENGINE_API_INCLUDE_DIR ${MINECPP_ENGINE_API_DIR}/include/minecpp/service/engine)
target_sources(minecpp_engine_api PUBLIC
        # Source files
        ${CMAKE_CURRENT_SOURCE_DIR}/Api.cpp

        # Header files
        ${MINECPP_ENGINE_API_INCLUDE_DIR}/Api.h
)

