// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2018 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
#include "alib/alib.hpp"

#if !defined (_GLIBCXX_CSTRING) && !defined(_CSTRING_)
    #include <cstring>
#endif
#if !defined (_GLIBCXX_MUTEX) && !defined(_MUTEX_)
    #include <mutex>
#endif

namespace aworx { namespace lib { namespace lang {

//! @cond NO_DOX

#if ALIB_FEAT_SINGLETON_MAPPED
    extern ALIB_API TypeMap<void*>  singletonMap; // not declared in a header, avoid clang (strict) warning
           ALIB_API TypeMap<void*>  singletonMap;


    #if ALIB_FEAT_THREADS
    extern std::recursive_mutex      singletonLock; // not declared in a header, avoid clang (strict) warning
           std::recursive_mutex      singletonLock;
    #endif

    bool getSingleton  ( const std::type_info& type, void* theSingleton )
    {
        #if ALIB_FEAT_THREADS
        singletonLock.lock();
        #endif
        auto entry= singletonMap.find( type );
        if ( entry != singletonMap.end() )
        {
            memcpy( theSingleton, &entry->second, sizeof(void*) );

            #if ALIB_FEAT_THREADS
            singletonLock.unlock();
            #endif
            return true;
        }

        // we do not unlock when we have not found the singleton
        return false;
    }

    void  storeSingleton( const std::type_info& type, void* theSingleton )
    {
        singletonMap[type]= theSingleton;

        // we unlock now as we were locked in getProcessSingleton
        #if ALIB_FEAT_THREADS
        singletonLock.unlock();
        #endif
    }

    void  removeSingleton( const std::type_info& type )
    {
        auto it= singletonMap.find(type);
        #if defined(ALIB_ASSERT_ERROR)
            ALIB_ASSERT_ERROR( it != singletonMap.end(), "Can not remove singleton: Singleton not found" )
        #endif
        singletonMap.erase( it );
    }
#endif

void DeleteSingletons()
{
    #if ALIB_FEAT_SINGLETON_MAPPED
        for ( auto& entry : singletonMap)
        {
            Singleton<void*>* theSingleton;
            memcpy( &theSingleton, &entry.second, sizeof(void*) );
            delete theSingleton;
        }
        singletonMap.clear();
    #endif
}

// #################################################################################################
// Debug method
// #################################################################################################
#if ALIB_FEAT_SINGLETON_MAPPED
    #if ALIB_DEBUG
        } // aworx::lib[::lang]
        namespace debug {

        std::vector<std::pair<const std::type_info*, void*>>  GetSingletons()
        {
            std::vector<std::pair<const std::type_info*, void*>> result;
            for( auto& it : lang::singletonMap )
                result.emplace_back( &it.first.get(), it.second);

            return result;
        }
    #endif
#endif

//! @endcond

}}}// namespace [aworx::lib::lang]

