//
// Copyright (c) 2025-2025 Martin Moene
//
// https://github.com/martinmoene/string-bare
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// TODO: Plan
// - [x] use C++20 std::string_view, not C++17 for presence of ctor(char* begin, char* end)
// - [x] Reconsider above for C++17 string-string_view interoperability ?
// - [ ] implement functions
// - [ ] support string_view as source?
// - [ ] constexpr / string_constexpr / string_constexpr14
// - [ ] nodiscard / string_nodiscard
// - [ ] noexcept / string_noexcept
// - [ ] MK macros
// - [ ] create functions via MK macros

#ifndef NONSTD_STRING_BARE_HPP
#define NONSTD_STRING_BARE_HPP

#define string_bare_MAJOR  0
#define string_bare_MINOR  0
#define string_bare_PATCH  0

#define string_bare_VERSION  string_STRINGIFY(string_bare_MAJOR) "." string_STRINGIFY(string_bare_MINOR) "." string_STRINGIFY(string_bare_PATCH)

#define string_STRINGIFY(  x )  string_STRINGIFY_( x )
#define string_STRINGIFY_( x )  #x

// tweak header support:

#ifdef __has_include
# if __has_include(<nonstd/string.tweak.hpp>)
#  include <nonstd/string.tweak.hpp>
# endif
#define string_HAVE_TWEAK_HEADER  1
#else
#define string_HAVE_TWEAK_HEADER  0
//# pragma message("string.hpp: Note: Tweak header not supported.")
#endif

// string configuration:

// Select character types to provide:

#if !defined( string_CONFIG_PROVIDE_CHAR_T )
# define string_CONFIG_PROVIDE_CHAR_T  1
#endif

#if !defined( string_CONFIG_PROVIDE_WCHAR_T )
# define string_CONFIG_PROVIDE_WCHAR_T  0
#endif

#if !defined( string_CONFIG_PROVIDE_CHAR8_T )
# define string_CONFIG_PROVIDE_CHAR8_T  0
#endif

#if !defined( string_CONFIG_PROVIDE_CHAR16_T )
# define string_CONFIG_PROVIDE_CHAR16_T  0
#endif

#if !defined( string_CONFIG_PROVIDE_CHAR32_T )
# define string_CONFIG_PROVIDE_CHAR32_T  0
#endif

// Provide regex variants: default off, as it increases compile time considerably.

#if !defined( string_CONFIG_PROVIDE_REGEX )
# define string_CONFIG_PROVIDE_REGEX  0
#endif

// Control presence of exception handling (try and auto discover):

#ifndef string_CONFIG_NO_EXCEPTIONS
# if defined(_MSC_VER)
# include <cstddef>     // for _HAS_EXCEPTIONS
# endif
# if defined(__cpp_exceptions) || defined(__EXCEPTIONS) || (_HAS_EXCEPTIONS)
#  define string_CONFIG_NO_EXCEPTIONS  0
# else
#  define string_CONFIG_NO_EXCEPTIONS  1
# endif
#endif

// C++ language version detection:
// Note: VC14.0/1900 (VS2015) lacks too much from C++14.

#ifndef   string_CPLUSPLUS
# if defined(_MSVC_LANG ) && !defined(__clang__)
#  define string_CPLUSPLUS  (_MSC_VER == 1900 ? 201103L : _MSVC_LANG )
# else
#  define string_CPLUSPLUS  __cplusplus
# endif
#endif

#define string_CPP98_OR_GREATER  ( string_CPLUSPLUS >= 199711L )
#define string_CPP11_OR_GREATER  ( string_CPLUSPLUS >= 201103L )
#define string_CPP14_OR_GREATER  ( string_CPLUSPLUS >= 201402L )
#define string_CPP17_OR_GREATER  ( string_CPLUSPLUS >= 201703L )
#define string_CPP20_OR_GREATER  ( string_CPLUSPLUS >= 202002L )
#define string_CPP23_OR_GREATER  ( string_CPLUSPLUS >= 202302L )
#define string_CPP26_OR_GREATER  ( string_CPLUSPLUS >  202302L )  // not finalized yet

// MSVC version:

#if defined(_MSC_VER ) && !defined(__clang__)
# define string_COMPILER_MSVC_VER           (_MSC_VER )
# define string_COMPILER_MSVC_VERSION       (_MSC_VER / 10 - 10 * ( 5 + (_MSC_VER < 1900 ) ) )
# define string_COMPILER_MSVC_VERSION_FULL  (_MSC_VER - 100 * ( 5 + (_MSC_VER < 1900 ) ) )
#else
# define string_COMPILER_MSVC_VER           0
# define string_COMPILER_MSVC_VERSION       0
# define string_COMPILER_MSVC_VERSION_FULL  0
#endif

// clang version:

#define string_COMPILER_VERSION( major, minor, patch ) ( 10 * ( 10 * (major) + (minor) ) + (patch) )

#if defined( __apple_build_version__ )
# define string_COMPILER_APPLECLANG_VERSION string_COMPILER_VERSION( __clang_major__, __clang_minor__, __clang_patchlevel__ )
# define string_COMPILER_CLANG_VERSION 0
#elif defined( __clang__ )
# define string_COMPILER_APPLECLANG_VERSION 0
# define string_COMPILER_CLANG_VERSION string_COMPILER_VERSION( __clang_major__, __clang_minor__, __clang_patchlevel__ )
#else
# define string_COMPILER_APPLECLANG_VERSION 0
# define string_COMPILER_CLANG_VERSION 0
#endif

// GNUC version:

#if defined(__GNUC__) && !defined(__clang__)
# define string_COMPILER_GNUC_VERSION string_COMPILER_VERSION( __GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__ )
#else
# define string_COMPILER_GNUC_VERSION 0
#endif

// half-open range [lo..hi):
#define string_BETWEEN( v, lo, hi ) ( (lo) <= (v) && (v) < (hi) )

// Presence of language and library features:

#define string_CPP11_100  (string_CPP11_OR_GREATER || string_COMPILER_MSVC_VER >= 1600)
#define string_CPP11_110  (string_CPP11_OR_GREATER || string_COMPILER_MSVC_VER >= 1700)
#define string_CPP11_120  (string_CPP11_OR_GREATER || string_COMPILER_MSVC_VER >= 1800)
#define string_CPP11_140  (string_CPP11_OR_GREATER || string_COMPILER_MSVC_VER >= 1900)
#define string_CPP11_141  (string_CPP11_OR_GREATER || string_COMPILER_MSVC_VER >= 1910)

#define string_CPP11_000  (string_CPP11_OR_GREATER)

#define string_CPP14_000  (string_CPP14_OR_GREATER)
#define string_CPP14_120  (string_CPP14_OR_GREATER || string_COMPILER_MSVC_VER >= 1800)

#define string_CPP17_000  (string_CPP17_OR_GREATER)
#define string_CPP17_120  (string_CPP17_OR_GREATER || string_COMPILER_MSVC_VER >= 1800)
#define string_CPP17_140  (string_CPP17_OR_GREATER || string_COMPILER_MSVC_VER >= 1900)

#define string_CPP20_000  (string_CPP20_OR_GREATER)

// Presence of C++11 language features:

#define string_HAVE_FREE_BEGIN              string_CPP11_120
#define string_HAVE_CONSTEXPR_11           (string_CPP11_000 && !string_BETWEEN(string_COMPILER_MSVC_VER, 1, 1910))
#define string_HAVE_NOEXCEPT                string_CPP11_140
#define string_HAVE_NULLPTR                 string_CPP11_100
#define string_HAVE_DEFAULT_FN_TPL_ARGS     string_CPP11_120
#define string_HAVE_EXPLICIT_CONVERSION     string_CPP11_120
#define string_HAVE_CHAR16_T                string_CPP11_000
#define string_HAVE_CHAR32_T                string_HAVE_CHAR16_T

