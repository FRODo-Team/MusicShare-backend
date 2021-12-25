#include <gtest/gtest.h>
#include "mus-utility/crypto.h"

TEST(TestUtilityCrypto, EqualStringsHashedEqually) {
    // arrange
    const std::string str1 = "HelloThisIsSomeString";
    const std::string str2 = str1;

    // act
    std::string hashed_1 = music_share::utility::Crypto::HashString_SHA256(str1);
    std::string hashed_2 = music_share::utility::Crypto::HashString_SHA256(str2);

    // assert
    ASSERT_STREQ(hashed_1.c_str(), hashed_2.c_str());
}
