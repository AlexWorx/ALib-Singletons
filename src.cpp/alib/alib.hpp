// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
/** @file */ // Hello Doxygen

#ifndef HPP_ALIB
#define HPP_ALIB 1


// Uncomment to test for unnecessary includes. Must not be done with cotire unity builds.
// #define HPP_COM_ALIB_TEST_INCLUDES

// compiler check
#if defined(__GNUC__)
    #if __cplusplus < 201103L
        #error "ALib Needs C++ 11. Compilation aborted"
    #endif
#endif

#if defined ( _MSC_VER )  &&  _MSC_VER < 1600 // VS 2010 == VC10 == _MSC_VER 1600
    #error "ALib Needs C++ 11. Compilation aborted"
#endif

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
    //! @endcond NO_DOX

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
 * This group of symbols determine the availability of different <b>ALib Modules</b> of the
 * \b %ALib distribution used.<br>
 * The symbols are defined in header <c>alib/distribution.hpp</c>, which varies per distribution.
 *
 * For module <b>ALib Singleton</b> no symbol is defined, as this module is included in any
 * \b ALib distribution.
 *
 * \def  ALIB_MODULE_STRINGS
 *  Denotes if module <b>ALib Strings</b> is available in the library used.
 *
 * \def  ALIB_MODULE_BOXING
 *  Denotes if module <b>ALib Boxing</b> is available in the library used.
 *
 * \def  ALIB_MODULE_CONFIGURATION
 *  Denotes if module <b>ALib Configuration</b> is available in the library used.
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
    #define     ALIB_MODULE_ALL