// Presence of C++14 language features:

#define string_HAVE_CONSTEXPR_14            string_CPP14_000
#define string_HAVE_FREE_CBEGIN             string_CPP14_120

// Presence of C++17 language features:

#define string_HAVE_FREE_SIZE               string_CPP17_140
#define string_HAVE_NODISCARD               string_CPP17_000
#define string_HAVE_STRING_VIEW             string_CPP17_000

// Presence of C++20 language features:

#define string_HAVE_CHAR8_T                 string_CPP20_000

// Presence of C++ library features:

#define string_HAVE_REGEX                  (string_CPP11_000 && !string_BETWEEN(string_COMPILER_GNUC_VERSION, 1, 490))
#define string_HAVE_TYPE_TRAITS             string_CPP11_110

// Usage of C++ language features:

#if string_HAVE_CONSTEXPR_11
# define string_constexpr constexpr
#else
# define string_constexpr /*constexpr*/
#endif

#if string_HAVE_CONSTEXPR_14
# define string_constexpr14  constexpr
#else
# define string_constexpr14  /*constexpr*/
#endif

#if string_HAVE_EXPLICIT_CONVERSION
# define string_explicit  explicit
#else
# define string_explicit  /*explicit*/
#endif

#if string_HAVE_NOEXCEPT && !string_CONFIG_NO_EXCEPTIONS
# define string_noexcept noexcept
#else
# define string_noexcept /*noexcept*/
#endif

#if string_HAVE_NODISCARD
# define string_nodiscard [[nodiscard]]
#else
# define string_nodiscard /*[[nodiscard]]*/
#endif

#if string_HAVE_NULLPTR
# define string_nullptr nullptr
#else
# define string_nullptr NULL
#endif

#if string_HAVE_EXPLICIT_CONVERSION
# define string_explicit_cv explicit
#else
# define string_explicit_cv /*explicit*/
#endif

// Additional includes:

#include <cassert>

#include <algorithm>    // std::transform()
#include <iterator>
#include <locale>
#include <limits>
#include <string>
#include <tuple>
#include <vector>

#if string_HAVE_STRING_VIEW
# include <string_view>
#else
// # pragma message("string.hpp: Using internal nonstd::std17::string_view.")
#endif

#if string_CONFIG_PROVIDE_REGEX && string_HAVE_REGEX
# include <regex>
#endif

namespace nonstd {

//
// string details:
//

namespace string {

namespace detail {

// npos

#if string_CPP17_OR_GREATER
    static string_constexpr size_t npos = size_t(-1);
#elif string_CPP11_OR_GREATER
    enum : size_t { npos = size_t(-1) };
#else
    enum { npos = size_t(-1) };
#endif

} // namespace detail

namespace std14 {
} // namespace std14

namespace std17 {

#if string_HAVE_STRING_VIEW

using std::basic_string_view;

# if string_CONFIG_PROVIDE_CHAR_T
    using std::string_view;
# endif
# if string_CONFIG_PROVIDE_WCHAR_T
    using std::wstring_view;
# endif
# if string_CONFIG_PROVIDE_CHAR8_T
    using std::u8string_view;
# endif
# if string_CONFIG_PROVIDE_CHAR16_T
    using std::u16string_view;
# endif
# if string_CONFIG_PROVIDE_CHAR32_T
    using std::u32string_view;
# endif
# if string_CONFIG_PROVIDE_CHAR_T
    using std::u32string_view;
# endif

#else // string_HAVE_STRING_VIEW

// TODO: Local basic_string_view.

template
<
    class CharT,
    class Traits = std::char_traits<CharT>
>
class basic_string_view
{
public:
    // Member types:

    typedef Traits traits_type;
    typedef CharT  value_type;

    typedef CharT       * pointer;
    typedef CharT const * const_pointer;
    typedef CharT       & reference;
    typedef CharT const & const_reference;

    typedef const_pointer iterator;
    typedef const_pointer const_iterator;
    typedef std::reverse_iterator< const_iterator > reverse_iterator;
    typedef	std::reverse_iterator< const_iterator > const_reverse_iterator;

    typedef std::size_t     size_type;
    typedef std::ptrdiff_t  difference_type;

    // Constants:

#if string_CPP17_OR_GREATER
    static string_constexpr size_t npos = detail::npos;
#elif string_CPP11_OR_GREATER
    enum : size_t { npos = detail::npos };
#else
    enum { npos = detail::npos };
#endif

    // 24.4.2.1 Construction and assignment:

    string_constexpr basic_string_view() string_noexcept
        : data_( string_nullptr )
        , size_( 0 )
    {}

    string_constexpr basic_string_view( CharT const * s ) string_noexcept // non-standard noexcept
        : data_( s )
        , size_( Traits::length(s) )
    {}

    string_constexpr basic_string_view( CharT const * s, size_type count ) string_noexcept // non-standard noexcept
        : data_( s )
        , size_( count )
    {}

    string_constexpr basic_string_view( CharT const * b, CharT const * e ) string_noexcept // C++20, non-standard noexcept
        : data_( b )
        , size_( e - b )
    {}

    string_constexpr basic_string_view( std::basic_string<CharT> & s ) string_noexcept // non-standard noexcept
        : data_( s.data() )
        , size_( s.size() )
    {}

    string_constexpr basic_string_view( std::basic_string<CharT> const & s ) string_noexcept // non-standard noexcept
        : data_( s.data() )
        , size_( s.size() )
    {}

// #if string_HAVE_EXPLICIT_CONVERSION

    template< class Allocator >
    string_nodiscard string_explicit operator std::basic_string<CharT, Traits, Allocator>() const
    {
        return to_string( Allocator() );
    }

// #endif // string_HAVE_EXPLICIT_CONVERSION

#if string_CPP11_OR_GREATER

    template< class Allocator = std::allocator<CharT> >
    string_nodiscard std::basic_string<CharT, Traits, Allocator>
    to_string( Allocator const & a = Allocator() ) const
    {
        return std::basic_string<CharT, Traits, Allocator>( begin(), end(), a );
    }

#else

    string_nodiscard std::basic_string<CharT, Traits>
    to_string() const
    {
        return std::basic_string<CharT, Traits>( begin(), end() );
    }

    template< class Allocator >
    string_nodiscard std::basic_string<CharT, Traits, Allocator>
    to_string( Allocator const & a ) const
    {
        return std::basic_string<CharT, Traits, Allocator>( begin(), end(), a );
    }

#endif // string_CPP11_OR_GREATER

    string_nodiscard string_constexpr14 size_type find( basic_string_view v, size_type pos = 0 ) const string_noexcept  // (1)
    {
        return assert( v.size() == 0 || v.data() != string_nullptr )
            , pos >= size()
            ? npos
            : to_pos( std::search( cbegin() + pos, cend(), v.cbegin(), v.cend(), Traits::eq ) );
    }

    string_nodiscard string_constexpr14 size_type rfind( basic_string_view v, size_type pos = npos ) const string_noexcept  // (1)
    {
        if ( size() < v.size() )
        {
            return npos;
        }

        if ( v.empty() )
        {
            return (std::min)( size(), pos );
        }

        const_iterator last   = cbegin() + (std::min)( size() - v.size(), pos ) + v.size();
        const_iterator result = std::find_end( cbegin(), last, v.cbegin(), v.cend(), Traits::eq );

        return result != last ? size_type( result - cbegin() ) : npos;
    }

