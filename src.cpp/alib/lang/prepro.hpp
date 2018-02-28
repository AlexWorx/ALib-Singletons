// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  General ALib preprocessor macros
//
//  Copyright 2013-2018 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
/** @file */ // Hello Doxygen

// to preserve the right order, we are not includable directly from outside.
#if !defined(ALIB_PROPER_INCLUSION) || defined(HPP_ALIB_LIB_PREPRO)
    #error "include alib/alib.hpp instead of this header"
#endif

#ifndef HPP_ALIB_LIB_PREPRO
#define HPP_ALIB_LIB_PREPRO 1


/**
 * @defgroup GrpALibCodeSelectorSymbols ALib Symbols To Select Code Fragments
 *
 *  Symbols (C++ preprocessor macros) listed here, are mostly generated out of
 * \ref GrpALibCompilerSymbols. In this case, their name corresponds to these symbols, excluding
 * the suffixes <em>_ON</em> and <em>_OFF</em>.<p>
 *
 * These symbols must not be passed to the compiler and must also not be set manually from within
 * code entities that use \b %ALib libraries. They can be used in code entities that use \b %ALib to select
 * code depending on the same settings of \b %ALib compilation. Selection takes place,
 * using preprocessor directives:<p>
 * \code{.cpp}
 * #if ALIB_XYZ_SELECTOR
 *   // your selective code
 * #endif
 * \endcode
 *
 * \b %ALib Symbols are prefixed with <em>ALIB_</em>.<p>
 * @{ @}
 */

/**
 * @defgroup GrpALibMacros    ALib Macros
 *
 * The preprocessor macros listed here are utility macros used by A-Worx Library \e \b %ALib and
 * are documented as they might be useful for users of \b %ALib same as \b %ALib itself.
 *
 * The definition of the macros is dependent on \ref GrpALibCodeSelectorSymbols, which in turn
 * mostly depend on \ref GrpALibCompilerSymbols.
 *
 * Not listed here, are macros of \alox. Those are documented with
 * - \ref GrpMacrosDebugLog
 * - \ref GrpMacrosReleaseLog
 * @{ @}
 */



/**
 * @addtogroup GrpALibCompilerSymbols
 * @{
 *  \def  ALIB_DEBUG_ON
 *  This compiler symbol forces \b %ALib to compile in debug mode by defining the code selection symbol
 *  \ref ALIB_DEBUG. Plausibility and assertion checks are performed in this mode.<br>
 *  If neither this symbol nor \ref ALIB_DEBUG_OFF is provided, then \b %ALib headers rely on
 *  the symbol <b>NDEBUG</b>. If NDEBUG is given, \ref ALIB_DEBUG is not set. Otherwise it is.
 *
 *  \def  ALIB_DEBUG_OFF
 *  This compiler symbol forces \b %ALib to compile without internal plausibility and assertion checks,
 *  by leaving the code selection symbol \ref ALIB_DEBUG undefined.
 *  If neither this symbol nor \ref ALIB_DEBUG_OFF is provided, then \b %ALib headers rely on
 *  a set of standard symbols introduced (and set) by other libraries, e.g. <em>NDEBUG</em>.
 * @}
 *
 * @addtogroup GrpALibCodeSelectorSymbols
 * @{ \def  ALIB_DEBUG
 *  If true (1), plausibility checks and \b %ALib assertions are enabled.
 *  See \ref ALIB_DEBUG_ON and \ref ALIB_DEBUG_OFF for information about how to manipulate
 *  this symbol.
 * @}
 */
#if defined(DOX_PARSER)
    #define     ALIB_DEBUG
    #define     ALIB_DEBUG_ON
    #define     ALIB_DEBUG_OFF
#else

    #if defined(ALIB_DEBUG)
        #error "ALIB_DEBUG must not be set from outside"
    #endif

    #if defined(ALIB_DEBUG_OFF) && defined(ALIB_DEBUG_ON)
        #error "ALIB_DEBUG_OFF / ALIB_DEBUG_ON are both set"
    #endif

    #if !defined(ALIB_DEBUG_OFF) && ( defined(ALIB_DEBUG_ON) || !defined(NDEBUG) || defined(_DEBUG) || defined(DEBUG) )
        #define ALIB_DEBUG 1
    #else
        #define ALIB_DEBUG 0
    #endif

