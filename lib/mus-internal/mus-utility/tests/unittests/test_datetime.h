#include <gtest/gtest.h>
#include "mus-utility/datetime.h"
#include <sstream>

using music_share::utility::Datetime;

TEST(TestUtilityDatetime, Poof) {
    Datetime time = Datetime::GetCurrent();
    std::string sql = time.ToString(Datetime::Format::Sql_NoTimezone);
    std::string cookies = time.ToString(Datetime::Format::Cookies);

    ASSERT_NE(1, 0);
}