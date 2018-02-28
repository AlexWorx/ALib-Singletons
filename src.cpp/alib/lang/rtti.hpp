// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Essential ALib types needed by every module
//
//  Copyright 2013-2018 A-Worx GmbH, Germany
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

namespace aworx { namespace lib { namespace lang {


// #################################################################################################
// Unordered map utility for storing type_info objects
// #################################################################################################

namespace detail {

/**
 * Alias for <c>std::reference_wrapper\<const std::type_info\></c>.
 */
using WrappedTypeInfo= std::reference_wrapper<const std::type_info>;

/**
 * Provides hash function for <c>std::type_info</c> references wrapped in
 * <c>std::reference_wrapper</c>.
 */
struct WrappedTypeInfoHasher
{
    /**
     * Invokes <c>std::type_info::hash_code</c> on the wrapped type.
     * @param typeinfo  The wrapped type information.
     * @return The hash value
     */
    std::size_t operator()(WrappedTypeInfo typeinfo) const
    {
        return typeinfo.get().hash_code();
    }
};

/**
 * <c>std::equal_to</c> predicate for <c>std::type_info</c> references wrapped in
 * <c>std::reference_wrapper</c>.
 */
struct WrappedTypeInfoPredEqualTo
{
    /**
     * Invokes <c>operator ==</c> with \p lhs and \p rhs.
     * @param lhs  The left-hand side value.
     * @param rhs  The right-hand side value.
     * @return \c true if the objects represent the same type, \c false otherwise.
     */
    bool operator()(WrappedTypeInfo lhs, WrappedTypeInfo rhs) const
    {
        return lhs.get() == rhs.get();
    }
};

} //namespace aworx::lib::lang[::detail]


#if ALIB_DEBUG
        } // aworx::lib[::lang]
        namespace debug {

    /** ********************************************************************************************
     * Retrieves human readable names from C++ runtime type information.<br>
     * This class is available only in debug compilations of \b %ALib.
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

}}; // namespace aworx[::lib::lang] (respectively aworx[::lib::debug])


/** ************************************************************************************************
 * Templated type definition for a <c>std::unordered_map</c> that uses key objects of type
 * \alib{lang,detail,WrappedTypeInfo}.<br>
 * This is used by \b %ALib internally to store pointers to objects to singletons of the
 * provided type.
 * @tparam T    The type of the objects to map.
 **************************************************************************************************/
template<typename T>
using TypeMap= std::unordered_map< lib::lang::detail::WrappedTypeInfo,
                                   T,
                                   lib::lang::detail::WrappedTypeInfoHasher,
                                   lib::lang::detail::WrappedTypeInfoPredEqualTo>;

} // namespace aworx
#endif // HPP_ALIB_LANG_RTTI