#else
#define ALIB_PROPER_INCLUSION
#endif


    // basics used with all modules
    #include "alib/alib/prepro.hpp"

    // read module-specific (distribution specific) preprocessor symbols
    #include "alib/distribution.hpp"

    #if !defined(ALIB_MODULE_ALL)
        #define ALIB_MODULE_ALL 0
    #endif

    #if !defined(ALIB_MODULE_CONFIGURATION)
        #define ALIB_MODULE_CONFIGURATION   ALIB_MODULE_ALL
    #endif
    #if !defined(ALIB_MODULE_BOXING)
        #define ALIB_MODULE_BOXING          ALIB_MODULE_ALL

    #endif
    #if !defined(ALIB_MODULE_STRINGS)
        #define ALIB_MODULE_STRINGS         (ALIB_MODULE_ALL || ALIB_MODULE_CONFIGURATION)
    #endif

    #if ALIB_MODULE_ALL  && !( ALIB_MODULE_BOXING || ALIB_MODULE_STRINGS )
        #pragma message ("Contradictionary definitions in 'alib/distribution.hpp'" )
    #endif

    #if ALIB_MODULE_BOXING || ALIB_MODULE_STRINGS
        #include "alib/alib/debug.hpp"
    #endif

    // Header: RTTI always needed
    #include "alib/lang/rtti.hpp"

    // Module: Singleton (the first, independent module)
    #include "alib/lang/singleton.hpp"

    // Module: Boxing
    #if ALIB_MODULE_BOXING
        #include "alib/lang/types.hpp"
        #include "alib/boxing/boxing.hpp"
    #else
        #define ALIB_FEAT_BOXING_FTYPES      0
        #define ALIB_FEAT_BOXING_STD_VECTOR  0
    #endif

    #if ALIB_MODULE_STRINGS
        #if !defined(HPP_ALIB_LANG_TYPES)
            #include "alib/lang/types.hpp"
        #endif

        #include "alib/lang/enums.hpp"
        #include "alib/strings/cstring.hpp"
        #include "alib/strings/string.hpp"
    #else
        #define ALIB_DEBUG_STRINGS  0
    #endif


    #if ALIB_MODULE_STRINGS
        #include "alib/strings/tstring.hpp"
        #include "alib/strings/stringliteral.hpp"
        #include "alib/strings/astring.hpp"
        #include "alib/strings/preallocatedstring.hpp"
    #endif

    #if ALIB_MODULE_STRINGS && ALIB_MODULE_BOXING && ALIB_FEAT_BOXING_FTYPES
        #include "alib/strings/stringboxing.hpp"
    #endif

    #if ALIB_MODULE_ALL
        #if !ALIB_FEAT_BOXING_FTYPES
            static_assert(0, "The full version of ALib must not be compiled with disabled default "
                             "boxing of fundamental types (See ALIB_FEAT_BOXING_FTYPES_OFF)."
        #endif
        #include "alib/lang/report.hpp"
    #endif

#undef  ALIB_PROPER_INCLUSION

// anything else is omitted with module "ALib Singleton"
#if ALIB_MODULE_BOXING || ALIB_MODULE_STRINGS


// #################################################################################################
// Version verification macros
// #################################################################################################

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
 * \def  ALIB_VERSION_VERYFIER
 *  The ALib version. The value of this macro is written into field
 *  \ref aworx::lib::ALIB::Version "ALIB::Version".
 *
 * \def  ALIB_COMPATIBILITY_VERIFYER
 *  Macro that 'calculates' the bits set in field
 *  \ref aworx::lib::ALIB::CompilationFlags "ALIB::CompilationFlags".
 *
 * \def  ALIB_DEBUG_VFYBIT
 *  The bit in field \ref aworx::lib::ALIB::CompilationFlags "ALIB::CompilationFlags" that
 *  stores information about the value of code selection symbol \ref ALIB_DEBUG.
 *
 * \def  ALIB_DEBUG_STRINGS_VFYBIT
 *  The bit in field \ref aworx::lib::ALIB::CompilationFlags "ALIB::CompilationFlags" that
 *  stores information about the value of code selection symbol \ref ALIB_DEBUG_STRINGS.
 *
 * \def  ALIB_FEAT_THREADS_VFYBIT
 *  The bit in field \ref aworx::lib::ALIB::CompilationFlags "ALIB::CompilationFlags" that
 *  stores information about the value of code selection symbol \ref ALIB_FEAT_THREADS.
 *
 * \def  ALIB_FEAT_SINGLETON_MAPPED_VFYBIT
 *  The bit in field \ref aworx::lib::ALIB::CompilationFlags "ALIB::CompilationFlags" that
 *  stores information about the value of code selection symbol \ref ALIB_FEAT_SINGLETON_MAPPED.
 *
 * \def  ALIB_FEAT_BOXING_FTYPES_VFYBIT
 *  The bit in field \ref aworx::lib::ALIB::CompilationFlags "ALIB::CompilationFlags" that
 *  stores information about the value of code selection symbol \ref ALIB_FEAT_BOXING_FTYPES.
 *
 * \def  ALIB_FEAT_BOXING_STD_VECTOR_VFYBIT
 *  The bit in field \ref aworx::lib::ALIB::CompilationFlags "ALIB::CompilationFlags" that
 *  stores information about the value of code selection symbol \ref ALIB_FEAT_BOXING_STD_VECTOR.
 *
 * \def  ALIB_MODULE_STRINGS_VFYBIT
 *  The bit in field \ref aworx::lib::ALIB::CompilationFlags "ALIB::CompilationFlags" that
 *  stores information about the value of code selection symbol \ref ALIB_MODULE_STRINGS.
 *
 * \def  ALIB_MODULE_BOXING_VFYBIT
 *  The bit in field \ref aworx::lib::ALIB::CompilationFlags "ALIB::CompilationFlags" that
 *  stores information about the value of code selection symbol \ref ALIB_MODULE_BOXING.
 *
 * \def  ALIB_MODULE_ALL_VFYBIT
 *  The bit in field \ref aworx::lib::ALIB::CompilationFlags "ALIB::CompilationFlags" that
 *  stores information about the value of code selection symbol \ref ALIB_MODULE_ALL.
 * @}
 * @}
 */


#define ALIB_VERSION_VERYFIER              1702

#define ALIB_DEBUG_VFYBIT                  (1 <<  0)
#define ALIB_DEBUG_STRINGS_VFYBIT          (1 <<  1)

#define ALIB_FEAT_THREADS_VFYBIT           (1 << 10)
#define ALIB_FEAT_SINGLETON_MAPPED_VFYBIT  (1 << 12)
#define ALIB_FEAT_BOXING_FTYPES_VFYBIT     (1 << 12)
#define ALIB_FEAT_BOXING_STD_VECTOR_VFYBIT (1 << 13)

