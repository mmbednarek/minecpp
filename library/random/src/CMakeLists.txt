set(MINECPP_RANDOM_INCLUDE_DIR ${MINECPP_RANDOM_DIR}/include/minecpp/random)
target_sources(minecpp_random PUBLIC
        # Source files
        ${CMAKE_CURRENT_SOURCE_DIR}/JavaRandom.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Mersenne.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Perlin3d.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Perlin.cpp

        # Header files
        ${MINECPP_RANDOM_INCLUDE_DIR}/JavaRandom.h
        ${MINECPP_RANDOM_INCLUDE_DIR}/Mersenne.h
        ${MINECPP_RANDOM_INCLUDE_DIR}/Perlin3d.h
        ${MINECPP_RANDOM_INCLUDE_DIR}/Perlin.h
        ${MINECPP_RANDOM_INCLUDE_DIR}/Random.h
)

