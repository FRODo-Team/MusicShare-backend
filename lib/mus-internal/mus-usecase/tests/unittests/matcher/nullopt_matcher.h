#ifndef MUS_INTERNAL_MATCHER_OPTIONAL_MATCHER_H_
#define MUS_INTERNAL_MATCHER_OPTIONAL_MATCHER_H_

#include <gmock/gmock.h>

#include <optional>

MATCHER_P(NulloptEqualement, other, "Equality matcher for type nullopt") {
    return arg == other;
}

#endif  // MUS_INTERNAL_MATCHER_OPTIONAL_MATCHER_H_