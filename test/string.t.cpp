// Copyright 2025-2025 Martin Moene
//
// https://github.com/martinmoene/string-lite
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "string-main.t.hpp"

#ifdef _WIN32
# define string_strdup  _strdup
#else
# include <string.h>  // strdup()
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

    using ::nonstd::string::std17::string_view;
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

// TODO Add tests for (internal) string_view:

CASE( "string_view: ..." "[.TODO]" )
{
}

// Observers:

// length():

CASE( "length: length of given string" )
{
    EXPECT( length("abc") == 3 );
    EXPECT( length(std::string("abc")) == 3 );
    EXPECT( length(std17::string_view("abc")) == 3 );
}

// size():

CASE( "size: length of given string" )
{
    EXPECT( size("abc") == 3 );
    EXPECT( size(std::string("abc")) == 3 );
    EXPECT( size(std17::string_view("abc")) == 3 );
}

// is_empty():

CASE( "is_empty: true if string is empty" )
{
    EXPECT(     is_empty("") );
    EXPECT_NOT( is_empty("a") );

    EXPECT(     is_empty(std::string()) );
    EXPECT_NOT( is_empty(std::string("x")) );

    EXPECT(     is_empty(std17::string_view()) );
    EXPECT_NOT( is_empty(std17::string_view("x")) );
}

// contains():

CASE( "contains: true if string contains substring" )
{
    // contains char:

    EXPECT(     contains("abc123mno123xyz", '1') );
    EXPECT_NOT( contains("abc123mno123xyz", '7') );

    EXPECT(     contains(std::string("abc123mno123xyz"), '1') );
    EXPECT_NOT( contains(std::string("abc123mno123xyz"), '7') );

    EXPECT(     contains(std17::string_view("abc123mno123xyz"), '1') );
    EXPECT_NOT( contains(std17::string_view("abc123mno123xyz"), '7') );

    // contains string:

    EXPECT(     contains("abc123mno123xyz", "123") );
    EXPECT_NOT( contains("abc123mno123xyz", "789") );

    EXPECT(     contains(std::string("abc123mno123xyz"), std::string("123")) );
    EXPECT_NOT( contains(std::string("abc123mno123xyz"), std::string("789")) );

    EXPECT(     contains(std17::string_view("abc123mno123xyz"), std17::string_view("123")) );
    EXPECT_NOT( contains(std17::string_view("abc123mno123xyz"), std17::string_view("789")) );
}

// contains_all_of()

CASE( "contains_all_of: true if string contains all characters of set" )
{
    EXPECT(     contains_all_of("abc123mno123xyz", "321cba") );
    EXPECT_NOT( contains_all_of("abc123mno123xyz", "321cbas7") );

    EXPECT(     contains_all_of(std::string("abc123mno123xyz"), std::string("321cba")) );
    EXPECT_NOT( contains_all_of(std::string("abc123mno123xyz"), std::string("321cbas7")) );

    EXPECT(     contains_all_of(std17::string_view("abc123mno123xyz"), std17::string_view("321cba")) );
    EXPECT_NOT( contains_all_of(std17::string_view("abc123mno123xyz"), std17::string_view("321cbas7")) );
}

// contains_any_of()

CASE( "contains_any_of: true if string contains any character of set" )
{
    EXPECT(     contains_any_of("abc123mno123xyz", "a1s7") );
    EXPECT_NOT( contains_any_of("abc123mno123xyz", "s7") );

    EXPECT(     contains_any_of(std::string("abc123mno123xyz"), std::string("a1s7")) );
    EXPECT_NOT( contains_any_of(std::string("abc123mno123xyz"), std::string("s7")) );

    EXPECT(     contains_any_of(std17::string_view("abc123mno123xyz"), std17::string_view("a1s7")) );
    EXPECT_NOT( contains_any_of(std17::string_view("abc123mno123xyz"), std17::string_view("s7")) );
}

// contains_none_of()

CASE( "contains_none_of: true if string contains no character of set" )
{
    EXPECT(     contains_none_of("abc123mno123xyz", "s7") );
    EXPECT_NOT( contains_none_of("abc123mno123xyz", "a1s7") );

    EXPECT(     contains_none_of(std::string("abc123mno123xyz"), std::string("s7")) );
    EXPECT_NOT( contains_none_of(std::string("abc123mno123xyz"), std::string("a1s7")) );

    EXPECT(     contains_none_of(std17::string_view("abc123mno123xyz"), std17::string_view("s7")) );
    EXPECT_NOT( contains_none_of(std17::string_view("abc123mno123xyz"), std17::string_view("a1s7")) );
}

// starts_with():