#endif //DOX_PARSER


/**
 * @addtogroup GrpALibMacros
 * @{
 * @name C/C++ Preprocessor Helper Macros
 *
 * The following macros are fundamental and building blocks for other macros.
 * @{
 *  \def  ALIB_STRINGIFY
 *  Makes as string from a preprocessor macro parameter.
 *
 *  \def  ALIB_CONCAT
 *  Concatenates two preprocessor macro parameters into one symbol.
 *
 *  \def  ALIB_IDENTIFIER
 *  This macro assembles an 'anonymous' identifier using the given prefix and the current
 *  line number within the source code file. This macro is used within other macros that
 *  need a C/C++ identifier internally.<br>
 *  As a sample, see macro \ref OWN.
 *
 *  \def  ALIB_COMMA
 *  Defines a simple comma (<c>','</c>). Used with macros when otherwise the use of a comma symbol
 *  leads to ambiguous syntax. For example when passing template types to macros.
 *
 *  Used with macros when otherwise the use of a comma symbol
 *  leads to ambiguous syntax. For example when passing template types to macros as shown here:
 *
 *          MY_MACRO( std::vector<int ALIB_COMMA double> )
 *
 *  \def  ALIB_COMMA_DBG
 *  Defines a simple comma (<c>','</c>) with \ref ALIB_DEBUG "debug compilations". In release
 *  compilations the macro is empty. This is useful for example when methods change their
 *  signature depending on the compilation type. The latter is unavoidable i.e if caller source code
 *  information should be passed for debugging.
 *
 *  Used with macros when otherwise the use of a comma symbol
 *  leads to ambiguous syntax. For example when passing template types to macros.
 * @}
 * @}
 */

#if defined( DOX_PARSER )
    #define     ALIB_STRINGIFY(a)
    #define     ALIB_CONCAT(a,b)
    #define     ALIB_IDENTIFIER(prefix)
#else

    #define     ALIB_STRINGIFY_X(a)     #a
    #define     ALIB_STRINGIFY(a)       ALIB_STRINGIFY_X(a)

    #define     ALIB_CONCAT_X(a,b)      a ## b
    #define     ALIB_CONCAT(a,b)        ALIB_CONCAT_X(a,b)

    #define     ALIB_IDENTIFIER(prefix) ALIB_CONCAT(prefix, __LINE__)
#endif

#define     ALIB_COMMA              ,
#if ALIB_DEBUG
#  define   ALIB_COMMA_DBG          ,
#else
#  define   ALIB_COMMA_DBG
#endif

/**
 * @addtogroup GrpALibCompilerSymbols
 * @{ \def  ALIB_API_IS_DLL
 *  This compiler symbol has to be defined when compiling \b %ALib classes into a DLL under
 *  Windows/MSC.
 *  Within code units that use a DLL that contains \b %ALib, this symbol must not be defined.
 * @}
 *
 * @addtogroup GrpALibCompilerSymbols
 * @{ \def  ALIB_API_NO_DLL
 *  This compiler symbol has to be defined when compiling \b %ALib classes directly into a project
 *  Windows/MSC (not using a DLL).
 *  \see #ALIB_API_IS_DLL and #ALIB_API
 * @}
 *
 */
#if defined(DOX_PARSER)
    #define    ALIB_API
    #define    ALIB_API_IS_DLL
    #define    ALIB_API_NO_DLL
#else
    #if defined( _MSC_VER ) && !defined( ALIB_API_NO_DLL )
        #ifdef ALIB_API_IS_DLL
            #define ALIB_API  __declspec(dllexport)
        #else
            #define ALIB_API  __declspec(dllimport)
        #endif
    #else
        #define ALIB_API
    #endif
#endif //DOX_PARSER


