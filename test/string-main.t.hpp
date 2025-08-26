// Copyright (c) 2025-2025 Martin Moene
//
// https://github.com/martinmoene/string-lite
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#ifndef TEST_STRING_BARE_H_INCLUDED
#define TEST_STRING_BARE_H_INCLUDED

#include string_STRING_HEADER

// Compiler warning suppression for usage of lest:

#ifdef __clang__
# pragma clang diagnostic ignored "-Wstring-conversion"
# pragma clang diagnostic ignored "-Wunused-parameter"
# pragma clang diagnostic ignored "-Wunused-template"
# pragma clang diagnostic ignored "-Wunused-function"
# pragma clang diagnostic ignored "-Wunused-member-function"
#elif defined __GNUC__
# pragma GCC   diagnostic ignored "-Wunused-parameter"
# pragma GCC   diagnostic ignored "-Wunused-function"
#endif

// Limit C++ Core Guidelines checking:

#if string_COMPILER_MSVC_VER >= 1910
# include <CppCoreCheck/Warnings.h>
# pragma warning(disable: ALL_CPPCORECHECK_WARNINGS)
#endif

#include <iostream>

// String to use with iterators:

inline std::string & text()
{
    static std::string text_("abc123mno123xyz");
    return text_;
}

inline nonstd::std17::string_view text_view()
{
    return ::nonstd::string::std17::string_view( text().c_str(), text().length() );
}

const auto sv_npos = ::nonstd::string::npos;

namespace std {

inline std::ostream & operator<<( std::ostream & os, ::nonstd::std17::string_view sv )
{
    return os << "'" << std::string( sv.begin(), sv.end() ) << "'";
}

template< typename T >
inline std::ostream & operator<<( std::ostream & os, std::vector<T>const & vec )
{
    os << "[vector:";

    for ( typename std::vector<T>::const_iterator pos = vec.begin(); pos != vec.end(); ++pos )
    {
        os << " '" << *pos << "',";
    }
    return os << "]";
}

inline std::ostream & operator<<( std::ostream & os, std::vector<::nonstd::std17::string_view> const & vec )
{
    os << "[vector:";

    for ( typename std::vector<::nonstd::std17::string_view>::const_iterator pos = vec.begin(); pos != vec.end(); ++pos )
    {
        os << " '" << std::string( pos->begin(), pos->end() ) << "',";
    }
    return os << "]";
}

}
namespace nonstd {
namespace string {
namespace std17 {

inline bool operator==( string_view const & a, std::string const & b )
{
    return std::string(a.begin(), a.end()) == b;
}

inline bool operator==( std::string const & a, string_view const & b )
{
    return b == a;
}

inline bool operator==( std::vector<string_view> const & a, std::vector<std::string> const & b )
{
    return std::equal( a.begin(), a.end(), b.begin() );
}

inline bool operator==( std::vector<std::string> const & a, std::vector<string_view> const & b )
{
    return b == a;
}

} // namespace std17
} // namespace string
} // namespace nonstd

namespace lest {

    using nonstd::std17::operator==;

} // namespace lest

// #include "lest.hpp"
#include "lest_cpp03.hpp"

extern lest::tests & specification();

#define CASE( name ) lest_CASE( specification(), name )

#endif // TEST_STRING_BARE_H_INCLUDED

// end of file