CASE( "starts_with: true if string starts with substring" )
{
    // starts with char:

    EXPECT(     starts_with("abc123mno123xyz", 'a') );
    EXPECT_NOT( starts_with("abc123mno123xyz", 'b') );

    EXPECT(     starts_with(std::string("abc123mno123xyz"), 'a') );
    EXPECT_NOT( starts_with(std::string("abc123mno123xyz"), 'b') );

    EXPECT(     starts_with(std17::string_view("abc123mno123xyz"), 'a') );
    EXPECT_NOT( starts_with(std17::string_view("abc123mno123xyz"), 'b') );

    // starts with string:

    EXPECT(     starts_with("abc123mno123xyz", "a") );
    EXPECT_NOT( starts_with("abc123mno123xyz", "b") );

    EXPECT(     starts_with(std::string("abc123mno123xyz"), std::string("a")) );
    EXPECT_NOT( starts_with(std::string("abc123mno123xyz"), std::string("b")) );

    EXPECT(     starts_with(std17::string_view("abc123mno123xyz"), std17::string_view("a")) );
    EXPECT_NOT( starts_with(std17::string_view("abc123mno123xyz"), std17::string_view("b")) );
}

// starts_with_all_of()

CASE( "starts_with_all_of: true if string starts with all characters of set" )
{
    EXPECT(     starts_with_all_of("abc123mno123xyz", "321cba") );
    EXPECT_NOT( starts_with_all_of("abc123mno123xyz", "321cbz") );

    EXPECT(     starts_with_all_of(std::string("abc123mno123xyz"), std::string("321cba")) );
    EXPECT_NOT( starts_with_all_of(std::string("abc123mno123xyz"), std::string("321cbz")) );

    EXPECT(     starts_with_all_of(std17::string_view("abc123mno123xyz"), std17::string_view("321cba")) );
    EXPECT_NOT( starts_with_all_of(std17::string_view("abc123mno123xyz"), std17::string_view("321cbz")) );
}

// starts_with_any_of()

CASE( "starts_with_any_of: true if string starts with any character of set" )
{
    EXPECT(     starts_with_any_of("abc123mno123xyz", "321cba") );
    EXPECT_NOT( starts_with_any_of("abc123mno123xyz", "789xyz") );

    EXPECT(     starts_with_any_of(std::string("abc123mno123xyz"), std::string("321cba")) );
    EXPECT_NOT( starts_with_any_of(std::string("abc123mno123xyz"), std::string("789xyz")) );

    EXPECT(     starts_with_any_of(std17::string_view("abc123mno123xyz"), std17::string_view("321cba")) );
    EXPECT_NOT( starts_with_any_of(std17::string_view("abc123mno123xyz"), std17::string_view("789xyz")) );
}

// starts_with_none_of()

CASE( "starts_with_none_of: true if string starts with no character of set" )
{
    EXPECT(     starts_with_none_of("abc123mno123xyz", "789xyz") );
    EXPECT_NOT( starts_with_none_of("abc123mno123xyz", "321cba") );

    EXPECT(     starts_with_none_of(std::string("abc123mno123xyz"), std::string("789xyz")) );
    EXPECT_NOT( starts_with_none_of(std::string("abc123mno123xyz"), std::string("321cba")) );

    EXPECT(     starts_with_none_of(std17::string_view("abc123mno123xyz"), std17::string_view("789xyz")) );
    EXPECT_NOT( starts_with_none_of(std17::string_view("abc123mno123xyz"), std17::string_view("321cba")) );
}

// ends_with():

CASE( "ends_with: true if string ends with substring" )
{
    // ends_with char:

    EXPECT(     ends_with("abc123mno123xyz", 'z') );
    EXPECT_NOT( ends_with("abc123mno123xyz", 'y') );

    EXPECT(     ends_with(std::string("abc123mno123xyz"), 'z') );
    EXPECT_NOT( ends_with(std::string("abc123mno123xyz"), 'y') );

    EXPECT(     ends_with(std17::string_view("abc123mno123xyz"), 'z') );
    EXPECT_NOT( ends_with(std17::string_view("abc123mno123xyz"), 'y') );

    // ends_with string:

    EXPECT(     ends_with("abc123mno123xyz", "z") );
    EXPECT_NOT( ends_with("abc123mno123xyz", "y") );

    EXPECT(     ends_with(std::string("abc123mno123xyz"), std::string("z")) );
    EXPECT_NOT( ends_with(std::string("abc123mno123xyz"), std::string("y")) );

    EXPECT(     ends_with(std17::string_view("abc123mno123xyz"), std17::string_view("z")) );
    EXPECT_NOT( ends_with(std17::string_view("abc123mno123xyz"), std17::string_view("y")) );
}

// ends_with_all_of()

CASE( "ends_with_all_of: true if string ends with all characters of set" )
{
    EXPECT(     ends_with_all_of("abc123mno123xyz", "321zyx") );
    EXPECT_NOT( ends_with_all_of("abc123mno123xyz", "321zya") );

    EXPECT(     ends_with_all_of(std::string("abc123mno123xyz"), std::string("321zyx")) );
    EXPECT_NOT( ends_with_all_of(std::string("abc123mno123xyz"), std::string("321zya")) );

    EXPECT(     ends_with_all_of(std17::string_view("abc123mno123xyz"), std17::string_view("321zyx")) );
    EXPECT_NOT( ends_with_all_of(std17::string_view("abc123mno123xyz"), std17::string_view("321zya")) );
}