#define ALIB_MODULE_ALL_VFYBIT             (1 << 20)
#define ALIB_MODULE_STRINGS_VFYBIT         (1 << 21)
#define ALIB_MODULE_BOXING_VFYBIT          (1 << 22)


#define    ALIB_COMPATIBILITY_VERIFYER  (   ALIB_DEBUG_VFYBIT                   * ALIB_DEBUG                    \
                                          + ALIB_FEAT_THREADS_VFYBIT            * ALIB_FEAT_THREADS             \
                                          + ALIB_FEAT_SINGLETON_MAPPED_VFYBIT   * ALIB_FEAT_SINGLETON_MAPPED    \
                                          + ALIB_FEAT_BOXING_FTYPES_VFYBIT      * ALIB_FEAT_BOXING_FTYPES       \
                                          + ALIB_FEAT_BOXING_STD_VECTOR_VFYBIT  * ALIB_FEAT_BOXING_STD_VECTOR   \
                                          + ALIB_DEBUG_STRINGS_VFYBIT           * ALIB_DEBUG_STRINGS            \
                                          + ALIB_MODULE_ALL_VFYBIT              * ALIB_MODULE_BOXING            \
                                          + ALIB_MODULE_STRINGS_VFYBIT          * ALIB_MODULE_STRINGS           \
                                          + ALIB_MODULE_BOXING_VFYBIT           * ALIB_MODULE_BOXING            \
                                        )



namespace aworx { namespace lib {


// #################################################################################################
// forward declarations
// #################################################################################################
#if ALIB_MODULE_CONFIGURATION
    namespace config  { class  Configuration;
                        struct VariableDefinition;   }
    namespace threads { class  SmartLock;            }
    namespace time    { class  Ticks;                }
#endif

// #################################################################################################
// class ALIB
// #################################################################################################

/** ************************************************************************************************
 * This class is a 100% static placeholder for global methods and fields of
 * \ref aworx::lib "ALib".
 * Among the things implemented here are:
 * - Collecting information on the executed process and its environment.
 * - Initialization of several ALib components with methods #Init and #TerminationCleanUp.
 * - Thread sleep methods
 *
 * \note In C# and Java implementations of this class, debug \e 'shortcuts' to methods of class
 *       \ref aworx::lib::lang::Report "Report" exist. In the C++ version, such methods are provided as
 *       macros named \e 'ALIB_XXX', e.g #ALIB_ASSERT_ERROR.
 *
 * <p>
 * \note The availability of certain fields and methods of this class is dependent the distribution
 *       version of \b %ALib. With module <b>ALib Singleton</b>, the class does not exist at
 *       all.<br>
 *       See \ref aworx::lib for more "namespace documentation" for information
 *       about \b %ALib modules and the distributions available.
 **************************************************************************************************/
class ALIB
{
    // #############################################################################################
    // internal statics
    // #############################################################################################
    protected:

        /**  State of initialization, used to avoid double initialization.   */
        static bool                                     initialized;

    // #############################################################################################
    // Public fields
    // #############################################################################################
    public:
        /** Returns state of initialization, used internally to avoid deadlocks during init.
         *  @return \c true if was initialized already. */
        static bool                                     IsInitialized()      { return initialized; }

        /**
         * These flags are used internally to detect incompatibilities when linking ALib to
         * binaries that use different compilation flags.
         */
        ALIB_API static    const uint64_t               CompilationFlags;

        /**
         * This is for creation (debug) output on information about the bits found in
         * field #CompilationFlags.
         */
        ALIB_API static
        std::pair <const char*, uint64_t>               CompilationFlagMeanings[9];

        /**
         * The ALib version. The versioning follows the scheme YYMM (2-digit year, 2-digit month)
         * of the initial release date.
         * Besides this version number, field #Revision indicates if this is a revised version
         * of a former release.
         */
        ALIB_API static    const int                    Version;

        /**
         * The revision number of this release. Each ALib #Version is initially released as
         * revision \e 0. Pure bug-fix releases that do not change the interface of ALib
         * are holding the same #Version but an increased number in this field.
         */
        ALIB_API static    const int                    Revision;


