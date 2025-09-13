// Copyright (c) 2016-2020 Martin Moene
//
// https://github.com/martinmoene/string-lite
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "nonstd/string.hpp"
#include <iostream>

template< typename T >
void use( T const & /*x*/) {}

#define string_PRESENT( x ) \
    std::cout << #x << ": " << x << "\n"

#define string_ABSENT( x ) \
    std::cout << #x << ": (undefined)\n"

void report()
{
#ifdef __cpp_exceptions
    string_PRESENT( __cpp_exceptions );
#else
    string_ABSENT(  __cpp_exceptions );
#endif

#ifdef __EXCEPTIONS
    string_PRESENT( __EXCEPTIONS );
#else
    string_ABSENT(  __EXCEPTIONS );
#endif

#ifdef _HAS_EXCEPTIONS
    string_PRESENT( _HAS_EXCEPTIONS );
#else
    string_ABSENT(  _HAS_EXCEPTIONS );
#endif

#ifdef _CPPUNWIND
    string_PRESENT( _CPPUNWIND );
#else
    string_ABSENT(  _CPPUNWIND );
#endif

#ifdef _CPPRTTI
    string_PRESENT( _CPPRTTI  );
#else
    string_ABSENT(  _CPPRTTI  );
#endif
}

int violate_access()
{
    // nonstd::expected<int, char> eu( nonstd:: make_unexpected('a') );

    // return eu.value();

    return -1;
}

int main()
{
    report();

#if ! nsel_CONFIG_NO_EXCEPTIONS_SEH
    return violate_access();
#else
    __try
    {
        return violate_access();
    }
    __except( EXCEPTION_EXECUTE_HANDLER )
    {
        std::cerr << "\n*** Executing SEH __except block ***\n";
    }
#endif
}

// end of file