// ends_with_any_of()

CASE( "ends_with_any_of: true if string ends with any character of set" )
{
    EXPECT(     ends_with_any_of("abc123mno123xyz", "321zyx") );
    EXPECT_NOT( ends_with_any_of("abc123mno123xyz", "789cba") );

    EXPECT(     ends_with_any_of(std::string("abc123mno123xyz"), std::string("321zyx")) );
    EXPECT_NOT( ends_with_any_of(std::string("abc123mno123xyz"), std::string("789cba")) );

    EXPECT(     ends_with_any_of(std17::string_view("abc123mno123xyz"), std17::string_view("321zyx")) );
    EXPECT_NOT( ends_with_any_of(std17::string_view("abc123mno123xyz"), std17::string_view("789cba")) );
}

// ends_with_none_of()

CASE( "ends_with_none_of: true if string ends with no character of set" )
{
    EXPECT(     ends_with_none_of("abc123mno123xyz", "321cba") );
    EXPECT_NOT( ends_with_none_of("abc123mno123xyz", "321cbz") );

    EXPECT(     ends_with_none_of(std::string("abc123mno123xyz"), std::string("321cba")) );
    EXPECT_NOT( ends_with_none_of(std::string("abc123mno123xyz"), std::string("321cbz")) );

    EXPECT(     ends_with_none_of(std17::string_view("abc123mno123xyz"), std17::string_view("321cba")) );
    EXPECT_NOT( ends_with_none_of(std17::string_view("abc123mno123xyz"), std17::string_view("321cbz")) );
}

// find_first():

CASE( "find_first: position of first substring in string" )
{
    // find_first char:

    EXPECT(       3 == find_first("abc123mno123xyz", '1') );
    EXPECT( sv_npos == find_first("abc123mno123xyz", '7') );

    EXPECT(       3 == find_first(std::string("abc123mno123xyz"), '1') );
    EXPECT( sv_npos == find_first(std::string("abc123mno123xyz"), '7') );

    EXPECT(       3 == find_first(std17::string_view("abc123mno123xyz"), '1') );
    EXPECT( sv_npos == find_first(std17::string_view("abc123mno123xyz"), '7') );

    // find_first string:

    EXPECT(       3 == find_first("abc123mno123xyz", "123") );
    EXPECT( sv_npos == find_first("abc123mno123xyz", "789") );

    EXPECT(       3 == find_first(std::string("abc123mno123xyz"), std::string("123")) );
    EXPECT( sv_npos == find_first(std::string("abc123mno123xyz"), std::string("789")) );

    EXPECT(       3 == find_first(std17::string_view("abc123mno123xyz"), std17::string_view("123")) );
    EXPECT( sv_npos == find_first(std17::string_view("abc123mno123xyz"), std17::string_view("789")) );
}

// find_last():

CASE( "find_last: position of last substring in string" )
{
    // find_last char:

    EXPECT(       9 == find_last("abc123mno123xyz", '1') );
    EXPECT( sv_npos == find_last("abc123mno123xyz", '7') );

    EXPECT(       9 == find_last(std::string("abc123mno123xyz"), '1') );
    EXPECT( sv_npos == find_last(std::string("abc123mno123xyz"), '7') );

    EXPECT(       9 == find_last(std17::string_view("abc123mno123xyz"), '1') );
    EXPECT( sv_npos == find_last(std17::string_view("abc123mno123xyz"), '7') );

    // find_last string:

    EXPECT(       9 == find_last("abc123mno123xyz", "123") );
    EXPECT( sv_npos == find_last("abc123mno123xyz", "789") );

    EXPECT(       9 == find_last(std::string("abc123mno123xyz"), std::string("123")) );
    EXPECT( sv_npos == find_last(std::string("abc123mno123xyz"), std::string("789")) );

    EXPECT(       9 == find_last(std17::string_view("abc123mno123xyz"), std17::string_view("123")) );
    EXPECT( sv_npos == find_last(std17::string_view("abc123mno123xyz"), std17::string_view("789")) );
}

// find_first_of()

CASE( "find_first_of: position of first character in string in set" )
{
    EXPECT(       3 == find_first_of("abc123mno123xyz", "321") );
    EXPECT( sv_npos == find_first_of("abc123mno123xyz", "789") );

    EXPECT(       3 == find_first_of(std::string("abc123mno123xyz"), std::string("321") ) );
    EXPECT( sv_npos == find_first_of(std::string("abc123mno123xyz"), std::string("789") ) );

    EXPECT(       3 == find_first_of(std17::string_view("abc123mno123xyz"), std17::string_view("321") ) );
    EXPECT( sv_npos == find_first_of(std17::string_view("abc123mno123xyz"), std17::string_view("789") ) );
}

