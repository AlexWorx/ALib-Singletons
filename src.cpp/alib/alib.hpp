// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2018 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
/** @file */ // Hello Doxygen

#ifndef HPP_ALIB
#define HPP_ALIB 1


#define ALIB_VERSION              1712
#define ALIB_REVISION                1

// Uncomment to test for unnecessary includes. Must not be done with cotire unity builds.
// #define HPP_COM_ALIB_TEST_INCLUDES


// #################################################################################################
// basic system headers
// #################################################################################################

#if !defined (_ASSERT_H)
    #include <assert.h>
#endif


// GNUC specific
#if defined( __GNUC__ )
    #if !defined (_GLIBCXX_CSTDINT)
        #include <cstdint>
    #endif

// Windows specific
#elif defined ( _MSC_VER )

    //! @cond NO_DOX
    // Include windows.h. but exclude rarely-used stuff from Windows headers. If these things are
    // needed by the software that incorporates ALib, then windows has to be
    // included before this header file is.
    #if !defined (_INC_WINDOWS)
        #define WIN32_LEAN_AND_MEAN
        #define NOGDI
        #define NOSERVICE
        #define NOMCX
        #define NOIME
        #define NOSOUND
        #define NOCOMM
        #define NOKANJI
        #define NORPC
        #define NOPROXYSTUB
        #define NOIMAGE
        #define NOTAPE
        #include <windows.h>
    #endif
    //! @endcond

    #if !defined (_STDINT)
        #include <stdint.h>
    #endif

// other platforms not tested, yet
#else
    #pragma message ("Unknown Platform in file: " __FILE__ )
#endif

// #################################################################################################
// Include ALib modules found
// #################################################################################################


/**
 * @addtogroup GrpALibCodeSelectorSymbols
 * @{
 * @name ALib Module Selection
 * This group of symbols determine the availability of different <b>%ALib Modules</b> of the
 * \b %ALib distribution used.<br>
 * The symbols are defined in header <c>alib/distribution.hpp</c>, which varies per distribution.
 *
 * For module <b>%ALib Singleton</b> no symbol is defined, as this module is included in any
 *  \b %ALib distribution.
 *
 * \def  ALIB_MODULE_STRINGS
 *  Denotes if module <b>%ALib Strings</b> is available in the library used.
 *
 * \def  ALIB_MODULE_BOXING
 *  Denotes if module <b>%ALib %Boxing</b> is available in the library used.
 *
 * \def  ALIB_MODULE_CONFIGURATION
 *  Denotes if module <b>%ALib Configuration</b> is available in the library used.
 *
 * \def  ALIB_MODULE_SYSTEM
 *  Denotes if module <b>%ALib System</b> is available in the library used.
 *
 * \def  ALIB_MODULE_ALL
 *  Denotes if this is a complete version of \b %ALib.
 *
 * @}
 * @}
 */

#if defined(DOX_PARSER)
    #define     ALIB_MODULE_BOXING
    #define     ALIB_MODULE_STRINGS
    #define     ALIB_MODULE_CONFIGURATION
    #define     ALIB_MODULE_SYSTEM
    #define     ALIB_MODULE_ALL
