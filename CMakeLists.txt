project("IOTA Core C functionality" C)
cmake_minimum_required(VERSION 3.0)

include(CTest)

include_directories(vendor/trezor-crypto)
add_subdirectory(vendor)


add_executable(conversion_test
    tests/conversion_test.c
    iota/conversion.c
    vendor/trezor-crypto/sha3.c

)

target_link_libraries(conversion_test
    Unity
)

add_test(conversion_test conversion_test)
