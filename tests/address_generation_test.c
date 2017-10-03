#include <unity.h>
#include <stdio.h>
#include "../iota/kerl.h"
#include "../iota/conversion.h"
#include "../iota/addresses.h"

void test_AddressGeneration()
{
    // Open the test-vector file
    FILE* fp;
    char* line = NULL;
    size_t len = 0;
    ssize_t read;

    char full_filename[1024];
    char kerl_testvectors_path[] = KERL_TEST_VECTORS_PATH;
    size_t kerl_testvectors_path_size = sizeof(kerl_testvectors_path);
    char filename[] = "generateNAddressesForSeed";
    memcpy(full_filename, kerl_testvectors_path, kerl_testvectors_path_size);
    memcpy(&full_filename[kerl_testvectors_path_size-1], filename, sizeof(filename));

    fp = fopen(full_filename, "r");
    if (fp == NULL) {
        TEST_ASSERT_FALSE_MESSAGE(true, "could not open test vectors file");
        return;
    }

    // read first line (headers)
    read = getline(&line, &len, fp);
    // go through all hashes
    char seed[81];
    char expected_address[81];
    uint32_t cnt = 0;
    while(cnt < 100 && (read = getline(&line, &len, fp)) != -1) {
        cnt++;
        memcpy(seed, line, 81);
        memcpy(expected_address, &line[82], 81);

        tryte_t trytes[81] = {0};
        trit_t seed_trits[243] = {0};
        chars_to_trytes(seed, trytes, 81);
        trytes_to_trits(trytes, seed_trits, 81);

        trit_t private_key[2*243*27];
        generate_private_key(seed_trits, 0, private_key);

        trit_t public_addr[243];
        generate_public_address(private_key, public_addr);

        // convert output to char format
        tryte_t trytes_out[81] = {0};
        char chars_out[81] = {0};
        trits_to_trytes(public_addr, trytes_out, 243);
        trytes_to_chars(trytes_out, chars_out, 81);

        TEST_ASSERT_EQUAL_HEX8_ARRAY_MESSAGE(expected_address, chars_out, 81, seed);
    }
}

int main(void)
{
    UNITY_BEGIN();

    // kerl hash
    RUN_TEST(test_AddressGeneration);

    return UNITY_END();
}
