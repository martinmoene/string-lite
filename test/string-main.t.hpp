// Copyright 2021-2021 by Martin Moene
//
// https://github.com/martinmoene/string-lite
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#ifndef TEST_STRING_LITE_H_INCLUDED
#define TEST_STRING_LITE_H_INCLUDED

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

// Limit C++ Core Guidelines checking to GSL Lite:

#if string_COMPILER_MSVC_VER >= 1910
# include <CppCoreCheck/Warnings.h>
# pragma warning(disable: ALL_CPPCORECHECK_WARNINGS)
#endif

#include <iostream>

namespace nonstd {

// use oparator<< instead of to_string() overload;
// see  http://stackoverflow.com/a/10651752/437272

// inline std::ostream & operator<<( std::ostream & os, nonstd::string_ const & v )
// {
//     return os << "[string:" << std::boolalpha << bool(v) << "]";
// }
}

namespace lest {

// using ::nonstd::operator<<;

} // namespace lest

#include "lest_cpp03.hpp"

extern lest::tests & specification();

#define CASE( name ) lest_CASE( specification(), name )

#endif // TEST_STRING_LITE_H_INCLUDED

// end of file