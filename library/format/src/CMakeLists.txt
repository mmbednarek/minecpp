set(MINECPP_FORMAT_INCLUDE_DIR ${MINECPP_FORMAT_DIR}/include/minecpp/format)

target_sources(minecpp_format PUBLIC
        # Source files
        ${CMAKE_CURRENT_SOURCE_DIR}/Format.cpp

        # Header files
        ${MINECPP_FORMAT_INCLUDE_DIR}/Format.h
)

# Subdirectories

