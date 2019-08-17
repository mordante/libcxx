//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <regex>

// template <class BidirectionalIterator,
//           class Allocator = allocator<sub_match<BidirectionalIterator>>>
// class match_results
// {
// public:
//     typedef sub_match<BidirectionalIterator>                  value_type;
//     typedef const value_type&                                 const_reference;
//     typedef const_reference                                   reference;
//     typedef /implementation-defined/                          const_iterator;
//     typedef const_iterator                                    iterator;
//     typedef typename iterator_traits<BidirectionalIterator>::difference_type difference_type;
//     typedef typename allocator_traits<Allocator>::size_type   size_type;
//     typedef Allocator                                         allocator_type;
//     typedef typename iterator_traits<BidirectionalIterator>::value_type char_type;
//     typedef basic_string<char_type>                           string_type;
//     typedef conditional_t<ContiguousIterator<_BidirectionalIterator>, basic_string_view<char_type>, string_type> string_view_type;

#include <array>
#include <deque>
#include <list>
#include <regex>
#include <span>
#include <type_traits>
#include "test_macros.h"

template <class CharT>
void
test()
{
    typedef std::match_results<CharT*> MR;
    static_assert((std::is_same<typename MR::value_type, std::sub_match<CharT*> >::value), "");
    static_assert((std::is_same<typename MR::const_reference, const std::sub_match<CharT*>& >::value), "");
    static_assert((std::is_same<typename MR::reference, std::sub_match<CharT*>& >::value), "");
    static_assert((!std::is_same<typename MR::const_iterator, void>::value), "");
    static_assert((std::is_same<typename MR::difference_type, std::ptrdiff_t>::value), "");
    static_assert((std::is_same<typename MR::size_type, std::size_t>::value), "");
    static_assert((std::is_same<typename MR::allocator_type, std::allocator<std::sub_match<CharT*> > >::value), "");
    static_assert((std::is_same<typename MR::char_type, CharT>::value), "");
    static_assert((std::is_same<typename MR::string_type, std::basic_string<CharT> >::value), "");
#if defined(__cpp_lib_string_view_regex)
    static_assert(std::is_same_v<typename MR::string_view_type, std::basic_string_view<CharT>>);
    static_assert(std::is_same_v<
        typename std::match_results<typename std::basic_string<CharT>::const_iterator>::string_view_type,
        std::basic_string_view<CharT>>);
    static_assert(std::is_same_v<
        typename std::match_results<typename std::basic_string_view<CharT>::const_iterator>::string_view_type,
        std::basic_string_view<CharT>>);
    static_assert(std::is_same_v<
        typename std::match_results<typename std::array<CharT,42>::const_iterator>::string_view_type,
        std::basic_string_view<CharT>>);
    static_assert(std::is_same_v<
        typename std::match_results<typename std::vector<CharT>::const_iterator>::string_view_type,
        std::basic_string_view<CharT>>);
    static_assert(std::is_same_v<
        typename std::match_results<typename std::span<CharT>::const_iterator>::string_view_type,
        std::basic_string_view<CharT>>);
#ifdef __cpp_lib_concepts
    static_assert(std::is_same_v<
        typename std::match_results<typename std::deque<CharT>::const_iterator>::string_view_type,
        std::basic_string<CharT>>);
#endif
    static_assert(std::is_same_v<
        typename std::match_results<typename std::list<CharT>::const_iterator>::string_view_type,
        std::basic_string<CharT>>);
#endif
}

int main(int, char**)
{
    test<char>();
    test<wchar_t>();

  return 0;
}