// find_last_of()

CASE( "find_last_of: position of last character in string in set" )
{
    EXPECT(      11 == find_last_of("abc123mno123xyz", "123") );
    EXPECT( sv_npos == find_last_of("abc123mno123xyz", "789") );

    EXPECT(      11 == find_last_of(std::string("abc123mno123xyz"), std::string("123") ) );
    EXPECT( sv_npos == find_last_of(std::string("abc123mno123xyz"), std::string("789") ) );

    EXPECT(      11 == find_last_of(std17::string_view("abc123mno123xyz"), std17::string_view("123") ) );
    EXPECT( sv_npos == find_last_of(std17::string_view("abc123mno123xyz"), std17::string_view("789") ) );
}

// find_first_not_of()

CASE( "find_first_not_of: position of first character in string not in set" )
{
    EXPECT(       3 == find_first_not_of("abc123mno123xyz", "cba") );
    EXPECT( sv_npos == find_first_not_of("abc123mno123xyz", "abc123mno123xyz") );

    EXPECT(       3 == find_first_not_of(std::string("abc123mno123xyz"), std::string("cba") ) );
    EXPECT( sv_npos == find_first_not_of(std::string("abc123mno123xyz"), std::string("abc123mno123xyz") ) );

    EXPECT(       3 == find_first_not_of(std17::string_view("abc123mno123xyz"), std17::string_view("cba") ) );
    EXPECT( sv_npos == find_first_not_of(std17::string_view("abc123mno123xyz"), std17::string_view("abc123mno123xyz") ) );
}

// find_last_not_of()

CASE( "find_last_not_of: position of last character in string not in set" )
{
    EXPECT(      11 == find_last_not_of("abc123mno123xyz", "zyx") );
    EXPECT( sv_npos == find_last_not_of("abc123mno123xyz", "abc123mno123xyz") );

    EXPECT(      11 == find_last_not_of(std::string("abc123mno123xyz"), std::string("zyx") ) );
    EXPECT( sv_npos == find_last_not_of(std::string("abc123mno123xyz"), std::string("abc123mno123xyz") ) );

    EXPECT(      11 == find_last_not_of(std17::string_view("abc123mno123xyz"), std17::string_view("zyx") ) );
    EXPECT( sv_npos == find_last_not_of(std17::string_view("abc123mno123xyz"), std17::string_view("abc123mno123xyz") ) );
}

// Modifiers:

// capitalize():

CASE( "capitalize: string transformed to start with capital" )
{
    EXPECT( capitalize("hello, world!") == "Hello, world!" );
    EXPECT( capitalize("Hello, world!") == "Hello, world!" );

    EXPECT( capitalize(std::string("hello, world!")) == "Hello, world!" );
    EXPECT( capitalize(std::string("Hello, world!")) == "Hello, world!" );

    EXPECT( capitalize(std17::string_view("hello, world!")) == "Hello, world!" );
    EXPECT( capitalize(std17::string_view("Hello, world!")) == "Hello, world!" );
}

// to_lowercase(), to_uppercase():

CASE( "to_lowercase: char transformed to lowercase" )
{
    EXPECT( to_lowercase('a') == 'a' );
    EXPECT( to_lowercase('A') == 'a' );
}

CASE( "to_lowercase: string transformed to lowercase" )
{
    EXPECT( to_lowercase(ustr()) == lstr() );
    EXPECT( to_lowercase(std::string(ustr())) == lstr() );
    EXPECT( to_lowercase(std17::string_view(ustr())) == lstr() );
}

CASE( "to_uppercase: char transformed to uppercase" )
{
    EXPECT( to_uppercase('a') == 'A' );
    EXPECT( to_uppercase('A') == 'A' );
}

CASE( "to_uppercase: string transformed to uppercase" )
{
    EXPECT( to_uppercase(lstr()) == ustr() );
    EXPECT( to_uppercase(std::string(lstr())) == ustr() );
    EXPECT( to_uppercase(std17::string_view(lstr())) == ustr() );
}

// append():

CASE( "append: string with second string concatenated to first string" )
{
    EXPECT( append("abc", "xyz") == "abcxyz" );
    EXPECT( append(std::string("abc"), std::string("xyz")) == "abcxyz" );
    EXPECT( append(std17::string_view("abc"), std17::string_view("xyz")) == "abcxyz" );
}

// substring()

