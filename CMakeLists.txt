cmake_minimum_required(VERSION 3.15)

project("PrimeDetectorPro" LANGUAGES C VERSION 0.0.0)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib/")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib/")

include_directories("${CMAKE_SOURCE_DIR}/include/")


add_executable("PrimeDetectorPro" "${CMAKE_SOURCE_DIR}/src/PrimeDetectorPro/PrimeDetectorPro.c")

add_executable("PrimeDetectorProTest" "${CMAKE_SOURCE_DIR}/src/PrimeDetectorPro/PrimeDetectorProTest.c")
target_compile_options("PrimeDetectorProTest" PRIVATE
    "$<$<CONFIG:Release>:/O2" "/Ob2" "/Oi" "/Ot" "/GL" "/arch:AVX2>"
)
target_link_options("PrimeDetectorProTest" PRIVATE
    "/LTCG"
)