        #if ALIB_MODULE_CONFIGURATION
            /**
             * The name of the configuration category of configuration variables used by ALib.<br>
             * Defaults to "ALIB".<br>
             * This value can be changed to avoid conflicts between applications (especially in
             * respect to environment variable settings). Changes should be placed at very initial
             * bootstrap code, before the invocation of #Init.
             * <p>
             * \note
             *   This field and corresponding variable definitions found in this class, are available
             *   only in module <b>ALib Configuration</b> or the complete distribution version
             *   of \b %ALib.
             */
            ALIB_API static    strings::String              ConfigCategoryName;

            ALIB_API static    config::VariableDefinition   RTE;                    ///< Configuration variable definition
            ALIB_API static    config::VariableDefinition   LOCALE;                 ///< Configuration variable definition
            ALIB_API static    config::VariableDefinition   WAIT_FOR_KEY_PRESS;     ///< Configuration variable definition
            ALIB_API static    config::VariableDefinition   HAS_CONSOLE_WINDOW;     ///< Configuration variable definition

        #endif // ALIB_MODULE_CONFIG

        /**
        * If \c true, within #TerminationCleanUp, it is waited for a key press in the console
        * window.<br>
        * By default, this flag is enabled when debugging a console application under Visual Studio.<br>
        * This default behavior can be overruled by setting configuration variable
        * [ALIB_WAIT_FOR_KEY_PRESS](../group__GrpALoxConfigVars.html).<br>
        * In addition, this public flag may be modified at runtime (after method #Init was invoked).
        */
        ALIB_API static    bool                            WaitForKeyPressOnTermination;

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
         * ALib provides one single lock for both, to protect also against interwoven
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
         *   Logging library \b ALox, which is built on ALib, will register whenever a \e Logger
         *   is used that writes to the standard output stream. Hence, applications that in
         *   parallel use, e.g. 'std::cout', should register at bootstrap and \e acquire this
         *   instance prior to writing. This way, log output and other application output is
         *   not mixed, but separated in different Lines.
         * <p>
         * \note
         *   This fields is available only in the complete distribution version of \b %ALib.
         */
        #if ALIB_MODULE_ALL
        ALIB_API static    threads::SmartLock              StdOutputStreamsLock;
        #endif

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
             *   This fields is available only with module <b>ALib Configuration</b> or with the
             *   complete distribution version of \b %ALib.
             **************************************************************************************/
            ALIB_API
            static bool                 HasConsoleWindow();
        #endif

        #if ALIB_MODULE_ALL
            /** ************************************************************************************
             * If \c true, the current process is under the hood of a debugger. This is evaluated
             * within \ref aworx::lib::ALIB::Init "ALIB::Init".
             * \see Field #DebuggerProcessNames.
             *
             * \note
             *   This fields is available only in the complete distribution version of \b %ALib.
             * @return \c true if the application is run in a debugger.
             **************************************************************************************/
            ALIB_API
            static bool                 IsDebuggerPresent();

            /** ************************************************************************************
             * Available under Unix like OS (incl. Mac OS) only.
             * Used by method #IsDebuggerPresent to determine if a debugger process is found in the
             * list of parent processes.<br>
             * May contain a list of process names, separated by the pipe symbol (<c>'|'</c>). It is
             * tested if the name of the parent process starts with one of the names contained herein.
             * Defaults to \c 'gdb|debugserver' and can be changed on bootstrap of the process if a
             * different debugger is used.
             *
             * \note
             *   This fields is available only in the complete distribution version of \b %ALib.
             **************************************************************************************/
            #if defined(__unix__) || defined(__APPLE__)
            ALIB_API
            static String               DebuggerProcessNames;
            #endif
        #endif

