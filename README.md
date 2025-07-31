# string bare: string facilities for C++11 and later (In Progress)

Another attempt at a hopefully generally useful C++ string algorithm library.

For now, have a look at section [Functions](#functions) and section [*string-bare* test specification](#a2) for the functions envisioned / implemented (at the moment). The in-place modification class of functions is decidedly absent.

Initially writing code for `char` type strings, followed by generalising and enabling selecting `char`, `wchar_t`, `char8_t`, `char16_t`, `char32_t` insofar feasible and sensible.

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

TBD

## In a nutshell

TBD

## License

*string bare* is distributed under the [Boost Software License](https://github.com/martinmoene/bit-lite/blob/master/LICENSE.txt).

## Dependencies

*string lite* has no other dependencies than the [C++ standard library](http://en.cppreference.com/w/cpp/header).

## Installation and use

*string bare* is a single-file header-only library. Put `string.hpp` in the [include](include) folder directly into the project source tree or somewhere reachable from your project.

## Synopsis

TBD

### Functions

<!-- string-main.t.exe -l @ | cut --delimiter=: -f 1 |sort |uniq |clip -->
Note, in the following names like SeekT indicate template parameters.

Current functions in the library:

```
bool is_empty(string_view)
size_t length(string_view)
size_t size(string_view)

bool contains( char | SeekT | std::regex)
*** bool contains_re( SeekT )

bool starts_with( char | SeekT | std::regex)
*** bool starts_with_re( SeekT )

bool ends_with( char | SeekT | std::regex)
*** bool ends_with_re( SeekT )

size_t find_first(string_view, char | SeekT | std::regex)
size_t find_first_re(string_view, SeekT)
size_t find_first_of(string_view, SeekT | std::regex)
*** size_t find_first_of_re(string_view, SeekT)
size_t find_first_not_of(string_view, SeekT | std::regex)
*** size_t find_first_not_of_re(string_view, SeekT)

size_t find_last(string_view, char | SeekT | std::regex)
*** size_t find_last_re(string_view, SeekT)
size_t find_last_of(string_view, SeekT | std::regex)
*** size_t find_last_of_re(string_view, SeekT)
size_t find_last_not_of(string_view, SeekT | std::regex)        non-regex
*** size_t find_last_not_of_re(string_view, SeekT)              to be implemented

char to_lowercase(char)
char to_uppercase(char)
string to_lowercase(string_view)
string to_uppercase(string_view)

string append(string_view, TailT)

string substring(string_view, size_t pos, size_t count)
*** string substring_re(string_view, string_view)

strip
strip_left
strip_left_re
strip_right             non-regex
strip_right_re          to be implemented

replace_all
replace_all_re
replace_first
replace_first_re
replace_last            non-regex
replace_last_re         to be implemented

join
split

split_left
split_right             to be implemented
```

### Configuration

#### Tweak header

TBD

#### Provided character types

```
string_CONFIG_PROVIDE_CHAR_T
string_CONFIG_PROVIDE_WCHAR_T
string_CONFIG_PROVIDE_CHAR8_T
string_CONFIG_PROVIDE_CHAR16_T
string_CONFIG_PROVIDE_CHAR32_T
```

#### Provide `std::regex` functions

```
string_CONFIG_PROVIDE_REGEX
```

#### Standard selection macro

TBD

#### Disable exceptions

```
string_CONFIG_NO_EXCEPTIONS
```

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
contains: true if string contains regular expression - string-regex
contains_re: true if string contains regular expression - char*-char*
contains_re: true if string contains regular expression - string-char*
contains_re: true if string contains regular expression - string-string
contains_re: true if string contains regular expression - string-string_view
contains_re: true if string contains regular expression - string_view-string_view
starts_with: true if string starts with sub string - char*-char
starts_with: true if string starts with sub string - string-char
starts_with: true if string starts with sub string - string_view-char
starts_with: true if string starts with sub string - char*-char*
starts_with: true if string starts with sub string - string-char*
starts_with: true if string starts with sub string - string-string
starts_with: true if string starts with sub string - string-string_view
starts_with: true if string starts with sub string - string_view-string_view
starts_with: true if string starts with regular expression - string-regex
starts_with_re: true if string starts with regular expression - char*-char*
starts_with_re: true if string starts with regular expression - string-char*
starts_with_re: true if string starts with regular expression - string-string
starts_with_re: true if string starts with regular expression - string-string_view
starts_with_re: true if string starts with regular expression - string-string_view
ends_with: true if string ends with sub string - char*-char
ends_with: true if string ends with sub string - string-char
ends_with: true if string ends with sub string - string_view-char
ends_with: true if string ends with sub string - string-char*
ends_with: true if string ends with sub string - char*-char*
ends_with: true if string ends with sub string - string-string
ends_with: true if string ends with sub string - string-string_view
ends_with: true if string ends with sub string - string_view-string_view
ends_with: true if string ends with regular expression - string-regex
ends_with_re: true if string ends with regular expression - char*-char*
ends_with_re: true if string ends with regular expression - string-char*
ends_with_re: true if string ends with regular expression - string-string
ends_with_re: true if string ends with regular expression - string-string_view
ends_with_re: true if string ends with regular expression - string_view-string_view
find_first: position of sub string in string - char*-char
find_first: position of sub string in string - string-char
find_first: position of sub string in string - string_view-char
find_first: position of sub string in string - char*-char*
find_first: position of sub string in string - string-char*
find_first: position of sub string in string - string-string
find_first: position of sub string in string - string-string_view
find_first: position of sub string in string - string_view-string_view
find_first: position of regex in string: string-regex
find_first_re: position of regex in string: char*-char*
find_first_re: position of regex in string: string-char*
find_first_re: position of regex in string: string-string
find_first_re: position of regex in string: string-string_view
find_first_re: position of regex in string: string_view-string_view
find_last: position of sub string in string - char*-char
find_last: position of sub string in string - string-char
find_last: position of sub string in string - string_view-char
find_last: position of sub string in string - char*-char*
find_last: position of sub string in string - string-char*
find_last: position of sub string in string - string-string
find_last: position of sub string in string - string-string_view
find_last: position of sub string in string - string_view-string_view
find_last: position of regex in string: string-regex
find_last_re: position of regex in string: char*-char*
find_last_re: position of regex in string: string-char*
find_last_re: position of regex in string: string-string
find_last_re: position of regex in string: string-string_view
find_last_re: position of regex in string: string_view-string_view
find_first_of: position of character in set in string - char*-char*
find_first_of: position of character in set in string - string-char*
find_first_of: position of character in set in string - string-string
find_first_of: position of character in set in string - string-string_view
find_first_of: position of character in set in string - string_view-string_view
find_first_of: position of character in set in string: string-regex
find_first_of_re: position of character in set in string: char*-char*
find_first_of_re: position of character in set in string: string-char*
find_first_of_re: position of character in set in string: string-string
find_first_of_re: position of character in set in string: string-string_view
find_first_of_re: position of character in set in string: string_view-string_view
find_last_of: position of character in set in string - char*-char*
find_last_of: position of character in set in string - string-char*
find_last_of: position of character in set in string - string-string
find_last_of: position of character in set in string - string-string_view
find_last_of: position of character in set in string - string_view-string_view
find_last_of: position of character in set in string: string-regex
find_last_of_re: position of character in set in string: char*-char*
find_last_of_re: position of character in set in string: string-char*
find_last_of_re: position of character in set in string: string-string
find_last_of_re: position of character in set in string: string-string_view
find_last_of_re: position of character in set in string: string_view-string_view
find_first_not_of: position of character in set in string - char*-char*
find_first_not_of: position of character in set in string - string-char*
find_first_not_of: position of character in set in string - string-string
find_first_not_of: position of character in set in string - string-string_view
find_first_not_of: position of character in set in string - string_view-string_view
find_first_not_of: position of character in set in string: optionally use find_first_of([^...]): string-regex
find_first_not_of_re: position of character in set in string: optionally use find_first_of_re([^...]): char*-char*
find_first_not_of_re: position of character in set in string: optionally use find_first_of_re([^...]): string-char*
find_first_not_of_re: position of character in set in string: optionally use find_first_of_re([^...]): string-string
find_first_not_of_re: position of character in set in string: optionally use find_first_of_re([^...]): string-string_view
find_first_not_of_re: position of character in set in string: optionally use find_first_of_re([^...]): string_view-string_view
find_last_not_of: position of character in set in string - char*-char*
find_last_not_of: position of character in set in string - string-char*
find_last_not_of: position of character in set in string - string-string
find_last_not_of: position of character in set in string - string-string_view
find_last_not_of: position of character in set in string - string_view-string_view
find_last_not_of: position of character in set in string: optionally use find_last_of([^...]): string-regex[.TODO]
find_last_not_of_re: position of character in set in string: optionally find_last_of_re([^...]): char*-char*[.TODO]
find_last_not_of_re: position of character in set in string: optionally find_last_of_re([^...]): string-char*[.TODO]
find_last_not_of_re: position of character in set in string: optionally find_last_of_re([^...]): string-string[.TODO]
find_last_not_of_re: position of character in set in string: optionally find_last_of_re([^...]): string-string_view[.TODO]
find_last_not_of_re: position of character in set in string: optionally find_last_of_re([^...]): string_view-string_view[.TODO]
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
substring: Return substring given regex - string_view-regex
substring_re: Return substring given regex - char*-char*
substring_re: Return substring given regex - string-char*
substring_re: Return substring given regex - string-string
substring_re: Return substring given regex - string-string_view
substring_re: Return substring given regex - string_view-string_view
strip_left: Remove characters in set from left of string [" \t\n"] - char*-char*
strip_left: Remove characters in set from left of string [" \t\n"] - string-char*
strip_left: Remove characters in set from left of string [" \t\n"] - string-string
strip_left: Remove characters in set from left of string [" \t\n"] - string-string_view
strip_left: Remove characters in set from left of string [" \t\n"] - string_view-string_view
strip_left: Remove characters in set from left of string [" \t\n"] - other-char*
strip_left: Remove characters in regex from left of string - string-regex
strip_left_re: Remove characters in regex from left of string - char*-char*
strip_left_re: Remove characters in regex from left of string - string-char*
strip_left_re: Remove characters in regex from left of string - string-string
strip_left_re: Remove characters in regex from left of string - string-string_view
strip_left_re: Remove characters in regex from left of string - string_view-string_view
strip_right: Remove characters in set from right of string [" \t\n"] - char*-char*
strip_right: Remove characters in set from right of string [" \t\n"] - string-char*
strip_right: Remove characters in set from right of string [" \t\n"] - string-string
strip_right: Remove characters in set from right of string [" \t\n"] - string-string_view
strip_right: Remove characters in set from right of string [" \t\n"] - string_view-string_view
strip_right: Remove characters in set from right of string [" \t\n"] - other-char*
strip_right: Remove characters in regex from right of string - string-regex[.TODO]
strip_right_re: Remove characters in regex from right of string - char*-char*[.TODO]
strip_right_re: Remove characters in regex from right of string - string-char*[.TODO]
strip_right_re: Remove characters in regex from right of string - string-string[.TODO]
strip_right_re: Remove characters in regex from right of string - string-string_view[.TODO]
strip_right_re: Remove characters in regex from right of string - string_view-string_view[.TODO]
strip: Remove characters in set from left and right of string [" \t\n"] - char*-char*
strip: Remove characters in set from left and right of string [" \t\n"] - string-char*
strip: Remove characters in set from left and right of string [" \t\n"] - string-string
strip: Remove characters in set from left and right of string [" \t\n"] - string-string_view
strip: Remove characters in set from left and right of string [" \t\n"] - string_view-string_view
strip: Remove characters in set from left and right of string [" \t\n"] - other-char*
strip: Remove characters in regex from left and right of string - string-regex[.TODO]
strip_re: Remove characters in regex from left and right of string - char*-char*[.TODO]
strip_re: Remove characters in regex from left and right of string - string-char*[.TODO]
strip_re: Remove characters in regex from left and right of string - string-string[.TODO]
strip_re: Remove characters in regex from left and right of string - string-string_view[.TODO]
strip_re: Remove characters in regex from left and right of string - string_view-string_view[.TODO]
string_view: ...[.TODO]
replace_all: Return string with all occurrences of sub string changed - char*-char*
replace_all: Return string with all occurrences of sub string changed - string-string
replace_all: Return string with all occurrences of sub string changed - string-string_view
replace_all: Return string with all occurrences of sub string changed - string_view-string_view
replace_all: Return string with all occurrences of regex changed - string-regex
replace_all_re: Return string with all occurrences of regex changed - char*-char*
replace_all_re: Return string with all occurrences of regex changed - string-char*
replace_all_re: Return string with all occurrences of regex changed - string-string
replace_all_re: Return string with all occurrences of regex changed - string-string_view
replace_all_re: Return string with all occurrences of regex changed - string_view-string_view
replace_first: Return string with first occurrence of sub string changed - char*-char*
replace_first: Return string with first occurrence of sub string changed - string-char*
replace_first: Return string with first occurrence of sub string changed - string-string
replace_first: Return string with first occurrence of sub string changed - string-string_view
replace_first: Return string with first occurrence of sub string changed - string_view-string_view
replace_first: Return string with first occurrence of regex changed - string-regex
replace_first_re: Return string with first occurrence of regex changed - char*-char*
replace_first_re: Return string with first occurrence of regex changed - string-char*
replace_first_re: Return string with first occurrence of regex changed - string-string
replace_first_re: Return string with first occurrence of regex changed - string-string_view
replace_first_re: Return string with first occurrence of regex changed - string_view-string_view
replace_last: Return string with last occurrence of sub string changed - char*-char*
replace_last: Return string with last occurrence of sub string changed - string-string
replace_last: Return string with last occurrence of sub string changed - string-string_view
replace_last: Return string with last occurrence of sub string changed - string_view-string_view
replace_last: Return string with last occurrence of regex changed - string-regex[.TODO]
replace_last_re: Return string with last occurrence of regex changed - char*-char*[.TODO]
replace_last_re: Return string with last occurrence of regex changed - string-char*[.TODO]
replace_last_re: Return string with last occurrence of regex changed - string-string[.TODO]
replace_last_re: Return string with last occurrence of regex changed - string-string_view[.TODO]
replace_last_re: Return string with last occurrence of regex changed - string_view-string_view[.TODO]
join: Join strings from collection into a string separated by given separator
split: Split string into vector of string_view given delimiter - literal_delimiter
split_left: Split string into two-element tuple given delimiter - forward - xxx_delimiter
split_right: Split string into two-element tuple given delimiter - reverse - xxx_delimiter
tweak header: Reads tweak header if supported [tweak]
```

</p>
</details>