    string_nodiscard string_constexpr14 size_type find( CharT c, size_type pos = 0 ) const string_noexcept  // (2)
    {
        return find( basic_string_view( &c, 1 ), pos );
    }

    string_nodiscard string_constexpr size_type find_first_of( basic_string_view v, size_type pos = 0 ) const string_noexcept  // (1)
    {
        return pos >= size()
            ? npos
            : to_pos( std::find_first_of( cbegin() + pos, cend(), v.cbegin(), v.cend(), Traits::eq ) );
    }

    string_nodiscard string_constexpr size_type find_first_of( CharT c, size_type pos = 0 ) const string_noexcept  // (2)
    {
        return find_first_of( basic_string_view( &c, 1 ), pos );
    }

    string_nodiscard string_constexpr size_type find_last_of( basic_string_view v, size_type pos = npos ) const string_noexcept  // (1)
    {
        return empty()
            ? npos
            : pos >= size()
            ? find_last_of( v, size() - 1 )
            : to_pos( std::find_first_of( const_reverse_iterator( cbegin() + pos + 1 ), crend(), v.cbegin(), v.cend(), Traits::eq ) );
    }

    string_nodiscard string_constexpr size_type find_first_not_of( basic_string_view v, size_type pos = 0 ) const string_noexcept  // (1)
    {
        return pos >= size()
            ? npos
            : to_pos( std::find_if( cbegin() + pos, cend(), not_in_view( v ) ) );
    }

    string_nodiscard string_constexpr size_type find_last_not_of( basic_string_view v, size_type pos = npos ) const string_noexcept  // (1)
    {
        return empty()
            ? npos
            : pos >= size()
            ? find_last_not_of( v, size() - 1 )
            : to_pos( std::find_if( const_reverse_iterator( cbegin() + pos + 1 ), crend(), not_in_view( v ) ) );
    }

    string_nodiscard string_constexpr bool          empty()  const string_noexcept { return size_ == 0; }
    string_nodiscard string_constexpr size_type     size()   const string_noexcept { return size_; }
    string_nodiscard string_constexpr size_type     length() const string_noexcept { return size_; }
    string_nodiscard string_constexpr const_pointer data()   const string_noexcept { return data_; }

    string_nodiscard string_constexpr14 basic_string_view substr( size_type pos = 0, size_type n = npos ) const
    {
#if string_CONFIG_NO_EXCEPTIONS
        assert( pos <= size() );
#else
        if ( pos > size() )
        {
            throw std::out_of_range("string_view::substr()");
        }
#endif
        return basic_string_view( data() + pos, (std::min)( n, size() - pos ) );
    }

    string_nodiscard string_constexpr const_iterator begin()  const string_noexcept { return data_;         }
    string_nodiscard string_constexpr const_iterator end()    const string_noexcept { return data_ + size_; }

    string_nodiscard string_constexpr const_iterator cbegin() const string_noexcept { return begin(); }
    string_nodiscard string_constexpr const_iterator cend()   const string_noexcept { return end();   }

    string_nodiscard string_constexpr const_reverse_iterator rbegin()  const string_noexcept { return const_reverse_iterator( end() );   }
    string_nodiscard string_constexpr const_reverse_iterator rend()    const string_noexcept { return const_reverse_iterator( begin() ); }

    string_nodiscard string_constexpr const_reverse_iterator crbegin() const string_noexcept { return rbegin(); }
    string_nodiscard string_constexpr const_reverse_iterator crend()   const string_noexcept { return rend();   }

private:
    struct not_in_view
    {
        const basic_string_view v;

        string_constexpr explicit not_in_view( basic_string_view v_ ) : v( v_ ) {}

        string_nodiscard string_constexpr bool operator()( CharT c ) const
        {
            return npos == v.find_first_of( c );
        }
    };

    string_nodiscard string_constexpr size_type to_pos( const_iterator it ) const
    {
        return it == cend() ? npos : size_type( it - cbegin() );
    }

