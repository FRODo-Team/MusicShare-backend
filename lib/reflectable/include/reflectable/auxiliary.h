// Oweners: Faris Nabiev, WEB-12
#ifndef MUS_REFLECATABLE_AUXILIARY_H_
#define MUS_REFLECATABLE_AUXILIARY_H_

#include <tuple>  // std::tuple
#include <cstddef>  // std::size_t
#include <concepts>  // std::integral

namespace music_share::reflectable {

template <std::integral T, T... S, typename Fn>
constexpr void foreach_in_tuple(std::integer_sequence<T, S...>, Fn&& fn) {
    (static_cast<void>(fn(std::integral_constant<T, S>())), ...);
}

template <typename T, typename Tuple, std::size_t... Indices>
T construct_from_tuple(Tuple&& tuple, std::index_sequence<Indices...> ) {
    return T(std::get<Indices>(std::forward<Tuple>(tuple))...);
}

template <typename T, typename Tuple>
T construct_from_tuple(Tuple&& tuple) {
    constexpr auto n = std::tuple_size<std::decay_t<Tuple>>::value;
    return construct_from_tuple<T>(std::forward<Tuple>(tuple),
                                   std::make_index_sequence<n>());
}

template <typename Fn, typename Tuple, std::size_t... Indices>
auto tuple_transform(Fn&& fn, Tuple&& tuple,
                     std::index_sequence<Indices...>) {
    return std::tuple(fn(std::get<Indices>(tuple))...);
}

template <typename Fn, typename Tuple>
auto tuple_transform(Fn&& fn, Tuple&& tuple) {
    constexpr auto n = std::tuple_size<std::decay_t<Tuple>>::value;
    return tuple_transform(std::forward<Fn>(fn),
                           std::forward<Tuple>(tuple),
                           std::make_index_sequence<n>());
}

}  // namespace music_share::dto

#endif  // MUS_REFLECATABLE_AUXILIARY_H_