    // #############################################################################################
    // Init/TerminationCleanUp()
    // #############################################################################################
    public:
        /** ****************************************************************************************
         * This method must be called prior to using ALib, e.g. at the beginning of
         * the \c main() method of an application. It is OK, to call this method more than once, which
         * allows independent code blocks (e.g. libraries) to bootstrap %ALIB independently.
         * However, only the first invocation is effective with the exclamation that if
         * command line parameters are provided with a call, those are set.
         * Also, the very first invocation should not be interrupted by a parallel invocation of a
         * second thread. Consequently, it has to be assured that this method is invoked once on
         * the real bootstrap an app.
         *
         * The following actions are performed in the full distribution version of \b ALib. With
         * different <b>ALib Module</b> distributions, none-applicable steps are omitted.
         * - The configuration object is created
         * - Classes of ALib namespace \ref aworx::lib::threads are prepared to work properly
         * - Classes of ALib namespace \ref aworx::lib::time are prepared to work properly
         * - glibc versions of ALib (GNU/unix) probably invoke glibc method
         *   <em>setlocale()</em>, depending on the setting of the environment variables
         *   <em>LANG</em> and <em>LANGUAGE</em>
         *   and depending on ALib configuration variable
         *   [ALIB_LOCALE](../group__GrpALoxConfigVars.html).
         * - Config variable [WAIT_FOR_KEY_PRESS](../group__GrpALoxConfigVars.html)
         *   is read and field #WaitForKeyPressOnTermination set accordingly
         *
         * \note If other, custom configuration data sources should be used already with this method
         *       (to read the configuration variables as described above),
         *       according configuration plug-ins have to be added attached to public, static field
         *       \ref aworx::lib::config::Configuration::Default "Configuration::Default"
         *       prior to invoking this method.
         *
         * <p>
         *
         * \note %ALIB must not be used before all global/static variables are created. Hence, it
         *       is not allowed to initialize %ALIB within static variable initialization code.
         *       This restriction is wanted by design, because different platforms and compilers
         *       implement the initialization phase of static and global code differently and it is
         *       not considered good programming style to rely on C++ bootstrap.
         *       Using %ALIB within C++ bootstrap is undefined behavior.
         *
         * <p>
         *
         * \note On the Windows platform, the Microsoft compiler provides the global variables
         *       <em>__argc</em> and <em>__argv</em> (respectively <em>__wargv</em> for wide
         *       character binaries. These variables a can be used if this method is invoked
         *       outside of the <em>main()</em> method.
         *
         * @param argc    Parameter usually taken from <em>standard C</em> \c main() method
         *                (the number of arguments in \p argv).
         *                Defaults to 0.
         * @param argv    Parameter usually taken from <em>standard C</em> \c main() method
         *                (pointer to a list of command line arguments).
         *                Defaults to nullptr.
         ******************************************************************************************/
        ALIB_API
        static void     Init( int argc =0,  char **argv =nullptr );

        /** ****************************************************************************************
         * Variant of method #Init, accepting command line arguments of type \c wchar_t.
         *
         * @param argc    Parameter usually taken from <em>standard C</em> \c main() method
         *                (the number of arguments in \p argv).
         * @param argv    The command line parameters as \c wchar_t.
         ******************************************************************************************/
        ALIB_API
        static void     Init( int  argc,    wchar_t **argv );

        /** ****************************************************************************************
         * Cleans up memory on termination. This method is useful if using memory analysis tools
         * (such as Valgrind) to remove any internal allocations before a program terminates.
         ******************************************************************************************/
        ALIB_API
        static void     TerminationCleanUp();


        /** ****************************************************************************************
         * Verifies a given sets of ALib compilation flags with the internal set
         * \ref ALIB::CompilationFlags. In case they are different in a way
         * that ALib gets incompatible (e.g. different class sizes, which results in errors that are
         * very hard to debug), the flags are written to \e cout for comparison and \c false is
         * returned.
         *
         * This method should be called on bootstrap to detect if incompatible library types were
         * built. If several libraries that use ALib are linked together, each should invoke this
         * test against separately. The macro \c ALIB_COMPATIBILITY_VERIFYER will provide the
         * flags.
         *
         * @param flags The flags externally grabbed using macro \c ALIB_COMPATIBILITY_VERIFYER.
         *
         * @return \c true if compatible, \c false else.
         ******************************************************************************************/
        ALIB_API
        static bool    VerifyCompilationFlags( uint64_t flags );

    // #############################################################################################
    // Other static interface methods
    // #############################################################################################
    public:
        /** ****************************************************************************************
         * Suspends the current thread by calling <em>std::this_thread::sleep_for</em>.
         * This is for compatibility with other platform versions of ALib.
         * Variants of this method are #SleepMicros and #SleepNanos.
         *
         *  @param milliseconds    Sleep time in milliseconds.
         ******************************************************************************************/
        ALIB_API  static void SleepMillis( int milliseconds );

