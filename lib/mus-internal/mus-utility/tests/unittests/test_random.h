#include <gtest/gtest.h>
#include "mus-utility/random.h"

// Да, тест тупой. Чисто на всякий случай. Генераторы - вещь сложная
TEST(TestUtilityRandom, RandomizerGeneratesDifferentResult) {
    const std::string s1 = music_share::utility::Random::GenerateString(30);
    const std::string s2 = music_share::utility::Random::GenerateString(30);

    ASSERT_STRNE(s1.c_str(), s2.c_str());
}

TEST(TestUtilityRandom, OutputStringLenghtSameAsRequiredOne) {
    const size_t l1 = 256;
    const size_t l2 = 32;
    const size_t l3 = 7;
    const size_t l4 = 1;

    const std::string s1 = music_share::utility::Random::GenerateString(l1);
    const std::string s2 = music_share::utility::Random::GenerateString(l2);
    const std::string s3 = music_share::utility::Random::GenerateString(l3);
    const std::string s4 = music_share::utility::Random::GenerateString(l4);

    ASSERT_EQ(s1.size(), l1);
    ASSERT_EQ(s2.size(), l2);
    ASSERT_EQ(s3.size(), l3);
    ASSERT_EQ(s4.size(), l4);
}
