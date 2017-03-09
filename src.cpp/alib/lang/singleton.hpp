// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Essential ALib types needed by every module
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
/** @file */ // Hello Doxygen

// to preserve the right order, we are not includable directly from outside.
#if !defined(ALIB_PROPER_INCLUSION) || defined(HPP_ALIB_LANG_SINGLETON)
    #error "include alib/alib.hpp instead of this header"
#endif

#ifndef HPP_ALIB_LANG_SINGLETON
#define HPP_ALIB_LANG_SINGLETON 1


#if ALIB_DEBUG && !defined (_GLIBCXX_VECTOR) && !defined(_VECTOR_)
    #include <vector>
#endif

/**
  * @addtogroup GrpALibCompilerSymbols
 * @{
 *  \def  ALIB_FEAT_SINGLETON_MAPPED_OFF
 *    This symbol may be passed to the compiler to define code selection symbol
 *    \ref ALIB_FEAT_SINGLETON_MAPPED to be \c 0 and this way overwrite the default setting.
 *
 *    See \ref ALIB_FEAT_SINGLETON_MAPPED for more information.
 *
 *  \def  ALIB_FEAT_SINGLETON_MAPPED_ON
 *    This symbol may be passed to the compiler to define code selection symbol
 *    \ref ALIB_FEAT_SINGLETON_MAPPED to be \c 1 and this way overwrite the default setting.
 *
 *    See \ref ALIB_FEAT_SINGLETON_MAPPED for more information.
 * @}
 *
 * @addtogroup GrpALibCodeSelectorSymbols
 * @{
 *  \def  ALIB_FEAT_SINGLETON_MAPPED
 *    Affects implementation of class
 *    \ref aworx::lib::lang::Singleton "Singleton". If this symbol represents \c true, then
 *    a static hash map is used to find the singleton objects, even if different data segments
 *    exist within one software process.<br>
 *    While the overhead imposed by such implementation is quite small, with this symbol being
 *    \c false, the overhead is omitted in scenarios when such effort is not necessary.
 *
 *    The symbol defaults to \c true on the windows platform, otherwise to \c false. The default
 *    value can be changed by passing one of the symbols
 *    \ref ALIB_FEAT_SINGLETON_MAPPED_OFF or \ref ALIB_FEAT_SINGLETON_MAPPED_ON to the C++ compiler
 *    when building the library.
 * @}
 */
#if defined(DOX_PARSER)
    #define ALIB_FEAT_SINGLETON_MAPPED
    #define ALIB_FEAT_SINGLETON_MAPPED_ON
    #define ALIB_FEAT_SINGLETON_MAPPED_OFF
#else
    #if defined(ALIB_FEAT_SINGLETON_MAPPED)
        #error "ALIB_FEAT_SINGLETON_MAPPED must not be set from outside. Use ALIB_FEAT_SINGLETON_MAPPED_ON/OFF instead!"
    #endif

    #if defined(ALIB_FEAT_SINGLETON_MAPPED_ON) && defined(ALIB_FEAT_SINGLETON_MAPPED_OFF)
        #error "Contradiction in compiler symbols: ALIB_FEAT_SINGLETON_MAPPED_ON and ALIB_FEAT_SINGLETON_MAPPED_OFF set!"
    #endif

    #if !defined(ALIB_FEAT_SINGLETON_MAPPED_ON) && !defined(ALIB_FEAT_SINGLETON_MAPPED_OFF)
        #if defined(_WIN32)
            #define ALIB_FEAT_SINGLETON_MAPPED   1
        #else
            #define ALIB_FEAT_SINGLETON_MAPPED   0
        #endif
    #else
        #if defined(ALIB_FEAT_SINGLETON_MAPPED_OFF)
            #define ALIB_FEAT_SINGLETON_MAPPED   0
        #else
            #define ALIB_FEAT_SINGLETON_MAPPED   1
        #endif
    #endif
#endif //DOX_PARSER


