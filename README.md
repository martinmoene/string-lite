# string bare: string facilities for C++11 and later (In Progress)

[![Language](https://img.shields.io/badge/C%2B%2B-11/14/17/20/23-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B#Standardization) [![License](https://img.shields.io/badge/license-BSL-blue.svg)](https://opensource.org/licenses/BSL-1.0) [![Build Status](https://github.com/martinmoene/string-bare/actions/workflows/ci.yml/badge.svg)](https://github.com/martinmoene/string-bare/actions/workflows/ci.yml) [![Version](https://badge.fury.io/gh/martinmoene%2Fstring-bare.svg)](https://github.com/martinmoene/string-bare/releases) [![download](https://img.shields.io/badge/latest-download-blue.svg)](https://github.com/martinmoene/string-bare/blob/master/include/nonstd/string.hpp) <!-- [![Conan](https://img.shields.io/badge/on-conan-blue.svg)](https://conan.io/center/string-bare) [![Try it on wandbox](https://img.shields.io/badge/on-wandbox-blue.svg)](https://wandbox.org/) [![Try it on godbolt online](https://img.shields.io/badge/on-godbolt-blue.svg)](https://godbolt.org/) -->

Another attempt at a hopefully generally useful C++ string algorithm library.

I'm still pondering to add functions that take a regular expression, as `std::regex`and as string (using `*_re()` function names), and the API to use for that.

For now, have a look at section [Documentation of *string bare*](#syn-doc) and section [*string-bare* test specification](#a2) for the functions envisioned / implemented (at the moment). The in-place modification class of functions is decidedly absent.

In general, functions take `string_view`s and thereby `char const *`, `std::string` and `std::string_view` ([note 1](#note-1)) as arguments en produce (return) a `bool`, `size_t`, `std::string` or a collection of `string_view`s.

Initially writing code for `char` type strings, followed by generalising and enabling selecting `char`, `wchar_t`, `char8_t`, `char16_t`, `char32_t` insofar feasible and sensible.

<a id="note-1"></a>Note 1: to support use of `string_view`s with C++ versions earlier than C++17, `string_view`s may be accessed as `nonstd::string::std17::string_view`, supplying a local `string_view` class or `std::string_view` if present.

**Contents**  

- [Example usage](#example-usage)
- [In a nutshell](#in-a-nutshell)
- [License](#license)
- [Dependencies](#dependencies)
- [Installation and use](#installation-and-use)
- [Synopsis](#synopsis)
- [Notes and references](#notes-and-references)
- [Appendix](#appendix)

## Example usage

```cpp
// Use nonstd::string's split():

#include "nonstd/string.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

template< typename T >
std::string contents(std::vector<T> const & coll)
{
    // using nonstd::to_string() for nonstd::std17::string_view:
    using nonstd::to_string;

    std::stringstream os;
    for ( auto const & elem : coll )
        os << "'" << to_string(elem) << "', ";
    return os.str();
}

template< typename T >
std::ostream & operator<<(std::ostream & os, std::vector<T> const & coll )
{
    return os << "[" << contents(coll) << "]";
}

int main()
{
    std::cout << nonstd::string::split("Hello, world", ", ");
}
```

### Compile and run

```bash
prompt> g++ -std=c++11 -Wall -I../include -o 01-basic.exe 01-basic.cpp && 01-basic.exe
['Hello', 'world', ]
```

## In a nutshell

**string bare** is a single-file header-only library to provide various string algorithms. Firstly meant to get you up and running easily, not necessarily to provide everything that might be useful and in the most efficient manner.

Creating *string bare* I've had a look at the [C++ standard](https://eel.is/c++draft/#strings), [Boost](https://www.boost.org/doc/libs/1_60_0/doc/html/string_algo.html), [Facebook Folly](https://github.com/facebook/folly/blob/master/folly/String.h), the [Python standard library](https://docs.python.org/3/library/string.html), the [proposal for `std::split()`](http://wg21.link/n3593) and several algorithms I created over time.

**Features and properties of string bare** are ease of installation (single header), freedom of dependencies other than the standard library.

## License

*string bare* is distributed under the [Boost Software License](https://github.com/martinmoene/bit-bare/blob/master/LICENSE.txt).

## Dependencies

*string bare* has no other dependencies than the [C++ standard library](http://en.cppreference.com/w/cpp/header).

## Installation and use

*string bare* is a single-file header-only library. Put `string.hpp` in the [include](include) folder directly into the project source tree or somewhere reachable from your project.

## Synopsis

**Contents**  
[Documentation of *string bare*](#documentation-of-string-bare)  
[Configuration](#configuration)  

<a id="syn-doc"></a>
### Documentation of *string bare*

The following table presents types, values and simplified, short prototypes of the functions in _string-bare_'s `nonstd` namespace.

| Kind           | Type or function                                                                   | Notes                                                                                             |
| -------------- | ---------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------- |
| **Type**       | **literal_delimiter**                                                              | a string, `literal_delimiter("exact_text")`                                                       |
| &nbsp;         | **any_of_delimiter**                                                               | any of given characters, `any_of_delimiter("+-")`                                                 |
| &nbsp;         | **fixed_delimiter**                                                                | fixed length, `fixed_delimiter(length)`                                                           |
| &nbsp;         | **limit_delimiter**                                                                | apply given delimiter a limited number of times (not implemented)                                 |
| &nbsp;         | **regex_delimiter**                                                                | regular expression, `regex_delimiter("regexp")`                                                   |
| &nbsp;         | **char_delimiter**                                                                 | a character, `char_delimiter('&')`                                                                |
| &nbsp;         | &nbsp;                                                                             | &nbsp;                                                                                            |
| **Value**      | size_t **string::npos**                                                            | not-found position value, in nonstd::string namespace                                             |
| &nbsp;         | &nbsp;                                                                             | &nbsp;                                                                                            |
| **Observers**  | size_t **length**(string_view sv)                                                  | length of string                                                                                  |
| &nbsp;         | size_t **size**(string_view sv)                                                    | length of string                                                                                  |
| &nbsp;         | bool **is_empty**(string_view sv)                                                  | true if string is empty                                                                           |
| &nbsp;         | bool **contains**(string_view sv, string_view what)                                | true if string contains given string                                                              |
| &nbsp;         | bool **starts_with**(string_view sv, string_view what)                             | true if string starts with given string                                                           |
| &nbsp;         | bool **ends_with**(string_view sv, string_view what)                               | true if string ends with given string                                                             |
| &nbsp;         | &nbsp;                                                                             | &nbsp;                                                                                            |
| **Searching**  | size_t **find_first**(string_view sv, string_view what)                            | position of first occurrence of given string, or npos                                             |
| &nbsp;         | size_t **find_first_of**(string_view sv, string_view set)                          | position of first occurrence of character in set, or npos                                         |
| &nbsp;         | size_t **find_first_not_of**(string_view sv, string_view set)                      | position of first occurrence of character not in set, or npos                                     |
| &nbsp;         | size_t **find_last**(string_view sv, string_view what)                             | position of last occurrence of given string, or npos                                              |
| &nbsp;         | size_t **find_last_of**(string_view sv, string_view set)                           | position of last occurrence of character in set, or npos                                          |
| &nbsp;         | size_t **find_last_not_of**(string_view sv, string_view set)                       | position of last occurrence of character not in set, or npos                                      |
| &nbsp;         | &nbsp;                                                                             | &nbsp;                                                                                            |
| **Modifiers**  | char_t **to_lowercase**(char_t chr)                                                | character transformed to lowercase                                                                |
| &nbsp;         | char_t **to_uppercase**(char_t chr)                                                | character transformed to uppercase                                                                |
| &nbsp;         | string **to_lowercase**(string_view sv)                                            | string transformed to lowercase                                                                   |
| &nbsp;         | string **to_uppercase**(string_view sv)                                            | string transformed to uppercase                                                                   |
| &nbsp;         | string **substring**(string_view sv, size_t pos \[, size_t count\]);               | substring starting at given position of given length, default up to end                           |
| &nbsp;         | string **strip**(string_view sv, string_view set)                                  | string with characters given in set stripped from left and right                                  |
| &nbsp;         | string **strip_left**(string_view sv, string_view set)                             | string with characters given in set stripped from left                                            |
| &nbsp;         | string **strip_right**(string_view sv, string_view set)                            | string with characters given in set stripped from right                                           |
| &nbsp;         | string **replace_all**(string_view sv, string_view what, string_view with)         | string with all occurrences of 'what' replaced with 'with'                                        |
| &nbsp;         | string **replace_first**(string_view sv, string_view what, string_view with)       | string with first occurrence of 'what' replaced with 'with'                                       |
| &nbsp;         | string **replace_last**(string_view sv, string_view what, string_view with)        | string with last occurrence of 'what' replaced with 'with'                                        |
| &nbsp;         | &nbsp;                                                                             | &nbsp;                                                                                            |
| **Combining**  | string **append**(string_view head, string_view tail)                              | string with tail appended to head                                                                 |
| &nbsp;         | string **join**(collection\<string_view\> vec, string_view sep)                    | string with elements of collection joined with given separator string                             |
| &nbsp;         | &nbsp;                                                                             | &nbsp;                                                                                            |
| **Separating** | vector\<string_view\> **split**(string_view sv, string_view set)                   | vector of string_view with elements of string separated by characters from given set              |
| &nbsp;         | tuple\<string_view, string_view\> **split_left**(string_view sv, Delimiter delim)  | tuple with head and tail string_view on given string as split at left by given delimiter          |
| &nbsp;         | tuple\<string_view, string_view\> **split_right**(string_view sv, Delimiter delim) | tuple with head and tail string_view on given string as split at right by given delimiter         |
| &nbsp;         | tuple\<string_view, string_view\> **split_left**(string_view sv, string_view set)  | tuple with head and tail string_view on given string as split at left by characters in given set  |
| &nbsp;         | tuple\<string_view, string_view\> **split_right**(string_view sv, string_view set) | tuple with head and tail string_view on given string as split at right by characters in given set |

### Configuration

#### Tweak header

If the compiler supports [`__has_include()`](https://en.cppreference.com/w/cpp/preprocessor/include), *string bare* supports the [tweak header](https://vector-of-bool.github.io/2020/10/04/lib-configuration.html) mechanism. Provide your *tweak header* as `nonstd/string.tweak.hpp` in a folder in the include-search-path. In the tweak header, provide definitions as documented below, like `#define string_CPLUSPLUS 201103L`.

#### Provided character types

-D<b>string_CONFIG_PROVIDE_XXX_T</b>=1  
Define the character type to provide the string algorithms for.

`string_CONFIG_PROVIDE_XXX_T` can be one or more of:

- `string_CONFIG_PROVIDE_CHAR_T`, default 1
- `string_CONFIG_PROVIDE_WCHAR_T`, default 0
- `string_CONFIG_PROVIDE_CHAR8_T`, default 0
- `string_CONFIG_PROVIDE_CHAR16_T`, default 0
- `string_CONFIG_PROVIDE_CHAR32_T`, default 0

#### Provide `std::regex` functions

TODO: regex function not yet available.

-D<b>string_CONFIG_PROVIDE_REGEX</b>=1  
Define this to 0 if you want to compile without regular expressions. Default is `1`. Note that including regular expressions incurs significant compilation overhead.

#### Standard selection macro

\-D<b>string\_CPLUSPLUS</b>=199711L  
Define this macro to override the auto-detection of the supported C++ standard, if your compiler does not set the `__cplusplus` macro correctly.

#### Disable exceptions

TODO: compilation without exceptions not yet available.

-D<b>string_CONFIG_NO_EXCEPTIONS</b>=0  
Define this to 1 if you want to compile without exceptions. If not defined, the header tries and detect if exceptions have been disabled (e.g. via `-fno-exceptions`). Default is undefined.

## Notes and references

TBD

- [n3593 - std::split(): An algorithm for splitting strings](http://wg21.link/n3593). / https://isocpp.org/files/papers/n3593.html
- [Martin Broadhurst. How to split a string in C++. 2016](http://www.martinbroadhurst.com/how-to-split-a-string-in-c.html).

## Appendix

<a id="a1"></a>
### A.1 Compile-time information

In the test runner, the version of *string-bare* is available via tag `[.version]`. The following tags are available for information on the compiler and on the C++ standard library used: `[.compiler]`, `[.stdc++]`, `[.stdlanguage]` and `[.stdlibrary]`.

<a id="a2"></a>
### A.2 *string-bare* test specification

<!-- string-main.t.exe -l @ | cut --delimiter=: -f 1 |sort |uniq |clip -->
<!-- string-main.t.exe -l |grep -v _re |grep -v regex |clip -->

<details>
<summary>click to expand</summary>
<p>

```
length: length of given string - char *
length: length of given string - std::string
size: length of given string - char *
size: length of given string - std::string
is_empty: true if string is empty - char *
is_empty: true if string is empty - string
contains: true if string contains sub string - char*-char
contains: true if string contains sub string - string-char
contains: true if string contains sub string - string_view-char
contains: true if string contains sub string - char*-char*
contains: true if string contains sub string - string-char*
contains: true if string contains sub string - string-string
contains: true if string contains sub string - string-string_view
contains: true if string contains sub string - string_view-string_view
starts_with: true if string starts with sub string - char*-char
starts_with: true if string starts with sub string - string-char
starts_with: true if string starts with sub string - string_view-char
starts_with: true if string starts with sub string - char*-char*
starts_with: true if string starts with sub string - string-char*
starts_with: true if string starts with sub string - string-string
starts_with: true if string starts with sub string - string-string_view
starts_with: true if string starts with sub string - string_view-string_view
ends_with: true if string ends with sub string - char*-char
ends_with: true if string ends with sub string - string-char
ends_with: true if string ends with sub string - string_view-char
ends_with: true if string ends with sub string - string-char*
ends_with: true if string ends with sub string - char*-char*
ends_with: true if string ends with sub string - string-string
ends_with: true if string ends with sub string - string-string_view
ends_with: true if string ends with sub string - string_view-string_view
find_first: position of sub string in string - char*-char
find_first: position of sub string in string - string-char
find_first: position of sub string in string - string_view-char
find_first: position of sub string in string - char*-char*
find_first: position of sub string in string - string-char*
find_first: position of sub string in string - string-string
find_first: position of sub string in string - string-string_view
find_first: position of sub string in string - string_view-string_view
find_last: position of sub string in string - char*-char
find_last: position of sub string in string - string-char
find_last: position of sub string in string - string_view-char
find_last: position of sub string in string - char*-char*
find_last: position of sub string in string - string-char*
find_last: position of sub string in string - string-string
find_last: position of sub string in string - string-string_view
find_last: position of sub string in string - string_view-string_view
find_first_of: position of character in set in string - char*-char*
find_first_of: position of character in set in string - string-char*
find_first_of: position of character in set in string - string-string
find_first_of: position of character in set in string - string-string_view
find_first_of: position of character in set in string - string_view-string_view
find_last_of: position of character in set in string - char*-char*
find_last_of: position of character in set in string - string-char*
find_last_of: position of character in set in string - string-string
find_last_of: position of character in set in string - string-string_view
find_last_of: position of character in set in string - string_view-string_view
find_first_not_of: position of character in set in string - char*-char*
find_first_not_of: position of character in set in string - string-char*
find_first_not_of: position of character in set in string - string-string
find_first_not_of: position of character in set in string - string-string_view
find_first_not_of: position of character in set in string - string_view-string_view
find_last_not_of: position of character in set in string - char*-char*
find_last_not_of: position of character in set in string - string-char*
find_last_not_of: position of character in set in string - string-string
find_last_not_of: position of character in set in string - string-string_view
find_last_not_of: position of character in set in string - string_view-string_view
to_lowercase: Return char in lowercase - char
to_lowercase: Return string in lowercase - char*
to_lowercase: Return string in lowercase - string
to_lowercase: Return string in lowercase - string_view
to_uppercase: Return char in uppercase - char
to_uppercase: Return string in uppercase - char*
to_uppercase: Return string in uppercase - string
to_uppercase: Return string in uppercase - string_view
append: Return string with second string append to first string - char*-char*
append: Return string with second string append to first string - string-char*
append: Return string with second string append to first string - string-string
append: Return string with second string append to first string - string-string_view
append: Return string with second string append to first string - string_view-string_view
substring: Return substring given position and length - char*-pos
substring: Return substring given position and length - string-pos
substring: Return substring given position and length - string_view-pos
strip_left: Remove characters in set from left of string [" \t\n"] - char*-char*
strip_left: Remove characters in set from left of string [" \t\n"] - string-char*
strip_left: Remove characters in set from left of string [" \t\n"] - string-string
strip_left: Remove characters in set from left of string [" \t\n"] - string-string_view
strip_left: Remove characters in set from left of string [" \t\n"] - string_view-string_view
strip_left: Remove characters in set from left of string [" \t\n"] - other-char*
strip_right: Remove characters in set from right of string [" \t\n"] - char*-char*
strip_right: Remove characters in set from right of string [" \t\n"] - string-char*
strip_right: Remove characters in set from right of string [" \t\n"] - string-string
strip_right: Remove characters in set from right of string [" \t\n"] - string-string_view
strip_right: Remove characters in set from right of string [" \t\n"] - string_view-string_view
strip_right: Remove characters in set from right of string [" \t\n"] - other-char*
strip: Remove characters in set from left and right of string [" \t\n"] - char*-char*
strip: Remove characters in set from left and right of string [" \t\n"] - string-char*
strip: Remove characters in set from left and right of string [" \t\n"] - string-string
strip: Remove characters in set from left and right of string [" \t\n"] - string-string_view
strip: Remove characters in set from left and right of string [" \t\n"] - string_view-string_view
strip: Remove characters in set from left and right of string [" \t\n"] - other-char*
replace_all: Return string with all occurrences of sub string changed - char*-char*
replace_all: Return string with all occurrences of sub string changed - string-string
replace_all: Return string with all occurrences of sub string changed - string-string_view
replace_all: Return string with all occurrences of sub string changed - string_view-string_view
replace_first: Return string with first occurrence of sub string changed - char*-char*
replace_first: Return string with first occurrence of sub string changed - string-char*
replace_first: Return string with first occurrence of sub string changed - string-string
replace_first: Return string with first occurrence of sub string changed - string-string_view
replace_first: Return string with first occurrence of sub string changed - string_view-string_view
replace_last: Return string with last occurrence of sub string changed - char*-char*
replace_last: Return string with last occurrence of sub string changed - string-string
replace_last: Return string with last occurrence of sub string changed - string-string_view
replace_last: Return string with last occurrence of sub string changed - string_view-string_view
join: Join strings from collection into a string separated by given separator
split: Split string into vector of string_view given delimiter - literal_delimiter
split_left: Split string into two-element tuple given delimiter - forward - xxx_delimiter
split_right: Split string into two-element tuple given delimiter - reverse - xxx_delimiter
tweak header: Reads tweak header if supported [tweak]
```

</p>
</details>