CASE( "substring: substring starting at given position of given length, default up to end" )
{
    EXPECT( substring("abcxyz", 2, 3) == "cxy" );
    EXPECT( substring("abcxyz", 2   ) == "cxyz" );
    EXPECT( substring("abcxyz"      ) == "abcxyz" );

    EXPECT( substring(std::string("abcxyz"), 2, 3) == "cxy" );
    EXPECT( substring(std::string("abcxyz"), 2   ) == "cxyz" );
    EXPECT( substring(std::string("abcxyz")      ) == "abcxyz" );

    EXPECT( substring(std17::string_view("abcxyz"), 2, 3) == "cxy" );
    EXPECT( substring(std17::string_view("abcxyz"), 2   ) == "cxyz" );
    EXPECT( substring(std17::string_view("abcxyz")      ) == "abcxyz" );
}

// erase():

CASE( "erase: string with substring at given position of given length removed - default up to end" )
{
    EXPECT( erase("abcxyz", 3, 2) == "abcz" );
    EXPECT( erase("abcxyz", 3   ) == "abc"  );

    EXPECT( erase(std::string("abcxyz"), 3, 2) == "abcz" );
    EXPECT( erase(std::string("abcxyz"), 3   ) == "abc"  );

    EXPECT( erase(std17::string_view("abcxyz"), 3, 2) == "abcz" );
    EXPECT( erase(std17::string_view("abcxyz"), 3   ) == "abc"  );
}

// erase_all():

CASE( "erase_all: string with all occurrences of substring removed" )
{
    EXPECT( erase_all("abcxyzabcxyzabc", "xyz") == "abcabcabc" );
    EXPECT( erase_all(std::string("abcxyzabcxyzabc"), std::string("xyz")) == "abcabcabc" );
    EXPECT( erase_all(std17::string_view("abcxyzabcxyzabc"), std17::string_view("xyz")) == "abcabcabc" );

    EXPECT( erase_all("abcxyzabcxyzabc", "123") == "abcxyzabcxyzabc" );
}

// erase_first():

CASE( "erase_first: string with first occurrence of substring removed" )
{
    EXPECT( erase_first("abcxyzabcxyzabc", "xyz") == "abcabcxyzabc" );
    EXPECT( erase_first(std::string("abcxyzabcxyzabc"), std::string("xyz")) == "abcabcxyzabc" );
    EXPECT( erase_first(std17::string_view("abcxyzabcxyzabc"), std17::string_view("xyz")) == "abcabcxyzabc" );

    EXPECT( erase_first("abcxyzabcxyzabc", "123") == "abcxyzabcxyzabc" );
}

// erase_last():

CASE( "erase_last: string with last occurrence of substring removed" )
{
    EXPECT( erase_last("abcxyzabcxyzabc", "xyz") == "abcxyzabcabc" );
    EXPECT( erase_last(std::string("abcxyzabcxyzabc"), std::string("xyz")) == "abcxyzabcabc" );
    EXPECT( erase_last(std17::string_view("abcxyzabcxyzabc"), std17::string_view("xyz")) == "abcxyzabcabc" );

    EXPECT( erase_last("abcxyzabcxyzabc", "123") == "abcxyzabcxyzabc" );
}

// insert():

CASE( "insert: string with substring inserted at given position" )
{
    EXPECT( insert( "abc123mno123xyz", 3, "789") == "abc789123mno123xyz" );
    EXPECT( insert( std::string("abc123mno123xyz"), 3, std::string("789")) == "abc789123mno123xyz" );
    EXPECT( insert( std17::string_view("abc123mno123xyz"), 3, std17::string_view("789")) == "abc789123mno123xyz" );
}

// replace():

CASE( "replace: string with substring given by position and length replaced" )
{
    EXPECT( replace( "abc123mno123xyz", 3, 6, "789") == "abc789123xyz" );
    EXPECT( replace( std::string("abc123mno123xyz"), 3, 6, std::string("789")) == "abc789123xyz" );
    EXPECT( replace( std17::string_view("abc123mno123xyz"), 3, 6, std17::string_view("789")) == "abc789123xyz" );
}

// replace_all():

CASE( "replace_all: string with all occurrences of substring replaced" )
{
    EXPECT( replace_all( "abc123mno123xyz", "123", "789") == "abc789mno789xyz" );
    EXPECT( replace_all( std::string("abc123mno123xyz"), std::string("123"), std::string("789") ) == "abc789mno789xyz" );
    EXPECT( replace_all( std17::string_view("abc123mno123xyz"), std17::string_view("123"), std17::string_view("789")) == "abc789mno789xyz" );
}

// replace_first():

CASE( "replace_first: string with first occurrence of substring replaced" )
{
    EXPECT( replace_first( "abc123mno123xyz", "123", "789") == "abc789mno123xyz" );
    EXPECT( replace_first( std::string("abc123mno123xyz"), std::string("123"), std::string("789") ) == "abc789mno123xyz" );
    EXPECT( replace_first( std17::string_view("abc123mno123xyz"), std17::string_view("123"), std17::string_view("789")) == "abc789mno123xyz" );
}

// replace_last():

