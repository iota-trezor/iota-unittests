#include <unity.h>
#include "../iota/transaction.h"
#include "../iota/conversion.h"

void test_CalculateStandardBundleHash()
{
    uint64_t timestamp = 1509635174;
    const char bundle_hash[] = "VEJURZLOSF9ZPCOQIILAIKMLCUUCKNEFZOVIGKEOLDVOTSA9SVSTVWJYFCZIYAUIYVD9ABQZHXYFC9PJX";
    const char tag[] = "TREZOR999999999999999999999";
    const char to_addr[] = "WJWFNLVTTFIFDFSBUWKBEFCHEEBTAXM9HVJJXJXV9DPVLSLPYLKU9CRFHESHEJZYIGWBNI9UYYWFXRJHD";
    const char from_addr[] = "MC9ZFTZBG9YGNDSLRWUVWZZXMZVJEZZMRWWCMQTG9HBEPTGSEEBMJX99U9UTP99EZZLX9HHACDNFWWTSX";
    const char remainder_addr[] = "JBKIFPLXDQGPAOA9IHSHHYPQGNHANBOHOEZDHSEXRSJAOHCJ9YTUDVNMFZMGCOXOVJIJRXSFKYOXILCZY";

    tryte_t hash_out[81] = {0};
    calculate_standard_bundle_hash(from_addr, to_addr, remainder_addr, 10000, 2001, tag, timestamp, hash_out);

    // Do a conversion to chars for easier comparison
    char hash_out_chars[82] = {0}; // one extra zero as string termination
    trytes_to_chars(hash_out, hash_out_chars, 81);
    TEST_ASSERT_EQUAL_STRING(bundle_hash, hash_out_chars);
}

void test_NormalizeHash()
{
    const char hash_in_chars[] = "VEJURZLOSF9ZPCOQIILAIKMLCUUCKNEFZOVIGKEOLDVOTSA9SVSTVWJYFCZIYAUIYVD9ABQZHXYFC9PJX";
    const char expected_normalized_hash_chars[] = "NNHURZLOSF9ZPCOQIILAIKMLCUUMMMEFZOVIGKEOLDVOTSA9SVSTVWNXFCZIYAUIYVD9ABQZHXYFC9PJX";

    // Convert to trytes first
    tryte_t hash_in[81];
    chars_to_trytes(hash_in_chars, hash_in, 81);
    tryte_t normalized_hash[81];

    // Call function
    normalize_hash(hash_in, normalized_hash);

    // Going to compare in chars, converting output to chars
    char normalized_hash_chars[82] = {0};
    trytes_to_chars(normalized_hash, normalized_hash_chars, 81);

    TEST_ASSERT_EQUAL_STRING(expected_normalized_hash_chars, normalized_hash_chars);

}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_CalculateStandardBundleHash);
    RUN_TEST(test_NormalizeHash);

    return UNITY_END();
}
