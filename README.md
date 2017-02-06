# Introduction 

This is a small piece of C++ 11 library code implementing the well known **Singleton Design Pattern**. 

With C++ templates, the usually proposed and widely discussed solution is so simple, that it would not justify even this project. Such simple solution looks as follows:

    // template class to provide singleton functionality
    template<typename T> class Singleton
    {
        public: static T* get() 
        { 
          static T thesingleton; 
          return &thesingleton; 
        }
    };
 
    // sample class implementing singleton
    class Sample : public Singleton<Sample>
    {
        // implementation of sample class...
    };

    // usage:
    Sample* sample= Sample::get();
           
This works fine in general unless you start accessing the same singleton objects from within different Windows DLLs or a Windows DLL and the main executable. Although running in one process, the singletons retrieved are singletons "per DLL/Executable". The reason for this is simply spoken that Windows DLLs dispose of an own data segment for global variables. This is different with shared libraries under GNU/Linux or macOS, which are designed to behave exactly as statically linked libraries. 

#The Solution

The code provided with this repository creates true singleton objects, even when Windows OS DLLs are used. This is achieved by creating a static hash map (only once) and collecting all singletons herein. The C++ runtime type information struct **std::type_info** is used as the key to the singletons in the hash map.

As a side effect, the singletons created can be "dumped out" for debug purposes by iterating the hash table. A corresponding debug method is provided with this implmementation.

As this approach imposes some overhead in respect to code size and speed, an alternative implementation that omits the use the hash map is provided. The code selects the "right" implementation depending on the platform it is compiled on. In addition, the implementation is switchable using compiler symbol definitions.  

#Restrictions / Penalties

- The singleton class needs to have a default (parameterless) constructor. (This might be overcome with a simple extension of the class, but is not implemented here) 
- The singleton class is virtual and hence all derived classes become virtual. This is needed to be able to have a virtual destructor.   
- There is a marginal performance penalty in comparison to more simple implementations of the singleton design pattern: Each *'code entity'* (DLL or main executable) needs to retrieve a singleton, which was potentially already created by another code entity, **once**. In other words, the first request for a specific singleton incorporates two small performance penalties for 
  1. setting and releasing a thread lock (mutex)
  2. retrieving the singleton or inserting the singleton if not retrieved.
- The memory penalty is also quite minimal and imposed by the creation of a static hash table, which holds a pointer to each Singleton.
- Upon exit of the process, programmers might want to explicitly free the hash table to avoid the detection of memory leaks by metrics tools like [Valgrind](http://valgrind.org/). (Otherwise this can be omitted, as the memory is cleaned by the OS probably much faster when a process exits).
- In general, it is advised to think twice before implementing the singleton design pattern. Often, this is considered bad code design. However, there can be very good reasons for having singletons in software.
  And do not be frustrated if "very wise people" tell you that you must never use a singleton. Your answer to them is: Each and every created instance of a virtual C++ class contains a pointer to a singleton, namely the [vtable](https://en.wikipedia.org/wiki/Virtual_method_table)!


#Documentation
This code is an extraction from some bigger library (see below). For the documentation of class Singleton use this 
[deep link](http://alexworx.github.io/ALox-Logging-Library/cpp_ref/classaworx_1_1lib_1_1lang_1_1Singleton.html) into ALib documentation.

#Requirements and Usage

**Requirements to use the code are:**

* C++ compilers supporting C++11 language level. Compilers tested are
  - GNU C++ V. 6.3 
  - Clang V. 3.9 
  - Microsoft Visual Studio 2015
* The code was tested under
  - GNU/Linux 32 and 64 bit
  - Microsoft Windows 32 and 64 bit
  - Mac OSX 64 bit
* The code compiles without warnings on maximum warning levels.   

**Usage options:**

1. Copy the code into your project, make changes as you wish (rename class adopt your own namespace, improve, etc.).
2. Compile the code to a library and add it to your project.
3. Use this feature together with other 
  [ALib for C++ Modules](http://alexworx.github.io/ALox-Logging-Library/cpp_ref/namespaceaworx_1_1lib.html)
  (Needs download from other repositories, see below).  
4. Use together with [ALox Logging Library](http://alexworx.github.io/ALox-Logging-Library/index.html), which is built upon ALib and has quite some unique features for debug and release logging. (Note: Of-course, all underlying **ALib** features, including the one described here, are exposed to users of **ALox**.) 
     

# ALib Main Distribution 
The code found in this repository represents a so called *"ALib Module"*, which means it is an extracted subset of [ALib for C++](http://alexworx.github.io/ALox-Logging-Library/cpp_ref/namespaceaworx_1_1lib.html). 
The effort to extract this module and make its sources available as a "stand alone" project is made to allow full source inclusion in a users project. This way, compilation and deployment dependencies get eliminated. Also, updates are not automatically deployed into a users project source tree, what protects from possible unwanted effects of such updates. Finally, a user might modify the sources and maintain a separate version, with no future update from the original.     

Other extracted *ALib Modules* available are:

- [ALib for C++ Boxing](https://github.com/AlexWorx/ALib-Boxing)  
- [ALib for C++ Strings](https://github.com/AlexWorx/ALib-Strings)
- [ALib for C++ BoxingAndStrings](https://github.com/AlexWorx/ALib-Boxing-And-Strings)
- [ALib for C++ Configuration](https://github.com/AlexWorx/ALib-Configuration)

Note: Of-course, the aforementioned reasons for extracting **ALib Modules** are considered disadvantages in many scenarios. The choice is yours.... 

The complete library [ALib for C++](http://alexworx.github.io/ALox-Logging-Library/cpp_ref/namespaceaworx_1_1lib.html), including available language variants [ALib for C#](http://alexworx.github.io/ALox-Logging-Library/cs_ref/namespacecs_1_1aworx_1_1lib.html) and [ALib for Java](http://alexworx.github.io/ALox-Logging-Library/java_ref/namespacecom_1_1aworx_1_1lib.html), is published as a *bundled package* together with [ALox Logging Library](http://alexworx.github.io/ALox-Logging-Library/index.html). **ALox** provides rich documentation including a detailed [Change Log](http://alexworx.github.io/ALox-Logging-Library/changelog.html) which separately lists the changes of underlying **ALib**, hence also the changes for this *ALib Module*. This module is updated with every update of **ALib/ALox** 
 
The software is duly tested with Unit Tests. However, those are not part of this distribution.

#Alternatives
The following alternatives may be worth mentioning:

- Probably the class code given as a sample above: This works well on GNU/Linux (even with shared libraries) and also with monolithic Windows OS executables. 
- Many code sample repositories, programming books, design pattern collections etc. are offering implementations of the Singleton Design Pattern. But be careful: most of these solutions do not work with windows DLLs!
- Create an abstract virtual singleton "interface" class and implement its virtual abstract method in each class you want to equip with a singleton. Return a private static instance of itself which you add as a member. 
  - Advantage: No need for having a hash map
  - Disadvantage: No templated approach. In ALib, we are using the Singleton nested in another template class. Therefore, this was no option for us. It would impose the need to manually add static specialized template objects to be feed to the linker with each new template specialization.
- [Loki](https://sourceforge.net/projects/loki-lib/)  Design Pattern Library (It seems to be DLL-safe, but we have not tested that.)








