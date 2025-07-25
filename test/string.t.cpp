// Copyright 2021-2021 Martin Moene
//
// https://github.com/martinmoene/string-lite
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "string-main.t.hpp"

#ifdef _WIN32
# define string_strdup  _strdup
#else
# define string_strdup   strdup
#endif

namespace {

using namespace nonstd;

struct scoped_str
{
    char * p;

    scoped_str( char const * s ) : p ( string_strdup(s) ) {}

    ~scoped_str() { delete p; }

    operator char const *() { return p; }

    char * get() { return p; }
};

inline char const * lstr() { return "a b c d e f g h i j k l m n o p q r s t u v w x y z"; }
inline char const * ustr() { return "A B C D E F G H I J K L M N O P Q R S T U V W X Y Z"; }

struct stringy : std::string
{
    stringy( char const * text )
        : std::string( text ) {}

    // std::string::iterator begin() { return }
};

namespace std17 {

    using ::nonstd::string::std20::string_view;
    inline typename string_view::size_type sv_npos() { return string_view::npos; }
}

// Tests:

CASE( "string: Setting Windows console to print utf8 characters" "[unicode][windows]" )
{
#if defined(_WIN32) && _WIN32
    // enable display of utf8, https://stackoverflow.com/a/19071749/437272
    EXPECT( SetConsoleOutputCP(65001) != 0 );
#else
    EXPECT( !!"string: skipping (non-Windows)" );
#endif
}

// Observers:

// length():

CASE( "length: length of given string - char *" )
{
    EXPECT( length("abc") == 3 );
}

CASE( "length: length of given string - std::string" )
{
    EXPECT( length(std::string("abc")) == 3 );
}

// size():

CASE( "size: length of given string - char *" )
{
    EXPECT( size("abc") == 3 );
}

CASE( "size: length of given string - std::string" )
{
    EXPECT( size(std::string("abc")) == 3 );
}

// is_empty():

CASE( "is_empty: true if string is empty - char *" )
{
    EXPECT(     is_empty("") );
    EXPECT_NOT( is_empty("a") );
}

CASE( "is_empty: true if string is empty - string" )
{
    EXPECT(     is_empty(std::string()) );
    EXPECT_NOT( is_empty(std::string("x")) );
}

// contains():

CASE( "contains: true if string contains sub string - string-char" )
{
    EXPECT(     contains(std::string("abc123mno123xyz"), '1') );
    EXPECT_NOT( contains(std::string("abc123mno123xyz"), '7') );
}

CASE( "contains: true if string contains sub string - string-char*" )
{
    EXPECT(     contains(std::string("abc123mno123xyz"), "123") );
    EXPECT_NOT( contains(std::string("abc123mno123xyz"), "789") );
}

CASE( "contains: true if string contains sub string - string-string" )
{
    EXPECT(     contains(std::string("abc123mno123xyz"), std::string("123")) );
    EXPECT_NOT( contains(std::string("abc123mno123xyz"), std::string("789")) );
}

CASE( "contains: true if string contains sub string - string-string_view" )
{
    EXPECT(     contains(std::string("abc123mno123xyz"), std20::string_view("123")) );
    EXPECT_NOT( contains(std::string("abc123mno123xyz"), std20::string_view("789")) );
}

CASE( "contains: true if string contains sub string - string_view-string_view" )
{
    EXPECT(     contains(std20::string_view("abc123mno123xyz"), std20::string_view("123")) );
    EXPECT_NOT( contains(std20::string_view("abc123mno123xyz"), std20::string_view("789")) );
}

CASE( "contains: true if string contains regular expression - string-std::regex" )
{
#if string_CONFIG_PROVIDE_REGEX
#if string_HAVE_REGEX
    EXPECT(     contains(std::string("abc123mno123xyz"), std::regex("[0-9]+")) );
    EXPECT_NOT( contains(std::string("abc123mno123xyz"), std::regex("[4-9]+")) );
#else
    EXPECT( !!"contains(regex) is not available (string_HAVE_REGEX)." );
#endif
#else
    EXPECT( !!"regex is not available (not configured, string_CONFIG_PROVIDE_REGEX)." );
#endif
}

CASE( "contains_re: true if string contains regular expression - string-char*" )
{
#if string_CONFIG_PROVIDE_REGEX
#if string_HAVE_REGEX
    EXPECT(     contains_re(std::string("abc123mno123xyz"), "^[a-z]+") );
    EXPECT(     contains_re(std::string("abc123mno123xyz"), "[0-9]+") );
    EXPECT_NOT( contains_re(std::string("abc123mno123xyz"), "[4-9]+") );
#else
    EXPECT( !!"contains(regex) is not available (string_HAVE_REGEX)." );
#endif
#else
    EXPECT( !!"regex is not available (not configured, string_CONFIG_PROVIDE_REGEX)." );
#endif
}

// starts_with():

CASE( "starts_with: true if string starts with sub string - string-char" )
{
    EXPECT(     starts_with(std::string("abc123mno123xyz"), 'a') );
    EXPECT_NOT( starts_with(std::string("abc123mno123xyz"), 'b') );
}

CASE( "starts_with: true if string starts with sub string - string-char*" )
{
    EXPECT(     starts_with(std::string("abc123mno123xyz"), "a") );
    EXPECT_NOT( starts_with(std::string("abc123mno123xyz"), "b") );
}

CASE( "starts_with: true if string starts with sub string - string-string" )
{
    EXPECT(     starts_with(std::string("abc123mno123xyz"), std::string("a")) );
    EXPECT_NOT( starts_with(std::string("abc123mno123xyz"), std::string("b")) );
}

CASE( "starts_with: true if string starts with sub string - string-string_view" )
{
    EXPECT(     starts_with(std::string("abc123mno123xyz"), std20::string_view("a")) );
    EXPECT_NOT( starts_with(std::string("abc123mno123xyz"), std20::string_view("b")) );
}

CASE( "starts_with: true if string starts with sub string - string_view-string_view" )
{
    EXPECT(     starts_with(std20::string_view("abc123mno123xyz"), std20::string_view("a")) );
    EXPECT_NOT( starts_with(std20::string_view("abc123mno123xyz"), std20::string_view("b")) );
}

CASE( "starts_with: true if string starts with regular expression - string-std::regex" "[.TODO]" )
{
#if string_CONFIG_PROVIDE_REGEX
#if string_HAVE_REGEX
    EXPECT(     starts_with(std::string("abc123mno123xyz"), std::regex("[a-c]")) );
    EXPECT_NOT( starts_with(std::string("abc123mno123xyz"), std::regex("[1-3]")) );
#else
    EXPECT( !!"starts_with(regex) is not available (string_HAVE_REGEX)." );
#endif
#else
    EXPECT( !!"regex is not available (not configured, string_CONFIG_PROVIDE_REGEX)." );
#endif
}

CASE( "starts_with_re: true if string starts with regular expression - string-char*" "[.TODO]" )
{
#if string_CONFIG_PROVIDE_REGEX
#if string_HAVE_REGEX
    EXPECT(     starts_with_re(std::string("abc123mno123xyz"), "[a-c]") );
    EXPECT_NOT( starts_with_re(std::string("abc123mno123xyz"), "[1-3]") );
#else
    EXPECT( !!"starts_with_re is not available (string_HAVE_REGEX)." );
#endif
#else
    EXPECT( !!"regex is not available (not configured, string_CONFIG_PROVIDE_REGEX)." );
#endif
}

// ends_with():

CASE( "ends_with: true if string ends with sub string - string-char" )
{
    EXPECT(     ends_with(std::string("abc123mno123xyz"), 'z') );
    EXPECT_NOT( ends_with(std::string("abc123mno123xyz"), 'y') );
}

CASE( "ends_with: true if string ends with sub string - string-char*" )
{
    EXPECT(     ends_with(std::string("abc123mno123xyz"), "z") );
    EXPECT_NOT( ends_with(std::string("abc123mno123xyz"), "y") );
}

CASE( "ends_with: true if string ends with sub string - string-string" )
{
    EXPECT(     ends_with(std::string("abc123mno123xyz"), std::string("z")) );
    EXPECT_NOT( ends_with(std::string("abc123mno123xyz"), std::string("y")) );
}

CASE( "ends_with: true if string ends with sub string - string-string_view" )
{
    EXPECT(     ends_with(std::string("abc123mno123xyz"), std20::string_view("z")) );
    EXPECT_NOT( ends_with(std::string("abc123mno123xyz"), std20::string_view("y")) );
}

CASE( "ends_with: true if string ends with sub string - string_view-string_view" )
{
    EXPECT(     ends_with(std20::string_view("abc123mno123xyz"), std20::string_view("z")) );
    EXPECT_NOT( ends_with(std20::string_view("abc123mno123xyz"), std20::string_view("y")) );
}

CASE( "ends_with: true if string ends with regular expression - string-std::regex" "[.TODO]" )
{
#if string_CONFIG_PROVIDE_REGEX
#if string_HAVE_REGEX
    EXPECT(     ends_with(std::string("abc123mno123xyz"), std::regex("[0-9]+")) );
    EXPECT_NOT( ends_with(std::string("abc123mno123xyz"), std::regex("[4-9]+")) );
#else
    EXPECT( !!"ends_with(regex) is not available (string_HAVE_REGEX)." );
#endif
#else
    EXPECT( !!"regex is not available (not configured, string_CONFIG_PROVIDE_REGEX)." );
#endif
}

CASE( "ends_with_re: true if string ends with regular expression - string-char*" "[.TODO]" )
{
#if string_CONFIG_PROVIDE_REGEX
#if string_HAVE_REGEX
    EXPECT(     ends_with_re(std::string("abc123mno123xyz"), "[0-9]+") );
    EXPECT_NOT( ends_with_re(std::string("abc123mno123xyz"), "[4-9]+") );
#else
    EXPECT( !!"ends_with_re is not available (string_HAVE_REGEX)." );
#endif
#else
    EXPECT( !!"regex is not available (not configured, string_CONFIG_PROVIDE_REGEX)." );
#endif
}

// find_first():

CASE( "find_first: position of sub string in string - string-char" )
{
    EXPECT(       3 == find_first("abc123mno123xyz", '1') );
    EXPECT( sv_npos == find_first("abc123mno123xyz", '7') );
}

CASE( "find_first: position of sub string in string - string-char*" )
{
    EXPECT(       3 == find_first("abc123mno123xyz", "123") );
    EXPECT( sv_npos == find_first("abc123mno123xyz", "789") );
}

CASE( "find_first: position of sub string in string - string-string" )
{
    EXPECT(       3 == find_first("abc123mno123xyz", std::string("123")) );
    EXPECT( sv_npos == find_first("abc123mno123xyz", std::string("789")) );
}

CASE( "find_first: position of sub string in string - string-string_view" )
{
    EXPECT(       3 == find_first("abc123mno123xyz", std20::string_view("123")) );
    EXPECT( sv_npos == find_first("abc123mno123xyz", std20::string_view("789")) );
}

CASE( "find_first: position of sub string in string_view - string_view-string_view" )
{
    // text((): "abc123mno123xyz"

    EXPECT(       3 == find_first(text_view(), std20::string_view("123")) );
    EXPECT( sv_npos == find_first(text_view(), std20::string_view("789")) );
}

CASE( "find_first: position of regex in string: string-std::regex" "[.TODO]" )
{
#if string_CONFIG_PROVIDE_REGEX
#if string_HAVE_REGEX
    EXPECT(       3 == find_first("abc123mno123xyz", std::regex("[0-9]+")) );
    EXPECT( sv_npos == find_first("abc123mno123xyz", std::regex("[7-9]+")) );
#else
    EXPECT( !!"find_first(regex) is not available (string_HAVE_REGEX)." );
#endif
#else
    EXPECT( !!"regex is not available (not configured, string_CONFIG_PROVIDE_REGEX)." );
#endif
}

// TODO: find_first_re()

CASE( "find_first_re: position of regex in string: string-char*" "[.TODO]" )
{
#if string_CONFIG_PROVIDE_REGEX
#if string_HAVE_REGEX
    EXPECT(       3 == find_first_re("abc123mno123xyz", "[0-9]") );
    EXPECT( sv_npos == find_first_re("abc123mno123xyz", "[7-9]") );
#else
    EXPECT( !!"find_first_re is not available (string_HAVE_REGEX)." );
#endif
#else
    EXPECT( !!"regex is not available (not configured, string_CONFIG_PROVIDE_REGEX)." );
#endif
}

// find_last():

CASE( "find_last: position of sub string in string - string-char" )
{
    EXPECT(       9 == find_last("abc123mno123xyz", '1') );
    EXPECT( sv_npos == find_last("abc123mno123xyz", '7') );
}

CASE( "find_last: position of sub string in string - string-char*" )
{
    EXPECT(       9 == find_last("abc123mno123xyz", "123") );
    EXPECT( sv_npos == find_last("abc123mno123xyz", "789") );
}

CASE( "find_last: position of sub string in string - string-string" )
{
    EXPECT(       9 == find_last("abc123mno123xyz", std::string("123")) );
    EXPECT( sv_npos == find_last("abc123mno123xyz", std::string("789")) );
}

CASE( "find_last: position of sub string in string - string-string_view" )
{
    EXPECT(       9 == find_last("abc123mno123xyz", std20::string_view("123")) );
    EXPECT( sv_npos == find_last("abc123mno123xyz", std20::string_view("789")) );
}

CASE( "find_last: position of sub string in string_view - string_view-string_view" )
{
    // text((): "abc123mno123xyz"

    EXPECT(       9 == find_last(text_view(), std20::string_view("123")) );
    EXPECT( sv_npos == find_last(text_view(), std20::string_view("789")) );
}

CASE( "find_last: position of regex in string: string-std::regex" "[.TODO]" )
{
#if string_CONFIG_PROVIDE_REGEX
#if string_HAVE_REGEX
    EXPECT(       9 == find_last("abc123mno123xyz", std::regex("[0-9]+")) );
    EXPECT( sv_npos == find_last("abc123mno123xyz", std::regex("[7-9]+")) );
#else
    EXPECT( !!"find_last(regex) is not available (string_HAVE_REGEX)." );
#endif
#else
    EXPECT( !!"regex is not available (not configured, string_CONFIG_PROVIDE_REGEX)." );
#endif
}

// TODO: find_last_re()

CASE( "find_last_re: position of regex in string: string-char*" "[.TODO]" )
{
#if string_CONFIG_PROVIDE_REGEX
#if string_HAVE_REGEX
    EXPECT(       9 == find_last_re("abc123mno123xyz", "[0-9]") );
    EXPECT( sv_npos == find_last_re("abc123mno123xyz", "[7-9]") );
#else
    EXPECT( !!"find_last_re is not available (string_HAVE_REGEX)." );
#endif
#else
    EXPECT( !!"regex is not available (not configured, string_CONFIG_PROVIDE_REGEX)." );
#endif
}

// find_first_of()

CASE( "find_first_of: position of sub string in string - char*-char*" )
{
    EXPECT(       3 == find_first_of("abc123mno123xyz", "321") );
    EXPECT( sv_npos == find_first_of("abc123mno123xyz", "789") );
}

CASE( "find_first_of: position of sub string in string - string-char*" )
{
    EXPECT(       3 == find_first_of(std::string("abc123mno123xyz"), "321") );
    EXPECT( sv_npos == find_first_of(std::string("abc123mno123xyz"), "789") );
}

CASE( "find_first_of: position of sub string in string - string-string" )
{
    EXPECT(       3 == find_first_of(std::string("abc123mno123xyz"), std::string("321") ) );
    EXPECT( sv_npos == find_first_of(std::string("abc123mno123xyz"), std::string("789") ) );
}

CASE( "find_first_of: position of regex in string: string-std::regex" "[.TODO]" )
{
#if string_CONFIG_PROVIDE_REGEX
#if string_HAVE_REGEX
    EXPECT(       3 == find_first_of(std::string("abc123mno123xyz"), std::regex("[0-9]+")) );
    EXPECT( sv_npos == find_first_of(std::string("abc123mno123xyz"), std::regex("[7-9]+")) );
#else
    EXPECT( !!"find_first_of(regex) is not available (string_HAVE_REGEX)." );
#endif
#else
    EXPECT( !!"regex is not available (not configured, string_CONFIG_PROVIDE_REGEX)." );
#endif
}

// find_first_of_re()

CASE( "find_first_of_re: position of regex in string: string-char*" "[.TODO]" )
{
#if string_CONFIG_PROVIDE_REGEX
#if string_HAVE_REGEX
    EXPECT(       3 == find_first_of_re(std::string("abc123mno123xyz"), "[0-9]+") );
    EXPECT( sv_npos == find_first_of_re(std::string("abc123mno123xyz"), "[7-9]+") );
#else
    EXPECT( !!"find_first_of_re is not available (string_HAVE_REGEX)." );
#endif
#else
    EXPECT( !!"regex is not available (not configured, string_CONFIG_PROVIDE_REGEX)." );
#endif
}

// TODO: find_last_of()

CASE( "find_last_of: position of sub string in string - char*-char*" )
{
    EXPECT(       11 == find_last_of("abc123mno123xyz", "123") );
    EXPECT( sv_npos == find_last_of("abc123mno123xyz", "789") );
}

CASE( "find_last_of: position of sub string in string - string-char*" )
{
    EXPECT(       11 == find_last_of(std::string("abc123mno123xyz"), "123") );
    EXPECT( sv_npos == find_last_of(std::string("abc123mno123xyz"), "789") );
}

CASE( "find_last_of: position of sub string in string - string-string" )
{
    EXPECT(       11 == find_last_of(std::string("abc123mno123xyz"), std::string("123") ) );
    EXPECT( sv_npos == find_last_of(std::string("abc123mno123xyz"), std::string("789") ) );
}

CASE( "find_last_of: position of regex in string: string-std::regex" "[.TODO]" )
{
#if string_CONFIG_PROVIDE_REGEX
#if string_HAVE_REGEX
    EXPECT(       3 == find_last_of(std::string("abc123mno123xyz"), std::regex("[0-9]+")) );
    EXPECT( sv_npos == find_last_of(std::string("abc123mno123xyz"), std::regex("[7-9]+")) );
#else
    EXPECT( !!"find_last_of(regex) is not available (string_HAVE_REGEX)." );
#endif
#else
    EXPECT( !!"regex is not available (not configured, string_CONFIG_PROVIDE_REGEX)." );
#endif
}

// find_last_of_re()

CASE( "find_last_of_re: position of regex in string: string-char*" "[.TODO]" )
{
#if string_CONFIG_PROVIDE_REGEX
#if string_HAVE_REGEX
    EXPECT(       3 == find_last_of_re(std::string("abc123mno123xyz"), "[0-9]+") );
    EXPECT( sv_npos == find_last_of_re(std::string("abc123mno123xyz"), "[7-9]+") );
#else
    EXPECT( !!"find_last_of_re is not available (string_HAVE_REGEX)." );
#endif
#else
    EXPECT( !!"regex is not available (not configured, string_CONFIG_PROVIDE_REGEX)." );
#endif
}

// TODO: find_first_not_of()

CASE( "find_first_not_of: position of sub string in string - char*-char*" )
{
    EXPECT(       3 == find_first_not_of("abc123mno123xyz", "cba") );
    EXPECT( sv_npos == find_first_not_of("abc123mno123xyz", "abc123mno123xyz") );
}

CASE( "find_first_not_of: position of sub string in string - string-char*" )
{
    EXPECT(       3 == find_first_not_of(std::string("abc123mno123xyz"), "cba") );
    EXPECT( sv_npos == find_first_not_of(std::string("abc123mno123xyz"), "abc123mno123xyz") );
}

CASE( "find_first_not_of: position of sub string in string - string-string" )
{
    EXPECT(       3 == find_first_not_of(std::string("abc123mno123xyz"), std::string("cba") ) );
    EXPECT( sv_npos == find_first_not_of(std::string("abc123mno123xyz"), std::string("abc123mno123xyz") ) );
}

CASE( "find_first_not_of: position of regex in string: string-std::regex" "[.TODO]" )
{
#if string_CONFIG_PROVIDE_REGEX
#if string_HAVE_REGEX
    EXPECT(       3 == find_first_not_of(std::string("abc123mno123xyz"), std::regex("[0-9]+")) );
    EXPECT( sv_npos == find_first_not_of(std::string("abc123mno123xyz"), std::regex("[7-9]+")) );
#else
    EXPECT( !!"find_first_not_of(regex) is not available (string_HAVE_REGEX)." );
#endif
#else
    EXPECT( !!"regex is not available (not configured, string_CONFIG_PROVIDE_REGEX)." );
#endif
}

// TODO: find_first_not_of_re()

CASE( "find_first_not_of_re: position of regex in string: string-char*" "[.TODO]" )
{
#if string_CONFIG_PROVIDE_REGEX
#if string_HAVE_REGEX
    EXPECT(       3 == find_first_not_of_re(std::string("abc123mno123xyz"), "[0-9]+") );
    EXPECT( sv_npos == find_first_not_of_re(std::string("abc123mno123xyz"), "[7-9]+") );
#else
    EXPECT( !!"find_first_not_of_re is not available (string_HAVE_REGEX)." );
#endif
#else
    EXPECT( !!"regex is not available (not configured, string_CONFIG_PROVIDE_REGEX)." );
#endif
}

// TODO: find_last_not_of()

CASE( "find_last_not_of: position of sub string in string - char*-char*" )
{
    EXPECT(      11 == find_last_not_of("abc123mno123xyz", "zyx") );
    EXPECT( sv_npos == find_last_not_of("abc123mno123xyz", "abc123mno123xyz") );
}

CASE( "find_last_not_of: position of sub string in string - string-char*" )
{
    EXPECT(      11 == find_last_not_of(std::string("abc123mno123xyz"), "zyx") );
    EXPECT( sv_npos == find_last_not_of(std::string("abc123mno123xyz"), "abc123mno123xyz") );
}

CASE( "find_last_not_of: position of sub string in string - string-string" )
{
    EXPECT(      11 == find_last_not_of(std::string("abc123mno123xyz"), std::string("zyx") ) );
    EXPECT( sv_npos == find_last_not_of(std::string("abc123mno123xyz"), std::string("abc123mno123xyz") ) );
}

CASE( "find_last_not_of: position of regex in string: string-std::regex" "[.TODO]" )
{
#if string_CONFIG_PROVIDE_REGEX
#if string_HAVE_REGEX
    EXPECT(      11 == find_last_not_of(std::string("abc123mno123xyz"), std::regex("[0-9]+")) );
    EXPECT( sv_npos == find_last_not_of(std::string("abc123mno123xyz"), std::regex("[7-9]+")) );
#else
    EXPECT( !!"find_last_not_of(regex) is not available (string_HAVE_REGEX)." );
#endif
#else
    EXPECT( !!"regex is not available (not configured, string_CONFIG_PROVIDE_REGEX)." );
#endif
}

// TODO: find_last_not_of_re()

CASE( "find_last_not_of_re: position of regex in string: string-char*" "[.TODO]" )
{
#if string_CONFIG_PROVIDE_REGEX
#if string_HAVE_REGEX
    EXPECT(      11 == find_last_not_of_re(std::string("abc123mno123xyz"), "[0-9]+") );
    EXPECT( sv_npos == find_last_not_of_re(std::string("abc123mno123xyz"), "[7-9]+") );
#else
    EXPECT( !!"find_last_not_of_re is not available (string_HAVE_REGEX)." );
#endif
#else
    EXPECT( !!"regex is not available (not configured, string_CONFIG_PROVIDE_REGEX)." );
#endif
}

// Modifiers:

// to_lowercase(), to_uppercase:

CASE( "to_lowercase: Return string in lowercase - char*" )
{
    EXPECT( to_lowercase(ustr()) == lstr() );
}

CASE( "to_lowercase: Return string in lowercase - string" )
{
    EXPECT( to_lowercase(std::string(ustr())) == lstr() );
}

CASE( "to_lowercase: Return string in lowercase - string_view" )
{
    EXPECT( to_lowercase(std20::string_view(ustr())) == lstr() );
}

CASE( "to_uppercase: Return string in uppercase - char*" )
{
    EXPECT( to_uppercase(lstr()) == ustr() );
}

CASE( "to_uppercase: Return string in uppercase - string" )
{
    EXPECT( to_uppercase(std::string(lstr())) == ustr() );
}

CASE( "to_uppercase: Return string in uppercase - string_view" )
{
    EXPECT( to_uppercase(std20::string_view(lstr())) == ustr() );
}

// append():

CASE( "append: Return string with second string append to first string - string-char*" )
{
    EXPECT( append(std::string("abc"), "xyz") == std::string("abcxyz") );
}

CASE( "append: Return string with second string append to first string - string-string" )
{
    EXPECT( append(std::string("abc"), std::string("xyz")) == std::string("abcxyz") );
}

CASE( "append: Return string with second string append to first string - string-string_view" )
{
    EXPECT( append(std::string("abc"), std20::string_view("xyz")) == std::string("abcxyz") );
}

// substring()

CASE( "substring: Return substring given position and length - char*-pos" )
{
    EXPECT( substring("abcxyz", 2, 3) == "cxy" );
    EXPECT( substring("abcxyz", 2   ) == "cxyz" );
    EXPECT( substring("abcxyz"      ) == "abcxyz" );
}

CASE( "substring: Return substring given position and length - string-pos" )
{
    EXPECT( substring(std::string("abcxyz"), 2, 3) == "cxy" );
    EXPECT( substring(std::string("abcxyz"), 2   ) == "cxyz" );
    EXPECT( substring(std::string("abcxyz")      ) == "abcxyz" );
}

CASE( "substring: Return substring given position and length - string_view-pos" )
{
    EXPECT( substring(std20::string_view("abcxyz"), 2, 3) == "cxy" );
    EXPECT( substring(std20::string_view("abcxyz"), 2   ) == "cxyz" );
    EXPECT( substring(std20::string_view("abcxyz")      ) == "abcxyz" );
}

CASE( "substring: Return substring given regex - string-regex" "[.TODO]" ) {}
CASE( "substring_re: Return substring given regex - string-char*" "[.TODO]" ) {}

// strip_left()

CASE( "strip_left: Remove characters in set from left of string [\" \\t\\n\"] - C-string" )
{
    EXPECT( strip_left(" \t\nabc", " \t\n") == std::string("abc") );
    EXPECT( strip_left(" #$%&abc", " #$%&") == std::string("abc") );
}

CASE( "strip_left: Remove characters in set from left of string [\" \\t\\n\"] - string" )
{
    EXPECT( strip_left(std::string(" \t\nabc"), " \t\n") == std::string("abc") );
    EXPECT( strip_left(std::string(" #$%&abc"), " #$%&") == std::string("abc") );
}

CASE( "strip_left: Remove characters in set from left of string [\" \\t\\n\"] - other" )
{
    EXPECT( strip_left(stringy(" \t\nabc"), " \t\n") == std::string("abc") );
    EXPECT( strip_left(stringy(" #$%&abc"), " #$%&") == std::string("abc") );

    // string_view not supported:

    // char s1[] = " \t\nabc";
    // char s2[] = " #$%&abc";

    // EXPECT( strip_left(std20::string_view(std::begin(s1), std::end(s1)), " \t\n") == std::string("abc") );
    // EXPECT( strip_left(std20::string_view(std::begin(s2), std::end(s2)), " #$%&") == std::string("abc") );
}

CASE( "strip_left: Remove characters in regex from left of string - string-regex" "[.TODO]" ) {}
CASE( "strip_left_re: Remove characters in regex from left of string - string-char*" "[.TODO]" ) {}

// strip_right()

CASE( "strip_right: Remove characters in set from right of string [\" \\t\\n\"] - string" )
{
    EXPECT( strip_right(std::string("abc \t\n"), " \t\n") == std::string("abc") );
    EXPECT( strip_right(std::string("abc #$%&"), " #$%&") == std::string("abc") );
}

CASE( "strip_right: Remove characters in set from right of string [\" \\t\\n\"] - other" )
{
    EXPECT( strip_right(stringy("abc \t\n"), " \t\n") == std::string("abc") );
    EXPECT( strip_right(stringy("abc #$%&"), " #$%&") == std::string("abc") );

    // string_view not supported:

    // char s1[] = "abc \t\n";
    // char s2[] = "abc #$%&";

    // EXPECT( strip_right(std20::string_view(begin(s1), end(s1)), " \t\n") == std::string("abc") );
    // EXPECT( strip_right(std20::string_view(begin(s2), end(s2)), " #$%&") == std::string("abc") );
}

CASE( "strip_right: Remove characters in regex from right of string - string-regex" "[.TODO]" ) {}
CASE( "strip_right_re: Remove characters in regex from right of string - string-char*" "[.TODO]" ) {}

// strip()

CASE( "strip: Remove characters in set from left and right of string [\" \\t\\n\"] - string" )
{
    EXPECT( strip(std::string(" \t\nabc \t\n"), " \t\n") == std::string("abc") );
    EXPECT( strip(std::string(" #$%&abc #$%&"), " #$%&") == std::string("abc") );
}

CASE( "strip: Remove characters in set from left and right of string [\" \\t\\n\"] - other" )
{
    EXPECT( strip(stringy(" \t\nabc \t\n"), " \t\n") == std::string("abc") );
    EXPECT( strip(stringy(" #$%&abc #$%&"), " #$%&") == std::string("abc") );

    // string_view not supported:

    // char s1[] = " \t\nabc";
    // char s2[] = " #$%&abc";

    // EXPECT( strip(std20::string_view(begin(s1), end(s1))) == std::string("abc") );
    // EXPECT( strip(std20::string_view(begin(s2), end(s2)), " #$%&") == std::string("abc") );
}

CASE( "strip: Remove characters in regex from left and right of string - string-regex" "[.TODO]" ) {}
CASE( "strip_re: Remove characters in regex from left and right of string - string-char*" "[.TODO]" ) {}

// TODO Add tests for (internal) string_view:

CASE( "string_view: ..." "[.TODO]" )
{
}

#if 1

// replace_all():

CASE( "replace_all: Return string with all occurrences of sub string changed - char*-char*" "[.TODO]" )
{
    EXPECT( replace_all( "abc123mno123xyz", "123", "789") == std::string("abc789mno789xyz") );
}

CASE( "replace_all: Return string with all occurrences of sub string changed - string-string" "[.TODO]" )
{
    EXPECT( replace_all( std::string("abc123mno123xyz"), std::string("123"), std::string("789") ) == std::string("abc789mno789xyz") );
}

CASE( "replace_all: Return string with all occurrences of sub string changed - string-string_view" "[.TODO]" )
{
    EXPECT( replace_all( std::string("abc123mno123xyz"), "123", "789") == std::string("abc789mno789xyz") );
}

CASE( "replace_all: Return string with all occurrences of regex changed - string-regex" "[.TODO]" ) {}
CASE( "replace_all_re: Return string with all occurrences of regex changed - string-char*" "[.TODO]" ) {}

// replace_first():

CASE( "replace_first: Return string with first occurrence of sub string changed - char*-char*" "[.TODO]" )
{
    EXPECT( replace_first( "abc123mno123xyz", "123", "789") == std::string("abc789mno123xyz") );
}

CASE( "replace_first: Return string with first occurrence of sub string changed - string-string" "[.TODO]" )
{
    EXPECT( replace_first( std::string("abc123mno123xyz"), std::string("123"), std::string("789") ) == std::string("abc789mno123xyz") );
}

CASE( "replace_first: Return string with first occurrence of sub string changed - string-string_view" "[.TODO]" )
{
    EXPECT( replace_first( std::string("abc123mno123xyz"), "123", "789") == std::string("abc789mno123xyz") );
}

CASE( "replace_first: Return string with first occurrence of sub string changed - string_view-string_view" "[.TODO]" )
{
    // TODO : implement detail::replace_first(it...)
    // EXPECT( replace_first( string_view("abc123mno123xyz"), "123", "789") == std::string("abc789mno789xyz") );
}

CASE( "replace_first: Return string with first occurrence of regex changed - string-regex" "[.TODO]" ) {}
CASE( "replace_first_re: Return string with first occurrence of regex changed - string-char*" "[.TODO]" ) {}

// replace_last():

CASE( "replace_last: Return string with last occurrence of sub string changed - char*-char*" "[.TODO]" )
{
    EXPECT( replace_last( "abc123mno123xyz", "123", "789") == std::string("abc123mno789xyz") );
}

CASE( "replace_last: Return string with last occurrence of sub string changed - string-string" "[.TODO]" )
{
    EXPECT( replace_last( std::string("abc123mno123xyz"), std::string("123"), std::string("789") ) == std::string("abc123mno789xyz") );
}

CASE( "replace_last: Return string with last occurrence of sub string changed - string-string_view" "[.TODO]" )
{
    EXPECT( replace_last( std::string("abc123mno123xyz"), "123", "789") == std::string("abc123mno789xyz") );
}

CASE( "replace_last: Return string with last occurrence of sub string changed - string_view-string_view" "[.TODO]" )
{
// TODO : implement detail::replace_last(it...)
    // EXPECT( replace_last( string_view("abc123mno123xyz"), "123", "789") == std::string("abc789mno789xyz") );
}

CASE( "replace_last: Return string with last occurrence of regex changed - string-regex" "[.TODO]" ) {}
CASE( "replace_last_re: Return string with last occurrence of regex changed - string-char*" "[.TODO]" ) {}

#endif

//
// Join, split:
//

std::vector<std::string>
make_vec_of_strings( char const * p="abc", char const * q="def", char const * r="ghi")
{
    std::vector<std::string> result;
    result.push_back(p);
    result.push_back(q);
    result.push_back(r);
    return result;
}

// join():

CASE( "join: Join strings from collection into a string separated by given separator" )
{
    std::vector<std::string> coll = make_vec_of_strings();

    EXPECT( join( coll, "-") == "abc-def-ghi" );
}

// split():
//
// - literal_delimiter - a single string delimiter
// - any_of_delimiter - any of given characters as delimiter
// - fixed_delimiter - fixed length delimiter
// - limit_delimiter - not implemented
// - regex_delimiter - regular expression delimiter
// - char_delimiter - single-char delimiter
// - above as empty limiters

CASE( "split: Split string into vector of string_view given delimiter - literal_delimiter" )
{
    std::vector<std::string> golden( make_vec_of_strings() );

    std::cout << golden << "\n";

    // EXPECT( split("abc..def..ghi", "..") == golden );
    // EXPECT( split("abc..def..ghi", literal_delimiter("..")) == golden );
}

#if 0

CASE( "split: Split string into vector of string_view given delimiter - literal_delimiter" )
{
    std::vector<std::string> golden( make_vec_of_strings("", "abc", "def") );

    EXPECT( split("-abc-def", "-") == golden );
}

CASE( "split: Split string into vector of string_view given delimiter - literal_delimiter" )
{
    std::vector<std::string> golden( make_vec_of_strings("abc", "", "def") );

    EXPECT( split("abc--def", "-") == golden );
}

CASE( "split: Split string into vector of string_view given delimiter - literal_delimiter" )
{
    std::vector<std::string> golden( make_vec_of_strings("abc", "def", "") );

    EXPECT( split("abc-def-", "-") == golden );
}

// TODO split case

CASE( "split: Split string into vector of string_view given delimiter - literal_delimiter" )
{
    std::vector<std::string> golden( make_vec_of_strings("", "abc", "") );

    EXPECT( split("-abc-", "-") == golden );
}

CASE( "split: Split string into vector of string_view given delimiter - any_of_delimiter" )
{
    std::vector<std::string> golden( make_vec_of_strings() );

    EXPECT( split("abc+def-ghi", any_of_delimiter("+-")) == golden );
}

CASE( "split: Split string into vector of string_view given delimiter - fixed_delimiter" )
{
    std::vector<std::string> golden( make_vec_of_strings() );

    EXPECT( split("abcdefghi", fixed_delimiter(3)) == golden );
}

CASE( "split: Split string into vector of string_view given delimiter - limit_delimiter" "[.TODO]" )
{
    std::vector<std::string> golden( make_vec_of_strings() );
}

CASE( "split: Split string into vector of string_view given delimiter - regex_delimiter" )
{
#if string_CONFIG_PROVIDE_REGEX
#if string_HAVE_REGEX
    std::vector<std::string> golden( make_vec_of_strings() );

    EXPECT( split("abc+-def-+ghi", regex_delimiter("[+-]+")) == golden );
#else
    EXPECT( !!"split is not available (no regex, string_HAVE_REGEX)." );
#endif
#else
    EXPECT( !!"regex_delimiter is not available (not configured, string_CONFIG_PROVIDE_REGEX)." );
#endif
}

CASE( "split: Split string into vector of string_view given delimiter - char_delimiter" )
{
    std::vector<std::string> golden( make_vec_of_strings("&", "&", "&") );

    EXPECT( split("abc&def&ghi&jkl", char_delimiter('&')) == golden );
}

CASE( "split: Split string into single characters given empty delimiter" )
{
    std::vector<std::string> golden( make_vec_of_strings("a", "b", "c") );

    EXPECT( split("abc", "") == golden );
    EXPECT( split("abc", literal_delimiter("")) == golden );
    EXPECT( split("abc", any_of_delimiter("")) == golden );
    EXPECT( split("abc", fixed_delimiter(1)) == golden );

#if string_HAVE_REGEX
    EXPECT( split("abc", regex_delimiter("")) == golden );
#endif
    // Not eligible:
    // EXPECT( split("abc", limit_delimiter("")) == golden );
    // EXPECT( split("abc", char_delimiter('x')) == golden );
}

#endif // Test Activation

// TODO: split_2

CASE( "split_2: Split string into two-element tuple given delimiter - forward - xxx_delimiter" )
{
    std20::string_view a, b;
    std::tie(a, b) = split_2("abc;def;ghi", ";");

    std::cout << "[a:" << a << "][b:" << b << "]\n";

    // EXPECT( split_2("abc;def;ghi", ";") == (std::tuple<std::string, std::string>("abc", "def;ghi")) );
    // EXPECT( std::get<1>(split_2("abc;def;ghi", ";")) == std::string("def;ghi" ));
}

// TODO: rsplit_2

CASE( "rsplit_2: Split string into two-element tuple given delimiter - reverse - xxx_delimiter" )
{
    std20::string_view a, b;
    std::tie(a, b) = rsplit_2("abc;def;ghi", ";");

    std::cout << "[a:" << a << "][b:" << b << "]\n";

    // EXPECT( split_2("abc;def;ghi", ";") == (std::tuple<std::string, std::string>("abc", "def;ghi")) );
    // EXPECT( std::get<1>(split_2("abc;def;ghi", ";")) == std::string("def;ghi" ));
}

CASE( "tweak header: Reads tweak header if supported " "[tweak]" )
{
#if string_HAVE_TWEAK_HEADER
    EXPECT( string_TWEAK_VALUE == 42 );
#else
    EXPECT( !!"Tweak header is not available (string_HAVE_TWEAK_HEADER: 0)." );
#endif
}

} // anonymous namespace