#else
#   define ALIB_PROPER_INCLUSION
#endif

    // basics used with all modules
    #include "alib/lang/prepro.hpp"

    // read module-specific (distribution specific) preprocessor symbols
    #include "alib/distribution.hpp"

    #if !defined(ALIB_MODULE_ALL)
        #define ALIB_MODULE_ALL 0
    #endif

    #if !defined(ALIB_MODULE_CONFIGURATION)
        #define ALIB_MODULE_CONFIGURATION   ALIB_MODULE_ALL
    #endif

    #if !defined(ALIB_MODULE_BOXING)
        #define ALIB_MODULE_BOXING        ( ALIB_MODULE_ALL || ALIB_MODULE_CONFIGURATION )
    #endif

    #if !defined(ALIB_MODULE_STRINGS)
        #define ALIB_MODULE_STRINGS       ( ALIB_MODULE_ALL || ALIB_MODULE_CONFIGURATION )
    #endif

    #if !defined(ALIB_MODULE_SYSTEM)
        #define ALIB_MODULE_SYSTEM          ALIB_MODULE_ALL
    #endif

    #if ALIB_MODULE_ALL  && !( ALIB_MODULE_BOXING || ALIB_MODULE_STRINGS )
        #pragma message ("Contradictionary definitions in 'alib/distribution.hpp'" )
    #endif

    #if ALIB_MODULE_BOXING || ALIB_MODULE_STRINGS
        #include "alib/debug/assert.hpp"
    #endif

    // always needed
    #include "alib/lang/rtti.hpp"

    // Module: Singleton (the first, independent module, always included)
    #include "alib/lang/singleton.hpp"


    #if ALIB_MODULE_BOXING || ALIB_MODULE_STRINGS
        #include "alib/lang/types.hpp"
    #endif


    #if ALIB_MODULE_STRINGS
        #if !defined(HPP_ALIB_LANG_TYPES)
            #include "alib/lang/types.hpp"
        #endif

        #include "alib/lang/enums.hpp"
        #include "alib/strings/cstring.hpp"
        #include "alib/strings/string.hpp"
        #include "alib/strings/tstring.hpp"
        #include "alib/strings/stringliteral.hpp"
        #include "alib/strings/astring.hpp"
        #include "alib/strings/preallocatedstring.hpp"

        #include "alib/lang/resources.hpp"
        #include "alib/lang/library.hpp"
        #include "alib/strings/stringlib.hpp"
    #else
        #define ALIB_DEBUG_STRINGS  0
    #endif



    #if ALIB_MODULE_BOXING
        #include "alib/boxing/boxinglib.hpp"
    #else
        #define ALIB_FEAT_BOXING_FTYPES      0
        #define ALIB_FEAT_BOXING_STD_VECTOR  0
    #endif

    #if ALIB_MODULE_STRINGS
    #   include "alib/lang/langlib.hpp"
    #endif

    #if ALIB_MODULE_STRINGS && ALIB_MODULE_BOXING && ALIB_FEAT_BOXING_FTYPES
        #include "alib/strings/boxing/stringboxing.hpp"
    #endif

    #if ALIB_MODULE_ALL
        #if !ALIB_FEAT_BOXING_FTYPES
            static_assert(0, "The full version of ALib must not be compiled with disabled default "
                             "boxing of fundamental types (See ALIB_FEAT_BOXING_FTYPES_OFF)."
        #endif
        #include "alib/lang/report.hpp"
    #endif

    #if ALIB_MODULE_STRINGS  && !defined(HPP_ALIB_LANG_ENUM_META_DATA)
        #include "alib/lang/enumbitwise.hpp"
        #include "alib/lang/enummetadata.hpp"
    #endif


    #if ALIB_MODULE_CONFIGURATION
        #include "alib/config/configlib.hpp"
    #endif


    #if ALIB_MODULE_ALL || ALIB_MODULE_CONFIGURATION
        #include "alib/system/systemlib.hpp"
    #endif

#undef  ALIB_PROPER_INCLUSION

#if ALIB_MODULE_BOXING || ALIB_MODULE_STRINGS



// #################################################################################################
// Version verification macros
// #################################################################################################

/**
 * @defgroup GrpALibCompilerSymbols ALib Compilation Symbols
 *
 * Symbols (C++ preprocessor macros) listed here, support adding or removing features to \b %ALib when
 * compiling the library and any code unit that uses \b %ALib.
 * These symbols must be used <em>only within makefiles or IDE project files to be passed to the
 * C++ compiler (!) </em> (normally -D option). In other words: they must not be defined or undefined
 * within the source code that uses \b %ALib.
 *
 * \b %ALib Symbols are prefixed with <em>ALIB_</em>.
 *
 * For most of the symbols, a version with suffix <em>_ON</em> and for some also one with the suffix
 * <em>_OFF</em> exists. These symbol decide about the definition, respectively the avoidance of the
 * definition of a corresponding <em>code selection symbol</em> that is named the same without the
 * suffix.<br>
 * If both are set at the same time, a compiler error is generated by \b %ALib header files.
 * If none of them is passed to the compiler, a default value is assumed.<p>
 *
 * As a convenience, to get default behavior, no symbol needs to be passed to the compiler.<p>
 *
 * \note Some of the compilation symbols are changing the definition of classes and methods which
 *       makes binaries incompatible with binaries that do not use the same setting for each of
 *       these symbols.<br>
 *       Symbols that have to be kept equal across compilation units are denoted in this
 *       documentation.
 * @{ @}
 */

/**
 * @addtogroup GrpALibMacros
 * @{
 * @name ALib Version And Feature Verification
 * Macros used to verify that the \b %ALib binary used has the right version is is compiled with
 * the same feature set as the current compilation unit.
 * For this, version and feature flags are compiled statically into the library.
 * The macros are used internally, respectively 'automatically'. Hence, they need not to be used
 * directly clients of the library.
 *
 * \def  ALIB_VERSION
 *  The \b %ALib version number. The value of this macro is written into field
 *  \alib{lang,Library::Version} of singleton \ref aworx::lib::ALIB (and corresponding
 *  sub-library objects as well).
 *
 * \def  ALIB_REVISION
 *  The \b %ALib revision number. The value of this macro is written into field
 *  \alib{lang,Library::Revision} of singleton \ref aworx::lib::ALIB (and corresponding
 *  sub-library singletons as well).
 *
 * \def  ALIB_COMPILATION_FLAGS
 *  Macro to provide the a compilation flag verifier value to be used with method
 *  \alib{lang,Library::VerifyCompilationFlags} of singleton \alib{ALIB}.
 *
 * @}
 * @}
 */

#if defined(DOX_PARSER)
    #define  ALIB_COMPILATION_FLAGS
#else
    #define ALIB_DEBUG_VFYBIT                  (1 <<  0)
    #define ALIB_DEBUG_STRINGS_VFYBIT          (1 <<  1)

    #define ALIB_FEAT_THREADS_VFYBIT           (1 << 10)
    #define ALIB_FEAT_SINGLETON_MAPPED_VFYBIT  (1 << 11)
    #define ALIB_FEAT_BOXING_FTYPES_VFYBIT     (1 << 12)
    #define ALIB_FEAT_BOXING_STD_VECTOR_VFYBIT (1 << 13)

    #define ALIB_MODULE_ALL_VFYBIT             (1 << 20)
    #define ALIB_MODULE_STRINGS_VFYBIT         (1 << 21)
    #define ALIB_MODULE_BOXING_VFYBIT          (1 << 22)


    #define    ALIB_COMPILATION_FLAGS                                                            \
    ( ALIB_DEBUG_VFYBIT + ( ALIB_DEBUG                          * ALIB_DEBUG_VFYBIT           )  \
                        + ( ALIB_FEAT_THREADS_VFYBIT            * ALIB_FEAT_THREADS           )  \
                        + ( ALIB_FEAT_SINGLETON_MAPPED_VFYBIT   * ALIB_FEAT_SINGLETON_MAPPED  )  \
                        + ( ALIB_FEAT_BOXING_FTYPES_VFYBIT      * ALIB_FEAT_BOXING_FTYPES     )  \
                        + ( ALIB_FEAT_BOXING_STD_VECTOR_VFYBIT  * ALIB_FEAT_BOXING_STD_VECTOR )  \
                        + ( ALIB_DEBUG_STRINGS_VFYBIT           * ALIB_DEBUG_STRINGS          )  \
                        + ( ALIB_MODULE_ALL_VFYBIT              * ALIB_MODULE_BOXING          )  \
                        + ( ALIB_MODULE_STRINGS_VFYBIT          * ALIB_MODULE_STRINGS         )  \
                        + ( ALIB_MODULE_BOXING_VFYBIT           * ALIB_MODULE_BOXING          )  \
    )
#endif



#if ALIB_MODULE_BOXING  || ALIB_MODULE_STRINGS

namespace aworx { namespace lib {

  /**
   * Internals of namespace #aworx::lib
   */
  namespace detail {

    #if defined(DOX_PARSER)
        /** ************************************************************************************
         * Same as \c std::strlen and \c std::wcslen but using char32_t arrays.
         * \note
         *   As far as we know, no (fast) platform specific versions of this method is
         *   available.
         *   Therefore, this method together with \alib{detail::strlen32} uses a
         *   preprocessor switch dependent on the sizeof(wchar_t).
         *
         * @param s Pointer to the start of the cstring.
         *
         * @return  The length of string, aka the first index containing a value \c 0.
         **************************************************************************************/
        ALIB_API extern
        size_t   strlen16( const char16_t* s );

        /** ************************************************************************************
         * Same as \c std::strlen and \c std::wcslen but using char32_t arrays.
         * \note
         *   As far as we know, no (fast) platform specific versions of this method is
         *   available.
         *   Therefore, this method together with \alib{detail::strlen16} uses a
         *   preprocessor switch dependent on the sizeof(wchar_t).
         *
         * @param s Pointer to the start of the cstring.
         *
         * @return  The length of string, aka the first index containing a value \c 0.
         **************************************************************************************/
        inline
        size_t   strlen32( const char32_t* s )
        {
            static_assert( sizeof(wchar_t) == sizeof( char32_t), "Error: Platform not supported" );
            return wcslen( reinterpret_cast<const wchar_t*>(s) );
        }

    #elif ALIB_SIZEOF_WCHAR_T == 4
        ALIB_API extern
        size_t   strlen16( const char16_t* s );

        inline
        size_t   strlen32( const char32_t* s )
        {
            static_assert( sizeof(wchar_t) == sizeof( char32_t), "Error: Platform not supported" );
            return wcslen( reinterpret_cast<const wchar_t*>(s) );
        }
    #else
        inline
        size_t   strlen16( const char16_t* s )
        {
            static_assert( sizeof(wchar_t) == sizeof( char16_t), "Error: Platform not supported" );
            return wcslen( reinterpret_cast<const wchar_t*>(s) );
        }

        ALIB_API extern
        size_t   strlen32( const char32_t* s );
    #endif

}}} //namespace [aworx::lib::detail]

#endif  // ALIB_MODULE_BOXING || ALIB_MODULE_STRINGS


#if ALIB_MODULE_STRINGS

namespace aworx { namespace lib {


// #################################################################################################
// forward declarations
// #################################################################################################
#if ALIB_MODULE_CONFIGURATION
    namespace config  { class  Configuration;
                        struct VariableDecl;   }
    namespace threads { class  ThreadLock;
                        class  SmartLock;            }
    namespace time    { class  Ticks;                }
#endif

// #################################################################################################
// Variables
// #################################################################################################
#if ALIB_MODULE_CONFIGURATION
    /**
     * Configuration variables of \alib.
     * \note
     *  The variables are declared using \alib{lang,T_EnumMetaDataDecl,enum meta data}
     *  and macro \ref ALIB_CONFIG_VARIABLES.
     *  Hence, all variable categories, names, default values and such can be modified
     *  by software using \alib by modifying the resource data of the
     *  \ref aworx::lib::ALIB "ALib library singleton".
     */
    enum class Variables
    {
        LOCALE               = 1   , ///< \alib Resourced variable.
        WAIT_FOR_KEY_PRESS   = 2   , ///< \alib Resourced variable.
        HAS_CONSOLE_WINDOW   = 3   , ///< \alib Resourced variable.
    };
#endif // ALIB_MODULE_CONFIG


// #################################################################################################
// class ALIB
// #################################################################################################

/** ************************************************************************************************
 * This is the library class for namespace \ref aworx::lib. As \alib is more a collection of
 * libraries than a simple one, in respect to library initialization not too much is performed
 * (in method #init), because the duties are distributed to the sub-libraries.
 *
 * Apart from implementing class \b %Library, this class is a 100% static placeholder for a few
 * global methods and fields.
 *
 * \note In C# and Java implementations of this class, debug \e 'shortcuts' to methods of class
 *       \ref aworx::lib::lang::Report "Report" exist. In the C++ version, such methods are provided as
 *       macros named \e 'ALIB_XXX', e.g #ALIB_ASSERT_ERROR.
 *
 * <p>
 * \note The availability of certain fields and methods of this class is dependent the distribution
 *       version of \b %ALib. With module <b>%ALib Singleton</b>, the class does not exist at
 *       all.<br>
 *       See \ref aworx::lib for more "namespace documentation" for information
 *       about \b %ALib modules and the distributions available.
 **************************************************************************************************/
class ALib  : public lang::Library
{
    // #############################################################################################
    // internal statics
    // #############################################################################################
    protected:

    // #############################################################################################
    // Public fields
    // #############################################################################################
    public:
        /**
        * If \c true, within #TerminationCleanUp, it is waited for a key press in the console
        * window.<br>
        * By default, this flag is enabled when debugging a console application under Visual Studio.<br>
        * This default behavior can be overruled by setting configuration variable
        * [ALIB_WAIT_FOR_KEY_PRESS](../group__GrpALoxConfigVars.html).<br>
        * In addition, this public flag may be modified at runtime (after method #Init was invoked).
        */
        bool         WaitForKeyPressOnTermination=                                            false;

        /**
         * This is a smart mutex that allows to lock an applications' <em>standard output
         * streams</em>.
         *
         * In multi-threaded processes, to protect the output streams from concurrent access,
         * this smart lock might be used by any \e entity that writes data to the streams.
         * Before it can be used (acquired and released), it is needed to register with the object
         * using
         * \ref aworx::lib::threads::SmartLock::AddAcquirer "SmartLock::AddAcquirer".
         * This has to be done once per thread that aims to write to the stream. Then, prior to
         * writing, this object has to be acquired and after writing released.
         *
         * Because often, the standard \e output stream and standard \e error stream are identical,
         * \b %ALib provides one single lock for both, to protect also against interwoven
         * standard output and error information.
         *
         * If the 'entity' that is registering is not of type
         * \ref aworx::lib::threads::ThreadLock "ThreadLock" it is allowed to provide \c nullptr
         * in the parameter of method \b AddAcquirer. In this case, the process of adding and
         * removing \e acquirers is not performed in a thread safe way. Therefore it is advised
         * to register so called anonymous (\c nullptr) \e acquirers only at bootstrap time, when
         * no parallel threads were started, yet.
         *
         * If an application is deemed to always write to the standard output streams from within
         * multiple threads, an alternative to registering each writing entity, is to
         * invoke \b AddAcquirer just two times in a row with \c nullptr at the start of a process
         * and then never do this again (and never de-register). This way, no thread needs
         * to register/deregister but threads may still \b Acquire and \b Release the lock without
         * being registered. In other words, once a smart lock is enabled, subsequent registrations
         * are just used to count and identify the de-registration.
         *
         * \note
         *   The advantage of the SmartLock is that if only one 'entity' registered, no
         *   system \e mutexes will be used with \b Acquire and \b Release, hence there is
         *   a performance gain. Such gain is not noticeable for the 'slow' terminal console output,
         *   but it is for fast, buffered output streams.
         * <p>
         * \note
         *   Logging library \b %ALox, which is built on \b %ALib, will register whenever a \e Logger
         *   is used that writes to the standard output stream. Hence, applications that in
         *   parallel use, e.g. 'std::cout', should register at bootstrap and \e acquire this
         *   instance prior to writing. This way, log output and other application output is
         *   not mixed, but separated in different Lines.
         * <p>
         * \note
         *   This fields is available only in the complete distribution version of \b %ALib.
         */
        #if ALIB_MODULE_ALL
            threads::SmartLock&                         StdOutputStreamsLock;
        #endif

    // #############################################################################################
    // Constructor
    // #############################################################################################
    public:
        ALIB_API        ALib();

    // #############################################################################################
    // Environment definition/detection
    // #############################################################################################
    public:

        #if ALIB_MODULE_CONFIGURATION
            /** ************************************************************************************
             * This determines if the current process has console output window attached.
             * While this is not detectable in Unix like systems (or just with huge efforts), in
             * windows it is. The determination works as follows
             *  - If configuration variable [ALIB_HAS_CONSOLE_WINDOW](../group__GrpALoxConfigVars.html)
             *    is set, its value is returned.
             *  - Otherwise, on Unix like OS\c true is returned
             *  - On Windows OS it is determined if a console window is attached to the process
             *    using system call \e GetConsoleWindow() and compare its result to \e NULL.
             *  @return \c true if the application has a console window attached.
             *
             * \note
             *   This fields is available only with module <b>%ALib Configuration</b> or with the
             *   complete distribution version of \b %ALib.
             **************************************************************************************/
            ALIB_API
            bool                        HasConsoleWindow();
        #endif

        #if ALIB_MODULE_ALL
            /** ************************************************************************************
             * If \c true, the current process is under the hood of a debugger.
             *
             * \note
             *   This fields is available only in the complete distribution version of \alib.
             *
             * @return \c true if the application is run in a debugger.
             **************************************************************************************/
            ALIB_API
            bool                        IsDebuggerPresent();

        #endif

    // #############################################################################################
    // Compilation Flags
    // #############################################################################################
    public:

        /** ****************************************************************************************
         * Checks the versions of \alib and if the current compilation unit shares compatible
         * compilation symbols with the \alib compilation.
         *
         * This method should be invoked in the bootstrap code of your processes and libraries
         * to check for compilation/link mismatch.
         * Use macro \ref ALIB_COMPILATION_FLAGS for parameter \p compilationFlags
         *
         * @param alibVersion      The \alib version required.
         * @param compilationFlags The flags as defined in invoking compilation unit.
         *                         Use \ref ALIB_COMPILATION_FLAGS.
         ******************************************************************************************/
        ALIB_API
        void     CheckCompatibility( int      alibVersion,
                                     uint64_t compilationFlags );


    // #############################################################################################
    // Other static interface methods
    // #############################################################################################
    public:
        /** ****************************************************************************************
         * Suspends the current thread by calling <em>std::this_thread::sleep_for</em>.
         * This is for compatibility with other platform versions of \b %ALib.
         * Variants of this method are #SleepMicros and #SleepNanos.
         *
         *  @param milliseconds    Sleep time in milliseconds.
         ******************************************************************************************/
        ALIB_API  static void SleepMillis( int milliseconds );

        /** ****************************************************************************************
         * Suspends the current thread by calling <em>std::this_thread::sleep_for</em>.
         * This is for compatibility with other platform versions of \b %ALib.
         * Variants of this method are #SleepMillis and #SleepNanos.
         *
         * @param microseconds    Sleep time in milliseconds.
         ******************************************************************************************/
        ALIB_API  static void SleepMicros( int microseconds );

        /** ****************************************************************************************
         * Suspends the current thread by calling <em>std::this_thread::sleep_for</em>.
         * This is for compatibility with other platform versions of \b %ALib.
         * Variants of this method are #SleepMicros and #SleepMillis.
         *
         * @param nanoseconds    Sleep time in nanoseconds.
         ******************************************************************************************/
        ALIB_API  static void SleepNanos( int nanoseconds );

        #if ALIB_MODULE_CONFIGURATION
            /** ************************************************************************************
             * Suspends the current thread by calling <em>std::this_thread::sleep_for</em>.
             * Provided for compatibility with other platform versions of \b %ALib.
             * Variants of this method are #SleepMillis, #SleepMicros and #SleepNanos.
             *
             * @param ticks Sleep time in \b %Ticks.
             **************************************************************************************/
            ALIB_API static void Sleep( const time::Ticks& ticks );
        #endif


    // #############################################################################################
    // Internal methods
    // #############################################################################################
    protected:
        /** ****************************************************************************************
         * Implementation of \alib{lang,Library::init}.
         *
         * In phase \alib{lang,Library::Phases::final} performs:
         * - In glibc versions of \b %ALib (GNU/unix) probably invoke glibc method
         *   <em>setlocale()</em>, depending on the setting of the environment variables
         *   <em>LANG</em> and <em>LANGUAGE</em>
         *   and depending on \b %ALib configuration variable
         *   [ALIB_LOCALE](../group__GrpALoxConfigVars.html).
         *
         *   In addition, invokes
         *   \alib{strings,NumberFormat::SetFromLocale} on static singleton
         *   \alib{strings,NumberFormat::Global}.
         *
         * - Config variable [WAIT_FOR_KEY_PRESS](../group__GrpALoxConfigVars.html)
         *   is read and field #WaitForKeyPressOnTermination set accordingly
         *
         *
         * @param phase  The initialization phase to perform.
         ******************************************************************************************/
        virtual void        init( Phases phase )                                           override;

        /** ****************************************************************************************
         * Implementation of
         * \alib{lang,Library::terminationCleanUp}.
         ******************************************************************************************/
        virtual void        terminationCleanUp()                                           override;


};// class ALib


/** ************************************************************************************************
 * The static library singleton of namespace #aworx::lib.
 **************************************************************************************************/
ALIB_API
extern ALib   ALIB;

} // namespace lib

/** Type alias name in namespace #aworx. */
using ALib=                     aworx::lib::ALib;

} // namespace aworx


#if ALIB_MODULE_CONFIGURATION
    ALIB_CONFIG_VARIABLES( aworx::lib::Variables, lib::ALIB, "Var" )
#endif


// #################################################################################################
// Further standard includes (for convenience)
// #################################################################################################
#if !defined(DOX_PARSER)
#define ALIB_PROPER_INCLUSION
#endif

    #include "alib/strings/applicables.hpp"

#undef ALIB_PROPER_INCLUSION

#endif // ALIB_MODULE_STRINGS


#endif // just module ALib Singleton

#endif // HPP_ALIB
