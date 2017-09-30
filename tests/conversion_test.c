#include <unity.h>
#include "../iota/conversion.h"
#include <string.h>

void test_ThreeTritsToSingleTryte(void)
{
    trit_t trits_9[] = { 0,  0,  0}; // 0
    trit_t trits_E[] = {-1, -1,  1}; // 5
    trit_t trits_N[] = {-1, -1, -1}; // -13
    trit_t trits_V[] = { 1,  1, -1}; // -5

    tryte_t trytes_out[1] = {0};
    int ret;
    ret = trits_to_trytes(trits_9, trytes_out, 3);
    TEST_ASSERT_EQUAL(0, trytes_out[0]);
    TEST_ASSERT_EQUAL(0, ret);

    ret = trits_to_trytes(trits_E, trytes_out, 3);
    TEST_ASSERT_EQUAL(5, trytes_out[0]);
    TEST_ASSERT_EQUAL(0, ret);

    ret = trits_to_trytes(trits_N, trytes_out, 3);
    TEST_ASSERT_EQUAL(-13, trytes_out[0]);
    TEST_ASSERT_EQUAL(0, ret);

    ret = trits_to_trytes(trits_V, trytes_out, 3);
    TEST_ASSERT_EQUAL(-5, trytes_out[0]);
    TEST_ASSERT_EQUAL(0, ret);
}

void test_InvalidNumberOfTrits(void)
{
    trit_t trits_V[] = { 1,  1, -1}; // -5
    tryte_t trytes_out[1] = {0};

    int ret;
    ret = trits_to_trytes(trits_V, trytes_out, 2);
    // Unchanged
    TEST_ASSERT_EQUAL(0, trytes_out[0]);
    // Error
    TEST_ASSERT_EQUAL(-1, ret);
}

void test_MultipleTritsToTrytes(void)
{
    trit_t trits_EN[] = { -1, -1,  1, -1, -1, -1}; // 5, -13
    tryte_t trytes_out[2] = {0, 0};

    int ret;
    ret = trits_to_trytes(trits_EN, trytes_out, 6);
    TEST_ASSERT_EQUAL(5, trytes_out[0]);
    TEST_ASSERT_EQUAL(-13, trytes_out[1]);
    TEST_ASSERT_EQUAL(0, ret);
}

void test_Int32ToTrits(void)
{
    int32_t value = 10;
    trit_t trits_out[10] = {0};

    int ret;
    ret = int32_to_trits(value, trits_out, 10);

    TEST_ASSERT_EQUAL(1, trits_out[0]);
    TEST_ASSERT_EQUAL(0, trits_out[1]);
    TEST_ASSERT_EQUAL(1, trits_out[2]);
    // No error
    TEST_ASSERT_EQUAL(0, ret);

    value = -17;
    ret = int32_to_trits(value, trits_out, 10);

    TEST_ASSERT_EQUAL(1, trits_out[0]);
    TEST_ASSERT_EQUAL(0, trits_out[1]);
    TEST_ASSERT_EQUAL(1, trits_out[2]);
    TEST_ASSERT_EQUAL(-1, trits_out[3]);
    // No error
    TEST_ASSERT_EQUAL(0, ret);
}

void test_Int32ToTritsMaxLengthExceeded()
{
    int32_t value = -17;
    trit_t trits_out[10] = {0};

    int ret;
    ret = int32_to_trits(value, trits_out, 3);

    // Values are partly written
    TEST_ASSERT_EQUAL(1, trits_out[0]);
    TEST_ASSERT_EQUAL(0, trits_out[1]);
    TEST_ASSERT_EQUAL(1, trits_out[2]);
    TEST_ASSERT_EQUAL(0, trits_out[3]); // This one is not written

    // Max length exceeded, give error
    TEST_ASSERT_EQUAL(-1, ret);
}

void test_TrytesToTrits(void)
{
    tryte_t trytes_in[2] = {-5, 13}; // [1,1,-1] [1,1,1]
    trit_t trits_out[6] = {0};

    int ret;
    ret = trytes_to_trits(trytes_in, trits_out, 2);

    TEST_ASSERT_EQUAL(1, trits_out[0]);
    TEST_ASSERT_EQUAL(1, trits_out[1]);
    TEST_ASSERT_EQUAL(-1, trits_out[2]);
    TEST_ASSERT_EQUAL(1, trits_out[3]);
    TEST_ASSERT_EQUAL(1, trits_out[4]);
    TEST_ASSERT_EQUAL(1, trits_out[5]);
    TEST_ASSERT_EQUAL(0, ret);
}

