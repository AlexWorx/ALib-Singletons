// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
#include "alib/alib.hpp"

#if ALIB_DEBUG


#if defined(__GNUC__) || defined(__clang__)

    #include <cxxabi.h>
    #include <cassert>

#else

#endif

namespace aworx { namespace lib {

/**
 * This namespace is available only in debug compilations of \b %ALib (see code selection symbol
 * \ref ALIB_DEBUG).
 * It is used to collect debug facilities from other \b %ALib namespaces.
 */
namespace debug {


// #################################################################################################
// class TypeDemangler
// #################################################################################################
#if defined(__GNUC__) || defined(__clang__)

    TypeDemangler::TypeDemangler( const std::type_info& typeInfo )
    {
        int status;
        name= abi::__cxa_demangle( typeInfo.name(), nullptr, nullptr, &status);
        assert( status==0 );
    }

    TypeDemangler::~TypeDemangler()
    {
        if ( name )
            free(static_cast<void*>( const_cast<char*>(name) ) );
    }

    const char* TypeDemangler::Get()
    {
        return name;
    }

#else

    TypeDemangler::TypeDemangler( const type_info& typeInfo )
    {
        name= typeInfo.name();
        if (strncmp( name, "class ", 6) == 0)
            name+= 6;
    }

    TypeDemangler::~TypeDemangler()
    {
    }

    const char* TypeDemangler::Get()
    {
        return name;
    }
#endif


}}}// namespace [aworx::lib::debug]


#endif

