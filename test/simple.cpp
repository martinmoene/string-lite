// cl -nologo -std:c++latest -EHsc -I../include simple.cpp
// g++ -std=c++17 -I../include -o simple.exe simple.cpp

#include "nonstd/string.hpp"

#include <locale>
#include <codecvt>
#include <string>
#include <iostream>
// #include <ios>

#if defined(_WIN32) && _WIN32
# include <Windows.h>   // for SetConsoleOutputCP()
#endif

using namespace nonstd;

// To keep it simple than string-lite:
// - no char* as first argument
//

// Functions:

// void print( std::basic_string_view<CharT> text )

// std::wstring_convert<std::codecvt_utf8_utf16<wchar_t> > myconvW;
// std::wstring_convert<std::codecvt_utf8_utf16<char16_t> > myconv16;

#define B( arg ) std::cout  << std::boolalpha << (#arg) << ": '[not shown]\n"; (void)(arg);
#define P( arg ) std::cout  << std::boolalpha << (#arg) << ": '" << (arg) << "'\n";
#define W( arg ) std::wcout << std::boolalpha << (#arg) << ": '" << (arg) << "'\n";
// #define X( arg ) std::cout  << (#arg) << ": '" << myconv16.to_bytes(arg) << "'\n";

// int main()
// {
//     std::wstring ws(L"Your UTF-16 text");
//     std::string bs = myconv.to_bytes(ws);
//     std::cout << bs << '\n';
// }

// char * gtext = "G:Hello, world!";

#if !string_HAVE_STRING_VIEW

template< typename CharT >
std::basic_ostream<CharT> & operator<<(std::basic_ostream<CharT> &os, nonstd::string::std17::basic_string_view<CharT> vw)
{
    return os << vw.to_string();
}

#endif

