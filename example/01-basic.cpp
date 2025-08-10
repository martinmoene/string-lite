// Use nonstd::string's split():

#include "nonstd/string.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#if string_CPP11_000

template< typename T >
std::string contents(std::vector<T> const & coll)
{
    // using to_string() for nonstd::string::string_view:

    std::stringstream os;
    for ( auto const & elem : coll )
        os << "'" << std::string(elem) << "', ";
    return os.str();
}

#else

template< typename T >
std::string contents(std::vector<T> const & coll)
{
    // using to_string() for nonstd::string::string_view:

    typename std::vector<T>::const_iterator pos = coll.begin();
    typename std::vector<T>::const_iterator end = coll.end();

    std::stringstream os;
    for ( ; pos != end; ++pos )
        os << "'" << std::string(*pos) << "', ";
    return os.str();
}

#endif

template< typename T >
std::ostream & operator<<(std::ostream & os, std::vector<T> const & coll )
{
    return os << "[" << contents(coll) << "]";
}

int main()
{
    std::cout << nonstd::split("Hello, world", ",");
}

// cl -nologo -EHsc -I../include 01-basic.cpp && 01-basic.exe
// clang-cl -EHsc -D_CRT_SECURE_NO_WARNINGS -I../include 01-basic.cpp && 01-basic.exe
// g++ -std=c++11 -Wall -I../include -o 01-basic.exe 01-basic.cpp && 01-basic.exe

// Output:
// ['Hello', ' world', ]
