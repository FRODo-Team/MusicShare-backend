// Oweners: Faris Nabiev, WEB-12
#ifndef MUS_REFLECATABLE_REFLECTABLE_H_
#define MUS_REFLECATABLE_REFLECTABLE_H_

#include <tuple>  // std::tuple
#include <type_traits>  // std::true_type, std::false_type

namespace music_share::reflectable {

template <typename Class, typename T>
struct Property {
    constexpr Property(T Class::*field, const char* name)
        : field(field), name(name) {}

    using Type = T;

    T Class::*field;
    const char* name;
};

template <typename Any>
struct is_property: std::false_type {};
template <typename Class, typename T>
struct is_property<Property<Class, T>>: std::true_type {};

template <typename T>
concept Describable = requires() {
    is_property<T>::value;
};

template <typename Any>
struct is_properties: std::false_type {};
template <Describable... Props>
struct is_properties<std::tuple<Props...>>: std::true_type {};

template <typename T>
concept Reflectable = requires() {
    T::properties;
    is_properties<decltype(T::properties)>::value;
};

}  // namespace music_share::dto

#endif  // MUS_REFLECATABLE_REFLECTABLE_H_
