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
Current functions in the library:

```
is_empty
length
size

contains
contains_re

starts_with
starts_with_re

ends_with
ends_with_re

find_first
find_first_re
find_first_of
find_first_of_re
find_first_not_of
find_first_not_of_re

find_last
find_last_re
find_last_of
find_last_of_re
find_last_not_of        non-regex
find_last_not_of_re     to be implemented

to_lowercase
to_uppercase

append

substring
substring_re

strip
strip_left
strip_left_re
strip_right             non-regex
strip_right_re          to be implemented

replace_all             to be implemented (regex done)
replace_all_re          done
replace_first           to be implemented (regex done)
replace_first_re        done
replace_last            to be implemented
replace_last_re         ...

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
contains: true if string contains sub string - string-char
contains: true if string contains sub string - string-char*
contains: true if string contains sub string - string-string
contains: true if string contains sub string - string-string_view
contains: true if string contains sub string - string_view-string_view
contains: true if string contains regular expression - string-std::regex
contains_re: true if string contains regular expression - string-char*
starts_with: true if string starts with sub string - string-char
starts_with: true if string starts with sub string - string-char*
starts_with: true if string starts with sub string - string-string
starts_with: true if string starts with sub string - string-string_view
starts_with: true if string starts with sub string - string_view-string_view
starts_with: true if string starts with regular expression - string-std::regex
starts_with_re: true if string starts with regular expression - string-char*
ends_with: true if string ends with sub string - string-char
ends_with: true if string ends with sub string - string-char*
ends_with: true if string ends with sub string - string-string
ends_with: true if string ends with sub string - string-string_view
ends_with: true if string ends with sub string - string_view-string_view
ends_with: true if string ends with regular expression - string-std::regex
ends_with_re: true if string ends with regular expression - string-char*
find_first: position of sub string in string - string-char
find_first: position of sub string in string - string-char*
find_first: position of sub string in string - string-string
find_first: position of sub string in string - string-string_view
find_first: position of sub string in string_view - string_view-string_view
find_first: position of regex in string: string-std::regex
find_first_re: position of regex in string: string-char*
find_last: position of sub string in string - string-char
find_last: position of sub string in string - string-char*
find_last: position of sub string in string - string-string
find_last: position of sub string in string - string-string_view
find_last: position of sub string in string_view - string_view-string_view
find_last: position of regex in string: string-std::regex
find_last_re: position of regex in string: string-char*
find_first_of: position of character in set in string - char*-char*
find_first_of: position of character in set in string - string-char*
find_first_of: position of character in set in string - string-string
find_first_of: position of character in set in string: string-std::regex
find_first_of_re: position of character in set in string: string-char*
find_last_of: position of character in set in string - char*-char*
find_last_of: position of character in set in string - string-char*
find_last_of: position of character in set in string - string-string
find_last_of: position of character in set in string: string-std::regex
find_last_of_re: position of character in set in string: string-char*
find_first_not_of: position of character in set in string - char*-char*
find_first_not_of: position of character in set in string - string-char*
find_first_not_of: position of character in set in string - string-string
find_first_not_of: position of character in set in string: optionally use find_first_of([^...]): string-std::regex
find_first_not_of_re: position of character in set in string: optionally use find_first_of_re([^...]): string-char*
find_last_not_of: position of character in set in string - char*-char*
find_last_not_of: position of character in set in string - string-char*
find_last_not_of: position of character in set in string - string-string
find_last_not_of: position of character in set in string: optionally use find_last_of([^...]): string-std::regex[.TODO]
find_last_not_of_re: position of character in set in string: optionally find_last_of_re([^...]): string-char*[.TODO]
to_lowercase: Return string in lowercase - char*
to_lowercase: Return string in lowercase - string
to_lowercase: Return string in lowercase - string_view
to_uppercase: Return string in uppercase - char*
to_uppercase: Return string in uppercase - string
to_uppercase: Return string in uppercase - string_view
append: Return string with second string append to first string - string-char*
append: Return string with second string append to first string - string-string
append: Return string with second string append to first string - string-string_view
substring: Return substring given position and length - char*-pos
substring: Return substring given position and length - string-pos
substring: Return substring given position and length - string_view-pos
substring: Return substring given regex - string-regex
substring_re: Return substring given regex - string-char*
strip_left: Remove characters in set from left of string [" \t\n"] - C-string
strip_left: Remove characters in set from left of string [" \t\n"] - string
strip_left: Remove characters in set from left of string [" \t\n"] - other
strip_left: Remove characters in regex from left of string - string-regex
strip_left_re: Remove characters in regex from left of string - string-char*
strip_right: Remove characters in set from right of string [" \t\n"] - string
strip_right: Remove characters in set from right of string [" \t\n"] - other
strip_right: Remove characters in regex from right of string - string-regex[.TODO]
strip_right_re: Remove characters in regex from right of string - string-char*[.TODO]
strip: Remove characters in set from left and right of string [" \t\n"] - string
strip: Remove characters in set from left and right of string [" \t\n"] - other
strip: Remove characters in regex from left and right of string - string-regex[.TODO]
strip_re: Remove characters in regex from left and right of string - string-char*[.TODO]
string_view: ...[.TODO]
replace_all: Return string with all occurrences of sub string changed - char*-char*[.TODO]
replace_all: Return string with all occurrences of sub string changed - string-string[.TODO]
replace_all: Return string with all occurrences of sub string changed - string-string_view[.TODO]
replace_all: Return string with all occurrences of regex changed - string-regex
replace_all_re: Return string with all occurrences of regex changed - string-char*
replace_first: Return string with first occurrence of sub string changed - char*-char*[.TODO]
replace_first: Return string with first occurrence of sub string changed - string-string[.TODO]
replace_first: Return string with first occurrence of sub string changed - string-string_view[.TODO]
replace_first: Return string with first occurrence of sub string changed - string_view-string_view[.TODO]
replace_first: Return string with first occurrence of regex changed - string-regex
replace_first_re: Return string with first occurrence of regex changed - string-char*
replace_last: Return string with last occurrence of sub string changed - char*-char*[.TODO]
replace_last: Return string with last occurrence of sub string changed - string-string[.TODO]
replace_last: Return string with last occurrence of sub string changed - string-string_view[.TODO]
replace_last: Return string with last occurrence of sub string changed - string_view-string_view[.TODO]
replace_last: Return string with last occurrence of regex changed - string-regex[.TODO]
replace_last_re: Return string with last occurrence of regex changed - string-char*[.TODO]
join: Join strings from collection into a string separated by given separator
split: Split string into vector of string_view given delimiter - literal_delimiter
split_left: Split string into two-element tuple given delimiter - forward - xxx_delimiter
split_right: Split string into two-element tuple given delimiter - reverse - xxx_delimiter
tweak header: Reads tweak header if supported [tweak]
```

</p>
</details>
