:: g++ - Compile all permutations of C++ std and string_view-s:

@echo off
for %%v in ( string_CONFIG_SELECT_STRING_VIEW_INTERNAL string_CONFIG_SELECT_STRING_VIEW_NONSTD ) do (
    for %%s in ( c++98 c++03 c++11 c++14 c++17 c++2a ) do (
        call tg.bat %%s %%v
    )
)

for %%v in ( string_CONFIG_SELECT_STRING_VIEW_STD ) do (
    for %%s in ( c++17 c++2a ) do (
        call tg.bat %%s %%v
    )
)
