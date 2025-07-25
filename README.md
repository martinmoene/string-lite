# string bare: string facilities for C++11 and later (In Progress)

Another attempt at a hopefully generally useful C++ string algorithm library.

For now, have a look at section [*string-bare* test specification](#ad) for the functions envisioned / implemented (at the moment). The in-place modification class of functions is decidedly absent.

Initially writing code for `char` type strings, followed by generalising and enabling selecting `char`, `wchar_t`, `char8_t`, `char16_t`, `char32_t` insofar feasible and sensible.

## Appendix

<a id="ad"></a>
### A.d *string-bare* test specification

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
contains: true if string contains regular expression - string-std::regex[.TODO]
contains_re: true if string contains regular expression - string-char*[.TODO]
starts_with: true if string starts with sub string - string-char
starts_with: true if string starts with sub string - string-char*
starts_with: true if string starts with sub string - string-string
starts_with: true if string starts with sub string - string-string_view
starts_with: true if string starts with sub string - string_view-string_view
starts_with: true if string starts with regular expression - string-std::regex[.TODO]
starts_with_re: true if string starts with regular expression - string-char*[.TODO]
ends_with: true if string ends with sub string - string-char
ends_with: true if string ends with sub string - string-char*
ends_with: true if string ends with sub string - string-string
ends_with: true if string ends with sub string - string-string_view
ends_with: true if string ends with sub string - string_view-string_view
ends_with: true if string ends with regular expression - string-std::regex[.TODO]
ends_with_re: true if string ends with regular expression - string-char*[.TODO]
find_first: position of sub string in string - string-char
find_first: position of sub string in string - string-char*
find_first: position of sub string in string - string-string
find_first: position of sub string in string - string-string_view
find_first: position of sub string in string_view - string_view-string_view
find_first: position of regex in string: string-std::regex[.TODO]
find_first_re: position of regex in string: string-char*[.TODO]
find_last: position of sub string in string - string-char
find_last: position of sub string in string - string-char*
find_last: position of sub string in string - string-string
find_last: position of sub string in string - string-string_view
find_last: position of sub string in string_view - string_view-string_view
find_last: position of regex in string: string-std::regex[.TODO]
find_last_re: position of regex in string: string-char*[.TODO]
find_first_of: position of sub string in string - char*-char*
find_first_of: position of sub string in string - string-char*
find_first_of: position of sub string in string - string-string
find_first_of: position of regex in string: string-std::regex[.TODO]
find_first_of_re: position of regex in string: string-char*[.TODO]
find_last_of: position of sub string in string - char*-char*
find_last_of: position of sub string in string - string-char*
find_last_of: position of sub string in string - string-string
find_last_of: position of regex in string: string-std::regex[.TODO]
find_last_of_re: position of regex in string: string-char*[.TODO]
find_first_not_of: position of sub string in string - char*-char*
find_first_not_of: position of sub string in string - string-char*
find_first_not_of: position of sub string in string - string-string
find_first_not_of: position of regex in string: string-std::regex[.TODO]
find_first_not_of_re: position of regex in string: string-char*[.TODO]
find_last_not_of: position of sub string in string - char*-char*
find_last_not_of: position of sub string in string - string-char*
find_last_not_of: position of sub string in string - string-string
find_last_not_of: position of regex in string: string-std::regex[.TODO]
find_last_not_of_re: position of regex in string: string-char*[.TODO]
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
substring: Return substring given regex - string-regex[.TODO]
substring_re: Return substring given regex - string-char*[.TODO]
strip_left: Remove characters in set from left of string [" \t\n"] - C-string
strip_left: Remove characters in set from left of string [" \t\n"] - string
strip_left: Remove characters in set from left of string [" \t\n"] - other
strip_left: Remove characters in regex from left of string - string-regex[.TODO]
strip_left_re: Remove characters in regex from left of string - string-char*[.TODO]
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
replace_all: Return string with all occurrences of regex changed - string-regex[.TODO]
replace_all_re: Return string with all occurrences of regex changed - string-char*[.TODO]
replace_first: Return string with first occurrence of sub string changed - char*-char*[.TODO]
replace_first: Return string with first occurrence of sub string changed - string-string[.TODO]
replace_first: Return string with first occurrence of sub string changed - string-string_view[.TODO]
replace_first: Return string with first occurrence of sub string changed - string_view-string_view[.TODO]
replace_first: Return string with first occurrence of regex changed - string-regex[.TODO]
replace_first_re: Return string with first occurrence of regex changed - string-char*[.TODO]
replace_last: Return string with last occurrence of sub string changed - char*-char*[.TODO]
replace_last: Return string with last occurrence of sub string changed - string-string[.TODO]
replace_last: Return string with last occurrence of sub string changed - string-string_view[.TODO]
replace_last: Return string with last occurrence of sub string changed - string_view-string_view[.TODO]
replace_last: Return string with last occurrence of regex changed - string-regex[.TODO]
replace_last_re: Return string with last occurrence of regex changed - string-char*[.TODO]
join: Join strings from collection into a string separated by given separator
split: Split string into vector of string_view given delimiter - literal_delimiter
split_2: Split string into two-element tuple given delimiter - xxx_delimiter
tweak header: Reads tweak header if supported [tweak]
```

</p>
</details>