    string_nodiscard string_constexpr size_type to_pos( const_reverse_iterator it ) const
    {
        return it == crend() ? npos : size_type( crend() - it - 1 );
    }

private:
    const_pointer data_;
    size_type     size_;
};

#if string_CONFIG_PROVIDE_CHAR_T
typedef basic_string_view<char>      string_view;
#endif

#if string_CONFIG_PROVIDE_WCHAR_T
typedef basic_string_view<wchar_t>   wstring_view;
#endif

#if string_CONFIG_PROVIDE_CHAR8_T && string_HAVE_CHAR8_T
typedef basic_string_view<char8_t>  u8string_view;
#endif

#if string_CONFIG_PROVIDE_CHAR16_T
typedef basic_string_view<char16_t>  u16string_view;
#endif

#if string_CONFIG_PROVIDE_CHAR32_T
typedef basic_string_view<char32_t>  u32string_view;
#endif

template< typename T >
string_nodiscard inline size_t size( basic_string_view<T> const & sv )
{
    return sv.size();
}

#endif // string_HAVE_STRING_VIEW

} // namespace std17

namespace std20 {

// type identity, to establish non-deduced contexts in template argument deduction:

template< typename T >
struct type_identity
{
    typedef T type;
};

} // namespace std20

namespace std23 {
} // namespace std23

namespace detail {

//
// Utilities:
//

template< typename CharT >
string_nodiscard string_constexpr CharT nullchr() noexcept
{
    return 0;
}

#if string_HAVE_STRING_VIEW
    #define MK_DETAIL_TO_STRING_SV(T)               \
    string_nodiscard inline std::basic_string<T>    \
    to_string( std17::basic_string_view<T> sv )     \
    {                                               \
        return std::basic_string<T>( sv );          \
    }
#else
    #define MK_DETAIL_TO_STRING_SV(T)               \
    string_nodiscard inline std::basic_string<T>    \
    to_string( std17::basic_string_view<T> sv )     \
    {                                               \
        return std::basic_string<T>( sv.begin(), sv.end() );    \
    }
#endif

#if string_CONFIG_PROVIDE_CHAR_T
    MK_DETAIL_TO_STRING_SV( char )
#endif
#if string_CONFIG_PROVIDE_WCHAR_T
    MK_DETAIL_TO_STRING_SV( wchar_t )
#endif
#if string_CONFIG_PROVIDE_CHAR8_T
    MK_DETAIL_TO_STRING_SV( char8_t )
#endif
#if string_CONFIG_PROVIDE_CHAR16_T
    MK_DETAIL_TO_STRING_SV( char16_t )
#endif
#if string_CONFIG_PROVIDE_CHAR32_T
    MK_DETAIL_TO_STRING_SV( char32_t )
#endif

#undef MK_DETAIL_TO_STRING_SV

}  // namespace detail
}  // namespace string

// enable use of string-specific namespaces detail and stdxx:

using namespace string;
//
// Observers
//

// length()

#define string_MK_LENGTH(T) \
    string_nodiscard inline std::size_t length( std17::basic_string_view<T> text ) noexcept \
    { \
        return text.length(); \
    }\

// size()

#define string_MK_SIZE(T) \
    string_nodiscard inline std::size_t size( std17::basic_string_view<T> text ) noexcept \
    { \
        return text.size(); \
    }\

// is_empty()

#define string_MK_IS_EMPTY(T) \
    string_nodiscard inline bool is_empty( std17::basic_string_view<T> text ) noexcept \
    { \
        return text.empty(); \
    }\

//
// Searching:
//

namespace string {
namespace detail {

template< typename SeekT >
string_nodiscard std::size_t find_first( std17::string_view text, SeekT const & seek, std::size_t pos )
{
    return text.find( seek, pos );
}

} // namespace detail
} // namespace string

// find_first()

#define string_MK_FIND_FIRST(T) /*TODO: MK()*/

template< typename SeekT >
string_nodiscard std::size_t find_first( std17::string_view text, SeekT const & seek )
{
    return text.find( seek );
}

string_nodiscard inline std::size_t find_first( std17::string_view text, char seek )
{
#if string_CPP17_000
    return find_first( text, std::string( &seek, &seek + 1 ) );
#else
    return find_first( text, std17::string_view( &seek, &seek + 1 ) );
#endif
}

#if string_CONFIG_PROVIDE_REGEX && string_HAVE_REGEX

// find_first(regex)

string_nodiscard inline std::size_t find_first( std17::string_view text, std::regex const & re )
{
    std::match_results< std17::string_view::const_iterator > result;

    return std::regex_search( text.begin(), text.end(), result, re ) ? result.position() : detail::npos;
}

// find_first_re()

template< typename SeekT >
string_nodiscard std::size_t find_first_re( std17::string_view text, SeekT const & seek )
{
    return find_first( text, std::regex(seek) );
}

#endif // regex

// find_last()

#define string_MK_FIND_LAST(T) /*TODO: MK()*/

template< typename SeekT >
string_nodiscard std::size_t find_last( std17::string_view text, SeekT const & seek )
{
    return text.rfind( seek );
}

string_nodiscard inline std::size_t find_last( std17::string_view text, char seek )
{
#if string_CPP17_000
    return find_last( text, std::string( &seek, &seek + 1 ) );
#else
    return find_last( text, std17::string_view( &seek, &seek + 1 ) );
#endif
}

#if string_CONFIG_PROVIDE_REGEX && string_HAVE_REGEX

// find_last(regex): use std::regex_iterator?

string_nodiscard inline std::size_t find_last( std17::string_view text, std::regex const & re )
{
    auto elem_begin = std::regex_iterator<std17::string_view::const_iterator>( text.begin(), text.end(), re );
    auto elem_end   = std::regex_iterator<std17::string_view::const_iterator>();

    size_t last_pos = detail::npos;
    for (std::regex_iterator<std17::string_view::const_iterator> i = elem_begin; i != elem_end; ++i)
    {
        last_pos = i->position();
    }

    return last_pos;
}

// find_last_re()

template< typename SeekT >
string_nodiscard std::size_t find_last_re( std17::string_view text, SeekT const & seek )
{
    return find_last( text, std::regex(seek) );
}

#endif // regex

// find_first_of()

#define string_MK_FIND_FIRST_OF(T) /*TODO: MK()*/

template< typename SeekT >
string_nodiscard std::size_t find_first_of( std17::string_view text, SeekT const & seek )
{
    return text.find_first_of( seek );
}

#if string_CONFIG_PROVIDE_REGEX && string_HAVE_REGEX

// find_first_of(regex)

string_nodiscard inline std::size_t find_first_of( std17::string_view text, std::regex const & re )
{
    return find_first( text, re );
}

// find_first_of_re()

template< typename SeekT >
string_nodiscard inline std::size_t find_first_of_re( std17::string_view text, SeekT const & seek )
{
    return find_first_of( text, std::regex(seek) );
}

#endif // regex

// find_last_of()

#define string_MK_FIND_LAST_OF(T) /*TODO: MK()*/

template< typename SeekT >
string_nodiscard std::size_t find_last_of( std17::string_view text, SeekT const & seek )
{
    return text.find_last_of( seek );
}

#if string_CONFIG_PROVIDE_REGEX && string_HAVE_REGEX

// TODO: find_last_of(regex)

string_nodiscard inline std::size_t find_last_of( std17::string_view text, std::regex const & re )
{
    return find_last( text, re );
}

// find_last_of_re()

template< typename SeekT >
string_nodiscard inline std::size_t find_last_of_re( std17::string_view text, SeekT const & seek )
{
    return find_last_of( text, std::regex(seek) );
}

#endif // regex

// find_first_not_of()

#define string_MK_FIND_FIRST_NOT_OF(T) /*TODO: MK()*/

template< typename SeekT >
string_nodiscard std::size_t find_first_not_of( std17::string_view text, SeekT const & seek )
{
    return text.find_first_not_of( seek );
}

#if string_CONFIG_PROVIDE_REGEX && string_HAVE_REGEX

// Avoid signed/unsigned mismatch.

template< typename T >
size_t to_size( T value )
{
    return static_cast<size_t>( value );
}

// find_first_not_of(regex), optionally use find_first_of_([^regex])

string_nodiscard inline std::size_t find_first_not_of( std17::string_view text, std::regex const & re )
{
    std::match_results< std17::string_view::const_iterator > result;

    return std::regex_search( text.begin(), text.end(), result, re ) && result.position() == 0 && to_size(result.length()) < text.length()
        ? result.length() 
        : detail::npos;
}

// find_first_not_of_re()

template< typename SeekT >
string_nodiscard inline std::size_t find_first_not_of_re( std17::string_view text, SeekT const & seek )
{
    return find_first_not_of( text, std::regex(seek) );
}

#endif // regex

// find_last_not_of()

#define string_MK_FIND_LAST_NOT_OF(T) /*TODO: MK()*/

template< typename SeekT >
string_nodiscard std::size_t find_last_not_of( std17::string_view text, SeekT const & seek )
{
    return text.find_last_not_of( seek );
}

#if string_CONFIG_PROVIDE_REGEX && string_HAVE_REGEX

// TODO: find_last_not_of(regex), optionally use find_last_of_([^regex])

string_nodiscard inline std::size_t find_last_not_of( std17::string_view text, std::regex const & re )
{
#if 1
    return detail::npos;
#else
    auto elem_begin = std::regex_iterator<std17::string_view::const_iterator>( text.begin(), text.end(), re );
    auto elem_end   = std::regex_iterator<std17::string_view::const_iterator>();

    size_t last_pos = detail::npos;
    size_t prev_pos = 0;
    size_t last_len = 0;
    size_t prev_len = 0;
    for (std::regex_iterator<std17::string_view::const_iterator> i = elem_begin; i != elem_end; ++i)
    {
        prev_pos = last_pos;
        prev_len = last_len;
        last_pos = i->position();
        last_len = i->length();
    }

    std::cout << "\nfind_last_not_of pos:" << last_pos << " last_len:" << last_len << "\n";

    // TODO: add checks:
    return last_pos == detail::npos ? 0 : last_pos - 1;
#endif
}

// find_first_not_of_re()

template< typename SeekT >
string_nodiscard inline std::size_t find_last_not_of_re( std17::string_view text, SeekT const & seek )
{
    return find_last_not_of( text, std::regex(seek) );
}

#endif // regex

// TODO: ??? find_if()

// TODO: ??? find_if_not()

// contains() - C++23

#define string_MK_CONTAINS(T) /*TODO: MK()*/

template< typename SeekT >
string_nodiscard bool contains( std17::string_view text, SeekT const & seek )
{
#if string_CPP23_OR_GREATER
    return text.contains( seek );
#else
    return detail::npos != find_first(text, seek);
#endif
}

#if string_CONFIG_PROVIDE_REGEX && string_HAVE_REGEX

// contains(regex)

string_nodiscard inline bool contains( std17::string_view text, std::regex const & re )
{
    return std::regex_search( text.begin(), text.end(), re );
}

// contains_re()

#define string_MK_CONTAINS_RE(T) /*TODO: MK()*/

template< typename SeekT >
string_nodiscard bool contains_re( std17::string_view text, SeekT const & seek )
{
    return contains( text, std::regex(seek) );
}

#endif // regex

// starts_with() - C++20

#define string_MK_STARTS_WITH(T) /*TODO: MK()*/

template< typename SeekT >
string_nodiscard bool starts_with( std17::string_view text, SeekT const & seek )
{
#if string_CPP20_OR_GREATER
    return text.starts_with( seek );
#else
    std17::string_view look( seek );

    if ( size( look ) > size( text ) )
    {
        return false;
    }
    return std::equal( look.begin(), look.end(), text.begin() );
#endif
}

string_nodiscard inline bool starts_with( std17::string_view text, char seek )
{
#if string_CPP17_000
    return starts_with( text, std::string( &seek, &seek + 1) );
#else
    return starts_with( text, std17::string_view( &seek, &seek + 1) );
#endif
}

#if string_CONFIG_PROVIDE_REGEX && string_HAVE_REGEX

string_nodiscard inline bool starts_with( std17::string_view text, std::regex const & re )
{
    return 0 == find_first( text, re );
}

// starts_with_re()

#define string_MK_STARTS_WITH_RE(T) /*TODO: MK()*/

template< typename SeekT >
string_nodiscard bool starts_with_re( std17::string_view text, SeekT const & seek )
{
    return 0 == find_first_re( text, seek );
}

#endif // regex

// ends_with() - C++20

#define string_MK_ENDS_WITH(T) /*TODO: MK()*/

template< typename SeekT >
string_nodiscard bool ends_with( std17::string_view text, SeekT const & seek )
{
#if string_CPP20_OR_GREATER
    return text.ends_with( seek );
#else
    std17::string_view look( seek );

    if ( size( look ) > size( text ) )
    {
        return false;
    }
    return std::equal( look.rbegin(), look.rend(), text.rbegin() );
#endif
}

string_nodiscard inline bool ends_with( std17::string_view text, char seek )
{
#if string_CPP17_000
    return ends_with( text, std::string( &seek, &seek + 1) );
#else
    return ends_with( text, std17::string_view( &seek, &seek + 1) );
#endif
}

#if string_CONFIG_PROVIDE_REGEX && string_HAVE_REGEX

string_nodiscard inline bool ends_with( std17::string_view text, std::regex const & re )
{
    auto elem_begin = std::regex_iterator<std17::string_view::const_iterator>( text.begin(), text.end(), re );
    auto elem_end   = std::regex_iterator<std17::string_view::const_iterator>();

    size_t last_pos = detail::npos;
    size_t last_len = 0;
    for (std::regex_iterator<std17::string_view::const_iterator> i = elem_begin; i != elem_end; ++i)
    {
        last_pos = i->position();
        last_len = i->length();
    }

    return text.length() == last_pos + last_len;
}

// ends_with_re()

#define string_MK_ENDS_WITH_RE(T) /*TODO: MK()*/

template< typename SeekT >
string_nodiscard bool ends_with_re( std17::string_view text, SeekT const & seek )
{
    return ends_with( text, std::regex(seek) );
}

#endif // regex

//
// Modifiers:
//

namespace string {
namespace detail {