CASE( "replace_last: string with last occurrence of substring replaced" )
{
    EXPECT( replace_last( "abc123mno123xyz", "123", "789") == "abc123mno789xyz" );
    EXPECT( replace_last( std::string("abc123mno123xyz"), std::string("123"), std::string("789") ) == "abc123mno789xyz" );
    EXPECT( replace_last( std17::string_view("abc123mno123xyz"), std17::string_view("123"), std17::string_view("789")) == "abc123mno789xyz" );
}

// strip_left()

CASE( "strip_left: string with characters in set removed from left of string [\" \\t\\n\"]" )
{
    EXPECT( strip_left(" \t\nabc"         ) == "abc" );
    EXPECT( strip_left(" \t\nabc", " \t\n") == "abc" );
    EXPECT( strip_left(" #$%&abc", " #$%&") == "abc" );

    EXPECT( strip_left(std::string(" \t\nabc")                      ) == "abc" );
    EXPECT( strip_left(std::string(" \t\nabc"), std::string(" \t\n")) == "abc" );
    EXPECT( strip_left(std::string(" #$%&abc"), std::string(" #$%&")) == "abc" );

    EXPECT( strip_left(std17::string_view(" \t\nabc")                             ) == "abc" );
    EXPECT( strip_left(std17::string_view(" \t\nabc"), std17::string_view(" \t\n")) == "abc" );
    EXPECT( strip_left(std17::string_view(" #$%&abc"), std17::string_view(" #$%&")) == "abc" );

    EXPECT( strip_left(stringy(" \t\nabc")         ) == "abc" );
    EXPECT( strip_left(stringy(" \t\nabc"), " \t\n") == "abc" );
    EXPECT( strip_left(stringy(" #$%&abc"), " #$%&") == "abc" );
}

// strip_right()

CASE( "strip_right: string with characters in set removed from right of string [\" \\t\\n\"]" )
{
    EXPECT( strip_right(std::string("abc \t\n")         ) == "abc" );
    EXPECT( strip_right(std::string("abc \t\n"), " \t\n") == "abc" );
    EXPECT( strip_right(std::string("abc #$%&"), " #$%&") == "abc" );

    EXPECT( strip_right(std::string("abc \t\n")                      ) == "abc" );
    EXPECT( strip_right(std::string("abc \t\n"), std::string(" \t\n")) == "abc" );
    EXPECT( strip_right(std::string("abc #$%&"), std::string(" #$%&")) == "abc" );

    EXPECT( strip_right(std17::string_view("abc \t\n")                             ) == "abc" );
    EXPECT( strip_right(std17::string_view("abc \t\n"), std17::string_view(" \t\n")) == "abc" );
    EXPECT( strip_right(std17::string_view("abc #$%&"), std17::string_view(" #$%&")) == "abc" );

    EXPECT( strip_right(stringy("abc \t\n")         ) == "abc" );
    EXPECT( strip_right(stringy("abc \t\n"), " \t\n") == "abc" );
    EXPECT( strip_right(stringy("abc #$%&"), " #$%&") == "abc" );
}

// strip()

CASE( "strip: string with characters in set removed from left and right of string [\" \\t\\n\"]" )
{
    EXPECT( strip(" \t\nabc \t\n"         ) == "abc" );
    EXPECT( strip(" \t\nabc \t\n", " \t\n") == "abc" );
    EXPECT( strip(" #$%&abc #$%&", " #$%&") == "abc" );

    EXPECT( strip(std::string(" \t\nabc \t\n")                      ) == "abc" );
    EXPECT( strip(std::string(" \t\nabc \t\n"), std::string(" \t\n")) == "abc" );
    EXPECT( strip(std::string(" #$%&abc #$%&"), std::string(" #$%&")) == "abc" );

    EXPECT( strip(std17::string_view(" \t\nabc \t\n")                             ) == "abc" );
    EXPECT( strip(std17::string_view(" \t\nabc \t\n"), std17::string_view(" \t\n")) == "abc" );
    EXPECT( strip(std17::string_view(" #$%&abc #$%&"), std17::string_view(" #$%&")) == "abc" );

    EXPECT( strip(stringy(" \t\nabc \t\n")         ) == "abc" );
    EXPECT( strip(stringy(" \t\nabc \t\n"), " \t\n") == "abc" );
    EXPECT( strip(stringy(" #$%&abc #$%&"), " #$%&") == "abc" );
}

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

CASE( "join: string with strings from collection joined separated by given separator" )
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

CASE( "split: split string into vector of string_view given delimiter - literal_delimiter" )
{
    std::vector<std::string> golden( make_vec_of_strings() );

    EXPECT( split("abc..def..ghi", "..") == golden );
    EXPECT( split("abc..def..ghi", literal_delimiter("..")) == golden );
}

#if 0

CASE( "split: split string into vector of string_view given delimiter - literal_delimiter" )
{
    std::vector<std::string> golden( make_vec_of_strings("", "abc", "def") );

    EXPECT( split("-abc-def", "-") == golden );
}

