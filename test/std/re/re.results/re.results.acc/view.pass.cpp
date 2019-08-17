//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// UNSUPPORTED: c++03, c++11, c++14, c++17

// <regex>

// class match_results<BidirectionalIterator, Allocator>

// string_view_type str(size_type sub = 0) const;

#include <array>
#include <deque>
#include <list>
#include <regex>
#include <span>
#include <cassert>
#include "test_macros.h"

template <class CharT>
void
test()
{
    static_assert(!std::is_same_v<
        typename std::match_results<CharT*>::string_type,
        typename std::match_results<CharT*>::string_view_type>);
    static_assert(!std::is_same_v<
        typename std::match_results<const CharT*>::string_type,
        typename std::match_results<const CharT*>::string_view_type>);
    static_assert(!std::is_same_v<
        typename std::match_results<typename std::basic_string<CharT>::const_iterator>::string_type,
        typename std::match_results<typename std::basic_string<CharT>::const_iterator>::string_view_type>);
    static_assert(!std::is_same_v<
        typename std::match_results<typename std::basic_string_view<CharT>::const_iterator>::string_type,
        typename std::match_results<typename std::basic_string_view<CharT>::const_iterator>::string_view_type>);
    static_assert(!std::is_same_v<
        typename std::match_results<typename std::array<CharT,42>::const_iterator>::string_type,
        typename std::match_results<typename std::array<CharT,42>::const_iterator>::string_view_type>);
    static_assert(!std::is_same_v<
        typename std::match_results<typename std::vector<CharT>::const_iterator>::string_type,
        typename std::match_results<typename std::vector<CharT>::const_iterator>::string_view_type>);
    static_assert(!std::is_same_v<
        typename std::match_results<typename std::span<CharT>::const_iterator>::string_type,
        typename std::match_results<typename std::span<CharT>::const_iterator>::string_view_type>);
#ifdef __cpp_lib_concepts
    static_assert(std::is_same_v<
        typename std::match_results<typename std::deque<CharT>::const_iterator>::string_type,
        typename std::match_results<typename std::deque<CharT>::const_iterator>::string_view_type>);
#endif
    static_assert(std::is_same_v<
        typename std::match_results<typename std::list<CharT>::const_iterator>::string_type,
        typename std::match_results<typename std::list<CharT>::const_iterator>::string_view_type>);
}

int main(int, char**)
{
    test<char>();
    test<wchar_t>();

    std::match_results<const char*> m;
    const char s[] = "abcdefghijk";
    assert(std::regex_search(s, m, std::regex("cd((e)fg)hi")));
    assert(m.str() == std::string_view(m[0]));
    assert(m.str(0) == std::string_view(m[0]));
    assert(m.str(1) == std::string_view(m[1]));
    assert(m.str(2) == std::string_view(m[2]));
    assert(m.str(3) == std::string_view(m[3]));
    assert(m.str(4) == std::string_view(m[4]));

    return 0;
}