/**
 * @addtogroup GrpALibMacros
 * @{
 *
 *
 * @name C/C++ Language And Linkage Macros
 * The macros listed here are supporting C++ compilation and linking control and language
 * specific utilities.
 * @{
 *  \def  ALIB_API
 *    Used to export/import C++ symbols into a dynamic link library.
 *    Defined under Windows/MSC when compiling or using \b %ALib classes inside a DLL.
 *    Dependent on \ref ALIB_API_IS_DLL and \ref ALIB_API_NO_DLL.
 *
 *  \def  ALIB_DBG
 *    This simple macro may be used for placing debug statements into source code. Those get 'pruned'
 *    in release versions of \b %ALib (respectively of the software that uses \b %ALib and then this macro).
 *    It replaces
\verbatim
    #if ALIB_DEBUG
        // do stuff
    #endif
\endverbatim
 *    and is useful especially for single line statements.
 *
 *  \def ALIB_REL_DBG
 *    Similar to \ref ALIB_DBG, but accepts a release version of the code as well. The release
 *    version is expected as first macro parameter. Note, that the release code must not contain a
 *    comma (',')  while the debug code is allowed to. A comma in release code may be substituted
 *    with macro \ref ALIB_COMMA. However, more complicated stuff should be placed in usual
 *    <c>\#if</c>/<c>\#else</c>/<c>\#endif</c> statements.
 *
 *  \def ALIB_NO_RETURN
 *     Used as alias to C++ attribute <c>[[noreturn]]</c>.
 *     Defined if the compiler has support for it, else empty.
 *
 *  \def  ALIB_SIZEOF_WCHAR_T
 *    Compiler/platform dependent value. Gives the sizeof values of type \c wchar_t in bytes.
 *    Possible values are \b 2 and \b 4.
 *
 *  \def  ALIB_CPP14
 *  Macro which is \c 1 defined when compiled with <b>C++ 14</b> standard or higher and \c 0
 *  with <b>C++ 11</b>.
 *
 *  \def  ALIB_CPP14_CONSTEXPR
 *  Macro used in situations when C++ keyword \c constexpr is not allowed in <b>C++ 11</b> but in
 *  <b>C++ 14</b> onwards.
 *
 *  \def  ALIB_CPP17
 *  Macro which is \c 1 defined when compiled with <b>C++ 14</b> standard or higher and \c 0
 *  with <b>C++ 11</b>.
 *
 *  \def  ALIB_SRCPOS
 *  This macro fills in the built-in compiler symbols that provide the current source file,
 *  line number and function strings.<p>
 *  The macro should be used anywhere where this information is passed (as a nested macro in
 *  debug macros)<p>
 *
 *  \def  ALIB_SRCPOS_REL_EMPTY
 *  This macro is the same as \ref ALIB_SRCPOS but empty if \ref ALIB_DEBUG is
 *  not defined.<br>
 *  In comparisson to \ref ALIB_SRCPOS_REL_NULLED, this macro is to be used with invocations of
 *  methods that lack the corresponding parameters in release compilations.
 *
 *  \def  ALIB_SRCPOS_REL_NULLED
 *  In \ref ALIB_DEBUG "debug compilations" this macro is the same as \ref ALIB_SRCPOS.
 *  Otherwise evaluates to <c>nullptr, 0, nullptr</c>.<br>
 *  In comparisson to \ref ALIB_SRCPOS_REL_EMPTY, this macro is to be used with invocations of
 *  methods that keep the corresponding parameters in release compilations.
 *
 * \def  ALIB_TMP_SHOW_TYPE_IN_DEBUGGER
 *  Declares a local variable of a simple templated class  \b %ALibTMPDbgTypeCheck. The variable will
 *  be named \c dbgTypeCheck_TYPE, where "TYPE" is the inferred template type passed to this macro.
 *  In debug sessions the name of the type in question can be read from the type of this
 *  local variable.<br>
 *  This macro is empty in non-debug compilations.
 *
 * @}
 * @}
 */
#if defined(DOX_PARSER)
    #define     ALIB_DBG
    #define     ALIB_REL_DBG

    #define     ALIB_CPP14
    #define     ALIB_CPP14_CONSTEXPR
    #define     ALIB_CPP17

    #define     ALIB_NO_RETURN

    #define     ALIB_SIZEOF_WCHAR_T
    #define     ALIB_SRCPOS
    #define     ALIB_SRCPOS_REL_EMPTY
    #define     ALIB_SRCPOS_REL_NULLED

