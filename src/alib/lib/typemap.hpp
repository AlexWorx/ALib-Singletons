// #################################################################################################
//  ALib C++ Library
//
//  Copyright 2013-2019 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################

#ifndef HPP_ALIB_LIB_TYPEMAP
#define HPP_ALIB_LIB_TYPEMAP 1


#if !defined(HPP_ALIB_LIB_PREDEF_COMPILER)
#   include "alib/lib/predef_compiler.hpp"
#endif


#if !defined (_TYPEINFO) && !defined(_TYPEINFO_)
    #include <typeinfo>
#endif

#if !defined(_GLIBCXX_FUNCTIONAL) && !defined(_FUNCTIONAL_)
    #include <functional>
#endif

#if !defined(_GLIBCXX_UNORDERED_MAP) && !defined(_UNORDERED_MAP_)
    #include <unordered_map>
#endif

#if !defined(_GLIBCXX_SET) && !defined(_SET_)
    #include <set>
#endif

#if !defined(_GLIBCXX_TYPEINDEX) && !defined(_TYPEINDEX_)
    #include <typeindex>
#endif



#if ALIB_DOCUMENTATION_PARSER
namespace aworx { namespace lib {


/**
 * This namespace contains sub-namespaces that provide compatibility of 3rd-party types and
 * \alib that are not specific to dedicated \alibmods..<br>
 * The entities of those namespaces become available with the inclusion of optional "compatibility"
 * headers found in folder \b "alib/compatibility".
 */
namespace compatibility {


/**
 * This namespace documents compatibility features of \alib (that are not specific to  one of the
 * \alibmods) and the standard C++ class library found in namespace \c std.
 */
namespace std {
#else
    namespace std {
#endif

/** ************************************************************************************************
 * Specialization of functor <c>std::hash</c> for <c>std::type_info</c> references.
 * Due to the restrictions of <c>std::type_info</c>, instances are wrapped in
 * <c>std::reference_wrapper</c>.
 *
 * This specialization is provided with the inclusion of header file
 * <c>alib/lib/typemap.hpp</c>.<br>
 * While the documentation indicates namespace <c>aworx::lib::compatibility::std</c>, the
 * specialization is (as needed) implemented in namespace <c>std</c>.
 *
 * \see
 *   Type definition \alib{compatibility::std,TypeMap}.
 **************************************************************************************************/
template<> struct hash<std::reference_wrapper<const std::type_info>>
{
    /**
     * Invokes <c>std::type_info::hash_code</c> on the wrapped type.
     * @param typeinfo  The wrapped type information.
     * @return The hash value
     */
    inline
    std::size_t operator()(std::reference_wrapper<const std::type_info> typeinfo) const
    {
        return typeinfo.get().hash_code();
    }
};

/** ************************************************************************************************
 * Specialization of functor <c>std::equal_to</c> for <c>std::type_info</c> references.
 * Due to the restrictions of <c>std::type_info</c>, instances are wrapped in
 * <c>std::reference_wrapper</c>.
 *
 * This specialization is provided with the inclusion of header file
 * <c>alib/lib/typemap.hpp</c>.<br>
 * While the documentation indicates namespace <c>aworx::lib::compatibility::std</c>, the
 * specialization is (as needed) implemented in namespace <c>std</c>.
 *
 * \see
 *   Type definition \alib{compatibility::std,TypeMap}.
 **************************************************************************************************/
template<> struct equal_to<std::reference_wrapper<const std::type_info>>
{
    /**
     * Invokes <c>operator ==</c> with \p{lhs} and \p{rhs}.
     * @param lhs  The left-hand side value.
     * @param rhs  The right-hand side value.
     * @return \c true if the objects represent the same type, \c false otherwise.
     */
     inline
    bool operator()(std::reference_wrapper<const std::type_info> lhs, std::reference_wrapper<const std::type_info> rhs) const
    {
        return lhs.get() == rhs.get();
    }
};

/** ************************************************************************************************
 * Specialization of functor <c>std::less</c> for <c>std::type_info</c> references.
 * Due to the restrictions of <c>std::type_info</c>, instances are wrapped in
 * <c>std::reference_wrapper</c>.
 *
 * This specialization is provided with the inclusion of header file
 * <c>alib/lib/typemap.hpp</c>.<br>
 * While the documentation indicates namespace <c>aworx::lib::compatibility::std</c>, the
 * specialization is (as needed) implemented in namespace <c>std</c>.
 *
 * \see
 *   Type definition \alib{compatibility::std,TypeMap}.
 **************************************************************************************************/
template<> struct less<std::reference_wrapper<const std::type_info>>
{
    /**
     * Invokes <c>operator < </c> on the \c std::type_index of \p{lhs} and \p{rhs}.
     * @param lhs  The left-hand side value.
     * @param rhs  The right-hand side value.
     * @return \c true if the objects represent the same type, \c false otherwise.
     */
     inline
    bool operator()(std::reference_wrapper<const std::type_info> lhs, std::reference_wrapper<const std::type_info> rhs) const
    {
        return    std::type_index( lhs.get() )
                < std::type_index( rhs.get() );
    }
};

#if !ALIB_DOCUMENTATION_PARSER
}  namespace aworx {
#endif

/** ************************************************************************************************
 * Type definition for a <c>std::set</c> that uses key objects of type
 * <c>std::reference_wrapper<const std::type_info></c>.
 *
 * This type definition, as well as the according specializations of functors <c>std::hash</c>
 * and <c>std::equal_to</c>, are provided with the inclusion of header file
 * <c>alib/lib/typemap.hpp</c>.<br>
 * While the documentation indicates namespace <c>aworx::lib::compatibility::std</c>, the true
 * definition is located in namespace <c>aworx</c>.
 **************************************************************************************************/
using TypeSet= std::set<std::reference_wrapper<const std::type_info>>;

/** ************************************************************************************************
 * Templated type definition for a <c>std::unordered_map</c> that uses key objects of type
 * <c>std::reference_wrapper<const std::type_info></c>.
 *
 * This map is used by \alib internally, for example to store pointers to objects to singletons of
 * the provided type.
 *
 * This type definition, as well as the according specializations of functors <c>std::hash</c>
 * and <c>std::equal_to</c>, are provided with the inclusion of header file
 * <c>alib/lib/typemap.hpp</c>.<br>
 * While the documentation indicates namespace <c>aworx::lib::compatibility::std</c>, the true
 * definition is located in namespace <c>aworx</c>.
 *
 * @tparam T    The type of the objects to map.
 **************************************************************************************************/
template<typename T>
using TypeMap= std::unordered_map<std::reference_wrapper<const std::type_info>, T>;

#if ALIB_DOCUMENTATION_PARSER
}}}} // namespace [aworx::lib::compatibility::std]
#else
} // namespace aworx
#endif

#endif // HPP_ALIB_LIB_TYPEMAP