CASE( "split: split string into vector of string_view given delimiter - literal_delimiter" )
{
    std::vector<std::string> golden( make_vec_of_strings("abc", "", "def") );

    EXPECT( split("abc--def", "-") == golden );
}

CASE( "split: split string into vector of string_view given delimiter - literal_delimiter" )
{
    std::vector<std::string> golden( make_vec_of_strings("abc", "def", "") );

    EXPECT( split("abc-def-", "-") == golden );
}

// TODO split case

CASE( "split: split string into vector of string_view given delimiter - literal_delimiter" )
{
    std::vector<std::string> golden( make_vec_of_strings("", "abc", "") );

    EXPECT( split("-abc-", "-") == golden );
}

CASE( "split: split string into vector of string_view given delimiter - any_of_delimiter" )
{
    std::vector<std::string> golden( make_vec_of_strings() );

    EXPECT( split("abc+def-ghi", any_of_delimiter("+-")) == golden );
}

CASE( "split: split string into vector of string_view given delimiter - fixed_delimiter" )
{
    std::vector<std::string> golden( make_vec_of_strings() );

    EXPECT( split("abcdefghi", fixed_delimiter(3)) == golden );
}

CASE( "split: split string into vector of string_view given delimiter - limit_delimiter" "[.TODO]" )
{
    std::vector<std::string> golden( make_vec_of_strings() );
}

CASE( "split: split string into vector of string_view given delimiter - regex_delimiter" )
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

CASE( "split: split string into vector of string_view given delimiter - char_delimiter" )
{
    std::vector<std::string> golden( make_vec_of_strings("&", "&", "&") );

    EXPECT( split("abc&def&ghi&jkl", char_delimiter('&')) == golden );
}

CASE( "split: split string into single characters given empty delimiter" )
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

// split_left()

CASE( "split_left: split string into two-element tuple given set of delimiter characters - forward" )
{
    EXPECT( split_left("abc;:-"       , ";:-") == (std::tuple<std17::string_view, std17::string_view>("abc", "")) );
    EXPECT( split_left("abc;:-def;ghi", ";:-") == (std::tuple<std17::string_view, std17::string_view>("abc", "def;ghi" )) );
    EXPECT( split_left("abc;:-def;ghi", "/,.") == (std::tuple<std17::string_view, std17::string_view>("abc;:-def;ghi", "abc;:-def;ghi")) );

    EXPECT( split_left("abc;:-"       , ";:-", 2) == (std::tuple<std17::string_view, std17::string_view>("abc", "-")) );
    EXPECT( split_left("abc;:-"       , ";:-", 1) == (std::tuple<std17::string_view, std17::string_view>("abc", ":-")) );
    EXPECT( split_left("abc;:-"       , ";:-", 0) == (std::tuple<std17::string_view, std17::string_view>("abc", ";:-")) );

    EXPECT( split_left("abc123", "1234567890", 0) == (std::tuple<std17::string_view, std17::string_view>("abc", "123")) );
    EXPECT( split_left("123abc", "1234567890", 0) == (std::tuple<std17::string_view, std17::string_view>("", "123abc")) );

    EXPECT( split_left("class::member", ":") == (std::tuple<std17::string_view, std17::string_view>("class", "member")) );
}

// split_right()

CASE( "split_right: split string into two-element tuple given set of delimiter characters - reverse" )
{
    EXPECT( split_right(";:-abc"       , ";:-") == (std::tuple<std17::string_view, std17::string_view>("", "abc")) );
    EXPECT( split_right("abc;def;:-ghi", ";:-") == (std::tuple<std17::string_view, std17::string_view>("abc;def", "ghi" )) );
    EXPECT( split_right("abc;def;:-ghi", "/,.") == (std::tuple<std17::string_view, std17::string_view>("abc;def;:-ghi", "abc;def;:-ghi")) );

    EXPECT( split_right(";:-abc"       , ";:-", 2) == (std::tuple<std17::string_view, std17::string_view>(";", "abc")) );
    EXPECT( split_right(";:-abc"       , ";:-", 1) == (std::tuple<std17::string_view, std17::string_view>(";:", "abc")) );
    EXPECT( split_right(";:-abc"       , ";:-", 0) == (std::tuple<std17::string_view, std17::string_view>(";:-", "abc")) );

    EXPECT( split_right("123abc", "1234567890", 0) == (std::tuple<std17::string_view, std17::string_view>("123", "abc")) );
    EXPECT( split_right("abc123", "1234567890", 0) == (std::tuple<std17::string_view, std17::string_view>("abc123", "")) );

    EXPECT( split_right("class::member", ":") == (std::tuple<std17::string_view, std17::string_view>("class", "member")) );
}

// compare()