#else

    // debug/release code selection
    #if ALIB_DEBUG
        #define ALIB_DBG(...)    __VA_ARGS__
        #define ALIB_REL_DBG(releaseCode, ...)    __VA_ARGS__
    #else
        #define ALIB_DBG(...)
        #define ALIB_REL_DBG(releaseCode, ...)    releaseCode
    #endif

    // size of wchar_t
    #if defined(__WCHAR_MAX__)
        #if  __WCHAR_MAX__ == 0x7FFFFFFF
            #define     ALIB_SIZEOF_WCHAR_T    4
        #else
            #define     ALIB_SIZEOF_WCHAR_T    2
        #endif
    #elif defined(_MSC_VER)
        #define         ALIB_SIZEOF_WCHAR_T    2

    #elif defined(_MSC_VER)
        #define         ALIB_SIZEOF_WCHAR_T    4 // guessing, will be checked below
    #endif
    static_assert( sizeof(wchar_t) == ALIB_SIZEOF_WCHAR_T, "Error: Platform not supported" );

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
    #   elif _MSVC_LANG == 201703L
    #     define  ALIB_CPP14   1
    #     define  ALIB_CPP17   1
    #   else
            static_assert( false, "Unknown C++ Standard \"" ALIB_STRINGIFY(__cplusplus) "\"" )
    #       error "Aborting"
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
    #   elif __cplusplus == 201703L
    #     define  ALIB_CPP14   1
    #     define  ALIB_CPP17   1
    #   else
            static_assert( false, "Unknown C++ Standard \"" ALIB_STRINGIFY(__cplusplus) "\"" )
    #       error "Aborting"
    #   endif
    #endif

    #if ALIB_CPP14
    #   define ALIB_CPP14_CONSTEXPR constexpr
    #else
    #   define ALIB_CPP14_CONSTEXPR
    #endif


    // annotations
    #define ALIB_NO_RETURN              [[ noreturn ]]


    // Macros for passing source code information
    #if defined( __GNUC__ )
        #define ALIB_SRCPOS    __FILE__, __LINE__, __func__
      //#define ALIB_SRCPOS    __FILE__, __LINE__, __PRETTY_FUNCTION__
    #elif defined ( _MSC_VER )
        #define ALIB_SRCPOS     __FILE__, __LINE__, __FUNCTION__
      //#define ALIB_SRCPOS     __FILE__, __LINE__, __FUNCSIG__
    #else
        #pragma message ("Unknown Platform in file: " __FILE__ )
    #endif

    #if ALIB_DEBUG
        #define ALIB_SRCPOS_REL_EMPTY         ALIB_SRCPOS
        #define ALIB_SRCPOS_REL_NULLED        ALIB_SRCPOS
    #else
        #define ALIB_SRCPOS_REL_EMPTY
        #define ALIB_SRCPOS_REL_NULLED        nullptr, 0, nullptr
    #endif


#endif //DOX_PARSER




