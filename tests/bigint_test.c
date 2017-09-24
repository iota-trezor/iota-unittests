#include <unity.h>
#include "../iota/bigint.h"

/* private functions */
extern struct int_bool_pair full_add(const uint32_t ia, const uint32_t ib, const bool carry);

void test_FullAddSmallNumbers()
{
    struct int_bool_pair ret;

    ret = full_add(10000,20000,false);
    TEST_ASSERT_EQUAL(30000,ret.low);
    TEST_ASSERT_FALSE(ret.hi);

    ret = full_add(10000,20000,true);
    TEST_ASSERT_EQUAL(30001,ret.low);
    TEST_ASSERT_FALSE(ret.hi);
}

void test_FullAddBigNumbers()
{
    struct int_bool_pair ret;

    ret = full_add(0x7FFFFFFF,1,false);
    TEST_ASSERT_EQUAL_HEX32(0x80000000, ret.low);
    // Shifting sign is not overflow
    TEST_ASSERT_FALSE(ret.hi);

    // -1 + 4 = 3
    ret = full_add(0xFFFFFFFF,0x00000004,false);
    TEST_ASSERT_EQUAL_HEX32(0x00000003, ret.low);
    // Overflow!
    TEST_ASSERT_TRUE(ret.hi);
}

void test_FullAddSubtractSmallNumbers()
{
    struct int_bool_pair ret;
    ret = full_add(1, ~5, true);
    TEST_ASSERT_EQUAL(-4, ret.low);
    TEST_ASSERT_FALSE(ret.hi);

    // Different method, same result
    ret = full_add(1, -5, false);
    TEST_ASSERT_EQUAL(-4, ret.low);
    TEST_ASSERT_FALSE(ret.hi);

    // -123 + 257 = 134 (0x86)
    ret = full_add(-123, 257, false);
    TEST_ASSERT_EQUAL_HEX32(0x00000086, ret.low);
    TEST_ASSERT_TRUE(ret.hi);
}

void test_FullAddSubtractBigNumbers()
{
    struct int_bool_pair ret;

    // 2147483647 - 2147483648 = -1
    ret = full_add(0x7FFFFFFF, 0x80000000, false);
    TEST_ASSERT_EQUAL_HEX32(0xFFFFFFFF, ret.low);
    TEST_ASSERT_FALSE(ret.hi);

    // 2147483647 - 2147483647 = 0
    ret = full_add(0x7FFFFFFF, 0x80000001, false);
    TEST_ASSERT_EQUAL_HEX32(0x00000000, ret.low);
    TEST_ASSERT_TRUE(ret.hi);
}

void test_BigintAddIntWithoutOverflow()
{
    int32_t bigint_in[2] = {0x00005555, 0x00800000};
    int32_t bigint_out[2];
    int ret;

    ret = bigint_add_int(bigint_in, 0x00004444, bigint_out, 2);
    TEST_ASSERT_EQUAL_HEX32(0x00009999, bigint_out[0]);
    TEST_ASSERT_EQUAL_HEX32(0x00800000, bigint_out[1]);
}

void test_BigintAddIntWithOverflow()
{
    int32_t bigint_in[2] = {0xFFFFFFFF, 0x00800000};
    int32_t bigint_out[2] = {0};
    int ret;

    ret = bigint_add_int(bigint_in, 1, bigint_out, 2);
    TEST_ASSERT_EQUAL_HEX32(0x00000000, bigint_out[0]);
    TEST_ASSERT_EQUAL_HEX32(0x00800001, bigint_out[1]);
}

void test_SuperBigintAddIntWithoutOverflow()
{
    int32_t bigint_in[4] = {0x00003333, 0x00800000, 0xABABBABA, 0xAABBCCDD};
    int32_t bigint_out[4] = {0};
    int ret;

    ret = bigint_add_int(bigint_in, 0x11112222, bigint_out, 4);
    TEST_ASSERT_EQUAL_HEX32(0x11115555, bigint_out[0]);
    TEST_ASSERT_EQUAL_HEX32(0x00800000, bigint_out[1]);
    TEST_ASSERT_EQUAL_HEX32(0xABABBABA, bigint_out[2]);
    TEST_ASSERT_EQUAL_HEX32(0xAABBCCDD, bigint_out[3]);
}

void test_SuperBigintAddIntWithOverflow()
{
    int32_t bigint_in[4] = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x12345678};
    int32_t bigint_out[4] = {0};
    int ret;

    ret = bigint_add_int(bigint_in, 1, bigint_out, 4);
    TEST_ASSERT_EQUAL_HEX32(0x00000000, bigint_out[0]);
    TEST_ASSERT_EQUAL_HEX32(0x00000000, bigint_out[1]);
    TEST_ASSERT_EQUAL_HEX32(0x00000000, bigint_out[2]);
    TEST_ASSERT_EQUAL_HEX32(0x12345679, bigint_out[3]);

    TEST_ASSERT_EQUAL(0, ret);
}

void test_BigIntAddCompleteOverflowError()
{
    int32_t bigint_in[4] = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF};
    int32_t bigint_out[4] = {0};
    int ret;

    ret = bigint_add_int(bigint_in, 2, bigint_out, 4);
    TEST_ASSERT_EQUAL_HEX32(0x00000001, bigint_out[0]);
    TEST_ASSERT_EQUAL_HEX32(0x00000000, bigint_out[1]);
    TEST_ASSERT_EQUAL_HEX32(0x00000000, bigint_out[2]);
    TEST_ASSERT_EQUAL_HEX32(0x00000000, bigint_out[3]);

    // Sum didn't fit in the bigint
    TEST_ASSERT_EQUAL(-1, ret);
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_FullAddSmallNumbers);
    RUN_TEST(test_FullAddBigNumbers);
    RUN_TEST(test_FullAddSubtractSmallNumbers);
    RUN_TEST(test_FullAddSubtractBigNumbers);

    RUN_TEST(test_BigintAddIntWithoutOverflow);
    RUN_TEST(test_BigintAddIntWithOverflow);
    RUN_TEST(test_SuperBigintAddIntWithoutOverflow);
    RUN_TEST(test_SuperBigintAddIntWithOverflow);
    RUN_TEST(test_BigIntAddCompleteOverflowError);

    return UNITY_END();
}
