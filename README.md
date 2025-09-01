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

| Kind              | Type or function                                                                   | Notes                                                                                             |
| ----------------- | ---------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------- |
| **Type**          | **literal_delimiter**                                                              | a string, `literal_delimiter("exact_text")`                                                       |
| &nbsp;            | **any_of_delimiter**                                                               | any of given characters, `any_of_delimiter("+-")`                                                 |
| &nbsp;            | **fixed_delimiter**                                                                | fixed length, `fixed_delimiter(length)`                                                           |
| &nbsp;            | **limit_delimiter**                                                                | apply given delimiter a limited number of times (not implemented)                                 |
| &nbsp;            | **regex_delimiter**                                                                | regular expression, `regex_delimiter("regexp")`                                                   |
| &nbsp;            | **char_delimiter**                                                                 | a character, `char_delimiter('&')`                                                                |
| &nbsp;            | &nbsp;                                                                             | &nbsp;                                                                                            |
| **Value**         | size_t **string::npos**                                                            | not-found position value, in nonstd::string namespace                                             |
| &nbsp;            | &nbsp;                                                                             | &nbsp;                                                                                            |
| **Utilities**     | string **to_string**(string_view sv)                                               | string from local or C++17 std string_view                                                        |
| &nbsp;            | &nbsp;                                                                             | &nbsp;                                                                                            |
| **Observers**     | size_t **length**(string_view sv)                                                  | length of string                                                                                  |
| &nbsp;            | size_t **size**(string_view sv)                                                    | length of string                                                                                  |
| &nbsp;            | bool **is_empty**(string_view sv)                                                  | true if string is empty                                                                           |
| &nbsp;            | &nbsp;                                                                             | &nbsp;                                                                                            |
| &emsp;contains    | bool **contains**(string_view sv, string_view what)                                | true if string contains given string                                                              |
| &nbsp;            | bool **contains_all_of**(string_view sv, string_view set)                          | true if string contains all characters of set                                                     |
| &nbsp;            | bool **contains_any_of**(string_view sv, string_view set)                          | true if string contains any character of set                                                      |
| &nbsp;            | bool **contains_none_of**(string_view sv, string_view set)                         | true if string contains no character of set                                                       |
| &nbsp;            | &nbsp;                                                                             | &nbsp;                                                                                            |
| &emsp;starts_with | bool **starts_with**(string_view sv, string_view what)                             | true if string starts with given string                                                           |
| &nbsp;            | bool **starts_with_all_of**(string_view sv, string_view set)                       | true if string starts with all characters of set                                                  |
| &nbsp;            | bool **starts_with_any_of**(string_view sv, string_view set)                       | true if string starts with any character of set                                                   |
| &nbsp;            | bool **starts_with_none_of**(string_view sv, string_view set)                      | true if string starts with no character of set                                                    |
| &nbsp;            | &nbsp;                                                                             | &nbsp;                                                                                            |
| &emsp;ends_with   | bool **ends_with**(string_view sv, string_view what)                               | true if string ends with given string                                                             |
| &nbsp;            | bool **ends_with_all_of**(string_view sv, string_view set)                         | true if string ends with all characters of set                                                  |
| &nbsp;            | bool **ends_with_any_of**(string_view sv, string_view set)                         | true if string ends with any character of set                                                   |
| &nbsp;            | bool **ends_with_none_of**(string_view sv, string_view set)                        | true if string ends with no character of set                                                    |
| &nbsp;            | &nbsp;                                                                             | &nbsp;                                                                                            |
| **Searching**     | size_t **find_first**(string_view sv, string_view what)                            | position of first occurrence of given string, or npos                                             |
| &nbsp;            | size_t **find_first_of**(string_view sv, string_view set)                          | position of first occurrence of character in set, or npos                                         |
| &nbsp;            | size_t **find_first_not_of**(string_view sv, string_view set)                      | position of first occurrence of character not in set, or npos                                     |
| &nbsp;            | &nbsp;                                                                             | &nbsp;                                                                                            |
| &emsp;find        | size_t **find_last**(string_view sv, string_view what)                             | position of last occurrence of given string, or npos                                              |
| &nbsp;            | size_t **find_last_of**(string_view sv, string_view set)                           | position of last occurrence of character in set, or npos                                          |
| &nbsp;            | size_t **find_last_not_of**(string_view sv, string_view set)                       | position of last occurrence of character not in set, or npos                                      |
| &nbsp;            | &nbsp;                                                                             | &nbsp;                                                                                            |
| **Modifiers**     | char_t **to_lowercase**(char_t chr)                                                | character transformed to lowercase                                                                |
| &nbsp;            | char_t **to_uppercase**(char_t chr)                                                | character transformed to uppercase                                                                |
| &nbsp;            | string **to_lowercase**(string_view sv)                                            | string transformed to lowercase                                                                   |
| &nbsp;            | string **to_uppercase**(string_view sv)                                            | string transformed to uppercase                                                                   |
| &emsp;case        | string **capitalize**(string_view sv)                                              | string transformed to start with capital                                                          |
| &nbsp;            | &nbsp;                                                                             | &nbsp;                                                                                            |
| &emsp;substring   | string **substring**(string_view sv, size_t pos \[, size_t count\]);               | substring starting at given position of given length, default up to end                           |
| &nbsp;            | &nbsp;                                                                             | &nbsp;                                                                                            |
| &emsp;erase       | string **erase**(string_view sv, size_t pos \[, size_t count\])                    | string with substring at given position of given length removed, default up to end                |
| &nbsp;            | string **erase_all**(string_view sv, string_view what)                             | string with all occurrences of 'what' removed                                                     |
| &nbsp;            | string **erase_first**(string_view sv, string_view what)                           | string with first occurrence of 'what' removed                                                    |
| &nbsp;            | string **erase_last**(string_view sv, string_view what)                            | string with last occurrence of 'what' removed                                                     |
| &nbsp;            | &nbsp;                                                                             | &nbsp;                                                                                            |
| &emsp;insert      | string **insert**(string_view sv, size_t pos, string_view what)                    | string with substring 'what' inserted at given position                                           |
| &nbsp;            | &nbsp;                                                                             | &nbsp;                                                                                            |
| &emsp;replace     | string **replace**(string_view sv, size_t pos, size_t length, string_view with)    | string with substring pos to pos+length replaced with 'with'                                      |
| &nbsp;            | string **replace_all**(string_view sv, string_view what, string_view with)         | string with all occurrences of 'what' replaced with 'with'                                        |
| &nbsp;            | string **replace_first**(string_view sv, string_view what, string_view with)       | string with first occurrence of 'what' replaced with 'with'                                       |
| &nbsp;            | string **replace_last**(string_view sv, string_view what, string_view with)        | string with last occurrence of 'what' replaced with 'with'                                        |
| &nbsp;            | &nbsp;                                                                             | &nbsp;                                                                                            |
| &emsp;strip       | string **strip**(string_view sv, string_view set)                                  | string with characters given in set stripped from left and right                                  |
| &nbsp;            | string **strip_left**(string_view sv, string_view set)                             | string with characters given in set stripped from left                                            |
| &nbsp;            | string **strip_right**(string_view sv, string_view set)                            | string with characters given in set stripped from right                                           |
| &nbsp;            | &nbsp;                                                                             | &nbsp;                                                                                            |
| **Combining**     | string **append**(string_view head, string_view tail)                              | string with tail appended to head                                                                 |
| &nbsp;            | string **join**(collection\<string_view\> vec, string_view sep)                    | string with elements of collection joined with given separator string                             |
| &nbsp;            | &nbsp;                                                                             | &nbsp;                                                                                            |
| **Separating**    | vector\<string_view\> **split**(string_view sv, string_view set)                   | vector of string_view with elements of string separated by characters from given set              |
| &nbsp;            | tuple\<string_view, string_view\> **split_left**(string_view sv, Delimiter delim)  | tuple with head and tail string_view on given string as split at left by given delimiter          |
| &nbsp;            | tuple\<string_view, string_view\> **split_right**(string_view sv, Delimiter delim) | tuple with head and tail string_view on given string as split at right by given delimiter         |
| &nbsp;            | tuple\<string_view, string_view\> **split_left**(string_view sv, string_view set)  | tuple with head and tail string_view on given string as split at left by characters in given set  |
| &nbsp;            | tuple\<string_view, string_view\> **split_right**(string_view sv, string_view set) | tuple with head and tail string_view on given string as split at right by characters in given set |

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
length: length of given string
size: length of given string
is_empty: true if string is empty
contains: true if string contains substring
contains_all_of: true if string contains all characters of set
contains_any_of: true if string contains any character of set
contains_none_of: true if string contains no character of set
starts_with: true if string starts with substring
starts_with_all_of: true if string starts with all characters of set
starts_with_any_of: true if string starts with any character of set
starts_with_none_of: true if string starts with no character of set
ends_with: true if string ends with substring
ends_with_all_of: true if string ends with all characters of set
ends_with_any_of: true if string ends with any character of set
ends_with_none_of: true if string ends with no character of set
find_first: position of first substring in string
find_last: position of last substring in string
find_first_of: position of first character in string in set
find_last_of: position of last character in string in set
find_first_not_of: position of first character in string not in set
find_last_not_of: position of last character in string not in set
capitalize: string transformed to start with capital
to_lowercase: char transformed to lowercase
to_lowercase: string transformed to lowercase
to_uppercase: char transformed to uppercase
to_uppercase: string transformed to uppercase
append: string with second string concatenated to first string
substring: substring starting at given position of given length, default up to end
erase: string with substring at given position of given length removed - default up to end
erase_all: string with all occurrences of substring removed
erase_first: string with first occurrence of substring removed
erase_last: string with last occurrence of substring removed
insert: string with substring inserted at given position
replace: string with substring given by position and length replaced
replace_all: string with all occurrences of substring replaced
replace_first: string with first occurrence of substring replaced
replace_last: string with last occurrence of substring replaced
strip_left: string with characters in set removed from left of string [" \t\n"]
strip_right: string with characters in set removed from right of string [" \t\n"]
strip: string with characters in set removed from left and right of string [" \t\n"]
join: string with strings from collection joined separated by given separator
split: split string into vector of string_view given delimiter - literal_delimiter
split_left: split string into two-element tuple given delimiter - forward - literal_delimiter
split_right: split string into two-element tuple given delimiter - reverse - literal_delimiter
tweak header: Reads tweak header if supported [tweak]
```

</p>
</details>