/**
 * @addtogroup GrpALibMacros
 * @{
 * @name C/C++ Compiler Warning Control
 * \b %ALib sources are designed to be compiled on different compilers using the highest possible
 * compiler warning levels available.
 * In some situations, some warnings need to be temporarily disabled. The following macros do
 * this in a compiler agnostic way.
 * @{
 *
 * \def  ALIB_WARNINGS_RESTORE
 *  Reinstalls previous compiler warning settings. To be used in combination with macros
 *  - #ALIB_WARNINGS_ALLOW_TEMPLATE_META_PROGRAMMING.
 *  - #ALIB_WARNINGS_UNINITIALIZED_OFF.
 *  - #ALIB_WARNINGS_MACRO_NOT_USED_OFF.
 *  - #ALIB_WARNINGS_OVERLOAD_VIRTUAL_OFF.
 *  - #ALIB_WARNINGS_ALLOW_SPARSE_ENUM_SWITCH
 *  - #ALIB_WARNINGS_ALLOW_BITWISE_SWITCH
 *
 * \def  ALIB_WARNINGS_ALLOW_TEMPLATE_META_PROGRAMMING
 *  Preprocessor macro that disables warnings that usually are caused by template meta
 *  programming (if a strict warning policy is in place).
 *  The end is has to be marked with #ALIB_WARNINGS_RESTORE.<br>
 *
 *
 * \def  ALIB_WARNINGS_UNINITIALIZED_OFF
 *  Preprocessor macro to disable compiler warnings about uninitialized values.
 *
 * \def  ALIB_WARNINGS_MACRO_NOT_USED_OFF
 *  Preprocessor macro to disable compiler warnings about unused preprocessor macros.
 *
 * \def  ALIB_WARNINGS_OVERLOAD_VIRTUAL_OFF
 *  Preprocessor macro to disable compiler warnings about virtual methods that become hidden
 *  by overloaded methods with a different signature.
 *
 * \def  ALIB_WARNINGS_ALLOW_SPARSE_ENUM_SWITCH
 *  Preprocessor macro to disable compiler warnings when an enumeration element is switched while
 *  not all enumeration elements get caught.
 *
 * \def  ALIB_WARNINGS_ALLOW_BITWISE_SWITCH
 *  Preprocessor macro to disable compiler warnings when a
 *  "bitwise type scoped enumeration" (see \alib{lang,T_EnumIsBitwise}) or similar types with
 *  'sparse' case coverage are used in a switch statement.
 *
 * \def  ALIB_FALLTHROUGH
 *  Used with keyword \c switch to annotate a \c case block that has no \b break or (\c return, etc.).
 *  Avoids a warning with some compilers.
 * @}
 * @}
 */
#if defined(DOX_PARSER)
    #define     ALIB_WARNINGS_RESTORE
    #define     ALIB_WARNINGS_ALLOW_TEMPLATE_META_PROGRAMMING
    #define     ALIB_WARNINGS_UNINITIALIZED_OFF
    #define     ALIB_WARNINGS_OVERLOAD_VIRTUAL_OFF
    #define     ALIB_WARNINGS_MACRO_NOT_USED_OFF
    #define     ALIB_WARNINGS_ALLOW_SPARSE_ENUM_SWITCH
    #define     ALIB_WARNINGS_ALLOW_BITWISE_SWITCH
    #define     ALIB_FALLTHROUGH

#elif defined(__clang__)
    #if defined(__APPLE__)
        #define ALIB_WARNINGS_ALLOW_TEMPLATE_META_PROGRAMMING                       \
            _Pragma("clang diagnostic push")                                        \
            _Pragma("clang diagnostic ignored \"-Wold-style-cast\"")                \
            _Pragma("clang diagnostic ignored \"-Wcast-align\"")                    \
            _Pragma("clang diagnostic ignored \"-Wvoid-ptr-dereference\"")          \
            _Pragma("clang diagnostic ignored \"-Wextra-semi\"")                    \
            _Pragma("clang diagnostic ignored \"-Wnull-dereference\"")              \
            _Pragma("clang diagnostic ignored \"-Wdynamic-class-memaccess\"")       \
            _Pragma("clang diagnostic ignored \"-Wunneeded-internal-declaration\"") \
            _Pragma("clang diagnostic ignored \"-Wreturn-type\"")                   \

    #else
        #define ALIB_WARNINGS_ALLOW_TEMPLATE_META_PROGRAMMING                       \
            _Pragma("clang diagnostic push")                                        \
            _Pragma("clang diagnostic ignored \"-Wold-style-cast\"")                \
            _Pragma("clang diagnostic ignored \"-Wcast-align\"")                    \
            _Pragma("clang diagnostic ignored \"-Wvoid-ptr-dereference\"")          \
            _Pragma("clang diagnostic ignored \"-Wextra-semi\"")                    \
            _Pragma("clang diagnostic ignored \"-Wundefined-func-template\"")       \
            _Pragma("clang diagnostic ignored \"-Wdynamic-class-memaccess\"")       \
            _Pragma("clang diagnostic ignored \"-Wcast-qual\"")                     \
            _Pragma("clang diagnostic ignored \"-Wnull-dereference\"")              \
            _Pragma("clang diagnostic ignored \"-Wunused-function\"")               \
            _Pragma("clang diagnostic ignored \"-Wundefined-inline\"")              \
            _Pragma("clang diagnostic ignored \"-Wreturn-type\"")
    #endif

    #define ALIB_WARNINGS_UNINITIALIZED_OFF                                    \
        _Pragma("clang diagnostic push")                                       \
        _Pragma("clang diagnostic ignored \"-Wconditional-uninitialized\"")

    #define ALIB_WARNINGS_OVERLOAD_VIRTUAL_OFF                                 \
        _Pragma("clang diagnostic push")                                       \
        _Pragma("clang diagnostic ignored \"-Woverloaded-virtual\"")

    #define ALIB_WARNINGS_MACRO_NOT_USED_OFF                                   \
        _Pragma("clang diagnostic push")                                       \
        _Pragma("clang diagnostic ignored \"-Wunused-macros\"")

    #define ALIB_WARNINGS_ALLOW_SPARSE_ENUM_SWITCH                             \
        _Pragma("clang diagnostic push")                                       \
        _Pragma("clang diagnostic ignored \"-Wswitch-enum\"")                  \

    #define ALIB_WARNINGS_ALLOW_BITWISE_SWITCH                                 \
        _Pragma("clang diagnostic push")                                       \
        _Pragma("clang diagnostic ignored \"-Wswitch\"")                       \
        _Pragma("clang diagnostic ignored \"-Wcovered-switch-default\"")       \

    #define ALIB_WARNINGS_RESTORE                                              \
        _Pragma("clang diagnostic pop")

    #define ALIB_FALLTHROUGH            [[clang::fallthrough]];