namespace aworx { namespace lib { namespace lang
{

// #################################################################################################
// Unordered map utility for storing type_info objects
// #################################################################################################

//! @cond NO_DOX
#if ALIB_FEAT_SINGLETON_MAPPED
extern ALIB_API bool  getSingleton   ( const std::type_info& type, void* theSingleton );
extern ALIB_API void  storeSingleton ( const std::type_info& type, void* theSingleton );
extern ALIB_API void  removeSingleton( const std::type_info& type );
#endif
//! @endcond NO_DOX


/** ************************************************************************************************
 * \note
 *   This class is extracted and exposed as an own <b>ALib Module</b>, found here:
 *   [ALib Singleton](https://github.com/AlexWorx/ALib-Singleton).
 *
 * <b>Background Information on Template Singletons and Windows OS DLLs:</b><br>
 * This template class implements the singleton design pattern using templates. In principle, this
 * is a very easy and straightforward thing and extensively discussed in the internet and
 * programming literature. However, in combination with using DLLs on Windows OS, things get a
 * little more complicated. A Windows OS DLL provides its own data segment and static function
 * variables defined in template classes (in header files!) are duplicated within DLLs and
 * the main executable. Now, if a standard implementation of the singleton pattern with templates
 * is used, the singletons received are "DLL-wide singletons" but not "process-wide singletons".
 *
 * Therefore, this implementation uses one static hash map to store each singleton instance of
 * any type. Then, if a singleton is requested for the first time, this hash map is consulted
 * for an already existing instance. Only if this fails, the singleton instance is created and
 * stored in the hash map to be found by other DLLs or the main executable.<br>
 * The pointer to the singleton created or found is then stored in static field #singleton of this
 * class. This way, a second request for the singleton (from within the same software entity), will
 * not have the need to search the map again.
 * In other words, the data model is as follows: each derived template type will have exactly one
 * singleton instance, stored in the static hash map which is defined only once (in the ALib
 * DLL or library). Software entities that have their own data segment (e.g. Windows DLLs) each
 * have one dedicated pointer to the singleton created by the entity itself or by one of the
 * other entities.
 *
 * <b>Switching Compilation Mode:</b><br>
 * As said above, the effort done with this implementations is needed only if a software process
 * uses different data segments for different portions of the code, for example processes which open
 * DLLs on Windows OS.
 * As this effort imposes a (small) overhead, the implementation of this class can be switched to
 * a simple implementation version, which just stores the singletons in a static field of the class.
 * The implementation is controlled by code selection symbol \ref ALIB_FEAT_SINGLETON_MAPPED.
 * On Windows OS the symbol defaults to \c true, otherwise to false.<br>
 * Now, Compiler symbols \ref ALIB_FEAT_SINGLETON_MAPPED_ON and \ref ALIB_FEAT_SINGLETON_MAPPED_OFF
 * can be used to overwrite this default settings. This could be done for the following reasons:
 * - \b %ALib is used on Windows OS, but not compiled as a DLL and the code that is using \b %ALib
 *   is restricted to one DLL or the main application exclusively. In this case, symbol
 *   \ref ALIB_FEAT_SINGLETON_MAPPED_OFF may be passed to the compiler to switch compilation
 *   to the simple mode.
 * - \b %ALib is used on GNU/Linux, but the debug features for listing all singletons created
 *   (described below) should be used. In this case, for the purpose of debugging, symbol
 *   \ref ALIB_FEAT_SINGLETON_MAPPED_ON may be passed to the compiler to switch compilation
 *   to use the hash map, even though this is not needed for that platform.
 *
 * <b>Usage:</b><br>
 * The implementation details described above are transparent in respect to using the class.
 *
 * A user type may inherit the singleton feature from this class by being derived from it,
 * with the template parameter \p TDerivedClass set to name just of the derived class type itself.
 * Then, static method #GetSingleton will return a singleton of the derived type.
 *
 * Here is a sample code deriving from this class:
 *
 *  \snippet "DOX_ALIB_LANG_SINGLETON.cpp"     DOX_ALIB_LANG_SINGLETON_1
 *
 * Now, the singleton can be requested as follows:
 *
 *  \snippet "DOX_ALIB_LANG_SINGLETON.cpp"     DOX_ALIB_LANG_SINGLETON_2
 *
 * Note that the singleton is \b not automatically the only instance of the
 * custom class. In this respected, class \b %Singleton is not \e 'strict':
 *
 *  \snippet "DOX_ALIB_LANG_SINGLETON.cpp"     DOX_ALIB_LANG_SINGLETON_3
 *
 * To create classes that implement strict singletons, two things have to be done:
 * 1. Provide a private constructor to the derived class and
 * 2. make parent class \b %Singleton be a friend of it.
 *
 * This is shown in the following sample:
 *  \snippet "DOX_ALIB_LANG_SINGLETON.cpp"     DOX_ALIB_LANG_SINGLETON_STRICT_1
 *  \snippet "DOX_ALIB_LANG_SINGLETON.cpp"     DOX_ALIB_LANG_SINGLETON_STRICT_2
 *
 * Prior to terminating the process, the singletons can be destructed and deleted using namespace function
 * \ref aworx::lib::lang::DeleteSingletons. See this method's description for more information.
 * Especially Note that method
 * \ref aworx::lib::ALIB::TerminationCleanUp "ALIB::TerminationCleanUp" invokes this method already.
 *
 *
 * <b>Restrictions / Penalties:</b><br>
 *
 * - The singleton class needs to have a default (parameterless) constructor.
 *   (This might be overcome with a templated get-method that forwards variadic arguments, but
 *   is not implemented here.)
 * - The singleton class is virtual and hence all derived classes become virtual. This is needed
 *   to be able to have a virtual destructor.
 * - There is a minimal performance penalty in comparison to more simple implementations of the singleton
 *   design pattern: Each <em>'code entity'</em> (DLL or main executable)
 *   needs to retrieve a singleton which was potentially already created by another code
 *   entity, \b once. In other words, only the first request for the singleton incorporates two
 *   small performance penalties for
 *   1. setting and releasing a thread lock (mutex)
 *   2. retrieving the singleton or inserting the singleton if not retrieved.
 * - The memory penalty is also quite minimal and imposed by the creation of a static hash table,
 *   which holds a pointer to each Singleton.
 * - Upon exit of the process, programmers might want to explicitly free the hash table to avoid
 *   the detection of memory leaks by metrics tools like [Valgrind](http://valgrind.org/).
 *   (Otherwise this can be omitted, as the memory is cleaned by the OS probably much faster when a
 *   process exits).
 * - In general, it is advised to think twice before implementing the singleton design pattern.
 *   Often, this is considered bad code design. However, there can be very good reasons for having
 *   singletons in software.
 *   And do not be frustrated if "very wise people" tell you that you must never use a singleton.
 *   Your answer to them is: Each and every created instance of a virtual C++ class contains
 *   a pointer to a singleton, namely the [vtable](https://en.wikipedia.org/wiki/Virtual_method_table)!
 *
 * <b>Listing Types in Debug Compilations:</b><br>
 * As described above, to extend the singleton concept across DLL bounds, a static hash map is
 * needed. Now, in debug compilations (see compilation symbol #ALIB_DEBUG), this map can be
 * dumped any time and this way all singletons created at a certain point at runtime can be
 * listed.
 * For this, ALib provides namespace function
 * \ref aworx::lib::debug::GetSingletons "GetSingletons".
 * This function is using class AString, and hence it is available only with ALib distributions that
 * includes module <b>ALib String</b>.
 * Fore example modules
 * [ALib Singleton](https://github.com/AlexWorx/ALib-Singleton) or
 * [ALib %Boxing](https://github.com/AlexWorx/ALib-Boxing) are missing this method.
 * The good news is, that it is quite easy to create an own debug method, just as the
 * following sample shows:
 *
 *  \snippet "DOX_ALIB_LANG_SINGLETON.cpp"     DOX_ALIB_LANG_SINGLETON_DEBUG_LIST_1
 *  \snippet "DOX_ALIB_LANG_SINGLETON.cpp"     DOX_ALIB_LANG_SINGLETON_DEBUG_LIST_2
 *
 * @tparam TDerivedClass Template parameter that denotes the name of the class that implements
 *                       the singleton.
 *
 **************************************************************************************************/
template <typename TDerivedClass>
class Singleton
{
    protected:
        /**  A pointer to the one and only singleton.   */
        static TDerivedClass*  singleton;

