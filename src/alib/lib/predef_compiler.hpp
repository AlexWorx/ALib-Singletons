// #################################################################################################
//  ALib C++ Library
//
//  Define code selection symbols for ALib features from given compiler symbols.
//
//  Copyright 2013-2019 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
#ifndef HPP_ALIB_LIB_PREDEF_COMPILER
#define HPP_ALIB_LIB_PREDEF_COMPILER 1

// is a Doxygen run?
#if defined(ALIB_DOCUMENTATION_PARSER)
    #define     ALIB_DOCUMENTATION_PARSER 1
#else
    #define     ALIB_DOCUMENTATION_PARSER 0
    #define     DOX_MARKER( marker )
#endif


// Debug or release compilation
#if defined(ALIB_DEBUG)
    #error "Code selector symbol ALIB_DEBUG must not be set from outside. Use postfix '_ON' or '_OFF' for compiler symbols."
#endif

#if defined(ALIB_DEBUG_OFF) && defined(ALIB_DEBUG_ON)
    #error "Compiler symbols ALIB_DEBUG_OFF / ALIB_DEBUG_ON are both set (contradiction)."
#endif

#if !defined(ALIB_DEBUG_OFF) && ( defined(ALIB_DEBUG_ON) || !defined(NDEBUG) || defined(_DEBUG) || defined(DEBUG) )
    #define ALIB_DEBUG 1
#else
    #define ALIB_DEBUG 0
#endif

#if ALIB_DEBUG
    #define ALIB_DBG(...)    __VA_ARGS__
    #define ALIB_REL(...)
    #define ALIB_REL_DBG(releaseCode, ...)    __VA_ARGS__
#else
    #define ALIB_DBG(...)
    #define ALIB_REL(...)    __VA_ARGS__
    #define ALIB_REL_DBG(releaseCode, ...)    releaseCode
#endif

// C++ standard
#if defined ( _MSC_VER )  &&  _MSC_VER < 1600 // VS 2010 == VC10 == _MSC_VER 1600
#   error "ALib needs C++ 11. Compilation aborted"
#endif
#if defined(_MSVC_LANG)
#     if  _MSVC_LANG == 201103L
#     define  ALIB_CPP14   0
#     define  ALIB_CPP17   0
#   elif  _MSVC_LANG == 201402L
#     define  ALIB_CPP14   1
#     define  ALIB_CPP17   0
#   elif _MSVC_LANG >= 201703L
#     define  ALIB_CPP14   1
#     define  ALIB_CPP17   1
#   endif
#else
#     if   __cplusplus < 201103L
#      error "ALib needs C++ 11. Compilation aborted"
#   elif   __cplusplus == 201103L
#     define  ALIB_CPP14   0
#     define  ALIB_CPP17   0
#   elif __cplusplus == 201402L
#     define  ALIB_CPP14   1
#     define  ALIB_CPP17   0
#   elif __cplusplus >= 201703L
#     define  ALIB_CPP14   1
#     define  ALIB_CPP17   1
#   endif
#endif

#if ALIB_CPP14
#   define ALIB_CPP14_CONSTEXPR     constexpr
#   define ALIB_CPP14_REL_CONSTEXPR constexpr
#else
#   define ALIB_CPP14_CONSTEXPR
#   if ALIB_DEBUG
#      define ALIB_CPP14_REL_CONSTEXPR
#   else
#      define ALIB_CPP14_REL_CONSTEXPR constexpr
#   endif
#endif

#if ALIB_CPP17
#   define ALIB_CPP17_CONSTEXPR     constexpr
#   define ALIB_CPP17_REL_CONSTEXPR constexpr
#else
#   define ALIB_CPP17_CONSTEXPR
#   if ALIB_DEBUG
#      define ALIB_CPP17_REL_CONSTEXPR
#   else
#      define ALIB_CPP17_REL_CONSTEXPR constexpr
#   endif
#endif

#if ALIB_DEBUG
#   define ALIB_REL_CONSTEXPR
#else
#   define ALIB_REL_CONSTEXPR     constexpr
#endif



// Windows DLL Import/Export
#if defined( _MSC_VER ) && !defined( ALIB_API_NO_DLL )
    #ifdef ALIB_API_IS_DLL
        #define ALIB_API  __declspec(dllexport)
    #else
        #define ALIB_API  __declspec(dllimport)
    #endif
#else
    #define ALIB_API
#endif


// annotations
#if defined( _MSC_VER )
#   define  ALIB_FORCE_INLINE           __forceinline
#else
#   define  ALIB_FORCE_INLINE           __attribute__((always_inline))   inline
#endif
#define     ALIB_NO_RETURN              [[ noreturn ]]