#elif defined(__GNUC__)
    #define ALIB_WARNINGS_ALLOW_TEMPLATE_META_PROGRAMMING                      \
        _Pragma("GCC diagnostic push")                                         \
        _Pragma("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")            \
        _Pragma("GCC diagnostic ignored \"-Wunused-function\"")                \
        _Pragma("GCC diagnostic ignored \"-Wreturn-type\"")

    #define ALIB_WARNINGS_UNINITIALIZED_OFF                                    \
        _Pragma("GCC diagnostic push")                                         \
        _Pragma("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")

    #define ALIB_WARNINGS_MACRO_NOT_USED_OFF                                   \
        _Pragma("GCC diagnostic push")                                         \

    #define ALIB_WARNINGS_OVERLOAD_VIRTUAL_OFF                                 \
        _Pragma("GCC diagnostic push")                                         \

    #define ALIB_WARNINGS_ALLOW_SPARSE_ENUM_SWITCH                             \
        _Pragma("GCC diagnostic push")                                         \

    #define ALIB_WARNINGS_ALLOW_BITWISE_SWITCH                                 \
        _Pragma("GCC diagnostic push")                                         \
        _Pragma("GCC diagnostic ignored \"-Wswitch\"")

    #define ALIB_WARNINGS_RESTORE                                              \
        _Pragma("GCC diagnostic pop")

    #if __GNUC__ < 7
      #define ALIB_FALLTHROUGH
    #else
      #define ALIB_FALLTHROUGH        [[gnu::fallthrough]];
    #endif

#elif defined(_MSC_VER)
    #define ALIB_WARNINGS_ALLOW_TEMPLATE_META_PROGRAMMING                      \
        __pragma(warning( push ))                                              \
        __pragma(warning( disable : 4127 ))                                    \
        __pragma(warning( disable : 4826 ))                                    \
        __pragma(warning( disable : 4716 ))                                    \
        __pragma(warning( disable : 4180 ))                                    \

    #define ALIB_WARNINGS_UNINITIALIZED_OFF                                    \
        __pragma(warning( push ))                                              \
        __pragma(warning( disable : 4701 ))                                    \

    #define ALIB_WARNINGS_MACRO_NOT_USED_OFF                                   \
        __pragma(warning( push ))                                              \

    #define ALIB_WARNINGS_OVERLOAD_VIRTUAL_OFF                                 \
        __pragma(warning( push ))                                              \

    #define ALIB_WARNINGS_ALLOW_SPARSE_ENUM_SWITCH                             \
        __pragma(warning( push ))                                              \

    #define ALIB_WARNINGS_ALLOW_BITWISE_SWITCH                                 \
        __pragma(warning( push ))                                              \

    #define ALIB_WARNINGS_RESTORE                                              \
        __pragma(warning( pop ))

    #define ALIB_FALLTHROUGH

