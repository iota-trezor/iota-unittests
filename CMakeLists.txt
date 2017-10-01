project("IOTA Core C functionality" C)
cmake_minimum_required(VERSION 3.0)

include(CTest)

include_directories(vendor/trezor-crypto)
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

add_executable(kerl_full_test
	tests/kerl_full_test.c
	iota/kerl.c
	iota/bigint.c
	iota/conversion.c
	vendor/trezor-crypto/sha3.c)
target_link_libraries(kerl_full_test Unity)
add_test(kerl_full kerl_full_test)
