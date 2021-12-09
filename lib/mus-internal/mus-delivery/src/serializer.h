#ifndef MUS_MUSINTERNAL_MUSDELIVERY_SERIALIZER_H_
#define MUS_MUSINTERNAL_MUSDELIVERY_SERIALIZER_H_

#include <nlohmann/json.hpp>

#include "reflectable/auxiliary.h"
#include "reflectable/reflectable.h"

namespace nlohmann {

template <music_share::reflectable::Reflectable T>
struct adl_serializer<T> {
    static void to_json(json& j, const T& obj) {
        constexpr auto n = std::tuple_size<decltype(T::properties)>::value;
        music_share::reflectable::foreach_in_tuple(
            std::make_index_sequence<n>(), [&](auto i) {
                constexpr auto property = std::get<i>(T::properties);
                j[property.name] = obj.*(property.field);
            }
        );
    }

    static void from_json(const json& j, T& obj) {
        constexpr auto n = std::tuple_size<decltype(T::properties)>::value;
        music_share::reflectable::foreach_in_tuple(
            std::make_index_sequence<n>(), [&](auto i) {
                constexpr auto property = std::get<i>(T::properties);
                j.at(property.name).get_to(obj.*(property.field));
            }
        );
    }

    static T from_json(const json& j) {
        auto initializer = music_share::reflectable::tuple_transform(
            [&](auto prop) {
                return j
                    .at(prop.name)
                    .template get<typename decltype(prop)::Type>();
            }, T::properties
        );

        return music_share::reflectable::construct_from_tuple<T>(initializer);
    }
};

}  // namespace nlohmann

#endif  // MUS_MUSINTERNAL_MUSDELIVERY_SERIALIZER_H_
