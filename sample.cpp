// #################################################################################################
//  ALib - A-Worx Utility Library
//  Singleton Sample
//
//  Copyright 2017 A-Worx GmbH, Germany
//  Published under Boost Software License (a free software license, see LICENSE.txt)
// #################################################################################################
#include "alib/alib.hpp"

#include <iostream>


// Derive a class from singleton, providing its name as template parameter:
class MyClass : public aworx::Singleton<MyClass>
{
    //... MyClass implementation
};

// Sample for a strict singleton: only one instance may exist
class JustOne : public aworx::Singleton<JustOne>
{
    friend aworx::Singleton<JustOne>;
    private: JustOne() {}

    //... class JustOne implementation
};


#if ALIB_DEBUG && ALIB_FEAT_SINGLETON_MAPPED

// import the map of singletons. This is not done in the header files by purpose!
namespace aworx { namespace lib { namespace lang {
    extern ALIB_API TypeMap<void*>  singletonMap;
}}}


// A simple debug dump function
void  DumpSingletons()
{
    std::cout << "Debug-Mode: Dumping Singletons: " << std::endl;

    for( auto it : aworx::lib::lang::singletonMap )
        std::cout << "  "
             << aworx::lib::debug::TypeDemangler(it.first.get()).Get()
             << " = 0x" << std::hex
             << reinterpret_cast<uint64_t>(it.second)
             << std::endl;
}
#endif

int main()
{

    MyClass* myClassSingleton= MyClass::GetSingleton();
    std::cout << "The singleton of MyClass is: " << std::hex  << myClassSingleton << std::endl;

    // It is still allowed to create other instances of MyClass (non-strict implementation)
    // but this will not appear in the singleton list below and is not considered a singleton.
    MyClass instance2;
    std::cout << "Another instance of MyClass is: " << std::hex  << &instance2     << std::endl;

    JustOne *theOne= JustOne::GetSingleton();
    // We can't create a second one, constructor is private


    // The dump function is only available if symbol ALIB_FEAT_SINGLETON_MAPPED is true.
    // On GNU/Linux and mac this defaults to false. (On Windows OS to true.)
    // The sample's cmake file however overwrites the default value for demonstration purpose!
    #if ALIB_DEBUG && ALIB_FEAT_SINGLETON_MAPPED
        DumpSingletons();
    #endif


    return 0;
}
