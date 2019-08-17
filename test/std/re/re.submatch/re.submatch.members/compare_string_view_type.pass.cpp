//===----------------------------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// UNSUPPORTED: c++98, c++03, c++11, c++14, c++17

// <regex>

// template <class BidirectionalIterator> class sub_match;

// int compare(string_view_type s) const;

#include <array>
#include <deque>
#include <list>
#include <regex>
#include <span>
#include <cassert>
#include "test_macros.h"

// TODO not the best place for this test find a better spot
template <class CharT>
void
test() // TAG REMOVE USE THE types.pass.cpp
{
    static_assert(!std::is_same_v<
        typename std::sub_match<CharT*>::string_type,
        typename std::sub_match<CharT*>::string_view_type>);
    static_assert(!std::is_same_v<
        typename std::sub_match<const CharT*>::string_type,
        typename std::sub_match<const CharT*>::string_view_type>);
    static_assert(!std::is_same_v<
        typename std::sub_match<typename std::basic_string<CharT>::const_iterator>::string_type,
        typename std::sub_match<typename std::basic_string<CharT>::const_iterator>::string_view_type>);
    static_assert(!std::is_same_v<
        typename std::sub_match<typename std::basic_string_view<CharT>::const_iterator>::string_type,
        typename std::sub_match<typename std::basic_string_view<CharT>::const_iterator>::string_view_type>);
    static_assert(!std::is_same_v<
        typename std::sub_match<typename std::array<CharT,42>::const_iterator>::string_type,
        typename std::sub_match<typename std::array<CharT,42>::const_iterator>::string_view_type>);
    static_assert(!std::is_same_v<
        typename std::sub_match<typename std::vector<CharT>::const_iterator>::string_type,
        typename std::sub_match<typename std::vector<CharT>::const_iterator>::string_view_type>);
    static_assert(!std::is_same_v<
        typename std::sub_match<typename std::span<CharT>::const_iterator>::string_type,
        typename std::sub_match<typename std::span<CharT>::const_iterator>::string_view_type>);
#ifdef __cpp_lib_concepts
    static_assert(std::is_same_v<
        typename std::sub_match<typename std::deque<CharT>::const_iterator>::string_type,
        typename std::sub_match<typename std::deque<CharT>::const_iterator>::string_view_type>);
#endif
    static_assert(std::is_same_v<
        typename std::sub_match<typename std::list<CharT>::const_iterator>::string_type,
        typename std::sub_match<typename std::list<CharT>::const_iterator>::string_view_type>);
}

int main()
{
    test<char>();
    test<wchar_t>();

    {
        typedef char CharT;
        typedef std::sub_match<const CharT*> SM;
        typedef SM::string_view_type string_view;
        SM sm = SM();
        assert(sm.compare(string_view()) == 0);
        const CharT s[] = {'1', '2', '3', 0};
        sm.first = s;
        sm.second = s + 3;
        sm.matched = true;
        assert(sm.compare(string_view()) > 0);
        assert(sm.compare(string_view("123")) == 0);
    }
    {
        typedef wchar_t CharT;
        typedef std::sub_match<const CharT*> SM;
        typedef SM::string_view_type string_view;
        SM sm = SM();
        assert(sm.compare(string_view()) == 0);
        const CharT s[] = {'1', '2', '3', 0};
        sm.first = s;
        sm.second = s + 3;
        sm.matched = true;
        assert(sm.compare(string_view()) > 0);
        assert(sm.compare(string_view(L"123")) == 0);
    }
}
