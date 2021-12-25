#include <gtest/gtest.h>

#include "test_crypto.h"
#include "test_random.h"

//#include "test_datetime.h"

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