    public:
        /**
         * Creates (if not done, yet) and returns the singleton of type \p TDerivedClass.
         * @return The singleton instance.
         */
        inline static TDerivedClass*    GetSingleton()
        {
            if( !singleton )
            {
                #if ALIB_FEAT_SINGLETON_MAPPED
                    Singleton<TDerivedClass>* castedAsSingleton;
                    if( !getSingleton(typeid(TDerivedClass), &castedAsSingleton ) )
                    {
                        singleton= new TDerivedClass();
                        castedAsSingleton= dynamic_cast<Singleton<TDerivedClass>*>( singleton );

                        storeSingleton( typeid(TDerivedClass), castedAsSingleton );
                    }
                    else
                    {
                        singleton= dynamic_cast<TDerivedClass*>( castedAsSingleton );
                    }
                #else
                    singleton= new TDerivedClass();
                #endif
            }
            return singleton;
        }

        /** Virtual destructor.     */
        virtual  ~Singleton()
        {
            #if ALIB_FEAT_SINGLETON_MAPPED
                removeSingleton( typeid(TDerivedClass) );
            #endif
        }

};// class Singleton

// The static singleton instance initialization
template <typename TDerivedClass>
TDerivedClass* Singleton<TDerivedClass>::singleton= nullptr;


/** ************************************************************************************************
 * Deletes the singletons.
 * Upon exit of the process, programmers might want to explicitly free the hash table to avoid
 * the detection of memory leaks by metrics tools like [Valgrind](http://valgrind.org/).
 * (Otherwise this can be omitted, as the memory is cleaned by the OS probably much faster when a
 * process exits).
 *
 * When using singletons with the full implementation of ALib (in contrast in using just the module
 * <b>ALib %Singleton</b>), then the method
 * \ref aworx::lib::ALIB::TerminationCleanUp "ALIB::TerminationCleanUp" invokes this method
 * already.
 *
 * \note This method is not thread-safe and hence must be called only on termination of the process
 *       when all threads which are using singletons are terminated.
 **************************************************************************************************/
ALIB_API void  DeleteSingletons();

#if ALIB_FEAT_SINGLETON_MAPPED
    #if ALIB_DEBUG
        // forward declaration
        }  namespace debug {

        /** ********************************************************************************************
         * This debug helper function writes all type names and addresses of each instance of class
         * \ref aworx::lib::lang::Singleton "Singleton"
         * currently defined into a vector.
         * It may be used to understand which singleton objects are created within a process at
         * at the point of invocation.
         *
         * \note This method is available only in debug compilations of %ALib and if
         *       code selection symbol \c ALIB_FEAT_SINGLETON_MAPPED is true.
         * <p>
         *
         * \note
         *  If a
         *  \ref aworx::lib "distribution module" of \b %Alib is used that includes
         *  \ref aworx::lib::strings "ALib Strings"
         *  then alternative method
         *  \ref aworx::lib::debug::GetSingletons(strings::AString&) "GetSingletons(strings::AString& target)"
         *  exists, which writes the list into an \b %AString, ready to be "dumped out".
         *
         * @return The list of singleton types with void pointers to the singletons.
         **********************************************************************************************/
        ALIB_API
        std::vector<std::pair<const std::type_info*, void*>>
        GetSingletons();
    #endif // ALIB_DEBUG
#endif // ALIB_FEAT_SINGLETON_MAPPED


}}; // namespace lib::lang

/** Type alias name in namespace #aworx. */
template<typename T>
using Singleton=    aworx::lib::lang::Singleton<T>;

} // namespace aworx



#endif // HPP_ALIB_LANG_SINGLETON
