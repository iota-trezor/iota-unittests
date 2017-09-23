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

void test_TrytesToTrits(void)
{
    TEST_ASSERT_TRUE(0);
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_ThreeTritsToSingleTryte);
    RUN_TEST(test_InvalidNumberOfTrits);
    RUN_TEST(test_MultipleTritsToTrytes);
    RUN_TEST(test_TrytesToTrits);

    return UNITY_END();
}
