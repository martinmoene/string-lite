:: g++ - Compile all permutations of C++ std and string_view-s:

@echo off
for %%s in ( c++11 c++14 c++17 c++20 c++23 ) do (
    call tg.bat %%s
)