    // Transform case (character):

template< typename CharT >
string_nodiscard CharT to_lowercase( CharT chr )
{
    return std::tolower( chr, std::locale() );
}

template< typename CharT >
string_nodiscard CharT to_uppercase( CharT chr )
{
    return std::toupper( chr, std::locale() );
}

// Transform case; serve both CharT* and StringT&:

template< typename CharT, typename Fn >
string_nodiscard std::basic_string<CharT> to_case( std::basic_string<CharT> text, Fn fn ) noexcept
{
    std::transform(
        std::begin( text ), std::end( text )
        , std::begin( text )
        , fn
    );
    return text;
}

} // namespace detail
} // namespace string

// to_lowercase()
// to_uppercase()

// template string_nodiscard std::basic_string<char> to_lowercase( std17::basic_string_view<char> text ) noexcept;

#define string_MK_TO_CASE_CHAR(T, Function) \
    string_nodiscard inline T to_ ## Function( T chr ) noexcept \
    { \
        return detail::to_ ## Function<T>( chr ); \
    }\

#define string_MK_TO_CASE_STRING(T, Function) \
    string_nodiscard inline std::basic_string<T> to_ ## Function( std17::basic_string_view<T> text ) noexcept \
    { \
        return detail::to_case( std::basic_string<T>(text), detail::to_ ## Function<T> ); \
    }\

// template< typename StringT >
// inline StringT const default_strip_set()
// {
//     return " \t\n";
// }

// strip_left()

#define string_MK_STRIP_LEFT(T) /*TODO: MK()*/

template< typename SetT >
string_nodiscard std::string
strip_left( std17::string_view text, SetT const & set )
{
    return std::string( text ).erase( 0, text.find_first_not_of( set ) );
}

#if string_CONFIG_PROVIDE_REGEX && string_HAVE_REGEX

string_nodiscard std::string inline
strip_left( std::string text, std::regex const & re )
{
    return text.erase( 0, find_first_not_of( text, re ) );
}

template< typename SetT >
string_nodiscard std::string
strip_left_re( std::string text, SetT const & set )
{
    return strip_left( text, std::regex( set ) );
}

#endif // regex

// strip_right()

#define string_MK_STRIP_RIGHT(T) /*TODO: MK()*/

template< typename SetT >
string_nodiscard std::string
strip_right( std17::string_view text, SetT const & set )
{
    return std::string( text ).erase( text.find_last_not_of( set ) + 1 );
}

#if string_CONFIG_PROVIDE_REGEX && string_HAVE_REGEX

string_nodiscard std::string inline
strip_right( std::string text, std::regex const & re )
{
    return text.erase( 0, find_last_not_of( text, re ) );
}

template< typename SetT >
string_nodiscard std::string
strip_right_re( std::string text, SetT const & set )
{
    return strip_right( text, std::regex( set ) );
}

#endif // regex

// strip()

#define string_MK_STRIP(T) /*TODO: MK()*/

template< typename SetT >
string_nodiscard std::string
strip( std17::string_view text, SetT const & set )
{
    return strip_left( strip_right( std::string(text), set ), set );
}

#if string_CONFIG_PROVIDE_REGEX && string_HAVE_REGEX

string_nodiscard std::string inline
strip( std::string text, std::regex const & re )
{
    return strip_left( strip_right( text, re ), re );
}

template< typename SetT >
string_nodiscard std::string
strip_re( std::string text, SetT const & set )
{
    return strip( text, std::regex( set ) );
}

#endif // regex

// replace_all()

namespace string {
namespace detail {

template< typename T, typename WithT >
std::string replace_all( std17::basic_string_view<T> text, std17::basic_string_view<T> what, WithT const & with )
{
    std::basic_string<T> result( text );

    if ( with == what )
        return result;

    for ( auto pos = detail::find_first( result, what, 0 ) ;; )
    {
        pos = detail::find_first( result, what, pos );

        if ( pos == std::string::npos )
            break;

        result.replace( pos, what.length(), with );
    }
    return result;
}

} // detail
} // namespace string

#define string_MK_REPLACE_ALL(T) /*TODO: MK()*/

template< typename WithT >
std::string replace_all( std17::string_view text, std17::string_view what, WithT const & with )
{
    return detail::replace_all( text, what, with );
}

#if string_CONFIG_PROVIDE_REGEX && string_HAVE_REGEX

template< typename WithT >
string_nodiscard std::string
replace_all( std::string text, std::regex const & re, WithT const & with )
{
    return std::regex_replace( text, re, with );
}

template< typename WhatT, typename WithT >
string_nodiscard std::string
replace_all_re( std::string text, WhatT const & what, WithT const & with )
{
    return std::regex_replace( text, std::regex(what), with );
}

#endif // regex

// replace_first()

#define string_MK_REPLACE_FIRST(T) /*TODO: MK()*/

template< typename WithT >
string_nodiscard std::string
replace_first( std17::string_view text, std17::string_view what, WithT const & with )
{
    std::string result( text );

    const auto pos = find_first( result, what );

    return pos != std::string::npos 
        ? result.replace( pos, what.length(), with )
        : "";
}

#if string_CONFIG_PROVIDE_REGEX && string_HAVE_REGEX

template< typename WithT >
string_nodiscard std::string
replace_first( std::string text, std::regex const & re, WithT const & with )
{
    return std::regex_replace( text, re, with, std::regex_constants::format_first_only );
}

template< typename WhatT, typename WithT >
string_nodiscard std::string
replace_first_re( std::string text, WhatT const & what, WithT const & with )
{
    return replace_first( text, std::regex( what ), with );
}

#endif // regex

// replace_last()

#define string_MK_REPLACE_LAST(T) /*TODO: MK()*/

template< typename WithT >
string_nodiscard std::string
replace_last( std17::string_view text,std17::string_view what, WithT const & with )
{
    std::string result( text );

    const auto pos = find_last( result, what );

    return pos != std::string::npos 
        ? result.replace( pos, what.length(), with )
        : "";
}

//
// Joining, splitting:
//

// append()

#define string_MK_APPEND(T) /*TODO: MK()*/

template< typename TailT >
string_nodiscard std::string
append( std17::string_view text, TailT const & tail )
{
#if string_CPP20_000
    return std::string( text ).append( tail );     // requires std::string_view, but using nonstd::string_view with C++17
#else
    return std::string( text ) + std::string(tail);
#endif
}

// substring()

#define string_MK_SUBSTRING(T) /*TODO: MK()*/

string_nodiscard inline std::string
substring( std17::string_view text, size_t pos = 0, size_t count = detail::npos )
{
    return std::string( text ).substr( pos, count );
}

#if string_CONFIG_PROVIDE_REGEX && string_HAVE_REGEX

namespace string {
namespace detail {

string_nodiscard inline std::string
substring( std17::string_view text, std::regex const & re )
{
    std::match_results< std17::string_view::const_iterator > result;

    return std::regex_search( text.begin(), text.end(), result, re )
        ? to_string( text.substr( result.position(), result.length() ) )
        : std::string{};
}

} // namespace detail
} // namespace string

string_nodiscard inline std::string
substring( std17::string_view text, std::regex const & re )
{
    return detail::substring( text, re );
}

// substring_re()

string_nodiscard inline std::string
substring_re( std17::string_view text, char const * re )
{
    return substring( text, std::regex(re) );
}

#endif // regex

// join()

namespace string {
namespace detail {

template< typename Coll, typename SepT, typename Result >
string_nodiscard Result
join( Coll const & coll, SepT const & sep, Result result )
{
    typename Coll::const_iterator const coll_begin = coll.cbegin();
    typename Coll::const_iterator const coll_end   = coll.cend();

    typename Coll::const_iterator pos = coll_begin;

    if ( pos != coll_end )
    {
        result = append( result, *pos++ );
    }

    for ( ; pos != coll_end; ++pos )
    {
        result = append( append( result,  sep ), *pos );
    }

    return result;
}
} // namespace detail
} // namespace string

#define string_MK_JOIN(T) /*TODO: MK()*/

template< typename Coll, typename SepT >
string_nodiscard std::string
join( Coll const & coll, SepT const & sep )
{
    return detail::join( coll, sep, std::string() );
}

// TODO: split

// split():

// Various kinds of delimiters:
// - literal_delimiter - a single string delimiter
// - any_of_delimiter - any of given characters as delimiter
// - fixed_delimiter - fixed length delimiter
// - limit_delimiter - not implemented
// - regex_delimiter - regular expression delimiter
// - char_delimiter - single-char delimiter

template< typename CharT >
std17::basic_string_view<CharT> basic_delimiter_end(std17::basic_string_view<CharT> sv)
{
    return std17::basic_string_view<CharT>(sv.data() + sv.size(), size_t(0));
}

// a single string delimiter:

template< typename CharT >
class basic_literal_delimiter
{
    const std::basic_string<CharT> delimiter_;
    mutable size_t found_;

public:
    explicit basic_literal_delimiter(std17::basic_string_view<CharT> sv)
        : delimiter_(detail::to_string(sv))
        , found_(0)
    {}

    size_t length() const
    {
        return delimiter_.length();
    }

    std17::basic_string_view<CharT> operator()(std17::basic_string_view<CharT> text, size_t pos) const
    {
        return find(text, pos);
    }

    std17::basic_string_view<CharT> find(std17::basic_string_view<CharT> text, size_t pos) const
    {
        // out of range, return 'empty' if last match was at end of text, else return 'done':
        if ( pos >= text.length())
        {
            // last delimiter match at end of text?
            if ( found_ != text.length() - 1 )
                return basic_delimiter_end(text);

            found_ = 0;
            return text.substr(text.length() - 1, 0);
        }

        // a single character at a time:
        if (0 == delimiter_.length())
        {
            return text.substr(pos, 1);
        }

        found_ = text.find(delimiter_, pos);

        // at a delimiter, or searching past the last delimiter:
        if (found_ == pos || pos == text.length())
        {
            return text.substr(pos, 0);
        }

        // no delimiter found:
        if (found_ == std17::basic_string_view<CharT>::npos)
        {
            // return remaining text:
            if (pos < text.length())
            {
                return text.substr(pos);
            }

            // nothing left, return 'done':
            return basic_delimiter_end(text);
        }

        // delimited text:
        return text.substr(pos, found_ - pos);
    }
};

// any of given characters as delimiter:

template< typename CharT >
class basic_any_of_delimiter
{
    const std::basic_string<CharT> delimiters_;

public:
    explicit basic_any_of_delimiter(std17::basic_string_view<CharT> sv)
        : delimiters_(detail::to_string(sv)) {}

    size_t length() const
    {
        return (std::min)( size_t(1), delimiters_.length());
    }

    std17::basic_string_view<CharT> operator()(std17::basic_string_view<CharT> text, size_t pos) const
    {
        return find(text, pos);
    }

    std17::basic_string_view<CharT> find(std17::basic_string_view<CharT> text, size_t pos) const
    {
        // out of range, return 'done':
        if ( pos > text.length())
            return basic_delimiter_end(text);

        // a single character at a time:
        if (0 == delimiters_.length())
        {
            return text.substr(pos, 1);
        }

        size_t found = text.find_first_of(delimiters_, pos);

        // at a delimiter, or searching past the last delimiter:
        if (found == pos || (pos == text.length()))
        {
            return std17::basic_string_view<CharT>();
        }

        // no delimiter found:
        if (found == std17::basic_string_view<CharT>::npos)
        {
            // return remaining text:
            if (pos < text.length())
            {
                return text.substr(pos);
            }

            // nothing left, return 'done':
            return basic_delimiter_end(text);
        }

        // delimited text:
        return text.substr(pos, found - pos);
    }
};

// fixed length delimiter:

template< typename CharT >
class basic_fixed_delimiter
{
    size_t len_;

public:
    explicit basic_fixed_delimiter(size_t len)
        : len_(len) {}

    size_t length() const
    {
        return 0;
    }

    std17::basic_string_view<CharT> operator()(std17::basic_string_view<CharT> text, size_t pos) const
    {
        return find(text, pos);
    }

    std17::basic_string_view<CharT> find(std17::basic_string_view<CharT> text, size_t pos) const
    {
        // out of range, return 'done':
        if ( pos > text.length())
            return basic_delimiter_end(text);

        // current slice:
        return text.substr(pos, len_);
    }
};

// TODO limit_delimiter - Delimiter template would take another Delimiter and a size_t limiting
// the given delimiter to matching a max numbers of times. This is similar to the 3rd argument to
// perl's split() function.

template< typename CharT, typename DelimiterT >
class basic_limit_delimiter;

// regular expression delimiter:

#if string_CONFIG_PROVIDE_REGEX && string_HAVE_REGEX

template< typename CharT >
class basic_regex_delimiter
{
    std::regex     delimiter_re_;               // regular expression designating delimiters
    size_t         delimiter_len_;              // length of regular expression
    mutable size_t matched_delimiter_length_;   // length of the actually matched delimiter
    mutable bool   trailing_delimiter_seen;     // whether to provide last empty result

public:
    explicit basic_regex_delimiter(std17::basic_string_view<CharT> sv)
        : delimiter_re_(detail::to_string(sv))
        , delimiter_len_(sv.length())
        , matched_delimiter_length_(0u)
        , trailing_delimiter_seen(false)
    {}

    size_t length() const
    {
        return matched_delimiter_length_;
    }

    std17::basic_string_view<CharT> operator()(std17::basic_string_view<CharT> text, size_t pos) const
    {
        return find(text, pos);
    }

    std17::basic_string_view<CharT> find(std17::basic_string_view<CharT> text, size_t pos) const
    {
        // trailing empty entry:
        // TODO this feels like a hack, don't know any better at this moment
        if (trailing_delimiter_seen)
        {
            trailing_delimiter_seen = false;
            return std17::basic_string_view<CharT>();
        }

        // out of range, return 'done':
        if ( pos > text.length())
            return basic_delimiter_end(text);

        // a single character at a time:
        if (0 == delimiter_len_)
        {
            return text.substr(pos, 1);
        }

        std::smatch m;
        std::basic_string<CharT> s = text.substr(pos);

        const bool found = std::regex_search(s, m, delimiter_re_);

        matched_delimiter_length_ = m.length();

        // no delimiter found:
        if (!found)
        {
            // return remaining text:
            if (pos < text.length())
            {
                return text.substr(pos);
            }

            // nothing left, return 'done':
            return basic_delimiter_end(text);
        }

        // at a trailing delimiter, remember for next round:
        else if ((size_t(m.position()) == s.length() - 1))
        {
            trailing_delimiter_seen = true;
        }

        // delimited text, the match in the input string:
        return text.substr(pos, m.position());
    }
};

#endif // string_HAVE_REGEX

// single-char delimiter:

template< typename CharT >
class basic_char_delimiter
{
    CharT c_;

public:
    explicit basic_char_delimiter(CharT c)
        : c_(c) {}

    size_t length() const
    {
        return 1;
    }

    std17::basic_string_view<CharT> operator()(std17::basic_string_view<CharT> text, size_t pos) const
    {
        return find(text, pos);
    }

    std17::basic_string_view<CharT> find(std17::basic_string_view<CharT> text, size_t pos) const
    {
        size_t found = text.find(c_, pos);

        // nothing left, return 'done':
        if (found == std17::basic_string_view<CharT>::npos)
            return basic_delimiter_end(text);

        // the c_ in the input string:
        return text.substr(found, 1);
    }
};

 // typedefs:

#if string_CONFIG_PROVIDE_CHAR_T
typedef basic_literal_delimiter< char  >  literal_delimiter;
typedef basic_any_of_delimiter<  char  >  any_of_delimiter;
typedef basic_fixed_delimiter<   char  >  fixed_delimiter;
typedef basic_char_delimiter<    char  >  char_delimiter;
// typedef basic_limit_delimiter<   char  >  limit_delimiter;
# if string_CONFIG_PROVIDE_REGEX
typedef basic_regex_delimiter<   char  >  regex_delimiter;
# endif
#endif

#if string_CONFIG_PROVIDE_WCHAR_T
typedef basic_literal_delimiter<wchar_t> wliteral_delimiter;
typedef basic_any_of_delimiter< wchar_t> wany_of_delimiter;
typedef basic_fixed_delimiter<  wchar_t> wfixed_delimiter;
typedef basic_char_delimiter<   wchar_t> wchar_t_delimiter;
// typedef basic_limit_delimiter<  wchar_t> wlimit_delimiter;
# if string_CONFIG_PROVIDE_REGEX && string_HAVE_REGEX
typedef basic_regex_delimiter<  wchar_t> wregex_delimiter;
# endif
#endif

#if string_CONFIG_PROVIDE_CHAR8_T && string_HAVE_CHAR8_T
typedef basic_literal_delimiter<char8_t> u16literal_delimiter;
typedef basic_any_of_delimiter< char8_t> u16any_of_delimiter;
typedef basic_fixed_delimiter<  char8_t> u16fixed_delimiter;
typedef basic_char_delimiter<   char8_t> u16char_delimiter;
// typedef basic_limit_delimiter<  char8_t> u16limit_delimiter;
# if string_CONFIG_PROVIDE_REGEX && string_HAVE_REGEX
typedef basic_regex_delimiter<  char8_t> u16regex_delimiter;
# endif
#endif

#if string_CONFIG_PROVIDE_CHAR16_T
typedef basic_literal_delimiter<char16_t> u16literal_delimiter;
typedef basic_any_of_delimiter< char16_t> u16any_of_delimiter;
typedef basic_fixed_delimiter<  char16_t> u16fixed_delimiter;
typedef basic_char_delimiter<   char16_t> u16char_delimiter;
// typedef basic_limit_delimiter<  char16_t> u16limit_delimiter;
# if string_CONFIG_PROVIDE_REGEX && string_HAVE_REGEX
typedef basic_regex_delimiter<  char16_t> u16regex_delimiter;
# endif
#endif

#if string_CONFIG_PROVIDE_CHAR32_T
typedef basic_literal_delimiter<char32_t> u32literal_delimiter;
typedef basic_any_of_delimiter< char32_t> u32any_of_delimiter;
typedef basic_fixed_delimiter<  char32_t> u32fixed_delimiter;
typedef basic_char_delimiter<   char32_t> u32char_delimiter;
// typedef basic_limit_delimiter<  char32_t> u32limit_delimiter;
# if string_CONFIG_PROVIDE_REGEX && string_HAVE_REGEX
typedef basic_regex_delimiter<  char32_t> u32regex_delimiter;
# endif
#endif

// split():

namespace string {
namespace detail {

// free function length(), for delimiter:

template< typename Coll >
string_nodiscard inline size_t length( Coll const & coll )
{
    return coll.length();
}

template< typename CharT, typename Delimiter >
std::vector< std17::basic_string_view<CharT> >
split( std17::basic_string_view<CharT> text, Delimiter delimiter, size_t Nsplit )
{
    std::vector< std17::basic_string_view<CharT> > result;

    size_t pos = 0;
    size_t cnt = 1; // for Nsplit

    for( std17::basic_string_view<CharT> sv = delimiter(text, pos); sv.cbegin() != text.cend(); sv = delimiter(text, pos), ++cnt )
    {
        if ( cnt >= Nsplit )
        {
            result.push_back( text.substr(pos) );   // push tail:
            break;
        }

        result.push_back(sv);
        pos = (sv.end() - text.begin()) + length(delimiter);
    }

    return result;
}

} // namespace detail
} // namespace string

// split -> vector

#define string_MK_SPLIT(T) /*TODO: MK()*/

template< typename CharT, typename Delimiter >
string_nodiscard std::vector< std17::string_view >
split( std17::string_view text, Delimiter delimiter, int count = std::numeric_limits<int>::max() )
{
    return detail::split( text, delimiter, count );
}

#if string_CONFIG_PROVIDE_CHAR_T
template<typename Delimiter> string_nodiscard std::vector< std17::string_view>
split( std17::string_view text, Delimiter delimiter, int count = std::numeric_limits<int>::max() )
{
    return detail::split(text, delimiter, count );
}

string_nodiscard inline std::vector<std17::string_view>
split( std17::string_view text, char const * d, int count = std::numeric_limits<int>::max() )
{
    return detail::split(text, literal_delimiter(d), count );
}

#if 0
string_nodiscard inline std::vector<std17::string_view>
rsplit( std17::string_view text, char const * d, int count = std::numeric_limits<int>::max() )
{
    return detail::split(text, reverse_literal_delimiter(d), count );
}
#endif
#endif

#if string_CONFIG_PROVIDE_WCHAR_T
template<typename Delimiter> string_nodiscard std::vector<std17::wstring_view>
split( std17::wstring_view text, Delimiter delimiter, int count = std::numeric_limits<int>::max() )
{
    return detail::split(text, delimiter, count );
}

string_nodiscard inline std::vector<std17::wstring_view>
split( std17::wstring_view text, wchar_t const * d, int count = 0 )
{
    return detail::split(text, wliteral_delimiter(d), count );
}
#endif

#if string_CONFIG_PROVIDE_CHAR8_T
template<typename Delimiter> string_nodiscard std::vector<std17::u8string_view>
split( std17::u8string_view text, Delimiter delimiter, int count = std::numeric_limits<int>::max() )
{
    return detail::split(text, delimiter, count );
}

string_nodiscard inline std::vector<std17::u8string_view>
split( std17::u8string_view text, char8_t const * d, int count = 0 )
{
    return detail::split(text, u8literal_delimiter(d), count );
}
#endif

#if string_CONFIG_PROVIDE_CHAR16_T
template<typename Delimiter> string_nodiscard std::vector<std17::u16string_view>
split( std17::u16string_view text, Delimiter delimiter, int count = std::numeric_limits<int>::max() )
{
    return detail::split(text, delimiter, count );
}

string_nodiscard inline std::vector<std17::u16string_view>
split( std17::u16string_view text, char16_t const * d, int count = 0 )
{
    return detail::split(text, u16literal_delimiter(d), count );
}
#endif

#if string_CONFIG_PROVIDE_CHAR32_T
template<typename Delimiter> string_nodiscard std::vector<std17::u32string_view>
split( std17::u32string_view text, Delimiter delimiter, int count = std::numeric_limits<int>::max() )
{
    return detail::split(text, delimiter, count );
}

inline string_nodiscard std::vector<std17::u32string_view>
split( std17::u32string_view text, char32_t const * d, int count = 0 )
{
    return detail::split(text, u32literal_delimiter(d), count );
}
#endif

#if string_CONFIG_PROVIDE_CHAR_T

// split_left -> tuple

template<typename Delimiter> string_nodiscard auto
split_left( std17::string_view const & text, Delimiter delimiter ) -> std::tuple<std17::string_view, std17::string_view>
{
    auto const result = split( text, delimiter, 2 );

    return { result[0], result[1] };
}

string_nodiscard inline auto
split_left(  std17::string_view text, char const * d ) -> std::tuple<std17::string_view, std17::string_view>
{
    return split_left( text, literal_delimiter(d) );
}

// TODO: split_right -> tuple

// Split string at given separator character, starting at right.

string_nodiscard inline auto
split_right(  std17::string_view , char const * ) -> std::tuple<std17::string_view, std17::string_view>
// split_right(  std17::string_view text, char const * d ) -> std::tuple<std17::string_view, std17::string_view>
{
    return { "TODO", "TODO" };
    // return split_right( text, reverse_literal_delimiter(d) );
}

#endif // string_CONFIG_PROVIDE_CHAR_T

//
// Define requested functions:
//

#if string_CONFIG_PROVIDE_CHAR_T

string_MK_LENGTH        ( char )
string_MK_SIZE          ( char )
string_MK_IS_EMPTY      ( char )
string_MK_FIND_FIRST    ( char )
string_MK_FIND_LAST     ( char )
string_MK_FIND_FIRST_OF ( char )
string_MK_FIND_LAST_OF  ( char )
string_MK_FIND_FIRST_NOT_OF( char )
string_MK_FIND_LAST_NOT_OF ( char )
string_MK_CONTAINS      ( char )
string_MK_STARTS_WITH   ( char )
string_MK_ENDS_WITH     ( char )
string_MK_TO_CASE_CHAR  ( char, lowercase )
string_MK_TO_CASE_CHAR  ( char, uppercase )
string_MK_TO_CASE_STRING( char, lowercase )
string_MK_TO_CASE_STRING( char, uppercase )
string_MK_STRIP_LEFT    ( char )
string_MK_STRIP_RIGHT   ( char )
string_MK_STRIP         ( char )
string_MK_REPLACE_ALL   ( char )
string_MK_REPLACE_FIRST ( char )
string_MK_REPLACE_LAST  ( char )
string_MK_APPEND        ( char )
string_MK_JOIN          ( char )
string_MK_SPLIT         ( char )
// ...
#endif

#if string_CONFIG_PROVIDE_WCHAR_T

string_MK_LENGTH        ( wchar_t )
string_MK_SIZE          ( wchar_t )
string_MK_IS_EMPTY      ( wchar_t )
string_MK_TO_CASE_CHAR  ( wchar_t, lowercase )
string_MK_TO_CASE_CHAR  ( wchar_t, uppercase )
string_MK_TO_CASE_STRING( wchar_t, lowercase )
string_MK_TO_CASE_STRING( wchar_t, uppercase )
// ...
#endif

#if string_CONFIG_PROVIDE_CHAR8_T && string_HAVE_CHAR8_T

string_MK_LENGTH        ( char8_t )
string_MK_SIZE          ( char8_t )
string_MK_IS_EMPTY      ( char8_t )
string_MK_TO_CASE_CHAR  ( char8_t, lowercase )
string_MK_TO_CASE_CHAR  ( char8_t, uppercase )
string_MK_TO_CASE_STRING( char8_t, lowercase )
string_MK_TO_CASE_STRING( char8_t, uppercase )
// ...
// #undef string_MK_...
#endif

#if string_CONFIG_PROVIDE_CHAR16_T

string_MK_LENGTH  ( char16_t )
string_MK_SIZE    ( char16_t )
string_MK_IS_EMPTY( char16_t )
// string_MK_TO_CASE( char16_t, lowercase )    // doesn't work
// string_MK_TO_CASE( char16_t, uppercase  )   // doesn't work
// ...
// #undef string_MK_...
#endif

#if string_CONFIG_PROVIDE_CHAR32_T

string_MK_LENGTH  ( char32_t )
string_MK_SIZE    ( char32_t )
string_MK_IS_EMPTY( char32_t )
// string_MK_TO_CASE( char32_t, lowercase )    // doesn't work
// string_MK_TO_CASE( char32_t, uppercase  )   // doesn't work
// ...
// #undef string_MK_...
#endif

#undef string_MK_LENGTH
#undef string_MK_SIZE
#undef string_MK_IS_EMPTY
#undef string_MK_TO_CASE

} // namespace nonstd

#endif  // NONSTD_STRING_BARE_HPP

/*
 * end of file
 */