void test_TritsToBytesSmallPositiveNumber()
{
    trit_t trits_in[243] = {0};
    trit_t first_trits[3] = {1, 0, 1}; // 10
    memcpy(trits_in, first_trits, sizeof(first_trits));
    int32_t bytes_out[12] = {0};

    int ret;
    ret = trits_to_bytes(trits_in, bytes_out);
    TEST_ASSERT_EQUAL_HEX32(0x0000000A, bytes_out[0]);
    TEST_ASSERT_EQUAL_HEX32(0x00000000, bytes_out[1]);
    TEST_ASSERT_EQUAL(0, ret);
}

void test_TritsToBytesPositiveNumber()
{
    trit_t trits_in[243] = {0};
    trit_t first_trits[24] = { 1, 0,  1, -1, -1, 1, 0, -1,  0, 1, 1, 1,
                              -1, 0, -1, -1, -1, 1, 1,  1, -1, 1, 0, 0};
    memcpy(trits_in, first_trits, sizeof(first_trits));
    int32_t bytes_out[12] = {0};

    int ret;
    ret = trits_to_bytes(trits_in, bytes_out);

    TEST_ASSERT_EQUAL_HEX32(0x00000080, bytes_out[0]);
    TEST_ASSERT_EQUAL_HEX32(0x00000002, bytes_out[1]);
    TEST_ASSERT_EQUAL_HEX32(0x00000000, bytes_out[2]);

    TEST_ASSERT_EQUAL(0, ret);
}

void test_TritsToBytesSmallNegativeNumber()
{
    trit_t trits_in[243] = {0};
    trit_t first_trits[3] = {-1, 0, -1}; // -10 = 0xF6
    memcpy(trits_in, first_trits, sizeof(first_trits));
    int32_t bytes_out[12] = {0};

    int ret;
    ret = trits_to_bytes(trits_in, bytes_out);
    TEST_ASSERT_EQUAL_HEX32(0xFFFFFFF6, bytes_out[0]);
    TEST_ASSERT_EQUAL_HEX32(0xFFFFFFFF, bytes_out[1]);
    TEST_ASSERT_EQUAL_HEX32(0xFFFFFFFF, bytes_out[2]);
    TEST_ASSERT_EQUAL(0, ret);
}

void testTritsToBytesLargeNegativeNumber()
{
    trit_t trits_in[243] = {0};
    trit_t first_trits[24] = { -1, 0,  -1, +1, +1, -1, 0, +1,  0, -1, -1, -1,
                              +1, 0, +1, +1, +1, -1, -1,  -1, +1, -1, 0, 0};
    memcpy(trits_in, first_trits, sizeof(first_trits));
    int32_t bytes_out[12] = {0};

    int ret;
    ret = trits_to_bytes(trits_in, bytes_out);

    TEST_ASSERT_EQUAL_HEX32(0xFFFFFF80, bytes_out[0]);
    TEST_ASSERT_EQUAL_HEX32(0xFFFFFFFD, bytes_out[1]);
    TEST_ASSERT_EQUAL_HEX32(0xFFFFFFFF, bytes_out[2]);

    TEST_ASSERT_EQUAL(0, ret);
}


void test_TritsToBytesLastTritIsIgnored()
{
    // Last trit is 1, but will be ignored by the conversion.
    // It is considered to be zero
    trit_t trits_in[243] = {0};
    trits_in[242] = 1;
    int32_t bytes_out[12] = {0};
    int ret;

    ret = trits_to_bytes(trits_in, bytes_out);

    TEST_ASSERT_EQUAL_HEX32(0x00000000, bytes_out[0]);
    TEST_ASSERT_EQUAL_HEX32(0x00000000, bytes_out[1]);
    TEST_ASSERT_EQUAL_HEX32(0x00000000, bytes_out[11]);

    TEST_ASSERT_EQUAL(0, ret);
}

void testTritsToBytesLargestPossibleNumber()
{
    // Last trit is 1, but will be ignored by the conversion.
    // It is considered to be zero
    trit_t trits_in[243];
    for (int i = 0; i < 243; i++) { trits_in[i] = 1; }
    int32_t bytes_out[12];
    int ret;

    ret = trits_to_bytes(trits_in, bytes_out);

    TEST_ASSERT_EQUAL_HEX32(0xA5CE8964, bytes_out[0]);
    TEST_ASSERT_EQUAL_HEX32(0x9F007669, bytes_out[1]);
    TEST_ASSERT_EQUAL_HEX32(0x5E69EBEF, bytes_out[11]);
}