#else
    #define ALIB_WARNINGS_ALLOW_TEMPLATE_META_PROGRAMMING
    #define ALIB_WARNINGS_RESTORE
    #define ALIB_FALLTHROUGH
#endif

#if ALIB_DEBUG && !defined(DOX_PARSER)
    namespace aworx { namespace lib { template <typename TCheck> class ALibTMPDbgTypeCheck { public: TCheck* typeAsPointer= nullptr; }; }}
    #define ALIB_TMP_SHOW_TYPE_IN_DEBUGGER(type) aworx::lib::ALibTMPDbgTypeCheck<type> dbgTypeCheck_ ## type; (void) dbgTypeCheck_ ## type;
#else
    #define ALIB_TMP_SHOW_TYPE_IN_DEBUGGER(type)
#endif

/**
 * @addtogroup GrpALibCompilerSymbols
 * @{
 *  \def  ALIB_AVOID_ANALYZER_WARNINGS_ON
 *    This compiler symbol enables additional debug code that tries to prevent external analysis
 *    tools (e.g. [Valgrind](https://www.valgrind.org/)) to raise unnecessary warnings or errors.
 *
 *    When provided, it defines \ref ALIB_AVOID_ANALYZER_WARNINGS.
 *
 *  \def  ALIB_AVOID_ANALYZER_WARNINGS_OFF
 *    Disables certain debug code. See \ref ALIB_AVOID_ANALYZER_WARNINGS_ON.
 *    This symbol represents the default behavior and is provided for completeness.
 * @}
 *
 * @addtogroup GrpALibCodeSelectorSymbols
 * @{
 *  \def  ALIB_AVOID_ANALYZER_WARNINGS
 *    Selects extra debug code to avoid potential warnings of external analyze tools.
 *    Gets defined by compiler symbol \ref ALIB_AVOID_ANALYZER_WARNINGS_ON.
 * @}
 */

#if defined(DOX_PARSER)
    #define     ALIB_AVOID_ANALYZER_WARNINGS
    #define     ALIB_AVOID_ANALYZER_WARNINGS_OFF
    #define     ALIB_AVOID_ANALYZER_WARNINGS_ON
#else
    #if defined(ALIB_AVOID_ANALYZER_WARNINGS_OFF) && defined(ALIB_AVOID_ANALYZER_WARNINGS_ON)
        #error "ALIB_AVOID_ANALYZER_WARNINGS_OFF / ALIB_AVOID_ANALYZER_WARNINGS_ON are both set"
    #endif

    #if defined( ALIB_AVOID_ANALYZER_WARNINGS_ON )
        #define    ALIB_AVOID_ANALYZER_WARNINGS 1
    #else
        #define    ALIB_AVOID_ANALYZER_WARNINGS 0
    #endif
#endif //DOX_PARSER



/**
 * @addtogroup GrpALibCompilerSymbols
 * @{
 *  \def  ALIB_FEAT_THREADS_ON
 *    This compiler symbol enables the use of threads within \b %ALib, by.
 *    defining source selection symbol \ref ALIB_FEAT_THREADS.
 *    This is the default, hence the symbol is not needed to be passed, but it is available for
 *    completeness.<br>
 *    See \ref ALIB_FEAT_THREADS_OFF for more information.
 *
 *  \def  ALIB_FEAT_THREADS_OFF
 *    This compiler symbol disables the use of threads within \b %ALib, by
 *    preventing the definition of source selection symbol \ref ALIB_FEAT_THREADS.
 *    This might be useful for platforms where no thread library is available or to minimize code
 *    size. In general, if unsure, do not use this symbol and use the multi-threaded version of \b %ALib.<br>
 *    When this symbol is set, classes
 *    \ref aworx::lib::threads::Thread "Thread" and
 *    \ref aworx::lib::threads::Runnable "Runnable" are not available. However, the classes
 *    \ref aworx::lib::threads::ThreadLockNR "ThreadLockNR" and
 *    \ref aworx::lib::threads::ThreadLock "ThreadLock" are!
 *    Their interface remains the same, but they do not perform any locking. Due to this behavior,
 *    it is possible to write code that performs due locking while still, in single threaded
 *    compilation, the code does not suffer any performance drawbacks, because lock code  will be
 *    <em>pruned</em>.
 * @}
 *
 * @addtogroup GrpALibCodeSelectorSymbols
 * @{
 *  \def  ALIB_FEAT_THREADS
 *    Selects code within \b %ALib (or source entities that use \b %ALib) that cares about threads and
 *    due locking of shared resources.
 *    See compiler symbol \ref ALIB_FEAT_THREADS_OFF for more information.
 * @}
 */
