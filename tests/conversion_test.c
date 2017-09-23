#include <unity.h>
#include "../iota/conversion.h"

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

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_ThreeTritsToSingleTryte);
    RUN_TEST(test_InvalidNumberOfTrits);
    RUN_TEST(test_MultipleTritsToTrytes);
    RUN_TEST(test_Int32ToTrits);
    RUN_TEST(test_Int32ToTritsMaxLengthExceeded);
    RUN_TEST(test_TrytesToTrits);

    return UNITY_END();
}
