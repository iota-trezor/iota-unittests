project("IOTA Core C functionality" C)
cmake_minimum_required(VERSION 3.0)

include(CTest)

add_definitions(-DKERL_TEST_VECTORS_PATH="${PROJECT_SOURCE_DIR}/vendor/kerl/test_vectors/")

include_directories(.)
add_subdirectory(vendor)


add_executable(conversion_test
	tests/conversion_test.c
	iota/conversion.c
        iota/bigint.c
)
target_link_libraries(conversion_test Unity)
add_test(conversion conversion_test)

add_executable(bigint_test
	tests/bigint_test.c
	iota/bigint.c)
target_link_libraries(bigint_test Unity)
add_test(bigint bigint_test)

add_executable(kerl_test
	tests/kerl_test.c
	iota/kerl.c
	iota/bigint.c
	iota/conversion.c
	vendor/trezor-crypto/sha3.c)
target_link_libraries(kerl_test Unity)
add_test(kerl kerl_test)

add_executable(kerl_trytes_and_hashes_test
	tests/kerl_trytes_and_hashes_test.c
	iota/kerl.c
	iota/bigint.c
	iota/conversion.c
	vendor/trezor-crypto/sha3.c)
target_link_libraries(kerl_trytes_and_hashes_test Unity)
add_test(kerl_trytes_and_hashes kerl_trytes_and_hashes_test)

add_executable(kerl_trytes_and_multi_squeeze_test
	tests/kerl_trytes_and_multi_squeeze_test.c
	iota/kerl.c
	iota/bigint.c
	iota/conversion.c
	vendor/trezor-crypto/sha3.c)
target_link_libraries(kerl_trytes_and_multi_squeeze_test Unity)
add_test(kerl_trytes_and_multi_squeeze kerl_trytes_and_multi_squeeze_test)

add_executable(kerl_multitrytes_and_hashes_test
        tests/kerl_multitrytes_and_hashes_test.c
        iota/kerl.c
        iota/bigint.c
        iota/conversion.c
        vendor/trezor-crypto/sha3.c)
target_link_libraries(kerl_multitrytes_and_hashes_test Unity)
add_test(kerl_multitrytes_and_hashes kerl_multitrytes_and_hashes_test)

add_executable(address_generation_test
        tests/address_generation_test.c
        iota/kerl.c
        iota/bigint.c
        iota/conversion.c
        iota/addresses.c
        vendor/trezor-crypto/sha3.c)
target_link_libraries(address_generation_test Unity)
add_test(address_generation address_generation_test)