int main()
{
    try
    {
#if string_COMPILER_MSVC_VER
        // With GCC a couple of lines are not sequential when unsynced:
        std::cout.sync_with_stdio( false );
#endif
#if defined(_WIN32) && _WIN32
        // enable display of utf8, https://stackoverflow.com/a/19071749/437272
        SetConsoleOutputCP(65001) ; /*!= 0; */
#endif
        { P( length(  "Abc" ) ); }
        { P( length( std::string (  "Abc")) ); }
#if string_CONFIG_PROVIDE_WCHAR_T
        { P( length( L"Abc" ) ); }
        { P( length( std::wstring( L"Abc")) ); }
#endif

        { P( size(  "Abc" ) ); }
        { P( size( std::string (  "Abc")) ); }
#if string_CONFIG_PROVIDE_WCHAR_T
        { P( size( L"Abc" ) ); }
        { P( size( std::wstring( L"Abc")) ); }
#endif

        { P( is_empty(  ""    ) ); }
        { P( is_empty(  "Abc" ) ); }
        { P( is_empty( std::string (  "Abc")) ); }
#if string_CONFIG_PROVIDE_WCHAR_T
        { P( is_empty( L"Abc" ) ); }
        { P( is_empty( std::wstring( L"Abc")) ); }
#endif

        { P( find_first( "abbba", "bb" )); }
        { P( find_first( std::string("abbba"), "bb" )); }
        { P( find_first( std::string("abbba"), std::string("bb"))); }

        { P( find_last( "abbba", "bb" )); }
        { P( find_last( std::string("abbba"), "bb" )); }
        { P( find_last( std::string("abbba"), std::string("bb"))); }

        { P( find_first_of( "abcde", "ce" )); }
        { P( find_first_of( std::string("abcde"), "ce" )); }
        { P( find_first_of( std::string("abcde"), std::string("ce"))); }

        { P( find_last_of( "abcde", "ce" )); }
        { P( find_last_of( std::string("abcde"), "ce" )); }
        { P( find_last_of( std::string("abcde"), std::string("ce"))); }

        { P( find_first_not_of( "abcde", "ab" )); }
        { P( find_first_not_of( std::string("abcde"), "ab" )); }
        { P( find_first_not_of( std::string("abcde"), std::string("ab"))); }

        { P( find_last_not_of( "abcde", "de" )); }
        { P( find_last_not_of( std::string("abcde"), "de" )); }
        { P( find_last_not_of( std::string("abcde"), std::string("de"))); }

        { P( contains( "abbba", "bb" )); }
        { P( contains( std::string("abbba"), "bb" )); }
        { P( contains( std::string("abbba"), std::string("bb"))); }

        { P( starts_with( "abbba", "ab" )); }
        { P( starts_with( std::string("abbba"), "ab" )); }
        { P( starts_with( std::string("abbba"), std::string("ab"))); }

        { P( ends_with( "abbba", "ba" )); }
        { P( ends_with( std::string("abbba"), "ba" )); }
        { P( ends_with( std::string("abbba"), std::string("ba"))); }


#if !string_HAVE_CHAR8_T
        { auto result = to_lowercase( u8"aBC");               std::cout << result << "\n"; }
#endif
        { auto result = to_lowercase( "aBC");                 std::cout << result << "\n"; }
        { auto result = to_lowercase( std::string("aBC") );   std::cout << result << "\n";  }
#if string_CONFIG_PROVIDE_WCHAR_T
        { auto result = to_lowercase( L"aBC");                std::wcout << result << "\n"; }
        { auto result = to_lowercase( std::wstring(L"aBC") ); std::wcout << result << "\n"; }
#endif

        // { auto result = to_lowercase( u"ABC");                 /*std::wcout << result << "\n"; */ }
        // { auto result = to_lowercase( U"ABC");                 /*std::cout << result << "\n"; */}

#if !string_HAVE_CHAR8_T
        { auto result = to_uppercase( u8"Abc");               std::cout << result << "\n"; }
#endif
        { auto result = to_uppercase( "Abc");                 std::cout << result << "\n"; }
        { auto result = to_uppercase( std::string("Abc") );   std::cout << result << "\n";  }
#if string_CONFIG_PROVIDE_WCHAR_T
        { auto result = to_uppercase( L"Abc");                std::wcout << result << "\n"; }
        { auto result = to_uppercase( std::wstring(L"Abc") ); std::wcout << result << "\n"; }
#endif

        { P( strip_left( "abcde", "ab" )); }
        { P( strip_left( std::string("abcde"), "ba" )); }
        { P( strip_left( std::string("abcde"), std::string("ba"))); }

        { P( strip_right( "abcde", "de" )); }
        { P( strip_right( std::string("abcde"), "ed" )); }
        { P( strip_right( std::string("abcde"), std::string("ed"))); }

        { P( strip( "abcde", "abde" )); }
        { P( strip( std::string("abcde"), "deab" )); }
        { P( strip( std::string("abcde"), std::string("deab"))); }

        { P( replace_all( "abcde", "bcd", "xyz" )); }
        { P( replace_all( std::string("abcde"), "bcd", "xyz" )); }
        { P( replace_all( std::string("abcde"), std::string("bcd"), "xyz")); }
        { P( replace_all( std::string("abcde"), std::string("bcd"), std::string("xyz"))); }

        { P( replace_first( "abcde", "bcd", "xyz" )); }
        { P( replace_first( std::string("abcde"), "bcd", "xyz" )); }
        { P( replace_first( std::string("abcde"), std::string("bcd"), "xyz")); }
        { P( replace_first( std::string("abcde"), std::string("bcd"), std::string("xyz"))); }

        { P( replace_last( "abcde", "bcd", "xyz" )); }
        { P( replace_last( std::string("abcde"), "bcd", "xyz" )); }
        { P( replace_last( std::string("abcde"), std::string("bcd"), "xyz")); }
        { P( replace_last( std::string("abcde"), std::string("bcd"), std::string("xyz"))); }

        { P( append( "abc", "def" )); }
        { P( append( std::string("abc"), "def" )); }
        { P( append( std::string("abc"), std::string("def"))); }

        // join()
        {
            using std::vector;
            using nonstd::std17::string_view;

            vector<string_view> coll = { "abc", "def", "ghi"};

            P( join( coll, "-" ) );
        }

        // split()
        {
            auto result = split("abc;def;ghi", "X");
            for ( const auto & item : result )
            {
                std::cout << "[" << item << "]";
            }
            std::cout << "\n";
        }{
            auto result = split("abc;def;ghi", ";");
            for ( const auto & item : result )
            {
                std::cout << "[" << item << "]";
            }
            std::cout << "\n";
        }{
            auto result = split("abc;def;ghi", ";", 2);
            for ( const auto & item : result )
            {
                std::cout << "[" << item << "]";
            }
            std::cout << "\n";
        }

        // split_2()
        {
            std17::string_view a, b;
            std::tie(a, b) = split_2("abc;def;ghi", ";");

            std::cout << "[a:" << a << "][b:" << b << "]\n";
        }

    }
    catch (std::exception const & e)
    {
        std::cout << "Exception: " << e.what() << "\n";
    }
    catch (...)
    {
        std::cout << "Unknown Exception\n";
    }
}