        /** ****************************************************************************************
         * Suspends the current thread by calling <em>std::this_thread::sleep_for</em>.
         * This is for compatibility with other platform versions of ALib.
         * Variants of this method are #SleepMillis and #SleepNanos.
         *
         * @param microseconds    Sleep time in milliseconds.
         ******************************************************************************************/
        ALIB_API  static void SleepMicros( int microseconds );

        /** ****************************************************************************************
         * Suspends the current thread by calling <em>std::this_thread::sleep_for</em>.
         * This is for compatibility with other platform versions of ALib.
         * Variants of this method are #SleepMicros and #SleepMillis.
         *
         * @param nanoseconds    Sleep time in nanoseconds.
         ******************************************************************************************/
        ALIB_API  static void SleepNanos( int nanoseconds );

        #if ALIB_MODULE_CONFIGURATION
            /** ************************************************************************************
             * Suspends the current thread by calling <em>std::this_thread::sleep_for</em>.
             * Provided for compatibility with other platform versions of ALib.
             * Variants of this method are #SleepMillis, #SleepMicros and #SleepNanos.
             *
             * @param ticks Sleep time in \b %Ticks.
             **************************************************************************************/
            ALIB_API static void Sleep( const time::Ticks& ticks );
        #endif

    #if ALIB_MODULE_BOXING || ALIB_MODULE_STRINGS
        #if defined(DOX_PARSER)
            /** ************************************************************************************
             * Same as \c std::strlen and \c std::wcslen but using char32_t arrays.
             * \note
             *   As far as we know, no (fast) platform specific versions of this method is
             *   available. Therefore, this method, together with #strlen32 use a preprocessor
             *   switch dependent on the sizeof(wchar_t).
             *
             * @param s Pointer to the start of the cstring.
             *
             * @return  The length of string, aka the first index containing a value \c 0.
             **************************************************************************************/
            ALIB_API
            static size_t   strlen16( const char16_t* s );

            /** ************************************************************************************
             * Same as \c std::strlen and \c std::wcslen but using char32_t arrays.
             * \note
             *   As far as we know, no (fast) platform specific versions of this method is
             *   available. Therefore, this method, together with #strlen32 use a preprocessor
             *   switch dependent on the sizeof(wchar_t).
             *
             * @param s Pointer to the start of the cstring.
             *
             * @return  The length of string, aka the first index containing a value \c 0.
             **************************************************************************************/
            inline
            static size_t   strlen32( const char32_t* s )
            {
                static_assert( sizeof(wchar_t) == sizeof( char32_t), "Error: Platform not supported" );
                return wcslen( reinterpret_cast<const wchar_t*>(s) );
            }

        #elif ALIB_SIZEOF_WCHAR_T == 4
            ALIB_API
            static size_t   strlen16( const char16_t* s );

            inline
            static size_t   strlen32( const char32_t* s )
            {
                static_assert( sizeof(wchar_t) == sizeof( char32_t), "Error: Platform not supported" );
                return wcslen( reinterpret_cast<const wchar_t*>(s) );
            }
        #else
            inline
            static size_t   strlen16( const char16_t* s )
            {
                static_assert( sizeof(wchar_t) == sizeof( char16_t), "Error: Platform not supported" );
                return wcslen( reinterpret_cast<const wchar_t*>(s) );
            }

            ALIB_API
            static size_t   strlen32( const char32_t* s );
        #endif
    #endif


    // #############################################################################################
    // Internal methods
    // #############################################################################################
    protected:
        /** ****************************************************************************************
         * Implements public methods #Init.
         ******************************************************************************************/
        static void           init();

};// class ALIB

} // namespace lib

/** Type alias name in namespace #aworx. */
using ALIB=                     aworx::lib::ALIB;


} // namespace aworx


// #################################################################################################
// Further standard includes (for convenience)
// #################################################################################################
// #################################################################################################
#if ALIB_MODULE_STRINGS
    #if !defined(DOX_PARSER)
    #define ALIB_PROPER_INCLUSION
    #endif

        #include "alib/strings/applyto.hpp"
        #include "alib/strings/applyformat.hpp"

    #undef ALIB_PROPER_INCLUSION
#endif


#endif // just module ALib Singleton

#endif // HPP_ALIB_MODULES