// Warnings
#if defined(__clang__)

    #define ALIB_WARNINGS_UNINITIALIZED_OFF                                     \
        _Pragma("clang diagnostic push")                                        \
        _Pragma("clang diagnostic ignored \"-Wconditional-uninitialized\"")

    #define ALIB_WARNINGS_OVERLOAD_VIRTUAL_OFF                                  \
        _Pragma("clang diagnostic push")                                        \
        _Pragma("clang diagnostic ignored \"-Woverloaded-virtual\"")

    #define ALIB_WARNINGS_ALLOW_MACRO_REDEFINITION                              \
        _Pragma("clang diagnostic push")                                        \
        _Pragma("clang diagnostic ignored \"-Wmacro-redefined\"")

    #define ALIB_WARNINGS_MACRO_NOT_USED_OFF                                    \
        _Pragma("clang diagnostic push")                                        \
        _Pragma("clang diagnostic ignored \"-Wunused-macros\"")

    #define ALIB_WARNINGS_ALLOW_SPARSE_ENUM_SWITCH                              \
        _Pragma("clang diagnostic push")                                        \
        _Pragma("clang diagnostic ignored \"-Wswitch-enum\"")                   \

    #define ALIB_WARNINGS_ALLOW_BITWISE_SWITCH                                  \
        _Pragma("clang diagnostic push")                                        \
        _Pragma("clang diagnostic ignored \"-Wswitch\"")                        \
        _Pragma("clang diagnostic ignored \"-Wcovered-switch-default\"")        \

    #define ALIB_WARNINGS_IGNORE_UNUSED_PARAMETER                               \
        _Pragma("clang diagnostic push")                                        \
        _Pragma("clang diagnostic ignored \"-Wunused-parameter\"")              \

    #define ALIB_WARNINGS_IGNORE_IF_CONSTEXPR                                   \
        _Pragma("clang diagnostic push")                                        \

    #define ALIB_WARNINGS_IGNORE_INTEGRAL_CONSTANT_OVERFLOW                     \
        _Pragma("clang diagnostic push")                                        \

    #define ALIB_WARNINGS_IGNORE_DOCS                                           \
        _Pragma("clang diagnostic push")                                        \
        _Pragma("clang diagnostic ignored \"-Wdocumentation\"")                 \


    #define ALIB_WARNINGS_RESTORE                                               \
        _Pragma("clang diagnostic pop")

    #define ALIB_FALLTHROUGH            [[clang::fallthrough]];

#elif defined(__GNUC__)

    #define ALIB_WARNINGS_UNINITIALIZED_OFF                                     \
        _Pragma("GCC diagnostic push")                                          \
        _Pragma("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")

    #define ALIB_WARNINGS_ALLOW_MACRO_REDEFINITION                              \
        _Pragma("GCC diagnostic push")                                          \

    #define ALIB_WARNINGS_MACRO_NOT_USED_OFF                                    \
        _Pragma("GCC diagnostic push")                                          \

    #define ALIB_WARNINGS_OVERLOAD_VIRTUAL_OFF                                  \
        _Pragma("GCC diagnostic push")                                          \

    #define ALIB_WARNINGS_ALLOW_SPARSE_ENUM_SWITCH                              \
        _Pragma("GCC diagnostic push")                                          \

    #define ALIB_WARNINGS_ALLOW_BITWISE_SWITCH                                  \
        _Pragma("GCC diagnostic push")                                          \
        _Pragma("GCC diagnostic ignored \"-Wswitch\"")

    #define ALIB_WARNINGS_IGNORE_UNUSED_PARAMETER                               \
        _Pragma("GCC diagnostic push")                                          \
        _Pragma("GCC diagnostic ignored \"-Wunused-parameter\"")

    #define ALIB_WARNINGS_IGNORE_IF_CONSTEXPR                                   \
        _Pragma("GCC diagnostic push")                                          \

    #define ALIB_WARNINGS_IGNORE_INTEGRAL_CONSTANT_OVERFLOW                     \
        _Pragma("GCC diagnostic push")                                          \

    #define ALIB_WARNINGS_IGNORE_DOCS                                           \
        _Pragma("GCC diagnostic push")                                          \

    #define ALIB_WARNINGS_RESTORE                                               \
        _Pragma("GCC diagnostic pop")

    #if __GNUC__ < 7
      #define ALIB_FALLTHROUGH
    #else
      #define ALIB_FALLTHROUGH        [[gnu::fallthrough]];
    #endif

#elif defined(_MSC_VER)
    #define ALIB_WARNINGS_UNINITIALIZED_OFF                                    \
        __pragma(warning( push ))                                              \
        __pragma(warning( disable : 4701 ))                                    \

    #define ALIB_WARNINGS_MACRO_NOT_USED_OFF                                   \
        __pragma(warning( push ))                                              \

    #define ALIB_WARNINGS_OVERLOAD_VIRTUAL_OFF                                 \
        __pragma(warning( push ))                                              \

    #define ALIB_WARNINGS_ALLOW_SPARSE_ENUM_SWITCH                             \
        __pragma(warning( push ))                                              \

    #define ALIB_WARNINGS_ALLOW_SPARSE_ENUM_SWITCH                             \
        __pragma(warning( push ))                                              \

    #define ALIB_WARNINGS_ALLOW_MACRO_REDEFINITION                             \
        __pragma(warning( push ))                                              \
        __pragma(warning( disable : 4005 ))                                    \

    #define ALIB_WARNINGS_ALLOW_BITWISE_SWITCH                                 \
        __pragma(warning( push ))                                              \

    #define ALIB_WARNINGS_IGNORE_UNUSED_PARAMETER                              \
        __pragma(warning( push ))                                              \

#if !ALIB_CPP17
    #define ALIB_WARNINGS_IGNORE_IF_CONSTEXPR                                  \
        __pragma(warning( push ))                                              \
        __pragma(warning( disable : 4127 ))
#else
    #define ALIB_WARNINGS_IGNORE_IF_CONSTEXPR                                  \
        __pragma(warning( push ))
#endif

    #define ALIB_WARNINGS_IGNORE_INTEGRAL_CONSTANT_OVERFLOW                    \
        __pragma(warning( push ))                                              \
        __pragma(warning( disable : 4307 ))                                    \
        __pragma(warning( disable : 4293 ))                                    \

    #define ALIB_WARNINGS_IGNORE_DOCS                                          \
        __pragma(warning( push ))                                              \

    #define ALIB_WARNINGS_RESTORE                                              \
        __pragma(warning( pop  ))                                              \

    #define ALIB_FALLTHROUGH

#else
    #define ALIB_WARNINGS_RESTORE
    #define ALIB_FALLTHROUGH
#endif



#endif // HPP_ALIB_LIB_PREDEF_COMPILER
