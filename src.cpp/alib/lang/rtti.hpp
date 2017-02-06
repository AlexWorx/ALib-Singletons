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
#if !defined(ALIB_PROPER_INCLUSION) || defined(HPP_ALIB_LANG_RTTI)
    #error "include alib/alib.hpp instead of this header"
#endif

#ifndef HPP_ALIB_LANG_RTTI
#define HPP_ALIB_LANG_RTTI 1


#if !defined (_TYPEINFO) && !defined(_TYPEINFO_)
    #include <typeinfo>
#endif

#if !defined(_GLIBCXX_FUNCTIONAL) && !defined(_FUNCTIONAL_)
    #include <functional>
#endif

#if !defined(_GLIBCXX_UNORDERED_MAP) && !defined(_UNORDERED_MAP_)
    #include <unordered_map>
#endif

namespace aworx { namespace lib { namespace lang
{


// #################################################################################################
// Unordered map utility for storing type_info objects
// #################################################################################################

//! @cond NO_DOX
struct RTTIMap_Hasher
{
    std::size_t operator()(std::reference_wrapper<const std::type_info> code) const
    {
        return code.get().hash_code();
    }
};

struct RTTIMap_EqualTo
{
    bool operator()(std::reference_wrapper<const std::type_info> lhs,
                    std::reference_wrapper<const std::type_info> rhs) const
    {
        return lhs.get() == rhs.get();
    }
};
//! @endcond NO_DOX

/** ************************************************************************************************
 * Templated type definition for a hash map that stores objects of type \p TMapped with the
 * key being a C++ \b type_info reference object.<br>
 * This is mostly used by ALib internally to store pointers to objects to singletons of the
 * provided type.
 **************************************************************************************************/
template<typename TMapped>
using TypeinfoMap= std::unordered_map< std::reference_wrapper<const std::type_info>,
                                   TMapped,
                                   RTTIMap_Hasher,
                                   RTTIMap_EqualTo>;


#if ALIB_DEBUG
        } // aworx::lib[::lang]
        namespace debug {

    /** ********************************************************************************************
     * Retrieves human readable names from C++ runtime type information.<br>
     * This class is available only in debug compilations of ALib.
     **********************************************************************************************/
    class TypeDemangler
    {
        protected:
            /** The translated name name */
            const char* name;


        public:
            /** ************************************************************************************
             * Constructor
             * @param typeInfo The information struct on the C++ type.
             **************************************************************************************/
            ALIB_API
            TypeDemangler( const std::type_info& typeInfo );

            /** ************************************************************************************
             * Destructor
             **************************************************************************************/
            ALIB_API
            ~TypeDemangler();

            /** ************************************************************************************
             * Returns the demangled, human readable name of the type which was provided in the
             * constructor.
             * @return The demangled type name.
             **************************************************************************************/
            ALIB_API
            const char* Get();
    }; // class TypeDemangler

#endif // ALIB_DEBUG


}}; // // namespace aworx[::lib::lang] (respectively aworx[::lib::debug])


} // namespace aworx
#endif // HPP_ALIB_LANG_RTTI
