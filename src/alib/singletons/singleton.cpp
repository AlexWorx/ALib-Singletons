// #################################################################################################
//  ALib C++ Library
//
//  Copyright 2013-2019 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
#include "alib/singletons/singleton.hpp"

#if !defined (_GLIBCXX_CSTRING) && !defined(_CSTRING_)
#   include <cstring>
#endif
#if !defined (_GLIBCXX_MUTEX) && !defined(_MUTEX_)
#   include <mutex>
#endif

#if !defined (_GLIBCXX_MUTEX) && !defined(_MUTEX_)
#   include <mutex>
#endif

#if !defined (_ASSERT_H) && !defined(assert)
#   include <assert.h>
#endif

#if ALIB_FEAT_SINGLETON_MAPPED
#   include "alib/lib/typemap.hpp"
#endif

namespace aworx { namespace lib {


/**
 * This is the namespace of \alibmod <b>"Singletons"</b>. Please refer to the
 * \ref alib_mod_singletons "Programmer's Manual Of ALib Singletons" for information about
 * using this (single :-) \b %Singleton class in this tiny namespace.
 */
namespace singletons {

//! @cond NO_DOX

#if ALIB_FEAT_SINGLETON_MAPPED

extern ALIB_API TypeMap<void*>  singletonMap;
       ALIB_API TypeMap<void*>  singletonMap;

extern std::recursive_mutex     singletonLock;
       std::recursive_mutex     singletonLock;

bool getSingleton  ( const std::type_info& type, void* theSingleton )
{
    singletonLock.lock();
    auto entry= singletonMap.find( type );
    if ( entry != singletonMap.end() )
    {
        memcpy( theSingleton, &entry->second, sizeof(void*) );

        singletonLock.unlock();
        return true;
    }

    // we do not unlock when we have not found the singleton
    return false;
}

void  storeSingleton( const std::type_info& type, void* theSingleton )
{
    singletonMap[type]= theSingleton;

    // we unlock now as we were locked in getSingleton
    singletonLock.unlock();
}

void  removeSingleton( const std::type_info& type )
{
    auto it= singletonMap.find(type);
    assert( it != singletonMap.end() ); // Can not remove singleton: Singleton not found
    singletonMap.erase( it );
}

#endif  //ALIB_FEAT_SINGLETON_MAPPED

void DeleteSingletons()
{
    #if ALIB_FEAT_SINGLETON_MAPPED
        while (!singletonMap.empty())
        {
            Singleton<void*>* theSingleton;
            memcpy( &theSingleton, &singletonMap.begin()->second, sizeof(void*) );
            delete theSingleton; // the virtual destructor removes the singleton from the map.
        }
        singletonMap.clear();
    #endif
}

//! @endcond



#if ALIB_FEAT_SINGLETON_MAPPED
    TypeMap<void*> DbgGetSingletons()
    {
        return singletonMap;
    }
#endif

}}} // namespace [aworx::lib::singletons]

