// #################################################################################################
//  ALib C++ Library
//
//  Module Singletons
//
//  Copyright 2013-2019 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
#ifndef HPP_ALIB_SINGLETONS_SINGLETON
#define HPP_ALIB_SINGLETONS_SINGLETON 1

#if  !defined(HPP_ALIB_SINGLETONS_PREDEF)
#   include "alib/singletons/singletons_predef.hpp"
#endif

#if ALIB_DEBUG && !defined (_GLIBCXX_VECTOR) && !defined(_VECTOR_)
#   include <vector>
#endif


#if ALIB_FEAT_SINGLETON_MAPPED && ALIB_DEBUG  && !defined(HPP_ALIB_LIB_TYPEMAP)
#   include "alib/lib/typemap.hpp"
#endif

namespace aworx { namespace lib { namespace singletons {

// #################################################################################################
// Unordered map utility for storing type_info objects
// #################################################################################################

//! @cond NO_DOX
#if ALIB_FEAT_SINGLETON_MAPPED
extern ALIB_API bool  getSingleton   ( const std::type_info& type, void* theSingleton );
extern ALIB_API void  storeSingleton ( const std::type_info& type, void* theSingleton );
extern ALIB_API void  removeSingleton( const std::type_info& type );
#endif
//! @endcond

/** ************************************************************************************************
 * This class implements the "singleton pattern" for C++ using a common templated approach.
 * In case of Windows OS and DLL usage, the class overcomes the problem of having
 * a global data segment per DLL in addition to the one associated with the process that is using
 * the DLL.
 *
 * All details about implementation and usage of this class is provided in the module's
 * \ref alib_mod_singletons "Programmer's Manual".
 *
 * @tparam TDerivedClass Template parameter that denotes the name of the class that implements
 *                       the singleton.
 **************************************************************************************************/
template <typename TDerivedClass>
class Singleton
{
    protected:
        /** A pointer to the one and only singleton. */
        static TDerivedClass*  singleton;

    public:
        /**
         * Creates (if not done, yet) and returns the singleton of type \p{TDerivedClass}.
         * @return The singleton instance.
         */
        inline static TDerivedClass&    GetSingleton()
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
            return *singleton;
        }

        /** Virtual destructor. */
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
 * When using singletons with the full implementation of \alib (in contrast in using just the
 * module <b>%ALib %Singleton</b>), then method \aworx{lib,Module::TerminationCleanUp} invokes this
 * method already.
 *
 * \note This method is not thread-safe and hence must be called only on termination of the process
 *       when all threads which are using singletons are terminated.
 **************************************************************************************************/
ALIB_API void  DeleteSingletons();

#if ALIB_FEAT_SINGLETON_MAPPED &&  ALIB_DEBUG

    /** ********************************************************************************************
     * This debug helper function returns a type map with void pointers to all singletons.
     *
     * The function may be used to investiage which singleton objects are created within a
     * process and the point in (run-) time of creation.
     *
     * \note
     *   This method is available only in debug compilations of %ALib and if
     *   code selection symbol \ref ALIB_FEAT_SINGLETON_MAPPED evaluates to true.<br>
     *
     * \note
     *   If the \alibdist includes \alibmod_strings then a simple dumping method is available with
     *   \alib{singletons,DbgGetSingletons(NAString&)}.
     *
     * @return The map of singleton types with void pointers to the singletons.
     **********************************************************************************************/
    ALIB_API  TypeMap<void*>    DbgGetSingletons();

#endif // ALIB_FEAT_SINGLETON_MAPPED && ALIB_DEBUG


}} // namespace aworx[::lib::singletons]

/// Type alias in namespace #aworx.
template<typename T>
using Singleton=    aworx::lib::singletons::Singleton<T>;

} // namespace aworx



#endif // HPP_ALIB_SINGLETONS_SINGLETON
