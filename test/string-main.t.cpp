// Copyright 2025-2025 by Martin Moene
//
// https://github.com/martinmoene/string-lite
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "string-main.t.hpp"

// C++ language version (represent 98 as 3):

#define string_CPLUSPLUS_V  ( string_CPLUSPLUS / 100 - (string_CPLUSPLUS > 200000 ? 2000 : 1994) )

// Compiler versions:

// MSVC++  6.0  _MSC_VER == 1200  string_COMPILER_MSVC_VERSION ==  60  (Visual Studio 6.0)
// MSVC++  7.0  _MSC_VER == 1300  string_COMPILER_MSVC_VERSION ==  70  (Visual Studio .NET 2002)
// MSVC++  7.1  _MSC_VER == 1310  string_COMPILER_MSVC_VERSION ==  71  (Visual Studio .NET 2003)
// MSVC++  8.0  _MSC_VER == 1400  string_COMPILER_MSVC_VERSION ==  80  (Visual Studio 2005)
// MSVC++  9.0  _MSC_VER == 1500  string_COMPILER_MSVC_VERSION ==  90  (Visual Studio 2008)
// MSVC++ 10.0  _MSC_VER == 1600  string_COMPILER_MSVC_VERSION == 100  (Visual Studio 2010)
// MSVC++ 11.0  _MSC_VER == 1700  string_COMPILER_MSVC_VERSION == 110  (Visual Studio 2012)
// MSVC++ 12.0  _MSC_VER == 1800  string_COMPILER_MSVC_VERSION == 120  (Visual Studio 2013)
// MSVC++ 14.0  _MSC_VER == 1900  string_COMPILER_MSVC_VERSION == 140  (Visual Studio 2015)
// MSVC++ 14.1  _MSC_VER >= 1910  string_COMPILER_MSVC_VERSION == 141  (Visual Studio 2017)
// MSVC++ 14.2  _MSC_VER >= 1920  string_COMPILER_MSVC_VERSION == 142  (Visual Studio 2019)

#if 0

#if defined(_MSC_VER ) && !defined(__clang__)
# define string_COMPILER_MSVC_VER           (_MSC_VER )
# define string_COMPILER_MSVC_VERSION       (_MSC_VER / 10 - 10 * ( 5 + (_MSC_VER < 1900 ) ) )
# define string_COMPILER_MSVC_VERSION_FULL  (_MSC_VER - 100 * ( 5 + (_MSC_VER < 1900 ) ) )
#else
# define string_COMPILER_MSVC_VER           0
# define string_COMPILER_MSVC_VERSION       0
# define string_COMPILER_MSVC_VERSION_FULL  0
#endif

#define string_COMPILER_VERSION( major, minor, patch ) ( 10 * ( 10 * (major) + (minor) ) + (patch) )

#if defined( __apple_build_version__ )
# define string_COMPILER_APPLECLANG_VERSION string_COMPILER_VERSION( __clang_major__, __clang_minor__, __clang_patchlevel__ )
# define string_COMPILER_CLANG_VERSION 0
#elif defined( __clang__ )
# define string_COMPILER_APPLECLANG_VERSION 0
# define string_COMPILER_CLANG_VERSION string_COMPILER_VERSION( __clang_major__, __clang_minor__, __clang_patchlevel__ )
#else
# define string_COMPILER_APPLECLANG_VERSION 0
# define string_COMPILER_CLANG_VERSION 0
#endif

#if defined(__GNUC__) && !defined(__clang__)
# define string_COMPILER_GNUC_VERSION string_COMPILER_VERSION( __GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__ )
#else
# define string_COMPILER_GNUC_VERSION 0
#endif

#endif

#define string_PRESENT( x ) \
    std::cout << #x << ": " << x << "\n"

#define string_ABSENT( x ) \
    std::cout << #x << ": (undefined)\n"

lest::tests & specification()
{
    static lest::tests tests;
    return tests;
}

CASE( "string-lite version" "[.string][.version]" )
{
    string_PRESENT( string_bare_MAJOR   );
    string_PRESENT( string_bare_MINOR   );
    string_PRESENT( string_bare_PATCH   );
    string_PRESENT( string_bare_VERSION );

    // string_PRESENT( string_CPP98_FALLBACK );
}

CASE( "string-lite configuration" "[.string][.config]" )
{
    string_PRESENT( string_CPLUSPLUS );
    string_PRESENT( string_CPLUSPLUS_V );
}

CASE( "__cplusplus" "[.stdc++]" )
{
    string_PRESENT( __cplusplus );

#if _MSVC_LANG
    string_PRESENT( _MSVC_LANG );
#else
    string_ABSENT(  _MSVC_LANG );
#endif
}

CASE( "Compiler version" "[.compiler]" )
{
    string_PRESENT( string_COMPILER_APPLECLANG_VERSION );
    string_PRESENT( string_COMPILER_CLANG_VERSION );
    string_PRESENT( string_COMPILER_GNUC_VERSION );
    string_PRESENT( string_COMPILER_MSVC_VERSION );
    string_PRESENT( string_COMPILER_MSVC_VERSION_FULL );
}

CASE( "presence of C++ language features" "[.stdlanguage]" )
{
    string_PRESENT( string_HAVE_CONSTEXPR_11 );
    string_PRESENT( string_HAVE_DEFAULT_FN_TPL_ARGS );
    string_PRESENT( string_HAVE_EXPLICIT_CONVERSION );
    string_PRESENT( string_HAVE_NODISCARD );
    string_PRESENT( string_HAVE_NOEXCEPT );
}

CASE( "presence of C++ library features" "[.stdlibrary]" )
{
#if defined(_HAS_CPP0X) && _HAS_CPP0X
    string_PRESENT( _HAS_CPP0X );
#else
    string_ABSENT(  _HAS_CPP0X );
#endif
}

int main( int argc, char * argv[] )
{
    return lest::run( specification(), argc, argv );
}

#if 0
g++            -I../include -o string-main.t.exe string-main.t.cpp && string-main.t.exe --pass
g++ -std=c++98 -I../include -o string-main.t.exe string-main.t.cpp && string-main.t.exe --pass
g++ -std=c++03 -I../include -o string-main.t.exe string-main.t.cpp && string-main.t.exe --pass
g++ -std=c++0x -I../include -o string-main.t.exe string-main.t.cpp && string-main.t.exe --pass
g++ -std=c++11 -I../include -o string-main.t.exe string-main.t.cpp && string-main.t.exe --pass
g++ -std=c++14 -I../include -o string-main.t.exe string-main.t.cpp && string-main.t.exe --pass
g++ -std=c++17 -I../include -o string-main.t.exe string-main.t.cpp && string-main.t.exe --pass

cl -EHsc -I../include string-main.t.cpp && string-main.t.exe --pass
#endif

// end of file
