
// Copyright Paul Raffer 2020.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at
// https://www.boost.org/LICENSE_1_0.txt)

#if __cplusplus >= 201703L

#ifndef GPL_CONTAINER_TYPE_TRAITS_IS_CONTAINER_HPP
#define GPL_CONTAINER_TYPE_TRAITS_IS_CONTAINER_HPP


#include <type_traits>
#include <iterator>


namespace gpl // interface
{

template <typename T> T value;

template <typename C, typename = void> struct is_container : std::false_type {};

template <typename C> struct is_container<C, std::enable_if_t<
	std::is_same_v<typename C::value_type, typename C::value_type> && /*std::is_eraseable_v<typename C::value_type> &&*/
	std::is_same_v<typename C::reference, typename C::value_type&> &&
	std::is_same_v<typename C::const_reference, typename C::value_type const &> &&
	/*is_legacy_forward_iterator_v<typename C::iterator> &&*/ std::is_convertible_v<typename C::iterator, typename C::const_iterator> &&
	/*is_legacy_forward_iterator_v<typename C::const_iterator> &&*/
	std::is_integral_v<typename C::difference_type> && std::is_signed_v<typename C::difference_type> && std::is_same_v<typename C::difference_type, typename std::iterator_traits<typename C::iterator>::difference_type>  && std::is_same_v<typename C::difference_type, typename std::iterator_traits<typename C::const_iterator>::difference_type> &&
	std::is_integral_v<typename C::size_type> && std::is_unsigned_v<typename C::size_type> && (sizeof (typename C::size_type) >= sizeof (typename C::difference_type) / 2) &&
	
	std::is_same_v<decltype (C()), C> &&
	std::is_same_v<decltype (C(value<C>)), C> &&
#if __cplusplus >= 201103L
	std::is_same_v<decltype (C(std::declval<C>())), C> &&
#endif // __cplusplus >= 201103L
	std::is_same_v<decltype (value<C> = value<C>), C&> &&
	std::is_same_v<decltype (value<C> = std::declval<C>()), C&> &&
	std::is_same_v<decltype (value<C>.~C()), void> &&
	std::is_same_v<decltype (value<C>.begin()), typename C::iterator> && std::is_same_v<decltype (value<C const>.begin()), typename C::const_iterator> &&
	std::is_same_v<decltype (value<C>.end()), typename C::iterator> && std::is_same_v<decltype (value<C const>.end()), typename C::const_iterator> &&
#if __cplusplus >= 201103L
	std::is_same_v<decltype (value<C>.cbegin()), typename C::const_iterator> &&
	std::is_same_v<decltype (value<C>.cend()), typename C::const_iterator> &&
#endif // __cplusplus >= 201103L
	std::is_convertible_v<decltype (value<C> == value<C>), bool> &&
	std::is_convertible_v<decltype (value<C> != value<C>), bool> &&
	std::is_same_v<decltype (value<C>.swap(value<C>)), void> &&
	std::is_same_v<decltype (swap(value<C>, value<C>)), void> &&
	std::is_same_v<decltype (value<C>.size()), typename C::size_type> &&
	std::is_same_v<decltype (value<C>.max_size()), typename C::size_type> &&
	std::is_convertible_v<decltype (value<C>.empty()), bool>
>> : std::true_type {};

template <typename C> constexpr auto is_container_v = is_container<C>::value;

} // namespace gpl


#endif // GPL_CONTAINER_TYPE_TRAITS_IS_CONTAINER_HPP

#endif // __cplusplus >= 201703L
