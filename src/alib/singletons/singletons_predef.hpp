// #################################################################################################
//  ALib C++ Library
//
//  Define code selection symbols for ALib features from given compiler symbols.
//
//  Copyright 2013-2019 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
#ifndef HPP_ALIB_SINGLETONS_PREDEF
#define HPP_ALIB_SINGLETONS_PREDEF 1


#if !defined(HPP_ALIB_LIB_PREDEF_COMPILER)
#   include "alib/lib/predef_compiler.hpp"
#endif


// read compiler symbols and create corresponding code selector symbols
#if defined(ALIB_FEAT_SINGLETON_MAPPED)
    #error "Code selector symbol ALIB_FEAT_SINGLETON_MAPPED must not be set from outside. Use postfix '_ON' or '_OFF' for compiler symbols."
#endif

#if defined(ALIB_FEAT_SINGLETON_MAPPED_ON) && defined(ALIB_FEAT_SINGLETON_MAPPED_OFF)
    #error "Compiler symbols ALIB_FEAT_SINGLETON_MAPPED_ON and ALIB_FEAT_SINGLETON_MAPPED_OFF are both set (contradiciton)"
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



#endif // HPP_ALIB_SINGLETONS_PREDEF