#if defined(DOX_PARSER)
    #define     ALIB_FEAT_THREADS
    #define     ALIB_FEAT_THREADS_ON
    #define     ALIB_FEAT_THREADS_OFF
#else
    #if defined(ALIB_FEAT_THREADS)
        #error "ALIB_DEBUG must not be set from outside"
    #endif

    #if defined(ALIB_FEAT_THREADS_ON) && defined(ALIB_FEAT_THREADS_OFF)
        #error "ALIB_FEAT_THREADS_ON / ALIB_FEAT_THREADS_OFF are both set"
    #endif

    #if !defined(ALIB_FEAT_THREADS_OFF)
        #define ALIB_FEAT_THREADS 1
    #else
        #define ALIB_FEAT_THREADS 0
    #endif
#endif //DOX_PARSER

/**
 * @addtogroup GrpALibCompilerSymbols
 * @{
 *  \def  ALIB_FEAT_BOOST_REGEX_ON
 *    This compiler symbol enables the use of string utility class \alib{strings::util,RegexMatcher}
 *    by defining source selection symbol \ref ALIB_FEAT_BOOST_REGEX.
 *    Class \b %RegexMatcher is in fact only a simple wrapper around external
 *    [boost::regex library](http://www.boost.org).
 *
 *    If this symbol is not explicitly given to the compiler, \ref ALIB_FEAT_BOOST_REGEX remains
 *    undefined, the \b %boost library is not included and class \b %RegexMatcher is not available.
 *
 *  \def  ALIB_FEAT_BOOST_REGEX_OFF
 *    This compiler symbol disables the definition of source selection symbol
 *    \ref ALIB_FEAT_BOOST_REGEX.
 *
 *    This is the default, hence the symbol is not needed to be passed, but it is available for
 *    completeness.<br>
 *
 * @}
 *
 * @addtogroup GrpALibCodeSelectorSymbols
 * @{
 *  \def  ALIB_FEAT_BOOST_REGEX
 *    Selects code for class \alib{strings::util,RegexMatcher} and features within \b %ALib
 *    that uses this wrapper class.
 *
 *    See compiler symbol \ref ALIB_FEAT_BOOST_REGEX_ON for information on how to activate this
 *    library feature.
 * @}
 */
#if defined(DOX_PARSER)
    #define     ALIB_FEAT_BOOST_REGEX
    #define     ALIB_FEAT_BOOST_REGEX_ON
    #define     ALIB_FEAT_BOOST_REGEX_OFF
#else
    #if defined(ALIB_FEAT_BOOST_REGEX)
        #error "ALIB_FEAT_BOOST_REGEX must not be set from outside"
    #endif

    #if defined(ALIB_FEAT_BOOST_REGEX_ON) && defined(ALIB_FEAT_BOOST_REGEX_OFF)
        #error "ALIB_FEAT_BOOST_REGEX_ON / ALIB_FEAT_BOOST_REGEX_OFF are both set"
    #endif

    #if defined(ALIB_FEAT_BOOST_REGEX_ON)
        #define ALIB_FEAT_BOOST_REGEX 1
    #else
        #define ALIB_FEAT_BOOST_REGEX 0
    #endif
#endif //DOX_PARSER


#endif // HPP_ALIB_LIB_PREPRO