void testTritsToBytesAllZeros()
{
    trit_t trits_in[243] = {0};
    int32_t bytes_out[12];
    int ret;

    ret = trits_to_bytes(trits_in, bytes_out);

    TEST_ASSERT_EQUAL_HEX32(0x00000000, bytes_out[0]);
    TEST_ASSERT_EQUAL_HEX32(0x00000000, bytes_out[1]);
    TEST_ASSERT_EQUAL_HEX32(0x00000000, bytes_out[11]);

    TEST_ASSERT_EQUAL(0, ret);
}

void test_BytesToTritsAllZeros()
{
    int32_t bytes_in[12] = {0};
    trit_t trits_out[243] = {0};
    // initialize with wrong value
    for (int i = 0; i < 243; i++) { trits_out[i] = 127; }
    int ret;

    ret = bytes_to_trits(bytes_in, trits_out);

    TEST_ASSERT_EACH_EQUAL_INT8(0, trits_out, 243);
    TEST_ASSERT_EQUAL(0, ret);
}

void test_BytesToTritsSmallPositiveNumber()
{
    int32_t bytes_in[12] = {0};
    bytes_in[0] = 0x0000000A; // 10
    trit_t trits_out[243] = {0};
    int ret;

    ret = bytes_to_trits(bytes_in, trits_out);

    TEST_ASSERT_EQUAL(1, trits_out[0]);
    TEST_ASSERT_EQUAL(0, trits_out[1]);
    TEST_ASSERT_EQUAL(1, trits_out[2]);
}

void test_BytesToTritsLargePositiveNumber()
{
    int32_t bytes_in[12] = {0};
    bytes_in[0] = 0x00000080;
    bytes_in[1] = 0x00000002;
    trit_t trits_out[243] = {0};
    int ret;

    ret = bytes_to_trits(bytes_in, trits_out);

    trit_t expected_trits[24] = { 1, 0,  1, -1, -1, 1, 0, -1,  0, 1, 1, 1,
                                 -1, 0, -1, -1, -1, 1, 1,  1, -1, 1, 0, 0};
    TEST_ASSERT_EQUAL_INT8_ARRAY(expected_trits, trits_out, 24);
}

void test_CharsToTrytes()
{
    char chars_in[] = "9ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    tryte_t trytes_out[27] = {0};
    tryte_t expected_trytes[27] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,
                            -13, -12, -11, -10, -9, -8, -7, -6, -5, -4, -3, -2, -1};
    int ret;

    ret = chars_to_trytes(chars_in, trytes_out, 27);

    TEST_ASSERT_EQUAL_INT8_ARRAY(expected_trytes, trytes_out, 27);

    TEST_ASSERT_EQUAL(0, ret);
}

void test_TrytesToChars()
{
    tryte_t trytes_in[27] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,
                            -13, -12, -11, -10, -9, -8, -7, -6, -5, -4, -3, -2, -1};
    char chars_out[27] = {'\0'};
    char expected_chars[] = "9ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int ret;

    ret = trytes_to_chars(trytes_in, chars_out, 27);

    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_chars, chars_out, 27);

    TEST_ASSERT_EQUAL(0, ret);

}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_ThreeTritsToSingleTryte);
    RUN_TEST(test_InvalidNumberOfTrits);
    RUN_TEST(test_MultipleTritsToTrytes);
    RUN_TEST(test_Int32ToTrits);
    RUN_TEST(test_Int32ToTritsMaxLengthExceeded);
    RUN_TEST(test_TrytesToTrits);

    // trits_to_bytes
    RUN_TEST(test_TritsToBytesSmallPositiveNumber);
    RUN_TEST(test_TritsToBytesPositiveNumber);
    RUN_TEST(test_TritsToBytesSmallNegativeNumber);
    RUN_TEST(testTritsToBytesLargeNegativeNumber);
    RUN_TEST(test_TritsToBytesLastTritIsIgnored);
    RUN_TEST(testTritsToBytesLargestPossibleNumber);
    RUN_TEST(testTritsToBytesAllZeros);

    // bytes_to_trits
    RUN_TEST(test_BytesToTritsAllZeros);
    RUN_TEST(test_BytesToTritsSmallPositiveNumber);
    RUN_TEST(test_BytesToTritsLargePositiveNumber);

    // chars to trytes
    RUN_TEST(test_CharsToTrytes);

    // trytes to chars
    RUN_TEST(test_TrytesToChars);

    return UNITY_END();
}