CASE( "compare: negative, zero or positive for lsh is less than, equal to or greater than rhs" )
{
    EXPECT( compare("abc", "abc") == 0 );
    EXPECT( compare("aaa", "abc") != 0 );
    EXPECT( compare("aaa", "abc") <  0 );
    EXPECT( compare("aaa", "abc") <= 0 );
    EXPECT( compare("abc", "abc") <= 0 );
    EXPECT( compare("abc", "aaa") >= 0 );
    EXPECT( compare("abc", "aaa") >  0 );

    EXPECT_NOT( compare("abc", "abcd") == 0 );
    EXPECT    ( compare("abc", "abcd") != 0 );

    EXPECT( compare(std::string("abc"), std::string("abc")) == 0 );
    EXPECT( compare(std::string("aaa"), std::string("abc")) != 0 );
    EXPECT( compare(std::string("aaa"), std::string("abc")) <  0 );
    EXPECT( compare(std::string("aaa"), std::string("abc")) <= 0 );
    EXPECT( compare(std::string("abc"), std::string("abc")) <= 0 );
    EXPECT( compare(std::string("abc"), std::string("aaa")) >= 0 );
    EXPECT( compare(std::string("abc"), std::string("aaa")) >  0 );

    EXPECT_NOT( compare(std::string("abc"), std::string("abcd")) == 0 );
    EXPECT    ( compare(std::string("abc"), std::string("abcd")) != 0 );

    EXPECT( compare(std17::string_view("abc"), std17::string_view("abc")) == 0 );
    EXPECT( compare(std17::string_view("aaa"), std17::string_view("abc")) != 0 );
    EXPECT( compare(std17::string_view("aaa"), std17::string_view("abc")) <  0 );
    EXPECT( compare(std17::string_view("aaa"), std17::string_view("abc")) <= 0 );
    EXPECT( compare(std17::string_view("abc"), std17::string_view("abc")) <= 0 );
    EXPECT( compare(std17::string_view("abc"), std17::string_view("aaa")) >= 0 );
    EXPECT( compare(std17::string_view("abc"), std17::string_view("aaa")) >  0 );

    EXPECT_NOT( compare(std17::string_view("abc"), std17::string_view("abcd")) == 0 );
    EXPECT    ( compare(std17::string_view("abc"), std17::string_view("abcd")) != 0 );
}

// TODO: operator==(), etc.

// Note: cannot compare char const *, comparison of non-user-defined type(s)

CASE( "operator==(): true if lhs string is equal to rhs string" )
{
    EXPECT( std::string("abc") == std::string("abc") );
    EXPECT( std17::string_view("abc") == std17::string_view("abc") );

    EXPECT_NOT( std::string("aaa") == std::string("abc") );
    EXPECT_NOT( std17::string_view("aaa") == std17::string_view("abc") );
}

CASE( "operator!=(): true if lhs string is not equal to rhs string" )
{
    EXPECT( std::string("aaa") != std::string("abc") );
    EXPECT( std17::string_view("aaa") != std17::string_view("abc") );

    EXPECT_NOT( std::string("abc") != std::string("abc") );
    EXPECT_NOT( std17::string_view("abc") != std17::string_view("abc") );
}

CASE( "operator<(): true if lhs string is less than rhs string" )
{
    EXPECT( std::string("aaa") < std::string("abc") );
    EXPECT( std17::string_view("aaa") < std17::string_view("abc") );

    EXPECT_NOT( std::string("abc") < std::string("abc") );
    EXPECT_NOT( std17::string_view("abc") < std17::string_view("abc") );
}

CASE( "operator<=(): true if lhs string is less than or equal to rhs string" )
{
    EXPECT( std::string("abc") <= std::string("abc") );
    EXPECT( std17::string_view("abc") <= std17::string_view("abc") );

    EXPECT_NOT( std::string("abc") <= std::string("aaa") );
    EXPECT_NOT( std17::string_view("abc") <= std17::string_view("aaa") );
}

CASE( "operator>=(): true if lhs string is greater than or equal to rhs string" )
{
    EXPECT( std::string("abc") >= std::string("abc") );
    EXPECT( std17::string_view("abc") >= std17::string_view("abc") );

    EXPECT_NOT( std::string("aaa") == std::string("abc") );
    EXPECT_NOT( std17::string_view("aaa") == std17::string_view("abc") );
}

CASE( "operator>(): true if lhs string is greater than or equal to rhs string" )
{
    EXPECT( std::string("abc") > std::string("aaa") );
    EXPECT( std17::string_view("abc") > std17::string_view("aaa") );

    EXPECT_NOT( std::string("abc") > std::string("abc") );
    EXPECT_NOT( std17::string_view("abc") > std17::string_view("abc") );
}

// tweak header

CASE( "tweak header: Reads tweak header if supported " "[tweak]" )
{
#if string_HAVE_TWEAK_HEADER
    EXPECT( string_TWEAK_VALUE == 42 );
#else
    EXPECT( !!"Tweak header is not available (string_HAVE_TWEAK_HEADER: 0)." );
#endif
}

} // anonymous namespace
