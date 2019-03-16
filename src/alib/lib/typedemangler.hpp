// #################################################################################################
//  ALib C++ Library
//
//  Copyright 2013-2019 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
#ifndef HPP_ALIB_LIB_TYPEDEMANGLER
#define HPP_ALIB_LIB_TYPEDEMANGLER 1


#if !defined(HPP_ALIB_LIB_PREDEF_COMPILER)
#   include "alib/lib/predef_compiler.hpp"
#endif

#if !defined (_TYPEINFO) && !defined(_TYPEINFO_)
    #include <typeinfo>
#endif


#if ALIB_DEBUG

namespace aworx { namespace lib {

/** ********************************************************************************************
 * Retrieves human readable names from C++ run-time type information.<br>
 * This class is available only in debug compilations of \alib.
 **********************************************************************************************/
class DbgTypeDemangler
{
    protected:
        /** The translated name name. */
        const char*  name;

    public:
        /** ************************************************************************************
         * Constructor
         * @param typeInfo The information struct on the C++ type.
         **************************************************************************************/
        ALIB_API
        DbgTypeDemangler( const std::type_info& typeInfo );

        /** ************************************************************************************
         * Destructor
         **************************************************************************************/
        ALIB_API
        ~DbgTypeDemangler();

        /** ************************************************************************************
         * Returns the demangled, human readable name of the type which was provided in the
         * constructor.
         * @return The demangled type name.
         **************************************************************************************/
        ALIB_API
        const char*  Get();
}; // class DbgTypeDemangler


}} // namespace [aworx::lib}

#endif // ALIB_DEBUG

#endif // HPP_ALIB_LIB_TYPEDEMANGLER
