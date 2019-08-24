//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <regex>

// template <class BidirectionalIterator>
// class sub_match
//     : public pair<BidirectionalIterator, BidirectionalIterator>
// {
// public:
//     typedef BidirectionalIterator                               iterator;
//     typedef typename iterator_traits<iterator>::value_type      value_type;
//     typedef typename iterator_traits<iterator>::difference_type difference_type;
//     typedef basic_string<value_type>                            string_type;
//     typedef conditional_t<contiguous_iterator<_BidirectionalIterator>, basic_string_view<char_type>, string_type> string_view_type;
//
//     bool matched;
//     ...
// };

#include <array>
#include <deque>
#include <list>
#include <regex>
#include <span>
#include <type_traits>
#include <cassert>
#include "test_macros.h"

template <class CharT>
void
test()
{
#if defined(__cpp_lib_string_view_regex)
    static_assert(std::is_same_v<
        typename std::sub_match<const CharT*>::string_view_type,
        std::basic_string_view<CharT>>);
    static_assert(std::is_same_v<
        typename std::sub_match<typename std::basic_string<CharT>::const_iterator>::string_view_type,
        std::basic_string_view<CharT>>);
    static_assert(std::is_same_v<
        typename std::sub_match<typename std::basic_string_view<CharT>::const_iterator>::string_view_type,
        std::basic_string_view<CharT>>);
    static_assert(std::is_same_v<
        typename std::sub_match<typename std::array<CharT,42>::const_iterator>::string_view_type,
        std::basic_string_view<CharT>>);
    static_assert(std::is_same_v<
        typename std::sub_match<typename std::vector<CharT>::const_iterator>::string_view_type,
        std::basic_string_view<CharT>>);
    static_assert(std::is_same_v<
        typename std::sub_match<typename std::span<CharT>::const_iterator>::string_view_type,
        std::basic_string_view<CharT>>);
#ifdef __cpp_lib_concepts
    static_assert(std::is_same_v<
        typename std::sub_match<typename std::deque<CharT>::const_iterator>::string_view_type,
        std::basic_string<CharT>>);
#endif
    static_assert(std::is_same_v<
        typename std::sub_match<typename std::list<CharT>::const_iterator>::string_view_type,
        std::basic_string<CharT>>);
#endif
}

int main(int, char**)
{
    {
        typedef std::sub_match<char*> SM;
        static_assert((std::is_same<SM::iterator, char*>::value), "");
        static_assert((std::is_same<SM::value_type, char>::value), "");
        static_assert((std::is_same<SM::difference_type, std::ptrdiff_t>::value), "");
        static_assert((std::is_same<SM::string_type, std::string>::value), "");
#if defined(__cpp_lib_string_view_regex)
        static_assert((std::is_same<SM::string_view_type, std::string_view>::value), "");
#endif
        static_assert((std::is_convertible<SM*, std::pair<char*, char*>*>::value), "");

        SM sm;
        sm.first = nullptr;
        sm.second = nullptr;
        sm.matched = false;
    }
    {
        typedef std::sub_match<wchar_t*> SM;
        static_assert((std::is_same<SM::iterator, wchar_t*>::value), "");
        static_assert((std::is_same<SM::value_type, wchar_t>::value), "");
        static_assert((std::is_same<SM::difference_type, std::ptrdiff_t>::value), "");
        static_assert((std::is_same<SM::string_type, std::wstring>::value), "");
#if defined(__cpp_lib_string_view_regex)
        static_assert((std::is_same<SM::string_view_type, std::wstring_view>::value), "");
#endif
        static_assert((std::is_convertible<SM*, std::pair<wchar_t*, wchar_t*>*>::value), "");

        SM sm;
        sm.first = nullptr;
        sm.second = nullptr;
        sm.matched = false;
    }
    {
        static_assert((std::is_same<std::csub_match, std::sub_match<const char*> >::value), "");
        static_assert((std::is_same<std::wcsub_match, std::sub_match<const wchar_t*> >::value), "");
        static_assert((std::is_same<std::ssub_match, std::sub_match<std::string::const_iterator> >::value), "");
        static_assert((std::is_same<std::wssub_match, std::sub_match<std::wstring::const_iterator> >::value), "");
#if defined(__cpp_lib_string_view_regex)
        static_assert((std::is_same<std::svsub_match, std::sub_match<std::string_view::const_iterator> >::value), "");
        static_assert((std::is_same<std::wsvsub_match, std::sub_match<std::wstring_view::const_iterator> >::value), "");
#endif
    }

    test<char>();
    test<wchar_t>();

  return 0;
}
